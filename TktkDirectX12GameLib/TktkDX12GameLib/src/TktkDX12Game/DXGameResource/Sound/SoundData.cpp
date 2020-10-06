#include "TktkDX12Game/DXGameResource/Sound/SoundData.h"

#include <stdexcept>
#include "TktkDX12Game/DXGameResource/Sound/SoundPlayState.h"

namespace tktk
{
	// �T�E���h�o�b�t�@�̍ő吔
	constexpr unsigned int BufferQueueMax = 4U;

	// ���ۂɍ��T�E���h�o�b�t�@�̐�
	constexpr unsigned int BufferQueueAlloc = BufferQueueMax + 1U;

	SoundData::SoundData(const std::string & fileName, IXAudio2* xAudioPtr, HANDLE hEvent)
		: m_cSoundCallback(CSoundCallback(hEvent))
	{
		loadSound(fileName);

		HRESULT hr = xAudioPtr->CreateSourceVoice(
			&m_lpSourceVoice, &m_wfx, XAUDIO2_VOICE_NOPITCH, XAUDIO2_DEFAULT_FREQ_RATIO, &m_cSoundCallback, NULL, NULL
		);

		if (FAILED(hr)) throw std::runtime_error("create sourceVoice error");
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
		, m_wfx(other.m_wfx)
		, m_pcmwf(other.m_pcmwf)
		, m_cSoundCallback(other.m_cSoundCallback)
		, m_lpSourceVoice(other.m_lpSourceVoice)
		, m_buflen(other.m_buflen)
		, m_bufData(std::move(other.m_bufData))
		, m_soundPlayState(other.m_soundPlayState)
		, m_soundCount(other.m_soundCount)
		, m_sumReadlen(other.m_sumReadlen)
	{
		m_lpSourceVoice = nullptr;
		m_hmmio			= nullptr;
	}

	bool SoundData::isPlaySound() const
	{
 		return ((m_soundPlayState & SoundPlayState::Playing) != 0) && ((m_soundPlayState & SoundPlayState::Pause) == 0);
	}

	void SoundData::playSound(bool loopPlay)
	{
		// ���[�v�Đ����s���ꍇ�̓��[�v�t���O�𗧂Ă�
		if (loopPlay) m_soundPlayState |= SoundPlayState::Loop;

		// �T�E���h�����ɍĐ������������U��~����
		if ((m_soundPlayState & SoundPlayState::Playing) != 0) stopSound();

		// �|�[�Y���t���O�������Ă��Ȃ���΃T�E���h�̍Đ��󋵂�����������
		if ((m_soundPlayState & SoundPlayState::Pause) == 0) initSound();

		// �T�E���h�̍Đ����J�n����
		HRESULT hr = m_lpSourceVoice->Start(0, XAUDIO2_COMMIT_NOW);

		// �Đ��G���[�`�F�b�N
		if (FAILED(hr)) throw std::runtime_error("play sound error");

		// �|�[�Y���t���O��܂�
		m_soundPlayState &= (~SoundPlayState::Pause);

		// �Đ����t���O�𗧂Ă�
		m_soundPlayState |= SoundPlayState::Playing;
	}

	void SoundData::stopSound()
	{
		// �\�[�X�o�b�t�@���t���b�V������
		m_lpSourceVoice->FlushSourceBuffers();

		// �T�E���h�t�@�C���̓ǂݍ��݈ʒu�𓪂ɖ߂�
		mmioSeek(m_hmmio, -static_cast<long>(m_sumReadlen), SEEK_CUR);

		// �T�E���h�Đ��t���O������������
		m_soundPlayState = 0U;
	}

	void SoundData::pauseSound()
	{
		// �T�E���h���~����
		m_lpSourceVoice->Stop();

		// �|�[�Y���t���O�𗧂Ă�
		m_soundPlayState |= SoundPlayState::Pause;
	}

	void SoundData::update()
	{
		// ���݂̃T�E���h�̏�Ԃ��擾����
		XAUDIO2_VOICE_STATE voiceState;
		m_lpSourceVoice->GetState(&voiceState);

		// ���ݓǂݍ���ł���T�E���h�o�b�t�@���O�������牺�̏������X�L�b�v����
		if (voiceState.BuffersQueued == 0) return;

		// �T�E���h�o�b�t�@��ǂݍ��ޗ]�T����������ǂݍ���
		while (voiceState.BuffersQueued < BufferQueueMax && m_hmmio != nullptr)
		{
			// �T�E���h�o�b�t�@�ǂݍ��݈ʒu���X�V����
			unsigned char* bufLoadTopPtr = m_bufData.data() + m_buflen * m_soundCount;

			// �T�E���h�J�E���^�[���X�V����
			m_soundCount = (m_soundCount + 1) % BufferQueueAlloc;

			// �T�E���h�o�b�t�@���X�V���A�X�V�����o�b�t�@�T�C�Y���擾����
			auto readlen = mmioRead(m_hmmio, reinterpret_cast<HPSTR>(bufLoadTopPtr), m_buflen);

			// �X�V�����o�b�t�@�T�C�Y���O�ȉ���������
			if (readlen <= 0)
			{
				// ��~����O�̃T�E���h�Đ���Ԃ�ێ�����
				auto preSoundPlayState = m_soundPlayState;

				// �T�E���h���~����
				stopSound();

				// ���[�v�t���O�������Ă�����ēx�Đ�����
				if ((preSoundPlayState & SoundPlayState::Loop) != 0) playSound(true);

				// �ǂݍ��݃��[�v�𔲂���
				break;
			}
			
			// ���܂œǂݍ��񂾃T�E���h�o�b�t�@�̒������X�V����
			m_sumReadlen += readlen;

			// �\�[�X�{�C�X�Ƀf�[�^��]������ׂ̃p�����[�^
			XAUDIO2_BUFFER bufinfo;
			memset(&bufinfo, 0x00, sizeof(XAUDIO2_BUFFER));

			// �X�V�����o�b�t�@�̒������z������Z���i�ǂݍ��ރo�b�t�@�������Ȃ��j�̂ł���΁uXAUDIO2_END_OF_STREAM�v�t���O�𗧂Ă�
			bufinfo.Flags		= (static_cast<unsigned int>(readlen) >= m_buflen) ? 0 : XAUDIO2_END_OF_STREAM;
			// �]������o�b�t�@�̒���
			bufinfo.AudioBytes	= readlen;
			// �]������o�b�t�@�̓ǂݍ��݊J�n�ʒu
			bufinfo.pAudioData	= bufLoadTopPtr;
			// �]�������o�b�t�@�̂ǂ�����Đ����邩�H�i�������œ]������֌W���ɂO�j
			bufinfo.PlayBegin	= 0;
			// �]�������o�b�t�@�̑��Đ���
			bufinfo.PlayLength	= readlen / m_wfx.nBlockAlign;

			// �\�[�X�{�C�X�Ƀf�[�^��]������
			HRESULT hr = m_lpSourceVoice->SubmitSourceBuffer(&bufinfo, nullptr);

			// �\�[�X�{�C�X�ւ̃f�[�^�]���G���[�`�F�b�N
			if (FAILED(hr)) throw std::runtime_error("submit source buffer error");

			// �o�b�t�@�L���[���C���N�������g
			voiceState.BuffersQueued++;
		}
	}

	void SoundData::loadSound(const std::string & fileName)
	{
#ifdef _M_AMD64 /* x64�r���h�Ȃ� */

		std::wstring wstrFileName = std::wstring(fileName.begin(), fileName.end());
		const TCHAR* lpFileName = wstrFileName.c_str();
#else
		const TCHAR* lpFileName = TEXT(fileName.c_str());
#endif // _M_AMD64

		// ���t�\���t�@�C����ǂݍ��ގ��Ɏg�p����MMIO���f�[�^�\��
		MMIOINFO	mmioInfo;
		// ���t�\���t�@�C����ǂݍ��ގ��Ɏg�p����RIFF�`�����N���f�[�^�\���iwav�`�����N�p�j
		MMCKINFO	riffChunkInfo;
		// ���t�\���t�@�C����ǂݍ��ގ��Ɏg�p����RIFF�`�����N���f�[�^�\���i�t�H�[�}�b�g�`�����N�p�j
		MMCKINFO	formatChunkInfo;
		// ���t�\���t�@�C����ǂݍ��ގ��Ɏg�p����RIFF�`�����N���f�[�^�\���i�f�[�^�`�����N�p�j
		MMCKINFO	dataChunkInfo;

		// �G���[���m�p�ϐ�
		MMRESULT	mmret;

		// MMIO�f�[�^�\�������[���N���A
		memset(&mmioInfo, 0x00, sizeof(MMIOINFO));

		// MMIO�f�[�^�\������ǂݍ���
		m_hmmio = mmioOpen(const_cast<TCHAR *>(lpFileName), &mmioInfo, MMIO_READ);

		// �ǂݍ��݃G���[�`�F�b�N
		if (m_hmmio == NULL) throw std::runtime_error("load sound error");

		// RIFF�`����WAVE�`�����N�\�������[���N���A
		memset(&riffChunkInfo, 0x00, sizeof(MMCKINFO));

		// WAVE�`�����N�Ɉړ����邽�߂̏���ݒ�
		riffChunkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');

		// WAVE�`�����N�Ɉړ�
		mmret = mmioDescend(m_hmmio, &riffChunkInfo, NULL, MMIO_FINDRIFF);

		// �`�����N�ړ��G���[�`�F�b�N
		if (mmret != MMSYSERR_NOERROR) throw std::runtime_error("load sound error");

		// RIFF�`���̃t�H�[�}�b�g�`�����N�\�������[���N���A
		memset(&formatChunkInfo, 0x00, sizeof(MMCKINFO));

		// �t�H�[�}�b�g�`�����N�Ɉړ����邽�߂̏���ݒ�
		formatChunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');

		// WAVE�`�����N����t�H�[�}�b�g�`�����N�Ɉړ�
		mmret = mmioDescend(m_hmmio, &formatChunkInfo, &riffChunkInfo, MMIO_FINDCHUNK);

		// �`�����N�ړ��G���[�`�F�b�N
		if (mmret != MMSYSERR_NOERROR) throw std::runtime_error("load sound error");

		// TODO : �����̏����̈Ӗ��𗝉�����
		if (formatChunkInfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(m_hmmio, (HPSTR)&m_wfx, sizeof(WAVEFORMATEX));
		}
		else
		{
			mmioRead(m_hmmio, (HPSTR)&m_pcmwf, sizeof(PCMWAVEFORMAT));
			memset(&m_wfx, 0x00, sizeof(WAVEFORMATEX));
			memcpy(&m_wfx, &m_pcmwf, sizeof(PCMWAVEFORMAT));
			m_wfx.cbSize = 0;
		}
		
		// �t�H�[�}�b�g�`�����N����WAVE�`�����N�ɖ߂�
		mmioAscend(m_hmmio, &formatChunkInfo, 0);

		// RIFF�`���̃f�[�^�`�����N�\�������[���N���A
		memset(&dataChunkInfo, 0x00, sizeof(MMCKINFO));

		// �f�[�^�`�����N�Ɉړ����邽�߂̏���ݒ�
		dataChunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');

		// WAVE�`�����N����f�[�^�`�����N�Ɉړ�
		mmret = mmioDescend(m_hmmio, &dataChunkInfo, &riffChunkInfo, MMIO_FINDCHUNK);

		// �`�����N�ړ��G���[�`�F�b�N
		if (mmret != MMSYSERR_NOERROR) throw std::runtime_error("load sound error");
	}

	void SoundData::initSound()
	{
		// �T�E���h�o�b�t�@�̑傫����0.25�b�Ԃ̃T�E���h�f�[�^�̑傫���ɐݒ肷��
		m_buflen = m_wfx.nAvgBytesPerSec / 4;

		// �T�E���h�o�b�t�@���������ޗ̈���uBufferQueueAlloc�v�̐��������
		m_bufData.resize(m_buflen * BufferQueueAlloc);

		// �T�E���h�o�b�t�@��ǂݍ��ވʒu
		unsigned char* bufLoadTopPtr = m_bufData.data();

		// �T�E���h�o�b�t�@���X�V���A�X�V�����o�b�t�@�T�C�Y���擾����
		auto readlen = mmioRead(m_hmmio, (HPSTR)bufLoadTopPtr, m_buflen);

		// �T�E���h�o�b�t�@���X�V�G���[�`�F�b�N
		if (readlen <= 0) throw std::runtime_error("load sound buffer error");

		// �T�E���h�J�E���^�[��������
		m_soundCount = 1u;

		// ���܂œǂݍ��񂾃T�E���h�o�b�t�@�̒�����������
		m_sumReadlen = readlen;

		// �\�[�X�{�C�X�Ƀf�[�^��]������ׂ̃p�����[�^
		XAUDIO2_BUFFER bufinfo;
		memset(&bufinfo, 0x00, sizeof(XAUDIO2_BUFFER));

		// �X�V�����o�b�t�@�̒������z������Z���i�ǂݍ��ރo�b�t�@�������Ȃ��j�̂ł���΁uXAUDIO2_END_OF_STREAM�v�t���O�𗧂Ă�
		bufinfo.Flags = ((UINT32)readlen >= m_buflen) ? 0 : XAUDIO2_END_OF_STREAM;
		// �]������o�b�t�@�̒���
		bufinfo.AudioBytes = readlen;
		// �]������o�b�t�@�̓ǂݍ��݊J�n�ʒu
		bufinfo.pAudioData = bufLoadTopPtr;
		// �]�������o�b�t�@�̂ǂ�����Đ����邩�H�i�������œ]������֌W���ɂO�j
		bufinfo.PlayBegin = 0;
		// �]�������o�b�t�@�̑��Đ���
		bufinfo.PlayLength = readlen / m_wfx.nBlockAlign;

		// �\�[�X�{�C�X�Ƀf�[�^��]������
		HRESULT hr = m_lpSourceVoice->SubmitSourceBuffer(&bufinfo, NULL);

		// �\�[�X�{�C�X�ւ̃f�[�^�]���G���[�`�F�b�N
		if (FAILED(hr)) throw std::runtime_error("submit source buffer error");
	}
}