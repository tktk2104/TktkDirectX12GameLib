#ifndef STATE_MACHINE_LIST_H_
#define STATE_MACHINE_LIST_H_

/* std::unordered_map */
#include <unordered_map>

/* selfInitParam */
#include "Structs/StateMachineListInitParam.h"

/* funcUseType */
#include "Structs/StateTypeList.h"

/* class member */
#include "../../ComponentPtr.h"
#include "Structs/StateTypeHierarchy.h"

namespace tktk
{
	/* funcUseType */
	class ComponentBasePtr;
	class GameObjectPtr;

	/* class member */
	class StateMachine;

	// ステートマシンのポインタを管理するクラス
	// ※GameObjectの「setupStateMachine」関数で作成される
	class StateMachineList
	{
	public:

		StateMachineList(const StateMachineListInitParam& initParam, const GameObjectPtr& user);

	public:

		// 子要素、コンポーネントを追加するステートの階層を設定する
		// ※今後この関数を再び呼ばれるまで追加するステートの階層が固定される
		void setTargetHierarchy(const StateTypeHierarchy& targetHierarchy);

		// コンポーネントを追加する階層が登録されているか判定する
		bool isSetTargetHierarchy() const;

		// 事前に設定した階層に子要素を追加する
		void addChild(const GameObjectPtr& child);

		// 全ての階層から子要素を削除する
		void removeChild(const GameObjectPtr& child);

		// 事前に設定した階層にコンポーネントを追加する
		void addComponent(const ComponentBasePtr& componentPtr);

	private:

		// 入れ子１つ分の要素
		struct Node
		{
			ComponentPtr<StateMachine>					m_stateMachine;
			std::unordered_map<StateTypeCarrier, Node>	m_childNode;
		};

	private:

		// 親の状態を持つステートマシンを作る
		void createNode(StateMachineList::Node& parentNode, const StateMachineListInitParam::Node& nodeInitParam, const GameObjectPtr& user);

		// 子要素、コンポーネントを追加するステートの階層情報を取得する
		ComponentPtr<StateMachine> getTargetStateMachine() const;

		void removeChildImpl(const std::unordered_map<StateTypeCarrier, Node>& targetMap, const GameObjectPtr& child);

	private:

		// 子要素、コンポーネントを追加するステートの階層
		StateTypeHierarchy							m_targetHierarchy	{};

		// 入れ子構造でステートマシンを管理する
		std::unordered_map<StateTypeCarrier, Node>	m_stateMachineList	{};
	};
}
#endif // !STATE_MACHINE_LIST_H_