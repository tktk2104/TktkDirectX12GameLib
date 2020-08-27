#include "TktkDX12Game/DXGameResource/Sound/SoundData.h"

#include <stdexcept>
#include "TktkDX12Game/DXGameResource/Sound/SoundPlayState.h"

#define BUFFERQUEUE_MAX         4
#define BUFFERQUEUE_ALLOC       (BUFFERQUEUE_MAX + 1)

namespace tktk
{
	SoundData::SoundData(const std::string & fileName, IXAudio2* xAudioPtr, HANDLE hEvent)
		: m_cSoundCallback(CSoundCallback(hEvent))
	{
		loadSound(fileName);

		HRESULT hr = xAudioPtr->CreateSourceVoice(
			&m_lpSourceVoice, &m_wfx, XAUDIO2_VOICE_NOPITCH, XAUDIO2_DEFAULT_FREQ_RATIO, &m_cSoundCallback, NULL, NULL
		);

		if (FAILED(hr))
		{
			throw std::runtime_error("create sourceVoice error");
		}
	}

	SoundData::~SoundData()
	{
		stopSound();
		update();

		if (m_lpSourceVoice != nullptr)
			m_lpSourceVoice->DestroyVoice();

		if (m_hmmio != nullptr)
			mmioClose(m_hmmio, 0);
	}

	SoundData::SoundData(SoundData&& other) noexcept
		: m_hmmio(other.m_hmmio)
		, m_mmioInfo(other.m_mmioInfo)
		, m_riffChunkInfo(other.m_riffChunkInfo)
		, m_formatChunkInfo(other.m_formatChunkInfo)
		, m_dataChunkInfo(other.m_dataChunkInfo)
		, m_wfx(other.m_wfx)
		, m_pcmwf(other.m_pcmwf)
		, m_cSoundCallback(other.m_cSoundCallback)
		, m_lpSourceVoice(other.m_lpSourceVoice)
		, m_bufinfo(other.m_bufinfo)
		, m_voiceState(other.m_voiceState)
		, m_buflen(other.m_buflen)
		, m_bufData(std::move(other.m_bufData))
		, m_bufLoadPos(other.m_bufLoadPos)
		, m_readlen(other.m_readlen)
		, m_soundPlayState(other.m_soundPlayState)
		, m_soundCount(other.m_soundCount)
		, m_sumReadlen(other.m_sumReadlen)
	{
		m_lpSourceVoice = nullptr;
		m_hmmio = nullptr;
	}

	bool SoundData::isPlaySound() const
	{
 		return ((m_soundPlayState & SOUND_PLAY_STATE_PLAYING) != 0) && ((m_soundPlayState & SOUND_PLAY_STATE_PAUSE) == 0);
	}

	void SoundData::playSound(bool loopPlay)
	{
		if (loopPlay)
		{
			m_soundPlayState |= SOUND_PLAY_STATE_LOOP;
		}

		if ((m_soundPlayState & SOUND_PLAY_STATE_PAUSE) == 0)
		{
			initSound();
		}

		HRESULT hr = m_lpSourceVoice->Start(0, XAUDIO2_COMMIT_NOW);
		if (FAILED(hr))
		{
			throw std::runtime_error("play sound error");
		}

		m_soundPlayState &= (~SOUND_PLAY_STATE_PAUSE);
		m_soundPlayState |= SOUND_PLAY_STATE_PLAYING;
	}

	void SoundData::stopSound()
	{
		m_lpSourceVoice->FlushSourceBuffers();

		mmioSeek(m_hmmio, -static_cast<long>(m_sumReadlen), SEEK_CUR);

		m_soundPlayState &= (~SOUND_PLAY_STATE_PLAYING);
		m_soundPlayState &= (~SOUND_PLAY_STATE_PAUSE);
		m_soundPlayState &= (~SOUND_PLAY_STATE_LOOP);
	}

	void SoundData::pauseSound()
	{
		m_lpSourceVoice->Stop();

		m_soundPlayState |= SOUND_PLAY_STATE_PAUSE;
	}

