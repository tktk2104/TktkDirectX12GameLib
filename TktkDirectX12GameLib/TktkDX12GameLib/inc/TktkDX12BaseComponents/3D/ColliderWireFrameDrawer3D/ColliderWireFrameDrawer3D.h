#ifndef COLLIDER_WIRE_FRAME_DRAWER_3D_H_
#define COLLIDER_WIRE_FRAME_DRAWER_3D_H_

#include <vector>
#include <TktkMath/Structs/Color.h>
#include <TktkDX12Game/Component/ComponentBase.h>
#include "../MeshDrawer/BoxMeshWireFrameDrawer.h"
#include "../MeshDrawer/SphereMeshWireFrameDrawer.h"

namespace tktk
{
	class ColliderWireFrameDrawer3D
		: public ComponentBase
	{
	public:

		ColliderWireFrameDrawer3D(float	drawPriority, const tktkMath::Color& lineColor, const SphereMeshDrawerUseResourceHandles& useResourceHandles);

	public:

		void start();
		void onEnable();
		void onDisable();

	private:

		float			m_drawPriority;
		tktkMath::Color	m_lineColor;
		SphereMeshDrawerUseResourceHandles							m_useResourceHandles;
		std::vector<tktk::ComponentPtr<BoxMeshWireFrameDrawer>>		m_boxMeshWireFrameDrawerArray;
		std::vector<tktk::ComponentPtr<SphereMeshWireFrameDrawer>>	m_sphereMeshWireFrameDrawerArray;
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_3D_H_