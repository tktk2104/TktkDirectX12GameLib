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
	// 前方宣言達
	class GameObjectTagList;
	class StateMachineList;
	class ParentChildManager;
	class CurStateTypeList;
	class StateChangeTimer;
	class MessageStateChanger;
	
	// ゲームオブジェクトクラス
	class GameObject
		: public std::enable_shared_from_this<GameObject>
	{
	public:

		GameObject();
		~GameObject();

	public:

		void update();

	public: /* フラグ管理関数 */

		// アクティブフラグを設定する
		// ※falseを設定すると、所持するコンポーネント、子要素のゲームオブジェクトが非アクティブ状態になる
		void setActive(bool activeFlag);

		// オブジェクトを削除する
		// ※所持するコンポーネント、子要素のゲームオブジェクトが削除される
		void destroy();

		// アクティブフラグを取得する
		bool isActive() const;

		// 死亡フラグを取得する
		bool isDead() const;

	public: /* タグ管理関数 */

		// 自身のタグを追加する
		template<class TagType, is_idType<TagType> = nullptr>
		void addGameObjectTag(TagType tag) { addGameObjectTagImpl(static_cast<int>(tag)); }

		// 引数のタグを削除する
		template<class TagType, is_idType<TagType> = nullptr>
		void removeGameobjectTag(TagType tag) { removeGameobjectTagImpl(static_cast<int>(tag)); }

		// 引数のタグを持っているかの判定を行う
		template<class TagType, is_idType<TagType> = nullptr>
		bool containGameobjectTag(TagType tag) const { return containGameobjectTagImpl(static_cast<int>(tag)); }

	public: /* コンポーネント取得処理 */

		// テンプレート引数の型のコンポーネントを引数の値を使って作る
		// ※作ったコンポーネントは次のフレームの頭に追加される
		template <class ComponentType, class... Args>
		ComponentPtr<ComponentType> createComponent(Args&&... args) { return m_componentList->add<ComponentType>(DX12GameManager::createComponent<ComponentType>(GameObjectPtr(weak_from_this()), std::forward<Args>(args)...)); }

		// テンプレート引数の型のコンポーネントを持っていたら取得し、持っていなかったらnullptrを返す
		// ※複数同じ型のコンポーネントを所持していた場合、最初に見つけた１つを取得する
		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const { return m_componentList->find<ComponentType>(); }

		// テンプレート引数の型のコンポーネントを全て取得する
		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> getComponents() const { return m_componentList->findAll<ComponentType>(); }

	public: /* コンポーネント関数呼び出し処理 */

		// 全てのメッセージ取得関数を呼ぶ
		void runHandleMessageAll(unsigned int messageId, const MessageAttachment& value);

		// 全ての子供の全てのコンポーネントの親要素が変わった時関数を呼ぶ
		void runAfterChangeParentAll(const GameObjectPtr& beforParent);

		// 全てのコンポーネントの衝突開始関数を呼ぶ
		void runOnCollisionEnterAll(const GameObjectPtr& other);

		// 全てのコンポーネントの衝突中関数を呼ぶ
		void runOnCollisionStayAll(const GameObjectPtr& other);

		// 全てのコンポーネントの衝突終了関数を呼ぶ
		void runOnCollisionExitAll(const GameObjectPtr& other);

	public: /* 親子関係処理 */

		// 親要素を取得
		const GameObjectPtr& getParent() const;

		// 親要素を設定
		void setParent(const GameObjectPtr& parent);

		// 子要素のリストを取得
		const std::forward_list<GameObjectPtr>& getChildren() const;

		// 自身の子要素から引数のタグを持ったゲームオブジェクトを取得する
		// ※該当オブジェクトが無かった場合、空のGameObjectPtrを取得する
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		template<class TagType, is_idType<TagType> = nullptr>
		GameObjectPtr findChildWithTag(TagType tag) const { return findChildWithTagImpl(static_cast<int>(tag)); }

		// 自身の子要素から引数のタグを持ったゲームオブジェクトを全て取得する
		template<class TagType, is_idType<TagType> = nullptr>
		std::forward_list<GameObjectPtr> findChildrenWithTag(TagType tag) const { return findChildrenWithTagImpl(static_cast<int>(tag)); }

		// 子要素をリストに追加する
		void addChild(const GameObjectPtr& child);

		// 指定した子要素をリストから削除する
		void removeChild(const GameObjectPtr& child);

		// 全ての子要素にメッセージを送信する
		void sendMessage(unsigned int messageId, const MessageAttachment& value = {});

	public: /* ステートマシン関係処理 */

		// ステートの種類を引数として渡し、ステートマシンの操作に必要なコンポーネントを準備する
		void setupStateMachine(const StateMachineListInitParam& initParam);

		// ステートを有効にする
		template <class StateIdType>
		void stateEnable(StateIdType stateType) { stateEnableImpl(static_cast<int>(stateType)); };

		// ステートを無効にする
		template <class StateIdType>
		void stateDisable(StateIdType stateType) { stateDisableImpl(static_cast<int>(stateType)); };

		// 全てのステートを無効にする
		void clearState();

		// 引数のステートを持っているか？
		template <class StateIdType>
		bool containState(StateIdType stateType) { return containStateImpl(static_cast<int>(stateType)); };

		// ステートを指定し、子要素を追加する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		void addChild(std::initializer_list<StateIdType> targetState, const GameObjectPtr& child);

		// ステートを指定し、テンプレート引数の型のコンポーネントを引数の値を使って作る
		//  ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class ComponentType, class StateIdType, class... Args>
		ComponentPtr<ComponentType> createComponent(std::initializer_list<StateIdType> targetState, Args&&... args);

		// ステートを指定し、ステートを変更するタイマーを作る
		//  ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		ComponentPtr<StateChangeTimer> createStateChangeTimer(std::initializer_list<StateIdType> targetState, float stateChangeTimeSec, std::initializer_list<StateIdType> enableStates, std::initializer_list<StateIdType> disableStates);

		// ステートを指定し、メッセージ受信時にステートを変更するコンポーネントを作る
		//  ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class MessageType, class StateIdType>
		ComponentPtr<MessageStateChanger> createMessageStateChanger(std::initializer_list<StateIdType> targetState, MessageType messageType, std::initializer_list<StateIdType> enableStates, std::initializer_list<StateIdType> disableStates);

		// 子要素を指定のステートに追加する（※addChild(targetState, child)の内部実装）
		void setChildToStateMachine(const std::vector<int>& targetState, const GameObjectPtr& child);

		// コンポーネントを指定のステートに追加する（※createComponent<ComponentType>(targetState, args...)の内部実装）
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
		std::unique_ptr<GameObjectComponentList>			m_componentList			{};	// ※テンプレート関数を使用するため、前方宣言不可
		std::unique_ptr<StateMachineList>					m_stateMachineList		{};
		
		// デフォルトコンポーネント
		ComponentPtr<ParentChildManager>					m_parentChildManager	{};
		ComponentPtr<CurStateTypeList>						m_stateTypeList			{};

	public:

		// 不正な型が引数として渡された時の処理
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
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// ステートを指定し、子要素を追加する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline void GameObject::addChild(std::initializer_list<StateIdType> targetState, const GameObjectPtr& child)
	{
		// 指定したステートをint型にキャストする
		auto targetStateArray		= std::vector<StateIdType>(targetState);
		auto intTargetStateArray	= std::vector<int>();
		intTargetStateArray.reserve(targetStateArray.size());
		for (const auto& node : targetStateArray) intTargetStateArray.push_back(static_cast<int>(node));

		setChildToStateMachine(intTargetStateArray, child);
	}

	// ステートを指定し、テンプレート引数の型のコンポーネントを引数の値を使って作る
	//  ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class ComponentType, class StateIdType, class ...Args>
	inline ComponentPtr<ComponentType> GameObject::createComponent(std::initializer_list<StateIdType> targetState, Args&& ...args)
	{
		// 指定したステートをint型にキャストする
		auto targetStateArray = std::vector<StateIdType>(targetState);
		auto intTargetStateArray = std::vector<int>();
		intTargetStateArray.reserve(targetStateArray.size());
		for (const auto& node : targetStateArray) intTargetStateArray.push_back(static_cast<int>(node));

		auto createdComponent = DX12GameManager::createComponent<ComponentType>(GameObjectPtr(weak_from_this()), std::forward<Args>(args)...);
		createdComponent.lock()->setUser(GameObjectPtr(weak_from_this()));
		setComponentToStateMachine(intTargetStateArray, ComponentBasePtr(createdComponent));
		return m_componentList->add<ComponentType>(createdComponent);
	}

	// ステートを指定し、ステートを変更するタイマーを作る
	//  ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline ComponentPtr<StateChangeTimer> GameObject::createStateChangeTimer(std::initializer_list<StateIdType> targetState, float stateChangeTimeSec, std::initializer_list<StateIdType> enableStates, std::initializer_list<StateIdType> disableStates)
	{
		// 指定したステートをint型にキャストする
		auto targetStateArray = std::vector<StateIdType>(targetState);
		auto intTargetStateArray = std::vector<int>();
		intTargetStateArray.reserve(targetStateArray.size());
		for (const auto& node : targetStateArray) intTargetStateArray.push_back(static_cast<int>(node));

		// 有効にするステートをint型にキャストする
		auto enableStateArray	= std::vector<StateIdType>(enableStates);
		auto intEnableStateArray = std::vector<int>();
		intEnableStateArray.reserve(enableStateArray.size());
		for (const auto& node : enableStateArray) intEnableStateArray.push_back(static_cast<int>(node));

		// 無効にするステートをint型にキャスト
		auto disableStateArray = std::vector<StateIdType>(disableStates);
		auto intDisableStateArray = std::vector<int>();
		intDisableStateArray.reserve(disableStateArray.size());
		for (const auto& node : disableStateArray) intDisableStateArray.push_back(static_cast<int>(node));

		return createStateChangeTimerImpl(intTargetStateArray, stateChangeTimeSec, intEnableStateArray, intDisableStateArray);
	}

	// ステートを指定し、メッセージ受信時にステートを変更するコンポーネントを作る
		//  ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class MessageType, class StateIdType>
	inline ComponentPtr<MessageStateChanger> GameObject::createMessageStateChanger(std::initializer_list<StateIdType> targetState, MessageType stateChangeTimeSec, std::initializer_list<StateIdType> enableStates, std::initializer_list<StateIdType> disableStates)
	{
		// 指定したステートをint型にキャストする
		auto targetStateArray = std::vector<StateIdType>(targetState);
		auto intTargetStateArray = std::vector<int>();
		intTargetStateArray.reserve(targetStateArray.size());
		for (const auto& node : targetStateArray) intTargetStateArray.push_back(static_cast<int>(node));

		// 有効にするステートをint型にキャストする
		auto enableStateArray = std::vector<StateIdType>(enableStates);
		auto intEnableStateArray = std::vector<int>();
		intEnableStateArray.reserve(enableStateArray.size());
		for (const auto& node : enableStateArray) intEnableStateArray.push_back(static_cast<int>(node));

		// 無効にするステートをint型にキャスト
		auto disableStateArray = std::vector<StateIdType>(disableStates);
		auto intDisableStateArray = std::vector<int>();
		intDisableStateArray.reserve(disableStateArray.size());
		for (const auto& node : disableStateArray) intDisableStateArray.push_back(static_cast<int>(node));

		return createStateChangeTimerImpl(intTargetStateArray, stateChangeTimeSec, intEnableStateArray, intDisableStateArray);

		return ComponentPtr<StateChangeTimer>();
	}
}
#endif // !GAME_OBJECT_H_