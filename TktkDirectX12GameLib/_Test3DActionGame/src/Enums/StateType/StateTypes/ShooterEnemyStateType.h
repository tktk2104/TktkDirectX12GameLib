#ifndef SHOOTER_ENEMY_STATE_TYPE_H_
#define SHOOTER_ENEMY_STATE_TYPE_H_

enum class ShooterEnemyStateType
{
	/* ��{��� */
	Alive,	// �����X�e�[�g
	Dead,	// ���S�X�e�[�g

	/* �����X�e�[�g */
	Normal,	// �ʏ�X�e�[�g
	Damage,	// ��_���[�W�X�e�[�g

	/* �ʏ�X�e�[�g */
	Idle,			// �ҋ@�X�e�[�g
	Move,			// �ړ��X�e�[�g
	Attack,			// �U���X�e�[�g	

	/* �U���X�e�[�g */
	Attack_1,		// �ߋ����U���X�e�[�g
	Shot,			// �������U���X�e�[�g
};
#endif // !SHOOTER_ENEMY_STATE_TYPE_H_