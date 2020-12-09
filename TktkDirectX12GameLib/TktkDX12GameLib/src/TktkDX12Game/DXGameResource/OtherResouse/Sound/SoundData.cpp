#include "TktkDX12Game/DXGameResource/OtherResouse/Sound/SoundData.h"

#include <stdexcept>
#include "TktkDX12Game/DXGameResource/OtherResouse/Sound/SoundPlayState.h"

namespace tktk
{
	// �������݉\�ȃT�E���h�o�b�t�@�̐�
	constexpr unsigned int CanWriteBufferQueueNum = 4U;

	// �T�E���h�o�b�t�@�̑���
	constexpr unsigned int TotalBufferQueueNum = CanWriteBufferQueueNum + 1U;

	SoundData::SoundData(const std::string & fileName, IXAudio2* xAudioPtr, HANDLE hEvent)
		: m_cSoundCallback(CSoundCallback(hEvent))
	{
		// �T�E���h�f�[�^��ǂݍ���
		loadSound(fileName);

		// �ǂݍ��񂾃T�E���h�f�[�^����\�[�X�{�C�X�����
		HRESULT hr = xAudioPtr->CreateSourceVoice(&m_lpSourceVoice, &m_wfx, XAUDIO2_VOICE_NOPITCH, XAUDIO2_DEFAULT_FREQ_RATIO, &m_cSoundCallback, NULL, NULL);

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
		, m_cSoundCallback(other.m_cSoundCallback)
		, m_lpSourceVoice(other.m_lpSourceVoice)
		, m_bufferSize(other.m_bufferSize)
		, m_bufferData(std::move(other.m_bufferData))
		, m_soundPlayState(other.m_soundPlayState)
		, m_nextBufferWriteIndex(other.m_nextBufferWriteIndex)
		, m_sumLoadSize(other.m_sumLoadSize)
		, m_sumDataSize(other.m_sumDataSize)
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

		// �T�E���h�t�@�C���̓ǂݍ��݈ʒu�𓪂ɖ߂��i���܂œǂݍ��񂾃T�E���h�t�@�C���̍��v�T�C�Y�������ǂݍ��݈ʒu��߂��j
		mmioSeek(m_hmmio, -static_cast<long>(m_sumLoadSize), SEEK_CUR);

		// ���܂œǂݍ��񂾃T�E���h�t�@�C���̍��v������������
		m_sumLoadSize = 0U;

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
		// �T�E���h�Đ��t���O�������Ă��Ȃ�������T�E���h�̍X�V���s��Ȃ�
		if ((m_soundPlayState & SoundPlayState::Playing) == 0U) return;

		// ���݂̃T�E���h�̏�Ԃ��擾����
		XAUDIO2_VOICE_STATE voiceState;
		m_lpSourceVoice->GetState(&voiceState);

		// �T�E���h�o�b�t�@��ǂݍ��ޗ]�T����������ǂݍ���
		while (voiceState.BuffersQueued < CanWriteBufferQueueNum && m_hmmio != nullptr)
		{
			// ���ꂩ��T�E���h�f�[�^��ǂݍ��݁A�������ރ������A�h���X�����߂�
			unsigned char* bufLoadTopPtr = m_bufferData.data() + m_bufferSize * m_nextBufferWriteIndex;

			// �������݃C���f�b�N�X���X�V����
			m_nextBufferWriteIndex = (m_nextBufferWriteIndex + 1) % TotalBufferQueueNum;

			// �ǂݍ��ރf�[�^�̑傫��
			auto loadDataSize = m_bufferSize;

			// �T�E���h�̓ǂݍ��݂��I��������H
			bool soundLoadEnd = false;

			// �T�E���h�f�[�^���I�[�o�[���ēǂݍ������Ƃ����ꍇ�A
			if ((m_sumLoadSize + loadDataSize) >= m_sumDataSize)
			{
				// �ǂݍ��ރf�[�^�̑傫����␳����
				loadDataSize = m_sumDataSize - m_sumLoadSize;

				// �T�E���h�̓ǂݍ��݂��I����t���O�𗧂Ă�
				soundLoadEnd = true;
			}

			// �ǂݍ��ރf�[�^�����݂��Ȃ�������
			if (loadDataSize == 0U)
			{
				if (voiceState.BuffersQueued == 0U)
				{
					// ��~����O�̃T�E���h�Đ���Ԃ�ێ�����
					auto preSoundPlayState = m_soundPlayState;

					// �T�E���h���~����
					stopSound();

					// ���[�v�t���O�������Ă�����ēx�Đ�����
					if ((preSoundPlayState & SoundPlayState::Loop) != 0) playSound(true);
				}
				// �ǂݍ��݃��[�v�𔲂���
				break;
			}

			// �T�E���h�o�b�t�@���X�V���A�X�V�����o�b�t�@�T�C�Y���擾����
			auto resultLoadDataSize = mmioRead(m_hmmio, reinterpret_cast<HPSTR>(bufLoadTopPtr), loadDataSize);

			// ���ۂɓǂݍ��񂾃f�[�^�T�C�Y���ǂݍ��݃T�C�Y�ƈ�����ꍇ�A��������̖�肪�������Ă���
			if (resultLoadDataSize != loadDataSize)
			{
				throw std::runtime_error("load sound buffer error");
			}

			// ���܂œǂݍ��񂾃T�E���h�o�b�t�@�̑傫�����X�V����
			m_sumLoadSize += loadDataSize;

			// �\�[�X�{�C�X�Ƀf�[�^��]������ׂ̃p�����[�^
			XAUDIO2_BUFFER bufinfo;
			memset(&bufinfo, 0x00, sizeof(XAUDIO2_BUFFER));

			// �T�E���h�̓ǂݍ��݂��I�����Ă�����X�g���[���I���t���O�𗧂Ă�
			bufinfo.Flags = (soundLoadEnd) ? XAUDIO2_END_OF_STREAM : 0;
			// �]������o�b�t�@�̑傫��
			bufinfo.AudioBytes	= loadDataSize;
			// �]������o�b�t�@�̓ǂݍ��݊J�n�ʒu
			bufinfo.pAudioData	= bufLoadTopPtr;
			// �]�������o�b�t�@�̂ǂ�����Đ����邩�H�i�������œ]������֌W���ɂO�j
			bufinfo.PlayBegin	= 0;
			// �]�������o�b�t�@�̑��Đ���
			bufinfo.PlayLength	= loadDataSize / m_wfx.nBlockAlign;

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
			// �������T�C�Y�Ńt�H�[�}�b�g�f�[�^
			PCMWAVEFORMAT	pcmwf;

			mmioRead(m_hmmio, (HPSTR)&pcmwf, sizeof(PCMWAVEFORMAT));
			memset(&m_wfx, 0x00, sizeof(WAVEFORMATEX));
			memcpy(&m_wfx, &pcmwf, sizeof(PCMWAVEFORMAT));
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
	
		// �T�E���h�f�[�^�̑傫����ۑ�����i�o�C�g�j
		m_sumDataSize = dataChunkInfo.cksize;
	}

	void SoundData::initSound()
	{
		// �T�E���h�o�b�t�@�̑傫����0.25�b�Ԃ̃T�E���h�f�[�^�̑傫���ɐݒ肷��
		m_bufferSize = m_wfx.nAvgBytesPerSec / 4;

		// �T�E���h�o�b�t�@���������ޗ̈���uBufferQueueAlloc�v�̐��������
		m_bufferData.resize(m_bufferSize * TotalBufferQueueNum);

		// �T�E���h�o�b�t�@��ǂݍ��ވʒu
		unsigned char* bufLoadTopPtr = m_bufferData.data();

		auto tempBuflen = m_bufferSize;

		bool endSound = false;

		// �T�E���h�f�[�^���I�[�o�[���ăo�b�t�@�̓ǂݍ��݂��s�����Ƃ����ꍇ�A�ǂݍ��ݔ͈͂��C������
		if (tempBuflen >= m_sumDataSize)
		{
			tempBuflen = m_sumDataSize;
			endSound = true;
		}

		// �T�E���h�o�b�t�@���X�V���A�X�V�����o�b�t�@�T�C�Y���擾����
		auto readlen = mmioRead(m_hmmio, (HPSTR)bufLoadTopPtr, tempBuflen);

		// �T�E���h�o�b�t�@���X�V�G���[�`�F�b�N
		if (readlen <= 0) throw std::runtime_error("load sound buffer error");

		// �T�E���h�J�E���^�[��������
		m_nextBufferWriteIndex = 1u;

		// ���܂œǂݍ��񂾃T�E���h�o�b�t�@�̒�����������
		m_sumLoadSize = readlen;

		// �\�[�X�{�C�X�Ƀf�[�^��]������ׂ̃p�����[�^
		XAUDIO2_BUFFER bufinfo;
		memset(&bufinfo, 0x00, sizeof(XAUDIO2_BUFFER));

		// �X�V�����o�b�t�@�̒������z������Z���i�ǂݍ��ރo�b�t�@�������Ȃ��j�̂ł���΁uXAUDIO2_END_OF_STREAM�v�t���O�𗧂Ă�
		bufinfo.Flags = (endSound) ? XAUDIO2_END_OF_STREAM : 0;
		// �]������o�b�t�@�̒���
		bufinfo.AudioBytes = readlen;
		// �]������o�b�t�@�̓ǂݍ��݊J�n�ʒu
		bufinfo.pAudioData = bufLoadTopPtr;
		// �]�������o�b�t�@�̂ǂ�����Đ����邩�H�i�������œ]������֌W���ɂO�j
		bufinfo.PlayBegin = 0;
		// �]�������o�b�t�@�̑��Đ���
		bufinfo.PlayLength = readlen / m_wfx.nBlockAlign;

		// �\�[�X�{�C�X�Ƀf�[�^��]������
		HRESULT hr = m_lpSourceVoice->SubmitSourceBuffer(&bufinfo, nullptr);

		// �\�[�X�{�C�X�ւ̃f�[�^�]���G���[�`�F�b�N
		if (FAILED(hr)) throw std::runtime_error("submit source buffer error");
	}
}