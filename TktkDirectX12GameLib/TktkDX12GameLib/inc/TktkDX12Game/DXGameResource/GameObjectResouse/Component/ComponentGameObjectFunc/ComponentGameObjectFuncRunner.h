#ifndef COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_
#define COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_

/* class member */
#include "../ComponentBasePtr.h"
#include "../../../../EventMessage/MessageTypeCarrier.h"

namespace tktk
{
	struct ComponentGameObjectFuncVTable;
	class GameObjectPtr;
	class MessageAttachment;

	// �Q�[���I�u�W�F�N�g���g�p����R���|�[�l���g�̊֐������s����N���X
	class ComponentGameObjectFuncRunner
	{
	public:

		ComponentGameObjectFuncRunner(const ComponentBasePtr& componentPtr, ComponentGameObjectFuncVTable* vtablePtr);

	public:

		// �^�����B�������R���|�[�l���g�|�C���^���擾����
		const ComponentBasePtr& getComponentBasePtr() const;

		// ���b�Z�[�W�擾�֐����Ă�
		void runHandleMessage(MessageTypeCarrier type, const MessageAttachment& attachment) const;

		// �R���|�[�l���g�̐e�v�f���ς�������֐����Ă�
		void runAfterChangeParent(const GameObjectPtr& beforParent) const;

		// �R���|�[�l���g�̏ՓˊJ�n�֐����Ă�
		void runOnCollisionEnter(const GameObjectPtr& other) const;

		// �R���|�[�l���g�̏Փ˒��֐����Ă�
		void runOnCollisionStay(const GameObjectPtr& other) const;

		// �R���|�[�l���g�̏ՓˏI���֐����Ă�
		void runOnCollisionExit(const GameObjectPtr& other) const;

		// �R���|�[�l���g�̎��S�t���O���擾����
		bool isDead() const;

		// �R���|�[�l���g���E��
		void destroy() const;

	private:

		ComponentGameObjectFuncVTable*	m_vtablePtr;
		ComponentBasePtr				m_selfPtr;
	};
}
#endif // !COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_