#ifndef OTHER_RESOUSE_H_
#define OTHER_RESOUSE_H_

/* std::unique_ptr */
#include <memory>

/* funcUseType */
#include <string>
#include "../GameObjectResouse/GameObject/GameObjectTagCarrier.h"

namespace tktk
{
	/* class member */
	class SceneManager;
	class SoundManager;
	class FontManager;

	/* funcUseType */
	struct OtherResouseInitParam;
	struct SceneInitParam;

	// ���̑��̃��\�[�X���Ǘ�����N���X
	class OtherResouse
	{
	public:

		explicit OtherResouse(const OtherResouseInitParam& initParam);
		~OtherResouse();

	public:

		void update();

	public: /* �V�[���֌W�̏��� */

		// �V�[�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createScene(const SceneInitParam& initParam);

		// �V�[���̏I�����ɍ폜����Q�[���I�u�W�F�N�g�^�O��ݒ肷��
		void setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag);

		// �V�[����L���ɂ���
		void enableScene(size_t handle);

		// �V�[���𖳌��ɂ���
		void disableScene(size_t handle);

	public: /* �T�E���h�֌W�̏��� */

		// �ǂݍ��񂾃T�E���h�����ׂč폜����
		void clearSound();

		// �V�����T�E���h��ǂݍ��݁A���̃��\�[�X�̃n���h����Ԃ�
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		size_t loadSound(const std::string& fileName);

		// �w�肵���T�E���h���Đ�����
		void playSound(size_t handle, bool loopPlay);

		// �w�肵���T�E���h���~����
		void stopSound(size_t handle);

		// �w�肵���T�E���h���ꎞ��~����
		void pauseSound(size_t handle);

		// �匳�̉��ʂ�ύX����i0.0f�`1.0f�j
		void setMasterVolume(float volume);

	public: /* �t�H���g�֌W�̏��� */

		// �e�L�X�g��`�悷�邽�߂ɕK�v�Ȋ�{���\�[�X�����
		void createFontBaseResource();

		// �V�X�e���t�H���g���g�����������āA���̃��\�[�X�̃n���h����Ԃ�
		size_t createFont(const std::string& systemFontName, int fontSize, float fontThicknessRate);

		// �t�H���g�t�@�C����ǂݍ��݁A���̃t�H���g���g�����������āA���̃��\�[�X�̃n���h����Ԃ�
		size_t createFont(const std::string& fontFilePath, const std::string& fontName, int fontSize, float fontThicknessRate);

		// �w��̃A�b�v���[�h�o�b�t�@�Ɉ����̕�����̃e�N�X�`���f�[�^���������݁A�������񂾃o�b�t�@�̍ő傘���W��Ԃ�
		size_t updateTextTextureUploadBuffData(size_t handle, size_t uploadBufferHandle, const std::string& text);

		// �e�L�X�g�������ݗp�̃A�b�v���[�h�o�b�t�@�����A���̃n���h����Ԃ�
		size_t createTextTextureUploadBuffer();

	private:

		std::unique_ptr<SceneManager>	m_sceneManager;
		std::unique_ptr<SoundManager>	m_soundManager;
		std::unique_ptr<FontManager>	m_fontManager;
	};
}
#endif // !OTHER_RESOUSE_H_