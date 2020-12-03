#ifndef COLLIDER_WIRE_FRAME_DRAWER_3D_H_
#define COLLIDER_WIRE_FRAME_DRAWER_3D_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* class member */
#include <vector>
#include <TktkMath/Structs/Color.h>

namespace tktk
{
	/* class member */
	class MonoColorMeshDrawer;

	// 三次元衝突判定の境界線を表示するコンポーネント
	class ColliderWireFrameDrawer3D
		: public ComponentBase
	{
	public:

		explicit ColliderWireFrameDrawer3D(const tktkMath::Color& lineColor);

	public:

		void start();
		void onEnable();
		void onDisable();

	private:

		tktkMath::Color	m_lineColor;
		std::vector<tktk::ComponentPtr<MonoColorMeshDrawer>> m_wireFrameDrawerArray;
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_3D_H_