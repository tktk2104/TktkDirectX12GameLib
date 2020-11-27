#ifndef ACT_3D_BOSS_ENEMY_END_DOWN_H_
#define ACT_3D_BOSS_ENEMY_END_DOWN_H_

#include <TktkDX12GameLib.h>

// �{�X�G�l�~�[�̃_�E����Ԃ��I�����鏈�����s���R���|�[�l���g
class Act3D_BossEnemyEndDown
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyEndDown() = default;

public:

	void onEnable();
	void update();

private:

	// �N���オ��I���܂ł̎���
	constexpr static float EndDownTimeSec{ 0.8f };

private:

	// �_�E����Ԃ��I�����鏈�����s�����߂̃^�C�}�[
	float m_endDownUpSecTimer{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_END_DOWN_H_