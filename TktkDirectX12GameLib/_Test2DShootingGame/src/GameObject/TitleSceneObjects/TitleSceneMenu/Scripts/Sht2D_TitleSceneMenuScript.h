#ifndef SHT_2D_TITLE_SCENE_MENU_SCRIPT_H_
#define SHT_2D_TITLE_SCENE_MENU_SCRIPT_H_

#include <array>
#include <TktkDX12GameLib.h>

  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	������̃R���|�[�l���g�����ۂ́utktk::ComponentBase�v���p�����ĉ������B
	���@�V�[���Ɠ����悤�ɕ����̊֐����_�b�N�^�C�s���O�I�ɌĂ΂�܂��B
	���@�ǂ̂悤�Ȋ֐������邩�́uComponentBase.h�v���Q�Ƃ��ĉ������B�i�utktk::ComponentBase�v���V���O���N���b�N��F12�L�[����́j
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

// �^�C�g�����j���[�X�N���v�g
class Sht2D_TitleSceneMenuScript
	: public tktk::ComponentBase
{
public:

	Sht2D_TitleSceneMenuScript() = default;

public:

  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	�����̂Q�̊֐��̓t���[�����[�N���Ŏ����ŌĂ΂��֐��ł��B�֐������ԈႦ��ƌĂ΂�Ȃ��̂Œ��ӂ��܂��傤�B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	void start();
	void update();

private:

	void changeMenuState(int nextMenuState);

private:

	// ���j���[�̍��ڂ̎��
	enum class MenuContantType
	{
		GameStart,
		GemeEnd,
	};

private:

	// ���j���[���ڂ̑I������ύX����Ԋu�i�b�j
	constexpr static float ChangeMenuIntervalTimeSec{ 0.2f };

private:

	// ���j���[���ڂ̑I������ύX����Ԋu�̃^�C�}�[�i�b�j
	float m_changeMenuIntervalSecTimer	{ 0.0f };

	// ���ݑI������Ă��郁�j���[�̎��
	MenuContantType		m_curMenuState	{ MenuContantType::GameStart };

	// ���j���[�̍��ڃI�u�W�F�N�g�̃|�C���^���Ǘ�����z��
	std::array<tktk::GameObjectPtr, 2U> m_menuContantObjectArray;
};
#endif // !SHT_2D_TITLE_SCENE_MENU_SCRIPT_H_