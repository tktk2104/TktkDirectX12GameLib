#ifndef ACT_3D_SHOOTER_ENEMY_PARAM_H_
#define ACT_3D_SHOOTER_ENEMY_PARAM_H_

#include <TktkDX12GameLib.h>

// �������U���G�l�~�[�̔\�͒l�̃R���|�[�l���g
class Act3D_ShooterEnemyParam
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyParam() = default;

public:

	// �����̒l��HP�����炷
	void damage(int damage);

	// HP���[�������ʂ���
	bool outOfHp() const;

public:

	// �ő�HP
	constexpr int getMaxHp() const { return 5; }

private:

	// ���݂�HP
	int m_curHp{ getMaxHp() };
};
#endif // !ACT_3D_SHOOTER_ENEMY_PARAM_H_
