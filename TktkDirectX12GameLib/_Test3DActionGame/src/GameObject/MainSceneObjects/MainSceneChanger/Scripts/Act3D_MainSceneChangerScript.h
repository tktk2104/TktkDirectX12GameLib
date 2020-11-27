#ifndef ACT_3D_MAIN_SCENE_CHANGER_SCRIPT_H_
#define ACT_3D_MAIN_SCENE_CHANGER_SCRIPT_H_

#include <TktkDX12GameLib.h>

// ���C���V�[������J�ڂ����鏈�����s���R���|�[�l���g
class Act3D_MainSceneChangerScript
	: public tktk::ComponentBase
{
public:

	Act3D_MainSceneChangerScript() = default;

public:

	void start();
	void update();

private:

	// �V�[���J�ڂ���܂ł̎���
	constexpr static float SceneChangeTime{ 2.0f };

	// ���g���E���܂ł̎���
	constexpr static float SelfDeadTime{ 4.0f };

private:

	// �V�[���J�ڃ^�C�}�[
	float	m_sceneChangeSecTimer{ 0.0f };

	// �V�[���J�ڂ��J�n�������H
	bool	m_startSceneChange{ false };

	// �V�[���J�ڂ��I��������H
	bool	m_endSceneChange{ false };

	// ��ʂ̃t�F�[�h�p�X�v���C�g�`��R���|�[�l���g
	tktk::ComponentPtr<tktk::SpriteDrawer> m_fadeSprite;
};
#endif // !ACT_3D_MAIN_SCENE_CHANGER_SCRIPT_H_