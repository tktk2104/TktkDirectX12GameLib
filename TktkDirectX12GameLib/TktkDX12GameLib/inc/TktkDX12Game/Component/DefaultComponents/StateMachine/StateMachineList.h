#ifndef STATE_MACHINE_LIST_H_
#define STATE_MACHINE_LIST_H_

#include <memory>
#include <vector>
#include <unordered_map>
#include "../../../GameObject/GameObjectPtr.h"
#include "../../ComponentBasePtr.h"
#include "StateMachineListInitParam.h"

namespace tktk
{
	class GameObjectComponentList;
	class StateMachine;

	// ステートマシンのポインタを管理するクラス
	// ※GameObjectの「setupStateMachine」関数で作成される
	class StateMachineList
	{
	public:

		StateMachineList(const StateMachineListInitParam& initParam, const GameObjectPtr& user, const std::unique_ptr<GameObjectComponentList>& componentList);

	public:

		// int型の配列でステートを指定し、子要素を追加する
		// ※「{ 1, 10, 30 }」で「“ステート１”内の“ステート１０”内の“ステート３０”に追加」となる
		void addChild(const std::vector<int>& targetState, const GameObjectPtr& child);

		// int型の配列でステートを指定し、引数のコンポーネントを追加する
		// ※「{ 1, 10, 30 }」で「“ステート１”内の“ステート１０”内の“ステート３０”に追加」となる
		void addComponent(const std::vector<int>& targetState, const ComponentBasePtr& componentPtr);

	private:

		// 入れ子１つ分の要素
		struct Node
		{
			ComponentPtr<StateMachine>		m_stateMachine;
			std::unordered_map<int, Node>	m_childNode;
		};

	private:

		// 親の状態を持つステートマシンを作る
		void createNode(StateMachineList::Node& parentNode, const StateMachineListInitParam::Node<int>& nodeInitParam, const GameObjectPtr& user, const std::unique_ptr<GameObjectComponentList>& componentList);

		// int型の配列から指定のステートを取得する
		ComponentPtr<StateMachine> getTarget(const std::vector<int>& targetState) const;

	private:

		// 入れ子構造でポインタを管理する
		std::unordered_map<int, Node>	m_stateMachineList;
	};
}
#endif // !STATE_MACHINE_LIST_H_
