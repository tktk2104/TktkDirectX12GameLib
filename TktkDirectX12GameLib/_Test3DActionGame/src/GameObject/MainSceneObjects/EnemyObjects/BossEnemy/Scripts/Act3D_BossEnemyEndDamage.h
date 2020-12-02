#ifndef ACT_3D_BOSS_ENEMY_END_DAMAGE_H_
#define ACT_3D_BOSS_ENEMY_END_DAMAGE_H_

#include <TktkDX12GameLib.h>

// �{�X�G�l�~�[�̃_���[�W��Ԃ��I�����鏈�����s���R���|�[�l���g
class Act3D_BossEnemyEndDamage
	: public tktk::ComponentBase
{
public:

	void onEnable();
	void update();

private:

	// �_���[�W��Ԃ��I���܂ł̎���
	static constexpr float EndDamageTimeSec{ 0.1f };

private:

	// �_���[�W��Ԃ��I�����鏈�����s�����߂̃^�C�}�[
	float m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_END_DAMAGE_H_