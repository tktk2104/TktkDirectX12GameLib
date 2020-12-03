#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

/* std::unique_ptr */
#include <memory>

/* std::type_index */
#include <typeindex>

/* funcUseType */
#include "ComponentCollisionFunc/CollisionGroupTypeCarrier.h"
#include "ComponentBasePtr.h"

namespace tktk
{
	class ComponentMainList;
	class ComponentStartList;
	class ComponentDrawList;
	class ComponentCollisionList;
	struct ComponentListVTable;
	struct ComponentVTableBundle;
	class ComponentBase;

	// 全てのコンポーネントを管理するマネージャークラス
	class ComponentManager
	{
	public:

		ComponentManager();
		~ComponentManager();

	public:

		// 前フレームに追加されたコンポーネントをメインリストに追加する
		void movePreFrameAddedNode();

		// コンポーネントの更新処理
		void update();

		// 死んだコンポーネントを削除する
		void removeDeadComponent();

		// コンポーネントの描画処理
		void draw();

	public:

		// コンポーネントの型ごとの更新優先度を設定する
		// ※デフォルト（0.0f）で値が小さい程、早く実行される
		void addRunFuncPriority(std::type_index type, float priority);

		// 衝突判定の組み合わせを追加する
		void addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup);

		// 引数のコンポーネントを追加する
		ComponentBasePtr addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const std::shared_ptr<ComponentBase>& componentPtr);

	private:

		std::unique_ptr<ComponentMainList>		m_componentMainList;
		std::unique_ptr<ComponentStartList>		m_componentStartList;
		std::unique_ptr<ComponentDrawList>		m_componentDrawList;
		std::unique_ptr<ComponentCollisionList> m_componentCollisionList;
	};
}
#endif // !COMPONENT_MANAGER_H_