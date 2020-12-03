#ifndef GAME_OBJECT_COMPONENT_LIST_H_
#define GAME_OBJECT_COMPONENT_LIST_H_

/* std::type_index */
#include <typeindex>

/* std::forward_list */
#include <forward_list>

/* class member */
#include "../ComponentBasePtr.h"
#include "../../../../EventMessage/MessageTypeCarrier.h"

namespace tktk
{
	class ComponentGameObjectFuncRunner;
	struct ComponentGameObjectFuncVTable;
	class MessageAttachment;
	class GameObjectPtr;

	// �Q�[���I�u�W�F�N�g�������Ă���R���|�[�l���g�̃��X�g
	class GameObjectComponentList
	{
	public:

		GameObjectComponentList();
		~GameObjectComponentList();

	public:

		// �V���ȃR���|�[�l���g��ǉ�����
		void add(const ComponentBasePtr& componentPtr, ComponentGameObjectFuncVTable* vtablePtr);

		// �����̌^�̃R���|�[�l���g���擾����
		// ���擾�ł��Ȃ�������nullptr��Ԃ�
		// �������Y������R���|�[�l���g����������ŏ��Ɍ������P��Ԃ�
		ComponentBasePtr find(std::type_index type) const;

		// �����̌^�̃R���|�[�l���g��S�Ď擾����
		std::forward_list<ComponentBasePtr> findAll(std::type_index type) const;

		// �S�Ẵ��b�Z�[�W�擾�֐����Ă�
		void runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment) const;

		// �S�Ắu�q���̑S�ẴR���|�[�l���g�̐e�v�f���ς�������֐��v���Ă�
		void runAfterChangeParentAll(const GameObjectPtr& beforParent) const;

		// �S�ẴR���|�[�l���g�̏ՓˊJ�n�֐����Ă�
		void runOnCollisionEnterAll(const GameObjectPtr& other);

		// �S�ẴR���|�[�l���g�̏Փ˒��֐����Ă�
		void runOnCollisionStayAll(const GameObjectPtr& other);

		// �S�ẴR���|�[�l���g�̏ՓˏI���֐����Ă�
		void runOnCollisionExitAll(const GameObjectPtr& other);

		// ���݂̃t���[���ŏՓˏ������s�����I�u�W�F�N�g���X�g���N���A����
		void clearHitObjectList();

		// �S�ẴR���|�[�l���g���E��
		void destroyAll() const;

		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�ɒǉ�����
		void movePreFrameAddedNode();

		// ���S�t���O�������Ă���R���|�[�l���g���폜����
		void removeDeadComponent();

	private:

		std::forward_list<GameObjectPtr> m_curFrameHitObjectList;
		std::forward_list<ComponentGameObjectFuncRunner> m_componentList;
		std::forward_list<ComponentGameObjectFuncRunner> m_nextFrameAddNodeList;
	};
}
#endif // !GAME_OBJECT_COMPONENT_LIST_H_
