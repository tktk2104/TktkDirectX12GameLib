#ifndef SOUND_DATA_H_
#define SOUND_DATA_H_

/* std::vector */
#include <vector>

/* HMMIO, WAVEFORMATEX, PCMWAVEFORMAT, IXAudio2SourceVoice */
#include <xaudio2.h>
#undef min
#undef max

/* class member */
#include "CSoundCallback.h"

/* funcUseType */
#include <string>

namespace tktk
{
	// �T�E���h���Ǘ�����N���X
	class SoundData
	{
	public:

		SoundData(const std::string& fileName, IXAudio2* xAudioPtr, HANDLE hEvent);
		~SoundData();

		SoundData(const SoundData& other) = delete;
		SoundData& operator = (const SoundData& other) = delete;

		// ���[�u�R���X�g���N�^
		SoundData(SoundData&& other) noexcept;

	public:

		// �T�E���h���Đ����Ă��邩�H
		bool isPlaySound() const;

		// �T�E���h�̍Đ����J�n
		void playSound(bool loopPlay);

		// �T�E���h���Đ����~
		void stopSound();

		// �T�E���h�̍Đ����ꎞ��~
		void pauseSound();

		void update();

	private:

		void loadSound(const std::string& fileName);

		void initSound();

	private:

		// wav�t�@�C���̃n���h��
		HMMIO			m_hmmio{ nullptr };
		
		// wav�t�@�C���̃t�H�[�}�b�g���
		WAVEFORMATEX	m_wfx;

		// �T�E���h�̃R�[���o�b�N�����N���X
		CSoundCallback m_cSoundCallback;

		// �\�[�X�{�C�X
		IXAudio2SourceVoice* m_lpSourceVoice{ nullptr };

		// �T�E���h�o�b�t�@�P������̑傫��
		unsigned int m_bufferSize;

		// �T�E���h�o�b�t�@�i0.25�b�Ԃ̃T�E���h�f�[�^�����T�̃T�E���h�o�b�t�@���A�����đ��݂��Ă���j
		std::vector<unsigned char> m_bufferData;

		// �T�E���h�Đ��̏�Ԃ�\���r�b�g�t���O
		unsigned int m_soundPlayState{ 0U };

		// ���ɃT�E���h�f�[�^���������ރT�E���h�o�b�t�@�C���f�b�N�X�i�ubufferTopPtr + (bufferlen * nextBufferWriteIndex)�v�̃A�h���X�ɏ������ށj
		unsigned int m_nextBufferWriteIndex;

		// ���܂œǂݍ��񂾉����f�[�^�̍��v�T�C�Y
		unsigned int m_sumLoadSize;

		// �T�E���h�f�[�^�̍��v�T�C�Y
		unsigned int m_sumDataSize;
	};
}
#endif // !SOUND_DATA_H_