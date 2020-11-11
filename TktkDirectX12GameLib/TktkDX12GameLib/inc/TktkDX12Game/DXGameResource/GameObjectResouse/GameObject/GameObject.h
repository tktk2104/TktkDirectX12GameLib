#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

/* std::type_index */
#include <typeindex>

/* std::unique_ptr */
#include <memory>

/* std::forward_list */
#include <forward_list>

/* ComponentGameObjectFuncVTable */
#include "../Component/ComponentVTable.h"
#include "../Component/ComponentMainList/ComponentListVTable.h"

/* funcArgs */
#include "GameObjectTagCarrier.h"
#include "../../../EventMessage/MessageTypeCarrier.h"
#include "../../../EventMessage/MessageAttachment.h"
#include "../Component/DefaultComponents/StateMachine/Structs/StateMachineListInitParam.h"
#include "../Component/DefaultComponents/StateMachine/Structs/StateTypeCarrier.h"
#include "../Component/DefaultComponents/StateMachine/Structs/StateTypeHierarchy.h"
#include "../Component/DefaultComponents/StateMachine/Structs/StateTypeList.h"

/* ComponentPtr */
#include "../Component/ComponentBasePtr.h"
#include "../Component/ComponentPtr.h"

namespace tktk
{
	/* class member */
	class GameObjectTagList;
	class GameObjectComponentList;
	class StateMachineList;
	class ParentChildManager;
	class CurStateTypeList;
	
	/* funcUseType */
	class GameObjectPtr;

	// �Q�[���I�u�W�F�N�g�N���X
	class GameObject
		: public std::enable_shared_from_this<GameObject>
	{
	public:

		GameObject();
		~GameObject();

	public:

		void update();

	//************************************************************
	public: /* �t���O�Ǘ��֐� */

		// �A�N�e�B�u�t���O��ݒ肷��
		// ��false��ݒ肷��ƁA��������R���|�[�l���g�A�q�v�f�̃Q�[���I�u�W�F�N�g����A�N�e�B�u��ԂɂȂ�
		void setActive(bool activeFlag);

		// �I�u�W�F�N�g���폜����
		// ����������R���|�[�l���g�A�q�v�f�̃Q�[���I�u�W�F�N�g���폜�����
		void destroy();

		// �A�N�e�B�u�t���O���擾����
		bool isActive() const;

		// ���S�t���O���擾����
		bool isDead() const;

	//************************************************************
	public: /* �^�O�Ǘ��֐� */

		// ���g�̃^�O��ǉ�����
		void addGameObjectTag(GameObjectTagCarrier tag);

		// �����̃^�O���폜����
		void removeGameobjectTag(GameObjectTagCarrier tag);

		// �����̃^�O�������Ă��邩�̔�����s��
		bool containGameobjectTag(GameObjectTagCarrier tag) const;

	//************************************************************
	public: /* �R���|�[�l���g�擾���� */

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		// ��������R���|�[�l���g�͎��̃t���[���̓��ɒǉ������
		template <class ComponentType, class... Args>
		ComponentPtr<ComponentType> createComponent(Args&&... args)
		{
			auto basePtr = addComponent(typeid(ComponentType), &ComponentVTableInitializer<ComponentType>::m_componentVTableBundle, &ComponentListVTableInitializer<ComponentType>::m_componentListVTable, std::make_shared<ComponentType>(std::forward<Args>(args)...));
			return basePtr.castPtr<ComponentType>();
		}

		// �����̃R���|�[�l���g�����g�ɒǉ�����
		// ���ǉ������R���|�[�l���g�͎��̃t���[���̓��ɒǉ������
		ComponentBasePtr addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const std::shared_ptr<ComponentBase>& componentPtr);

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������Ă�����擾���A�����Ă��Ȃ�������nullptr��Ԃ�
		// �����������^�̃R���|�[�l���g���������Ă����ꍇ�A�ŏ��Ɍ������P���擾����
		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const { return getComponent(typeid(ComponentType)).castPtr<ComponentType>(); }

		// �����̌^�̃R���|�[�l���g���擾����
		// ���擾�ł��Ȃ�������nullptr��Ԃ�
		// �������Y������R���|�[�l���g����������ŏ��Ɍ������P��Ԃ�
		ComponentBasePtr getComponent(std::type_index type) const;

