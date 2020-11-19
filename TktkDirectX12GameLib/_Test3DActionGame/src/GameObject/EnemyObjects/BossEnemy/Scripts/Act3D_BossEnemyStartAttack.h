#ifndef ACT_3D_BOSS_ENEMY_START_ATTACK_H_
#define ACT_3D_BOSS_ENEMY_START_ATTACK_H_

#include <TktkDX12GameLib.h>

class Act3D_BossEnemyStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyStartAttack() = default;

public:

	void start();
	void update();

private:

	// �ʏ�U�����J�n����g�^�ォ�猩���u�G�l�~�[�̐��ʃx�N�g���ƁA�v���C���[�����̃x�N�g���v�̊Ԃ̊p�h�̍ő�l�i�x���@�j
	static constexpr float NormalAttackStartAngleDeg{ 45.0f };

	// ���[�����O�U�����J�n����g�^�ォ�猩���u�G�l�~�[�̐��ʃx�N�g���ƁA�v���C���[�����̃x�N�g���v�̊Ԃ̊p�h�̍ő�l�i�x���@�j
	static constexpr float RollAttackStartAngleDeg{ 45.0f };

	// �W�����v�U�����J�n����g�^�ォ�猩���u�G�l�~�[�̐��ʃx�N�g���ƁA�v���C���[�����̃x�N�g���v�̊Ԃ̊p�h�̍ő�l�i�x���@�j
	static constexpr float JumpAttackStartAngleDeg{ 1.0f };

	// �ʏ�U�����J�n����v���C���[�Ƃ̋���
	static constexpr float NormalAttackStartRange{ 4.0f };

	// ���[�����O�U�����J�n����v���C���[�Ƃ̋���
	static constexpr float RollAttackStartRange{ 12.0f };

	// �W�����v�U�����J�n����v���C���[�Ƃ̋���
	static constexpr float JumpAttackStartRange{ 15.0f };

	// �ʏ�U������n�܂����U�����I�������A�ĂэU���ł���悤�ɂȂ�܂ł̎��ԁi�b�j
	static constexpr float NormalAttackIntervalTimeSec{ 0.2f };

	// ���[�����O�U������n�܂����U�����I�������A�ĂэU���ł���悤�ɂȂ�܂ł̎��ԁi�b�j
	static constexpr float RollAttackIntervalTimeSec{ 0.5f };

	// �W�����v�U������n�܂����U�����I�������A�ĂэU���ł���悤�ɂȂ�܂ł̎��ԁi�b�j
	static constexpr float JumpAttackIntervalTimeSec{ 0.5f };

	// ���[�����O�U���̎��s�m���i�����j
	static constexpr float RollAttackMissRate{ 0.1f };

	// ���[�����O�U���̍ő�A���������i���̉񐔘A���Ő��������ꍇ�A���͕K�����s����j
	static constexpr unsigned int RollAttackMissCountMax{ 5U };

private:

	float									m_attackIntervelSecTimer{ 0.0f };
	unsigned int							m_rollAttackMissCounter{ 0U };
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_BOSS_ENEMY_START_ATTACK_H_
