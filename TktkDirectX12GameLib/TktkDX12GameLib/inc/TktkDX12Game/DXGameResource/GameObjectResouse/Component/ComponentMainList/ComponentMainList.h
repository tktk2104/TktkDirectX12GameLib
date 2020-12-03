#ifndef COMPONENT_MAIN_LIST_H_
#define COMPONENT_MAIN_LIST_H_

/* std::shared_ptr, std::weak_ptr */
#include <memory>

/* std::type_index */
#include <typeindex>

/* std::multimap */
#include <map>

/* std::unordered_map */
#include <unordered_map>

/* class member */
#include "../PriorityList/ComponentRunFuncPriorityList.h"

namespace tktk
{
	struct ComponentListVTable;
	class ComponentTypeList;
	class ComponentBase;

	class ComponentMainList
	{
	public:

		ComponentMainList();
		~ComponentMainList();

	public:

		// コンポーネントを追加する
		void addComponent(std::type_index type, ComponentListVTable* vtablePtr, const std::shared_ptr<ComponentBase>& componentPtr);

		// 引数の型のコンポーネントの更新優先度を設定する
		void addRunFuncPriority(std::type_index type, float priority);

		// 前フレームに追加されたコンポーネントをメインリストに追加する
		void movePreFrameAddedNode();

		// アクティブ状態の判定を行う
		void activeChangeCheck();

		// 更新処理を呼ぶ
		void update();

		// 衝突判定直前処理を呼ぶ
		void runBeforeCollide();

		// 衝突判定後処理を呼ぶ
		void runAfterCollide();

		// 死んだコンポーネントを削除する
		void removeDeadComponent();

	private:

		ComponentRunFuncPriorityList												m_priorityList;		// コンポーネントの更新処理の呼び出し順を管理するリスト
		std::multimap		<float,				std::shared_ptr<ComponentTypeList>>	m_mainMap;			// コンポーネントを巡回するためのマップ
		std::unordered_map	<std::type_index,	std::weak_ptr<ComponentTypeList>>	m_addComponentMap;	// コンポーネントを追加するためのマップ
	};
}
#endif // !COMPONENT_MAIN_LIST_H_