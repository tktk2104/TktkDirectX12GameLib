#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include <forward_list>
#include "../../ComponentBase.h"

namespace tktk
{
	class CurStateTypeList;

	// ステートマシーンコンポーネント
	// 【前提コンポーネント：CurStateTypeList】
	class StateMachine
		: public ComponentBase
	{
	public:

		StateMachine(int stateType);

	public:

		// <PolymorphismFunc>
		void onDisable();
		void start();
		void update();

	public:

		// このステートに子要素を追加する
		void addChild(const GameObjectPtr& child);

		// このステートにコンポーネントを追加する
		void addComponent(const ComponentBasePtr& componentPtr);

	private:

		// 自身のステートの種類
		int m_selfStateType;

		// 自身の現在のステートの種類のコンポーネント
		ComponentPtr<CurStateTypeList> m_curStateTypeList;

		// このステートが管理するGameObjectのコンテナ
		std::forward_list<GameObjectPtr> m_gameObjectList;

		// このステートが管理するコンポーネントのコンテナ
		std::forward_list<ComponentBasePtr> m_componentList;
	};
}
#endif // !STATE_MACHINE_H_