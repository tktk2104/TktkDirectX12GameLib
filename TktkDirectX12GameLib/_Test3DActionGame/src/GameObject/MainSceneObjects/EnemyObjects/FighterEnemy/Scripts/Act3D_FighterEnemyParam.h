#ifndef ACT_3D_FIGHTER_ENEMY_PARAM_H_
#define ACT_3D_FIGHTER_ENEMY_PARAM_H_

#include <TktkDX12GameLib.h>

// �ߋ����U���G�l�~�[�̔\�͒l�̃R���|�[�l���g
class Act3D_FighterEnemyParam
	: public tktk::ComponentBase
{
public:

	Act3D_FighterEnemyParam() = default;

public:

	// �����̒l����HP�����炷
	void damage(int damage);

	// Hp���[�������肷��
	bool outOfHp() const;

public:

	// �ő�HP
	constexpr int getMaxHp() const { return 8; }

private:

	// ���݂�Hp
	int m_curHp{ getMaxHp() };
};
#endif // !ACT_3D_FIGHTER_ENEMY_PARAM_H_