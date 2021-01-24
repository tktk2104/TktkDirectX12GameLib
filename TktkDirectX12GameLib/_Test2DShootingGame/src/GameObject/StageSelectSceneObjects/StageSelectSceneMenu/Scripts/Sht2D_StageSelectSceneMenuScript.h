#ifndef SHT_2D_STAGE_SELECT_SCENE_MENU_SCRIPT_H_
#define SHT_2D_STAGE_SELECT_SCENE_MENU_SCRIPT_H_

#include <array>
#include <TktkDX12GameLib.h>

// �X�e�[�W�Z���N�g���j���[�X�N���v�g
class Sht2D_StageSelectSceneMenuScript
	: public tktk::ComponentBase
{
public:

	Sht2D_StageSelectSceneMenuScript() = default;

public:

	void start();
	void update();

private:

	void changeMenuState(int nextMenuState);

private:

	// ���j���[�̍��ڂ̎��
	enum class MenuContantType
	{
		Stage1,
		Stage2,
		Stage3,
		Back,
	};

private:

	// ���j���[���ڂ̑I������ύX����Ԋu�i�b�j
	constexpr static float ChangeMenuIntervalTimeSec{ 0.2f };

private:

	// ���j���[���ڂ̑I������ύX����Ԋu�̃^�C�}�[�i�b�j
	float m_changeMenuIntervalSecTimer{ 0.0f };

	// ���ݑI������Ă��郁�j���[�̎��
	MenuContantType		m_curMenuState{ MenuContantType::Stage1 };

	// ���j���[�̍��ڃI�u�W�F�N�g�̃|�C���^���Ǘ�����z��
	std::array<tktk::GameObjectPtr, 4U> m_menuContantObjectArray;
};
#endif // !SHT_2D_STAGE_SELECT_SCENE_MENU_SCRIPT_H_