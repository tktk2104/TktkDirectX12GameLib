#ifndef SOUND_H_
#define SOUND_H_

/* IXAudio2, IXAudio2MasteringVoice, HANDLE */
#include <xaudio2.h>
#undef min
#undef max

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	class SoundData;

	// �uSoundData�v���Ǘ�����N���X
	class SoundManager
	{
	public:

		explicit SoundManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~SoundManager();

		SoundManager(const SoundManager& other) = delete;
		SoundManager& operator = (const SoundManager& other) = delete;

	public:

		void update();

	public:

		// �V���ȃT�E���h�����[�h���A���̃��\�[�X�̃n���h����Ԃ�
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		size_t load(const std::string& fileName);

		// �S�ẴT�E���h���폜����
		void clear();

		// �w�肵���T�E���h���Đ�����
		void play(size_t handle, bool loopPlay);

		// �w�肵���T�E���h���~����
		void stop(size_t handle);

		// �w�肵���T�E���h���ꎞ��~����
		void pause(size_t handle);

		// �匳�̉��ʂ�ύX����i0.0f�`1.0f�j
		void setMasterVolume(float volume);

	private:

		tktkContainer::ResourceContainer<SoundData> m_assets;

		// �T�E���h�̃C�x���g�����Ɏg�p����ϐ�
		HANDLE m_soundEvent{ NULL };

		// XAudio�̃|�C���^
		IXAudio2* m_xAudioPtr{ NULL };

		// �}�X�^�����O�{�C�X�̃|�C���^
		IXAudio2MasteringVoice* m_masterVoicePtr{ NULL };
	};
}
#endif // !SOUND_H_