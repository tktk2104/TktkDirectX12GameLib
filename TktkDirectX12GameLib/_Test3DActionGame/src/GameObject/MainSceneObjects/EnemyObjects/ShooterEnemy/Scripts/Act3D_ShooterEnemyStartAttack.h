#ifndef ACT_3D_SHOOTER_ENEMY_START_ATTACK_H_
#define ACT_3D_SHOOTER_ENEMY_START_ATTACK_H_

#include <TktkDX12GameLib.h>

class Act3D_ShooterEnemyStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyStartAttack() = default;

public:

	void start();
	void update();

private:

	// �ߋ����U�����J�n����g�^�ォ�猩���u�G�l�~�[�̐��ʃx�N�g���ƁA�v���C���[�����̃x�N�g���v�̊Ԃ̊p�h�̍ő�l�i�x���@�j
	static constexpr float ShortRangeAttackStartAngleDeg{ 45.0f };

	// �������U�����J�n����g�^�ォ�猩���u�G�l�~�[�̐��ʃx�N�g���ƁA�v���C���[�����̃x�N�g���v�̊Ԃ̊p�h�̍ő�l�i�x���@�j
	static constexpr float LongRangeAttackStartAngleDeg	{ 1.0f };

	// �ߋ����U�����J�n����v���C���[�Ƃ̋���
	static constexpr float ShortRangeAttackStartRange	{ 3.0f };

	// �������U�����J�n����v���C���[�Ƃ̋���
	static constexpr float LongRangeAttackStartRange	{ 30.0f };

	// �ߋ����U������n�܂����U�����I�������A�ĂэU���ł���悤�ɂȂ�܂ł̎��ԁi�b�j
	static constexpr float ShortRangeAttackIntervalTimeSec	{ 1.0f };

	// �������U������n�܂����U�����I�������A�ĂэU���ł���悤�ɂȂ�܂ł̎��ԁi�b�j
	static constexpr float LongRangeAttackIntervalTimeSec	{ 2.0f };

private:

	float									m_attackIntervelSecTimer{ 0.0f };
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_SHOOTER_ENEMY_START_ATTACK_H_