#ifndef ACT_3D_BOSS_ENEMY_START_ATTACK_H_
#define ACT_3D_BOSS_ENEMY_START_ATTACK_H_

#include <TktkDX12GameLib.h>
#include "Act3D_BossEnemyParam.h"

class Act3D_BossEnemyStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyStartAttack() = default;

public:

	void start();
	void update();

//************************************************************
private: /* �ʏ�U���̔\�� */

	// �U���J�n�ł���v���C���[�Ƃ̊p�x���i�x���@�j
	static constexpr float NormalAttackStartAngleDeg	{ 45.0f };

	// �U���J�n�ł���v���C���[�Ƃ̋���
	static constexpr float NormalAttackStartRange		{ 4.0f };

	// �����s���̃C���^�[�o���i�b�j
	static constexpr float NormalAttackIntervalTimeSec	{ 0.2f };

//************************************************************
private: /* ���[�����O�U���̔\�� */

	// �U���J�n�ł���v���C���[�Ƃ̊p�x���i�x���@�j
	static constexpr float RollAttackStartAngleDeg		{ 45.0f };

	// ���[�����O�U�����J�n����v���C���[�Ƃ̋���
	static constexpr float RollAttackStartRange			{ 12.0f };

	// �����s���̃C���^�[�o���i�b�j
	static constexpr float RollAttackIntervalTimeSec	{ 7.5f };

	//// �U���̎��s�m���i�����j
	//static constexpr float RollAttackMissRate			{ 0.1f };
	//
	//// �U���̍ő�A���������i���̉񐔘A���Ő��������ꍇ�A���͕K�����s����j
	//static constexpr unsigned int RollAttackMissCountMax{ 5U };

//************************************************************
private: /* �W�����v�U���̔\�� */

	// �U���J�n�ł���v���C���[�Ƃ̊p�x���i�x���@�j
	static constexpr float JumpAttackStartAngleDeg		{ 1.0f };

	// ���[�����O�U�����J�n����v���C���[�Ƃ̋���
	static constexpr float JumpAttackStartRange			{ 15.0f };

	// �����s���̃C���^�[�o���i�b�j
	static constexpr float JumpAttackIntervalTimeSec	{ 10.0f };

private:

	unsigned int								m_rollAttackMissCounter	{ 0U };
	tktk::ComponentPtr<Act3D_BossEnemyParam>	m_selfParam;
	tktk::ComponentPtr<tktk::Transform3D>		m_selfTransform;
	tktk::ComponentPtr<tktk::Transform3D>		m_playerTransform;
	
};
#endif // !ACT_3D_BOSS_ENEMY_START_ATTACK_H_
