#ifndef PLAYER_STATE_TYPE_H_
#define PLAYER_STATE_TYPE_H_

enum class PlayerStateType
{
	/* ��{��� */
	Normal,	// �ʏ�X�e�[�g
	Damage,	// ��_���[�W�X�e�[�g
	Dead,	// ���S�X�e�[�g

	/* �ʏ�X�e�[�g */
	Move,	// �ړ��X�e�[�g
	Attack,	// �U���X�e�[�g

	/* �ړ��X�e�[�g */
	Idle,			// �ҋ@�X�e�[�g
	WalkForward,	// �O���ړ��X�e�[�g
	WalkBackward,	// ����ړ����e�[�g
	WalkLeft,		// ���ړ��X�e�[�g
	WalkRight,		// �E�ړ��X�e�[�g
	RunForward,		// �O���ړ��X�e�[�g

	/* �U���X�e�[�g */
	Attack1,		// ��i�U���X�e�[�g
	Attack2,		// ��i�U���X�e�[�g	
	JumpAttack,		// �W�����v�U���X�e�[�g
};
#endif // !PLAYER_STATE_TYPE_H_