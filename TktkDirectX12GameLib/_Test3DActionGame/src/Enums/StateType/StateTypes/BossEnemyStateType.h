#ifndef BOSS_ENEMY_STATE_TYPE_H_
#define BOSS_ENEMY_STATE_TYPE_H_

enum class BossEnemyStateType
{
	/* ��{��� */
	Alive,	// �����X�e�[�g
	Dead,	// ���S�X�e�[�g

	/* �����X�e�[�g */
	Normal,	// �ʏ�X�e�[�g
	Down,	// �_�E�����X�e�[�g

	/* �ʏ�X�e�[�g */
	Idle,			// �ҋ@�X�e�[�g
	Move,			// �ړ��X�e�[�g
	Attack,			// �U���X�e�[�g	

	/* �U���X�e�[�g */
	NormalAttack,	// �ʏ�U���X�e�[�g
	JumpAttack,		// �W�����v�U���X�e�[�g
	RollAttack,		// ���[�����O�U���X�e�[�g
	MissRool,		// ���s���[�����O�X�e�[�g

	/* �_�E�����X�e�[�g */
	CantMove,	// �ړ��s�\�X�e�[�g
	StandUp,	// �N���オ��X�e�[�g

	/* ����X�e�[�g */
	Damage,		// �_���[�W�X�e�[�g�͂ǂ̃X�e�[�g�Ƃ������ɑ��݂�����
};
#endif // !BOSS_ENEMY_STATE_TYPE_H_