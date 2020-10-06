#ifndef SOUND_DATA_H_
#define SOUND_DATA_H_

#include <string>
#include <vector>
#include <xaudio2.h>
#undef min
#undef max
#include "CSoundCallback.h"

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
		// �t�H�[�}�b�g�`�����N���傫�����鎞�Ɏg�p�������
		PCMWAVEFORMAT	m_pcmwf;

		// �T�E���h�̃R�[���o�b�N�����N���X
		CSoundCallback m_cSoundCallback;

		// �\�[�X�{�C�X
		IXAudio2SourceVoice* m_lpSourceVoice{ nullptr };

		// �T�E���h�o�b�t�@�̑傫��
		unsigned int m_buflen;

		// �T�E���h�o�b�t�@�i0.25�b�Ԃ̃T�E���h�f�[�^�����T�̃T�E���h�o�b�t�@���A�����đ��݂��Ă���j
		std::vector<unsigned char> m_bufData;

		// �T�E���h�Đ��̏�Ԃ�\���r�b�g�t���O
		unsigned int m_soundPlayState{ 0U };

		// ���y�Đ��p�̃J�E���^
		unsigned int m_soundCount;

		// �T�E���h�o�b�t�@��ǂݍ��񂾑���
		unsigned int m_sumReadlen;
	};
}
#endif // !SOUND_DATA_H_