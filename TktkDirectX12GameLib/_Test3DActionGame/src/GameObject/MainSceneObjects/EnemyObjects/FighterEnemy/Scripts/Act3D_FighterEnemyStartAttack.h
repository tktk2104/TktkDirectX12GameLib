#ifndef ACT_3D_FIGHTER_ENEMY_START_ATTACK_H_
#define ACT_3D_FIGHTER_ENEMY_START_ATTACK_H_

#include <TktkDX12GameLib.h>

class Act3D_FighterEnemyStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_FighterEnemyStartAttack() = default;

public:

	void start();
	void update();

private:

	// �ʏ�U�����J�n����g�^�ォ�猩���u�G�l�~�[�̐��ʃx�N�g���ƁA�v���C���[�����̃x�N�g���v�̊Ԃ̊p�h�̍ő�l�i�x���@�j
	static constexpr float NormalAttackStartAngleDeg	{ 45.0f };

	// �W�����v�U�����J�n����g�^�ォ�猩���u�G�l�~�[�̐��ʃx�N�g���ƁA�v���C���[�����̃x�N�g���v�̊Ԃ̊p�h�̍ő�l�i�x���@�j
	static constexpr float JumpAttackStartAngleDeg		{ 1.0f };

	// �ʏ�U�����J�n����v���C���[�Ƃ̋���
	static constexpr float NormalAttackStartRange		{ 3.0f };

	// �W�����v�U�����J�n����v���C���[�Ƃ̋���
	static constexpr float JumpAttackStartRange			{ 7.0f };

	// �ʏ�U������n�܂����U�����I�������A�ĂэU���ł���悤�ɂȂ�܂ł̎��ԁi�b�j
	static constexpr float NormalAttackIntervalTimeSec	{ 1.0f };

	// �W�����v�U������n�܂����U�����I�������A�ĂэU���ł���悤�ɂȂ�܂ł̎��ԁi�b�j
	static constexpr float JumpAttackIntervalTimeSec	{ 1.5f };

private:

	float									m_attackIntervelSecTimer{ 0.0f };
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_FIGHTER_ENEMY_START_ATTACK_H_