	void SoundData::update()
	{
		m_lpSourceVoice->GetState(&m_voiceState);

		if (m_voiceState.BuffersQueued == 0)
		{
			if ((m_soundPlayState & SOUND_PLAY_STATE_LOOP) != 0)
			{
				stopSound();
				playSound(true);

				return;
			}

			stopSound();
			return;
		}

		// loading
		while (m_voiceState.BuffersQueued < BUFFERQUEUE_MAX && m_hmmio != NULL)
		{
			m_bufLoadPos = m_bufData.data() + m_buflen * m_soundCount;
			m_soundCount = (m_soundCount + 1) % BUFFERQUEUE_ALLOC;
			m_readlen = mmioRead(m_hmmio, (HPSTR)m_bufLoadPos, m_buflen);

			if (m_readlen <= 0) break;

			m_sumReadlen += m_readlen;

			m_bufinfo.Flags = ((UINT32)m_readlen >= m_buflen) ? 0 : XAUDIO2_END_OF_STREAM;
			m_bufinfo.AudioBytes = m_readlen;
			m_bufinfo.pAudioData = m_bufLoadPos;
			m_bufinfo.PlayBegin = 0;
			m_bufinfo.PlayLength = m_readlen / m_wfx.nBlockAlign;
			m_lpSourceVoice->SubmitSourceBuffer(&m_bufinfo, NULL);

			m_voiceState.BuffersQueued++;
		}
	}

	void SoundData::loadSound(const std::string & fileName)
	{
		const TCHAR *lpFileName = TEXT(fileName.c_str());

		// エラー検知用変数
		MMRESULT mmret;

		memset(&m_mmioInfo, 0x00, sizeof(m_mmioInfo));
		m_hmmio = mmioOpen(const_cast<TCHAR *>(lpFileName), &m_mmioInfo, MMIO_READ);
		if (m_hmmio == NULL)
		{
			throw std::runtime_error("load sound error");
		}

		memset(&m_riffChunkInfo, 0x00, sizeof(m_riffChunkInfo));
		m_riffChunkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmret = mmioDescend(m_hmmio, &m_riffChunkInfo, NULL, MMIO_FINDRIFF);
		if (mmret != MMSYSERR_NOERROR)
		{
			throw std::runtime_error("load sound error");
		}

		memset(&m_formatChunkInfo, 0x00, sizeof(m_formatChunkInfo));
		m_formatChunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmret = mmioDescend(m_hmmio, &m_formatChunkInfo, &m_riffChunkInfo, MMIO_FINDCHUNK);
		if (mmret != MMSYSERR_NOERROR)
		{
			throw std::runtime_error("load sound error");
		}

		if (m_formatChunkInfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(m_hmmio, (HPSTR)&m_wfx, sizeof(m_wfx));
		}
		else
		{
			mmioRead(m_hmmio, (HPSTR)&m_pcmwf, sizeof(m_pcmwf));
			memset(&m_wfx, 0x00, sizeof(m_wfx));
			memcpy(&m_wfx, &m_pcmwf, sizeof(m_pcmwf));
			m_wfx.cbSize = 0;
		}
		
		mmioAscend(m_hmmio, &m_formatChunkInfo, 0);

		memset(&m_dataChunkInfo, 0x00, sizeof(m_dataChunkInfo));
		m_dataChunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmret = mmioDescend(m_hmmio, &m_dataChunkInfo, &m_riffChunkInfo, MMIO_FINDCHUNK);
		if (mmret != MMSYSERR_NOERROR)
		{
			throw std::runtime_error("load sound error");
		}
	}

	void SoundData::initSound()
	{
		m_buflen = m_wfx.nAvgBytesPerSec / 4;
		m_bufData.resize(m_buflen * BUFFERQUEUE_ALLOC);
		m_bufLoadPos = m_bufData.data();

		m_readlen = mmioRead(m_hmmio, (HPSTR)m_bufLoadPos, m_buflen);
		if (m_readlen <= 0)
		{
			throw std::runtime_error("load sound buffer error");
		}

		m_soundCount = 1u;
		m_sumReadlen = m_readlen;

		memset(&m_bufinfo, 0x00, sizeof(m_bufinfo));
		m_bufinfo.Flags = ((UINT32)m_readlen >= m_buflen) ? 0 : XAUDIO2_END_OF_STREAM;
		m_bufinfo.AudioBytes = m_readlen;
		m_bufinfo.pAudioData = m_bufLoadPos;
		m_bufinfo.PlayBegin = 0;
		m_bufinfo.PlayLength = m_readlen / m_wfx.nBlockAlign;

		HRESULT hr = m_lpSourceVoice->SubmitSourceBuffer(&m_bufinfo, NULL);
		if (FAILED(hr))
		{
			throw std::runtime_error("create submit source buffer error");
		}
	}
}