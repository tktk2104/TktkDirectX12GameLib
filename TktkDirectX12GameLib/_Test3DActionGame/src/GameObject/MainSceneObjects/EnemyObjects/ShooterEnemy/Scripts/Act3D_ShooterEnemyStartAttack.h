#ifndef ACT_3D_SHOOTER_ENEMY_START_ATTACK_H_
#define ACT_3D_SHOOTER_ENEMY_START_ATTACK_H_

#include <TktkDX12GameLib.h>

// �������U���G�l�~�[�̍U���J�n�����R���|�[�l���g
class Act3D_ShooterEnemyStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyStartAttack() = default;

public:

	void start();
	void update();

//************************************************************
private: /* �ߋ����U���̔\�� */

	// �U���J�n�ł���v���C���[�Ƃ̊p�x���i�x���@�j
	static constexpr float ShortRangeAttackStartAngleDeg	{ 45.0f };

	// �U���J�n�ł���v���C���[�Ƃ̋���
	static constexpr float ShortRangeAttackStartRange		{ 3.0f };

	// �U���̃C���^�[�o���i�b�j
	static constexpr float ShortRangeAttackIntervalTimeSec	{ 1.0f };

//************************************************************
private: /* �������U���̔\�� */

	// �U���J�n�ł���v���C���[�Ƃ̊p�x���i�x���@�j
	static constexpr float LongRangeAttackStartAngleDeg		{ 1.0f };

	// �U���J�n�ł���v���C���[�Ƃ̋���
	static constexpr float LongRangeAttackStartRange		{ 30.0f };

	// �U���̃C���^�[�o���i�b�j
	static constexpr float LongRangeAttackIntervalTimeSec	{ 2.0f };

private:

	// �U���Ԋu���Ǘ�����^�C�}�[
	float									m_attackIntervelSecTimer{ 0.0f };

	// ���g�̍��W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;

	// �v���C���[�̍��W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_SHOOTER_ENEMY_START_ATTACK_H_