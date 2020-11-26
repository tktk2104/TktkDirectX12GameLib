#ifndef ACT_3D_SHOOTER_ENEMY_START_CHASE_H_
#define ACT_3D_SHOOTER_ENEMY_START_CHASE_H_

#include <TktkDX12GameLib.h>

class Act3D_ShooterEnemyStartChase
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyStartChase() = default;

public:

	void start();
	void update();

private:

	// �v���C���[�𔭌��ł��鋗��
	static constexpr float FindPlayerRange{ 30.0f };

	// �v���C���[�𔭌��ł���g�^�ォ�猩���u�G�l�~�[�̐��ʃx�N�g���ƁA�v���C���[�����̃x�N�g���v�̊Ԃ̊p�h�̍ő�l�i�x���@�j
	static constexpr float FindPlayerAngleDeg{ 100.0f };

private:

	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_SHOOTER_ENEMY_START_CHASE_H_
