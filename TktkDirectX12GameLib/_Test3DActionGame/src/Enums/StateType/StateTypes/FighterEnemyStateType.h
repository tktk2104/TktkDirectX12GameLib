#ifndef FIGHTER_ENEMY_STATE_TYPE_H_
#define FIGHTER_ENEMY_STATE_TYPE_H_

// �ߐڍU���G�l�~�[�̏�Ԃ̎��
enum class FighterEnemyState
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
	
	/* �ړ��X�e�[�g */
	Walk,	// �����X�e�[�g
	Run,	// ����X�e�[�g

	/* �U���X�e�[�g */
	Punch,		// �p���`�U���X�e�[�g
	Swiping,	// �X���C�v�U���X�e�[�g
	JumpAttack,	// �W�����v�U���X�e�[�g
};
#endif // !FIGHTER_ENEMY_STATE_TYPE_H_