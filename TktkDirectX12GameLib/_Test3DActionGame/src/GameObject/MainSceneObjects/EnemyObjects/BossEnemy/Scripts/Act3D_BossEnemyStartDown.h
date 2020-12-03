#ifndef ACT_3D_BOSS_ENEMY_START_DOWN_H_
#define ACT_3D_BOSS_ENEMY_START_DOWN_H_

#include <TktkDX12GameLib.h>

// �{�X�G�l�~�[�̃_�E����Ԃ��J�n���鏈�����s�����߂̃R���|�[�l���g
class Act3D_BossEnemyStartDown
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyStartDown() = default;

public:

	void onEnable();
	void update();

private:

	// �_�E����ԂɂȂ�܂ł̎���
	constexpr static float StartDownTimeSec{ 2.0f };

private:

	// �_�E����Ԃ��J�n���鏈�����s�����߂̃^�C�}�[
	float m_startDownSecTimer{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_START_DOWN_H_
