#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <memory>	// std::smart_ptr
#include <utility>	// std::forward
#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../Component/ComponentGameObjectFunc/GameObjectComponentList.h"
#include "../_MainManager/DX12GameManager.h"
#include "../Component/ComponentPtr.h"
#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateMachineListInitParam.h"

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
		template<class TagType, is_idType<TagType> = nullptr>
		void addGameObjectTag(TagType tag) { addGameObjectTagImpl(static_cast<int>(tag)); }

		// �����̃^�O���폜����
		template<class TagType, is_idType<TagType> = nullptr>
		void removeGameobjectTag(TagType tag) { removeGameobjectTagImpl(static_cast<int>(tag)); }

		// �����̃^�O�������Ă��邩�̔�����s��
		template<class TagType, is_idType<TagType> = nullptr>
		bool containGameobjectTag(TagType tag) const { return containGameobjectTagImpl(static_cast<int>(tag)); }

	public: /* �R���|�[�l���g�擾���� */

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		// ��������R���|�[�l���g�͎��̃t���[���̓��ɒǉ������
		template <class ComponentType, class... Args>
		ComponentPtr<ComponentType> createComponent(Args&&... args) { return m_componentList->add<ComponentType>(DX12GameManager::createComponent<ComponentType>(GameObjectPtr(weak_from_this()), std::forward<Args>(args)...)); }

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������Ă�����擾���A�����Ă��Ȃ�������nullptr��Ԃ�
		// �����������^�̃R���|�[�l���g���������Ă����ꍇ�A�ŏ��Ɍ������P���擾����
		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const { return m_componentList->find<ComponentType>(); }

		// �e���v���[�g�����̌^�̃R���|�[�l���g��S�Ď擾����
		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> getComponents() const { return m_componentList->findAll<ComponentType>(); }

	public: /* �R���|�[�l���g�֐��Ăяo������ */

		// �S�Ẵ��b�Z�[�W�擾�֐����Ă�
		void runHandleMessageAll(unsigned int messageId, const MessageAttachment& value);

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
		template<class TagType, is_idType<TagType> = nullptr>
		GameObjectPtr findChildWithTag(TagType tag) const { return findChildWithTagImpl(static_cast<int>(tag)); }

		// ���g�̎q�v�f��������̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		template<class TagType, is_idType<TagType> = nullptr>
		std::forward_list<GameObjectPtr> findChildrenWithTag(TagType tag) const { return findChildrenWithTagImpl(static_cast<int>(tag)); }

		// �q�v�f�����X�g�ɒǉ�����
		void addChild(const GameObjectPtr& child);

		// �w�肵���q�v�f�����X�g����폜����
		void removeChild(const GameObjectPtr& child);

		// �S�Ă̎q�v�f�Ƀ��b�Z�[�W�𑗐M����
		void sendMessage(unsigned int messageId, const MessageAttachment& value = {});

	public: /* �X�e�[�g�}�V���֌W���� */

		// �X�e�[�g�̎�ނ������Ƃ��ēn���A�X�e�[�g�}�V���̑���ɕK�v�ȃR���|�[�l���g����������
		void setupStateMachine(const StateMachineListInitParam& initParam);

		// �X�e�[�g��L���ɂ���
		template <class StateIdType>
		void stateEnable(StateIdType stateType) { stateEnableImpl(static_cast<int>(stateType)); };

		// �X�e�[�g�𖳌��ɂ���
		template <class StateIdType>
		void stateDisable(StateIdType stateType) { stateDisableImpl(static_cast<int>(stateType)); };

		// �S�ẴX�e�[�g�𖳌��ɂ���
		void clearState();

		// �����̃X�e�[�g�������Ă��邩�H
		template <class StateIdType>
		bool containState(StateIdType stateType) { return containStateImpl(static_cast<int>(stateType)); };

		// �X�e�[�g���w�肵�A�q�v�f��ǉ�����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		void addChild(std::initializer_list<StateIdType> targetState, const GameObjectPtr& child);

		// �X�e�[�g���w�肵�A�e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		//  ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class ComponentType, class StateIdType, class... Args>
		ComponentPtr<ComponentType> createComponent(std::initializer_list<StateIdType> targetState, Args&&... args);

		// �X�e�[�g���w�肵�A�X�e�[�g��ύX����^�C�}�[�����
		//  ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		ComponentPtr<StateChangeTimer> createStateChangeTimer(std::initializer_list<StateIdType> targetState, float stateChangeTimeSec, std::initializer_list<StateIdType> enableStates, std::initializer_list<StateIdType> disableStates);

		// �X�e�[�g���w�肵�A���b�Z�[�W��M���ɃX�e�[�g��ύX����R���|�[�l���g�����
		//  ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class MessageType, class StateIdType>
		ComponentPtr<MessageStateChanger> createMessageStateChanger(std::initializer_list<StateIdType> targetState, MessageType messageType, std::initializer_list<StateIdType> enableStates, std::initializer_list<StateIdType> disableStates);

		// �q�v�f���w��̃X�e�[�g�ɒǉ�����i��addChild(targetState, child)�̓��������j
		void setChildToStateMachine(const std::vector<int>& targetState, const GameObjectPtr& child);

		// �R���|�[�l���g���w��̃X�e�[�g�ɒǉ�����i��createComponent<ComponentType>(targetState, args...)�̓��������j
		void setComponentToStateMachine(const std::vector<int>& targetState, const ComponentBasePtr& componentPtr);

	private:

		void addGameObjectTagImpl(int tag);
		void removeGameobjectTagImpl(int tag);
		bool containGameobjectTagImpl(int tag) const;
		GameObjectPtr findChildWithTagImpl(int tag) const;
		std::forward_list<GameObjectPtr> findChildrenWithTagImpl(int tag) const;
		void stateEnableImpl(int stateType);
		void stateDisableImpl(int stateType);
		bool containStateImpl(int stateType);
		ComponentPtr<StateChangeTimer> createStateChangeTimerImpl(const std::vector<int>& targetState, float stateChangeTimeSec, const std::vector<int>& enableStateArray, const std::vector<int>& disableStateArray);
		ComponentPtr<MessageStateChanger> createMessageStateChanger(const std::vector<int>& targetState, unsigned int messageType, const std::vector<int>& enableStateArray, const std::vector<int>& disableStateArray);

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

	public:

		// �s���Ȍ^�������Ƃ��ēn���ꂽ���̏���
		template<class TagType, is_not_idType<TagType> = nullptr>
		void addGameObjectTag(TagType tag)				{ static_assert(false, "TagType Fraud Type"); }
		template<class TagType, is_not_idType<TagType> = nullptr>
		void removeGameobjectTag(TagType tag)			{ static_assert(false, "TagType Fraud Type"); }
		template<class TagType, is_not_idType<TagType> = nullptr>
		bool containGameobjectTag(TagType tag) const	{ static_assert(false, "TagType Fraud Type"); }
		template<class TagType, is_not_idType<TagType> = nullptr>
		GameObjectPtr findChildWithTag(TagType tag) const						{ static_assert(false, "TagType Fraud Type"); }
		template<class TagType, is_not_idType<TagType> = nullptr>
		std::forward_list<GameObjectPtr> findChildrenWithTag(TagType tag) const { static_assert(false, "TagType Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�q�v�f��ǉ�����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline void GameObject::addChild(std::initializer_list<StateIdType> targetState, const GameObjectPtr& child)
	{
		// �w�肵���X�e�[�g��int�^�ɃL���X�g����
		auto targetStateArray		= std::vector<StateIdType>(targetState);
		auto intTargetStateArray	= std::vector<int>();
		intTargetStateArray.reserve(targetStateArray.size());
		for (const auto& node : targetStateArray) intTargetStateArray.push_back(static_cast<int>(node));

		setChildToStateMachine(intTargetStateArray, child);
	}

	// �X�e�[�g���w�肵�A�e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
	//  ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class ComponentType, class StateIdType, class ...Args>
	inline ComponentPtr<ComponentType> GameObject::createComponent(std::initializer_list<StateIdType> targetState, Args&& ...args)
	{
		// �w�肵���X�e�[�g��int�^�ɃL���X�g����
		auto targetStateArray = std::vector<StateIdType>(targetState);
		auto intTargetStateArray = std::vector<int>();
		intTargetStateArray.reserve(targetStateArray.size());
		for (const auto& node : targetStateArray) intTargetStateArray.push_back(static_cast<int>(node));

		auto createdComponent = DX12GameManager::createComponent<ComponentType>(GameObjectPtr(weak_from_this()), std::forward<Args>(args)...);
		createdComponent.lock()->setUser(GameObjectPtr(weak_from_this()));
		setComponentToStateMachine(intTargetStateArray, ComponentBasePtr(createdComponent));
		return m_componentList->add<ComponentType>(createdComponent);
	}

	// �X�e�[�g���w�肵�A�X�e�[�g��ύX����^�C�}�[�����
	//  ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline ComponentPtr<StateChangeTimer> GameObject::createStateChangeTimer(std::initializer_list<StateIdType> targetState, float stateChangeTimeSec, std::initializer_list<StateIdType> enableStates, std::initializer_list<StateIdType> disableStates)
	{
		// �w�肵���X�e�[�g��int�^�ɃL���X�g����
		auto targetStateArray = std::vector<StateIdType>(targetState);
		auto intTargetStateArray = std::vector<int>();
		intTargetStateArray.reserve(targetStateArray.size());
		for (const auto& node : targetStateArray) intTargetStateArray.push_back(static_cast<int>(node));

		// �L���ɂ���X�e�[�g��int�^�ɃL���X�g����
		auto enableStateArray	= std::vector<StateIdType>(enableStates);
		auto intEnableStateArray = std::vector<int>();
		intEnableStateArray.reserve(enableStateArray.size());
		for (const auto& node : enableStateArray) intEnableStateArray.push_back(static_cast<int>(node));

		// �����ɂ���X�e�[�g��int�^�ɃL���X�g
		auto disableStateArray = std::vector<StateIdType>(disableStates);
		auto intDisableStateArray = std::vector<int>();
		intDisableStateArray.reserve(disableStateArray.size());
		for (const auto& node : disableStateArray) intDisableStateArray.push_back(static_cast<int>(node));

		return createStateChangeTimerImpl(intTargetStateArray, stateChangeTimeSec, intEnableStateArray, intDisableStateArray);
	}

	// �X�e�[�g���w�肵�A���b�Z�[�W��M���ɃX�e�[�g��ύX����R���|�[�l���g�����
		//  ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class MessageType, class StateIdType>
	inline ComponentPtr<MessageStateChanger> GameObject::createMessageStateChanger(std::initializer_list<StateIdType> targetState, MessageType stateChangeTimeSec, std::initializer_list<StateIdType> enableStates, std::initializer_list<StateIdType> disableStates)
	{
		// �w�肵���X�e�[�g��int�^�ɃL���X�g����
		auto targetStateArray = std::vector<StateIdType>(targetState);
		auto intTargetStateArray = std::vector<int>();
		intTargetStateArray.reserve(targetStateArray.size());
		for (const auto& node : targetStateArray) intTargetStateArray.push_back(static_cast<int>(node));

		// �L���ɂ���X�e�[�g��int�^�ɃL���X�g����
		auto enableStateArray = std::vector<StateIdType>(enableStates);
		auto intEnableStateArray = std::vector<int>();
		intEnableStateArray.reserve(enableStateArray.size());
		for (const auto& node : enableStateArray) intEnableStateArray.push_back(static_cast<int>(node));

		// �����ɂ���X�e�[�g��int�^�ɃL���X�g
		auto disableStateArray = std::vector<StateIdType>(disableStates);
		auto intDisableStateArray = std::vector<int>();
		intDisableStateArray.reserve(disableStateArray.size());
		for (const auto& node : disableStateArray) intDisableStateArray.push_back(static_cast<int>(node));

		return createStateChangeTimerImpl(intTargetStateArray, stateChangeTimeSec, intEnableStateArray, intDisableStateArray);

		return ComponentPtr<StateChangeTimer>();
	}
}
#endif // !GAME_OBJECT_H_