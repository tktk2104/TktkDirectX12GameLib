#ifndef ACT_3D_FIGHTER_ENEMY_END_ATTACK_H_
#define ACT_3D_FIGHTER_ENEMY_END_ATTACK_H_

#include <TktkDX12GameLib.h>
#include "../../../../../Enums/Enums.h"

// �ߋ����U���G�l�~�[�̍U����Ԃ��I�����鏈�����s���R���|�[�l���g
class Act3D_FighterEnemyEndAttack
	: public tktk::ComponentBase
{
public:

	Act3D_FighterEnemyEndAttack(float endAttackTimeSec, FighterEnemyState attackType);

public:

	void onEnable();
	void update();

private:

	// �U����Ԃ��I������܂ł̎��ԁi�b�j
	const float				m_endAttackTimeSec;

	// �I������ߐڍU���G�l�~�[�̏��
	const FighterEnemyState	m_attackType;

	// �U����Ԃ��I�����邽�߂̃^�C�}�[
	float					m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_FIGHTER_ENEMY_END_ATTACK_H_