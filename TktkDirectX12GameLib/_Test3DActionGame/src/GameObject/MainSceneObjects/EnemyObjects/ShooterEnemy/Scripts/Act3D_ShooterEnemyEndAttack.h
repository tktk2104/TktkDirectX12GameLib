#ifndef ACT_3D_SHOOTER_ENEMY_END_ATTACK_H_
#define ACT_3D_SHOOTER_ENEMY_END_ATTACK_H_

#include <TktkDX12GameLib.h>
#include "../../../../../Enums/Enums.h"

// �������U���G�l�~�[�̍U���I���R���|�[�l���g
class Act3D_ShooterEnemyEndAttack
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyEndAttack(float endAttackTimeSec, ShooterEnemyStateType attackType);

public:

	void onEnable();
	void update();

private:

	// �U�����I������܂ł̎��ԁi�b�j
	const float					m_endAttackTimeSec;

	// �I�����鉓�����U���G�l�~�[�̏��
	const ShooterEnemyStateType	m_attackType;

	// �U�����I�����邽�߂̃^�C�}�[
	float						m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_SHOOTER_ENEMY_END_ATTACK_H_