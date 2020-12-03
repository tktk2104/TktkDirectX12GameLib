#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

/* std::forward_list */
#include <forward_list>

/* baseClass */
#include "../../ComponentBase.h"

/* class member */
#include "Structs/StateTypeCarrier.h"

namespace tktk
{
	/* class member */
	class GameObjectPtr;
	class ComponentBasePtr;
	class CurStateTypeList;

	// ステートマシーンコンポーネント
	// 【前提コンポーネント：CurStateTypeList】
	class StateMachine
		: public ComponentBase
	{
	public:

		explicit StateMachine(StateTypeCarrier stateType);

	public:

		void onDisable();
		void start();
		void afterCollide();

	public:

		// このステートに子要素を追加する
		void addChild(const GameObjectPtr& child);

		// このステートから子要素を削除する
		void removeChild(const GameObjectPtr& child);

		// このステートにコンポーネントを追加する
		void addComponent(const ComponentBasePtr& componentPtr);

	private:

		// 自身のステートの種類
		StateTypeCarrier m_selfStateType;

		// 自身の現在のステートの種類のコンポーネント
		ComponentPtr<CurStateTypeList> m_curStateTypeList;

		// このステートが管理するGameObjectのコンテナ
		std::forward_list<GameObjectPtr> m_gameObjectList;

		// このステートが管理するコンポーネントのコンテナ
		std::forward_list<ComponentBasePtr> m_componentList;
	};
}
#endif // !STATE_MACHINE_H_