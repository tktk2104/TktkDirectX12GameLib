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
		void addGameObjectTag(GameObjectTagCarrier tag);

		// 引数のタグを削除する
		void removeGameobjectTag(GameObjectTagCarrier tag);

		// 引数のタグを持っているかの判定を行う
		bool containGameobjectTag(GameObjectTagCarrier tag) const;

	public: /* コンポーネント取得処理 */

		// テンプレート引数の型のコンポーネントを引数の値を使って作る
		// ※作ったコンポーネントは次のフレームの頭に追加される
		template <class ComponentType, class... Args>
		ComponentPtr<ComponentType> createComponent(Args&&... args)				{ return m_componentList->add<ComponentType>(DX12GameManager::createComponent<ComponentType>(GameObjectPtr(weak_from_this()), std::forward<Args>(args)...)); }

		// テンプレート引数の型のコンポーネントを持っていたら取得し、持っていなかったらnullptrを返す
		// ※複数同じ型のコンポーネントを所持していた場合、最初に見つけた１つを取得する
		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const						{ return m_componentList->find<ComponentType>(); }

		// テンプレート引数の型のコンポーネントを全て取得する
		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> getComponents() const	{ return m_componentList->findAll<ComponentType>(); }

	public: /* コンポーネント関数呼び出し処理 */

		// 全てのメッセージ取得関数を呼ぶ
		void runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment);

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
		GameObjectPtr findChildWithTag(GameObjectTagCarrier tag) const;

		// 自身の子要素から引数のタグを持ったゲームオブジェクトを全て取得する
		std::forward_list<GameObjectPtr> findChildrenWithTag(GameObjectTagCarrier tag) const;

		// 子要素をリストに追加する
		void addChild(const GameObjectPtr& child);

		// 指定した子要素をリストから削除する
		void removeChild(const GameObjectPtr& child);

		// 全ての子要素にメッセージを送信する
		void sendMessage(MessageTypeCarrier type, const MessageAttachment& attachment = {});

	public: /* ステートマシン関係処理 */

		// ステートの種類を引数として渡し、ステートマシンの操作に必要なコンポーネントを準備する
		void setupStateMachine(const StateMachineListInitParam& initParam);

		// ステートを有効にする
		void stateEnable(StateTypeCarrier stateType);

		// ステートを無効にする
		void stateDisable(StateTypeCarrier stateType);

		// ステートを指定し、その子要素に設定されているステートを全て有効にする
		void childStateEnable(const StateTypeHierarchy& targetState);

		// ステートを指定し、その子要素に設定されているステートを全て無効にする
		void childStateDisable(const StateTypeHierarchy& targetState);

		// 全てのステートを無効にする
		void clearState();

		// 引数のステートを持っているか？
		bool containState(StateTypeCarrier stateType);

		// ステートを指定し、子要素を追加する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		void addChild(const StateTypeHierarchy& targetState, const GameObjectPtr& child);

		// ステートを指定し、テンプレート引数の型のコンポーネントを引数の値を使って作る
		//  ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class ComponentType, class... Args>
		ComponentPtr<ComponentType> createComponentAndSetToState(const StateTypeHierarchy& targetState, Args&&... args)
		{
			auto createdComponent = createComponent<ComponentType>(std::forward<Args>(args)...);
			setComponentToStateMachine(targetState, createdComponent);
			return createdComponent;
		}

		// ステートを指定し、ステートを変更するタイマーを作る
		//  ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		ComponentPtr<StateChangeTimer> createStateChangeTimer(const StateTypeHierarchy& targetState, float stateChangeTimeSec, const StateTypeList& enableStates, const StateTypeList& disableStates);

		// ステートを指定し、メッセージ受信時にステートを変更するコンポーネントを作る
		//  ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		ComponentPtr<MessageStateChanger> createMessageStateChanger(const StateTypeHierarchy& targetState, MessageTypeCarrier messageType, const StateTypeList& enableStates, const StateTypeList& disableStates);

		// コンポーネントを指定のステートに追加する（※createComponent<ComponentType>(targetState, args...)の内部実装）
		void setComponentToStateMachine(const StateTypeHierarchy& targetState, const ComponentBasePtr& componentPtr);

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
	};
}
#endif // !GAME_OBJECT_H_