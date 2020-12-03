#ifndef GAME_OBJECT_RESOUSE_H_
#define GAME_OBJECT_RESOUSE_H_

/* std::unique_ptr */
#include <memory>

/* std::type_index */
#include <typeindex>

/* std::forward_list */
#include <forward_list>

/* funcUseType */
#include "GameObject/GameObjectPtr.h"
#include "GameObject/GameObjectTagCarrier.h"
#include "../../EventMessage/MessageTypeCarrier.h"
#include "Component/ComponentCollisionFunc/CollisionGroupTypeCarrier.h"
#include "Component/ComponentBasePtr.h"

namespace tktk
{
	class GameObjectManager;
	class ComponentManager;
	class MessageAttachment;
	struct ComponentListVTable;
	struct ComponentVTableBundle;
	class ComponentBase;

	// �Q�[���I�u�W�F�N�g�Ɋ֌W���郊�\�[�X���Ǘ�����N���X
	class GameObjectResouse
	{
	public:

		GameObjectResouse();
		~GameObjectResouse();

	public:

		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�ɒǉ�����
		void movePreFrameAddedNode();

		// �X�V����
		void update();

		// ���񂾃C���X�^���X���폜����
		void removeDeadInstance();

		// �`�揈��
		void draw();

	public: /* �Q�[���I�u�W�F�N�g�֌W�̏��� */

		// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
		void runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment);

		// �Q�[���I�u�W�F�N�g���쐬���A���̃|�C���^��Ԃ�
		GameObjectPtr createGameObject();

		// �����̃^�O���������Q�[���I�u�W�F�N�g���擾����
		// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
		GameObjectPtr findGameObjectWithTag(GameObjectTagCarrier tag) const;

		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagCarrier tag) const;

		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�č폜����
		void destroyGameObjectsWithTag(GameObjectTagCarrier tag);

	public: /* �R���|�[�l���g�֌W�̏��� */

		// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x��ݒ肷��
		// ���f�t�H���g�i0.0f�j�Œl�����������A�������s�����
		void addRunFuncPriority(std::type_index type, float priority);

		// �Փ˔���̑g�ݍ��킹��ǉ�����
		void addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup);

		// �����̃R���|�[�l���g��ǉ�����
		ComponentBasePtr addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const GameObjectPtr& user, const std::shared_ptr<ComponentBase>& componentPtr);

	private:

		std::unique_ptr<GameObjectManager>	m_gameObjectManager;
		std::unique_ptr<ComponentManager>	m_componentManager;
	};
}
#endif // !GAME_OBJECT_RESOUSE_H_