		// �e���v���[�g�����̌^�̃R���|�[�l���g��S�Ď擾����
		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> getComponents() const
		{
			std::forward_list<ComponentPtr<ComponentType>> castPtrList;
		
			for (const auto& basePtr : getComponents(typeid(ComponentType)))
			{
				castPtrList.push_front(basePtr.castPtr<ComponentType>);
			}
			return castPtrList;
		}

		// �����̌^�̃R���|�[�l���g��S�Ď擾����
		std::forward_list<ComponentBasePtr> getComponents(std::type_index type) const;

	//************************************************************
	public: /* �R���|�[�l���g�֐��Ăяo������ */

		// �S�Ẵ��b�Z�[�W�擾�֐����Ă�
		void runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment);

		// �S�Ă̎q���̑S�ẴR���|�[�l���g�̐e�v�f���ς�������֐����Ă�
		void runAfterChangeParentAll(const GameObjectPtr& beforParent);

		// �S�ẴR���|�[�l���g�̏ՓˊJ�n�֐����Ă�
		void runOnCollisionEnterAll(const GameObjectPtr& other);

		// �S�ẴR���|�[�l���g�̏Փ˒��֐����Ă�
		void runOnCollisionStayAll(const GameObjectPtr& other);

		// �S�ẴR���|�[�l���g�̏ՓˏI���֐����Ă�
		void runOnCollisionExitAll(const GameObjectPtr& other);

	//************************************************************
	public: /* �e�q�֌W���� */

		// �e�v�f���擾
		const GameObjectPtr& getParent() const;

		// �e�v�f��ݒ�
		void setParent(const GameObjectPtr& parent);

		// �q�v�f�̃��X�g���擾
		const std::forward_list<GameObjectPtr>& getChildren() const;

		// ���g�̎q�v�f��������̃^�O���������Q�[���I�u�W�F�N�g���擾����
		// ���Y���I�u�W�F�N�g�����������ꍇ�A���GameObjectPtr���擾����
		// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
		GameObjectPtr findChildWithTag(GameObjectTagCarrier tag) const;

		// ���g�̎q�v�f��������̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		std::forward_list<GameObjectPtr> findChildrenWithTag(GameObjectTagCarrier tag) const;

		// �q�v�f�����X�g�ɒǉ�����
		void addChild(const GameObjectPtr& child);

		// �w�肵���q�v�f�����X�g����폜����
		void removeChild(const GameObjectPtr& child);

		// �S�Ă̎q�v�f�Ƀ��b�Z�[�W�𑗐M����
		void sendMessage(MessageTypeCarrier type, const MessageAttachment& attachment = {});

	//************************************************************
	public: /* �X�e�[�g�}�V���֌W���� */

		// �X�e�[�g�̎�ނ������Ƃ��ēn���A�X�e�[�g�}�V���̑���ɕK�v�ȃR���|�[�l���g����������
		void setupStateMachine(const StateMachineListInitParam& initParam);

		// �q�v�f�A�R���|�[�l���g��ǉ�����X�e�[�g�̊K�w��ݒ肷��
		// �����ケ�̊֐����ĂьĂ΂��܂Œǉ�����X�e�[�g�̊K�w���Œ肳���
		void setTargetHierarchy(const StateTypeHierarchy& targetHierarchy);

		// �X�e�[�g��L���ɂ���
		void stateEnable(StateTypeCarrier stateType);

		// �X�e�[�g�𖳌��ɂ���
		void stateDisable(StateTypeCarrier stateType);

		// �S�ẴX�e�[�g�𖳌��ɂ���
		void clearState();

		// �����̃X�e�[�g�������Ă��邩�H
		bool containState(StateTypeCarrier stateType);

	private:

		bool m_isActive				{ true };
		bool m_nextFrameActive		{ true };
		bool m_isDead				{ false };

		std::unique_ptr<GameObjectTagList>		 m_tagList			{};
		std::unique_ptr<GameObjectComponentList> m_componentList	{};	// ���e���v���[�g�֐����g�p���邽�߁A�O���錾�s��
		std::unique_ptr<StateMachineList>		 m_stateMachineList	{};
		
		// �f�t�H���g�R���|�[�l���g
		ComponentPtr<ParentChildManager>		m_parentChildManager{};
		ComponentPtr<CurStateTypeList>			m_stateTypeList		{};
	};
}
#endif // !GAME_OBJECT_H_