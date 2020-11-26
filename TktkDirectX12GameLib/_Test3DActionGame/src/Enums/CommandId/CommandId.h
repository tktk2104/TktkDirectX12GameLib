#ifndef COMMAND_ID_H_
#define COMMAND_ID_H_

enum class CommandId
{
	Any,			// �����ꂩ�̓���

	MoveForward,	// �O���ړ�
	MoveBackward,	// ����ړ�
	MoveLeft,		// ���ړ�
	MoveRight,		// �E�ړ�

	LookLeft,		// �E���_�ړ�
	LookRight,		// �����_�ړ�

	Run,			// ����ړ�

	Attack,			// �U��
};
#endif // !COMMAND_ID_H_