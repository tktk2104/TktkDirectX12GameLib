#ifndef COMMAND_ID_H_
#define COMMAND_ID_H_

// �v���C���[���s���鑀��̎��
enum class CommandId
{
	Any,			// �����ꂩ�̓���

	MoveForward,	// �O���ړ�
	MoveBackward,	// ����ړ�
	MoveLeft,		// ���ړ�
	MoveRight,		// �E�ړ�

	LookLeft,		// �E���_�ړ�
	LookRight,		// �����_�ړ�

	LookEnemy,		// �G������

	Run,			// ����ړ�

	Dodge,			// ���

	Attack,			// �U��
};
#endif // !COMMAND_ID_H_