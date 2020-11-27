#ifndef ACT_3D_BOSS_ENEMY_END_ATTACK_H_
#define ACT_3D_BOSS_ENEMY_END_ATTACK_H_

#include <TktkDX12GameLib.h>
#include "../../../../../Enums/Enums.h"

// �{�X�G�l�~�[�̍U����Ԃ��I�����邽�߂̏������s���R���|�[�l���g
class Act3D_BossEnemyEndAttack
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyEndAttack(float endAttackTimeSec, BossEnemyStateType attackType);

public:

	void onEnable();
	void update();

private:

	// �U����Ԃ��I������܂ł̃^�C�}�[
	const float					m_endAttackTimeSec;

	// �I������U����Ԃ̎��
	const BossEnemyStateType	m_attackType;

	// �U����Ԃ��I�����鏈�����s���ׂ̃^�C�}�[
	float						m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_END_ATTACK_H_