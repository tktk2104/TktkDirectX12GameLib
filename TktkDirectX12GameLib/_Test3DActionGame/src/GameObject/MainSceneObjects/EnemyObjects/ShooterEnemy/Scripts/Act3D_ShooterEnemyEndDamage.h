#ifndef ACT_3D_SHOOTER_ENEMY_END_DAMAGE_H_
#define ACT_3D_SHOOTER_ENEMY_END_DAMAGE_H_

#include <TktkDX12GameLib.h>

// �������U���G�l�~�[�̃_���[�W��Ԃ��I������R���|�[�l���g
class Act3D_ShooterEnemyEndDamage
	: public tktk::ComponentBase
{
public:

	void onEnable();
	void update();

private:

	// �_���[�W��Ԃ��I���܂ł̎���
	static constexpr float EndDamageTimeSec{ 0.4f };

private:

	// �_���[�W��Ԃ��I�����邽�߂̃^�C�}�[
	float m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_SHOOTER_ENEMY_END_DAMAGE_H_
