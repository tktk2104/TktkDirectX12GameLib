#ifndef MOTION_ID_H_
#define MOTION_ID_H_

enum class MotionId
{
	PlayerIdle,			// �v���C���[�ҋ@��
	PlayerWalkForward,	// �v���C���[�O�������ړ�
	PlayerWalkBackward,	// �v���C���[��������ړ�
	PlayerWalkLeft,		// �v���C���[�������ړ�
	PlayerWalkRight,	// �v���C���[�������ړ�
	PlayerRunForward,	// �v���C���[�O������ړ�
	PlayerDodge,		// �v���C���[���
	PlayerDamage,		// �v���C���[�_���[�W
	PlayerDead,			// �v���C���[���S
	PlayerAttack1,		// �v���C���[���؂�
	PlayerAttack2,		// �v���C���[�c�؂�
	PlayerJumpAttack,	// �v���C���[�W�����v�؂�

	FighterEnemyIdle,			// �ߐڌ^�G�l�~�[�ҋ@��
	FighterEnemyStretchIdle,	// �ߐڌ^�G�l�~�[�ҋ@���L��
	FighterEnemyWalk,			// �ߐڌ^�G�l�~�[����
	FighterEnemyRun,			// �ߐڌ^�G�l�~�[����
	FighterEnemyPunch,			// �ߐڌ^�G�l�~�[�p���`
	FighterEnemySwiping,		// �ߐڌ^�G�l�~�[��U��p���`
	FighterEnemyJumpAttack,		// �ߐڌ^�G�l�~�[�W�����v�A�^�b�N
	FighterEnemyDamage,			// �ߐڌ^�G�l�~�[�_���[�W
	FighterEnemyDead,			// �ߐڌ^�G�l�~�[���S

	ShooterEnemyIdle,	// �������^�G�l�~�[�ҋ@��
	ShooterEnemyWalk,	// �������^�G�l�~�[����
	ShooterEnemyAttack,	// �������^�G�l�~�[�ߐڍU��
	ShooterEnemyShot,	// �������^�G�l�~�[�������U��
	ShooterEnemyDamage,	// �������^�G�l�~�[�_���[�W
	ShooterEnemyDead,	// �������^�G�l�~�[���S

	BossEnemyIlde,			// �{�X�^�G�l�~�[�ҋ@��
	BossEnemyRun,			// �{�X�^�G�l�~�[����
	BossEnemyNormalAttack,	// �{�X�^�G�l�~�[�ʏ�U��
	BossEnemyJumpAttack,	// �{�X�^�G�l�~�[�W�����v�U��
	BossEnemyRoolAttack,	// �{�X�^�G�l�~�[���[�����O�U��
	BossEnemyDown,			// �{�X�^�G�l�~�[���[�����O�����]��
	BossEnemyStandUp,		// �{�X�^�G�l�~�[�N���オ��
	BossEnemyDead,			// �{�X�^�G�l�~�[���S
};
#endif // !MOTION_ID_H_