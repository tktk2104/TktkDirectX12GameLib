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

	// ゲームオブジェクトクラス
	class GameObject
		: public std::enable_shared_from_this<GameObject>
	{
	public:

		GameObject();
		~GameObject();

	public:

		void update();

	//************************************************************
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

	//************************************************************
	public: /* タグ管理関数 */

		// 自身のタグを追加する
		void addGameObjectTag(GameObjectTagCarrier tag);

		// 引数のタグを削除する
		void removeGameobjectTag(GameObjectTagCarrier tag);

		// 引数のタグを持っているかの判定を行う
		bool containGameobjectTag(GameObjectTagCarrier tag) const;

	//************************************************************
	public: /* コンポーネント取得処理 */

		// テンプレート引数の型のコンポーネントを引数の値を使って作る
		// ※作ったコンポーネントは次のフレームの頭に追加される
		template <class ComponentType, class... Args>
		ComponentPtr<ComponentType> createComponent(Args&&... args)
		{
			auto basePtr = addComponent(typeid(ComponentType), &ComponentVTableInitializer<ComponentType>::m_componentVTableBundle, &ComponentListVTableInitializer<ComponentType>::m_componentListVTable, std::make_shared<ComponentType>(std::forward<Args>(args)...));
			return basePtr.castPtr<ComponentType>();
		}

		// 引数のコンポーネントを自身に追加する
		// ※追加したコンポーネントは次のフレームの頭に追加される
		ComponentBasePtr addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const std::shared_ptr<ComponentBase>& componentPtr);

		// テンプレート引数の型のコンポーネントを持っていたら取得し、持っていなかったらnullptrを返す
		// ※複数同じ型のコンポーネントを所持していた場合、最初に見つけた１つを取得する
		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const { return getComponent(typeid(ComponentType)).castPtr<ComponentType>(); }

		// 引数の型のコンポーネントを取得する
		// ※取得できなかったらnullptrを返す
		// ※複数該当するコンポーネントがあったら最初に見つけた１つを返す
		ComponentBasePtr getComponent(std::type_index type) const;

		// テンプレート引数の型のコンポーネントを全て取得する
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

		// 引数の型のコンポーネントを全て取得する
		std::forward_list<ComponentBasePtr> getComponents(std::type_index type) const;

	//************************************************************
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

	//************************************************************
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

	//************************************************************
	public: /* ステートマシン関係処理 */

		// ステートの種類を引数として渡し、ステートマシンの操作に必要なコンポーネントを準備する
		void setupStateMachine(const StateMachineListInitParam& initParam);

		// 子要素、コンポーネントを追加するステートの階層を設定する
		// ※今後この関数を再び呼ばれるまで追加するステートの階層が固定される
		void setTargetHierarchy(const StateTypeHierarchy& targetHierarchy);

		// ステートを有効にする
		void stateEnable(StateTypeCarrier stateType);

		// ステートを無効にする
		void stateDisable(StateTypeCarrier stateType);

		// 全てのステートを無効にする
		void clearState();

		// 引数のステートを持っているか？
		bool containState(StateTypeCarrier stateType);

	private:

		bool m_isActive				{ true };
		bool m_nextFrameActive		{ true };
		bool m_isDead				{ false };

		std::unique_ptr<GameObjectTagList>		 m_tagList			{};
		std::unique_ptr<GameObjectComponentList> m_componentList	{};	// ※テンプレート関数を使用するため、前方宣言不可
		std::unique_ptr<StateMachineList>		 m_stateMachineList	{};
		
		// デフォルトコンポーネント
		ComponentPtr<ParentChildManager>		m_parentChildManager{};
		ComponentPtr<CurStateTypeList>			m_stateTypeList		{};
	};
}
#endif // !GAME_OBJECT_H_