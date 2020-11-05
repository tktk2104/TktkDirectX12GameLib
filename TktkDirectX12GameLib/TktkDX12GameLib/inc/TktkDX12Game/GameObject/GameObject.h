#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

/* std::unique_ptr */
#include <memory>

/* std::forward */
#include <utility>

/* createComponent() */
#include "../_MainManager/DX12GameManager.h"

/* use templateFunc */
#include "../Component/ComponentGameObjectFunc/GameObjectComponentList.h"

/* funcArgs */
#include "GameObjectTagCarrier.h"
#include "../EventMessage/MessageTypeCarrier.h"
#include "../Component/DefaultComponents/StateMachine/StateMachineListInitParam.h"
#include "../Component/DefaultComponents/StateMachine/StateTypeCarrier.h"
#include "../Component/DefaultComponents/StateMachine/StateTypeHierarchy.h"
#include "../Component/DefaultComponents/StateMachine/StateTypeList.h"

/* ComponentPtr */
#include "../Component/ComponentPtr.h"

namespace tktk
{
	// �O���錾�B
	class GameObjectTagList;
	class StateMachineList;
	class ParentChildManager;
	class CurStateTypeList;
	class StateChangeTimer;
	class MessageStateChanger;
	
	// �Q�[���I�u�W�F�N�g�N���X
	class GameObject
		: public std::enable_shared_from_this<GameObject>
	{
	public:

		GameObject();
		~GameObject();

	public:

		void update();

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

	public: /* �^�O�Ǘ��֐� */

		// ���g�̃^�O��ǉ�����
		void addGameObjectTag(GameObjectTagCarrier tag);

		// �����̃^�O���폜����
		void removeGameobjectTag(GameObjectTagCarrier tag);

		// �����̃^�O�������Ă��邩�̔�����s��
		bool containGameobjectTag(GameObjectTagCarrier tag) const;

	public: /* �R���|�[�l���g�擾���� */

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		// ��������R���|�[�l���g�͎��̃t���[���̓��ɒǉ������
		template <class ComponentType, class... Args>
		ComponentPtr<ComponentType> createComponent(Args&&... args)				{ return m_componentList->add<ComponentType>(DX12GameManager::createComponent<ComponentType>(GameObjectPtr(weak_from_this()), std::forward<Args>(args)...)); }

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������Ă�����擾���A�����Ă��Ȃ�������nullptr��Ԃ�
		// �����������^�̃R���|�[�l���g���������Ă����ꍇ�A�ŏ��Ɍ������P���擾����
		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const						{ return m_componentList->find<ComponentType>(); }

		// �e���v���[�g�����̌^�̃R���|�[�l���g��S�Ď擾����
		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> getComponents() const	{ return m_componentList->findAll<ComponentType>(); }

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

	public: /* �X�e�[�g�}�V���֌W���� */

		// �X�e�[�g�̎�ނ������Ƃ��ēn���A�X�e�[�g�}�V���̑���ɕK�v�ȃR���|�[�l���g����������
		void setupStateMachine(const StateMachineListInitParam& initParam);

		// �X�e�[�g��L���ɂ���
		void stateEnable(StateTypeCarrier stateType);

		// �X�e�[�g�𖳌��ɂ���
		void stateDisable(StateTypeCarrier stateType);

		// �X�e�[�g���w�肵�A���̎q�v�f�ɐݒ肳��Ă���X�e�[�g��S�ėL���ɂ���
		void childStateEnable(const StateTypeHierarchy& targetState);

		// �X�e�[�g���w�肵�A���̎q�v�f�ɐݒ肳��Ă���X�e�[�g��S�Ė����ɂ���
		void childStateDisable(const StateTypeHierarchy& targetState);

		// �S�ẴX�e�[�g�𖳌��ɂ���
		void clearState();

		// �����̃X�e�[�g�������Ă��邩�H
		bool containState(StateTypeCarrier stateType);

		// �X�e�[�g���w�肵�A�q�v�f��ǉ�����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		void addChild(const StateTypeHierarchy& targetState, const GameObjectPtr& child);

		// �X�e�[�g���w�肵�A�e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		//  ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class ComponentType, class... Args>
		ComponentPtr<ComponentType> createComponentAndSetToState(const StateTypeHierarchy& targetState, Args&&... args)
		{
			auto createdComponent = createComponent<ComponentType>(std::forward<Args>(args)...);
			setComponentToStateMachine(targetState, createdComponent);
			return createdComponent;
		}

		// �X�e�[�g���w�肵�A�X�e�[�g��ύX����^�C�}�[�����
		//  ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		ComponentPtr<StateChangeTimer> createStateChangeTimer(const StateTypeHierarchy& targetState, float stateChangeTimeSec, const StateTypeList& enableStates, const StateTypeList& disableStates);

		// �X�e�[�g���w�肵�A���b�Z�[�W��M���ɃX�e�[�g��ύX����R���|�[�l���g�����
		//  ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		ComponentPtr<MessageStateChanger> createMessageStateChanger(const StateTypeHierarchy& targetState, MessageTypeCarrier messageType, const StateTypeList& enableStates, const StateTypeList& disableStates);

		// �R���|�[�l���g���w��̃X�e�[�g�ɒǉ�����i��createComponent<ComponentType>(targetState, args...)�̓��������j
		void setComponentToStateMachine(const StateTypeHierarchy& targetState, const ComponentBasePtr& componentPtr);

	private:

		bool												m_isActive				{ true };
		bool												m_nextFrameActive		{ true };
		bool												m_isDead				{ false };
		std::unique_ptr<GameObjectTagList>					m_tagList				{};
		std::unique_ptr<GameObjectComponentList>			m_componentList			{};	// ���e���v���[�g�֐����g�p���邽�߁A�O���錾�s��
		std::unique_ptr<StateMachineList>					m_stateMachineList		{};
		
		// �f�t�H���g�R���|�[�l���g
		ComponentPtr<ParentChildManager>					m_parentChildManager	{};
		ComponentPtr<CurStateTypeList>						m_stateTypeList			{};
	};
}
#endif // !GAME_OBJECT_H_