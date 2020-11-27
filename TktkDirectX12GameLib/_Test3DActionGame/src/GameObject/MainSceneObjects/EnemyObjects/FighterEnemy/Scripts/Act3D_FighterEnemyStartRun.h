#ifndef ACT3D_FIGHTER_ENEMY_START_RUN_H_
#define ACT3D_FIGHTER_ENEMY_START_RUN_H_

#include <TktkDX12GameLib.h>

// �ߐڍU���G�l�~�[�̃_�b�V���ړ����J�n���鏈�����s���R���|�[�l���g
class Act3D_FighterEnemyStartRun
	: public tktk::ComponentBase
{
public:

	void onEnable();
	void update();

private:

	// �_�b�V������������܂ł̎���
	static constexpr float StartRunTimeSec{ 3.0f };

private:

	// �_�b�V�����n�߂邽�߂̃^�C�}�[
	float m_startRunSecTimer{ 0.0f };
};
#endif // !ACT3D_FIGHTER_ENEMY_START_RUN_H_