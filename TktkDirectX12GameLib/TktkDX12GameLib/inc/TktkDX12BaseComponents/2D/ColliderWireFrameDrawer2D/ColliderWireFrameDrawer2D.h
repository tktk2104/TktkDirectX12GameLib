#ifndef COLLIDER_WIRE_FRAME_DRAWER_2D_H_
#define COLLIDER_WIRE_FRAME_DRAWER_2D_H_

#include <vector>
#include <TktkMath/Structs/Color.h>
#include <TktkDX12Game/Component/ComponentBase.h>
#include "../Line2dDrawer/Line2DDrawer.h"

namespace tktk
{
	class ColliderWireFrameDrawer2D
		: public ComponentBase
	{
	public:

		ColliderWireFrameDrawer2D(
			float drawPriority,
			const tktkMath::Color& lineColor
		);

	public:

		void start();
		void onEnable();
		void onDisable();

	private:

		// 各衝突判定コンポーネント毎に二次元線描画コンポーネントを作る
		void createCircleColliderWireFrameDrawer();
		void createRectColliderWireFrameDrawer();
		void createPolygon2dColliderWireFrameDrawer();

	private:

		float m_drawPriority;
		tktkMath::Color m_lineColor;
		std::vector<tktk::ComponentPtr<Line2DDrawer>> m_wireFrameDrawerArray;
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_2D_H_