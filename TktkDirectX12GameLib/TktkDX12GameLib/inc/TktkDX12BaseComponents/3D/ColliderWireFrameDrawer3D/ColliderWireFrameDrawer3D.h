#ifndef COLLIDER_WIRE_FRAME_DRAWER_3D_H_
#define COLLIDER_WIRE_FRAME_DRAWER_3D_H_

#include <vector>
#include <TktkMath/Structs/Color.h>
#include <TktkDX12Game/Component/ComponentBase.h>
#include "../MeshDrawer/SphereMeshWireFrameDrawer.h"

namespace tktk
{
	class ColliderWireFrameDrawer3D
		: public ComponentBase
	{
	public:

		ColliderWireFrameDrawer3D(
			float			drawPriority,
			unsigned int	cameraId,
			unsigned int	shadowMapCameraId,
			unsigned int	lightId,
			unsigned int	useRtvDescriptorHeapId,
			const tktkMath::Color& lineColor
		);

	public:

		void start();
		void onEnable();
		void onDisable();

	private:

		float			m_drawPriority;
		unsigned int	m_cameraId;
		unsigned int	m_shadowMapCameraId;
		unsigned int	m_lightId;
		unsigned int	m_useRtvDescriptorHeapId;
		tktkMath::Color	m_lineColor;
		std::vector<tktk::ComponentPtr<SphereMeshWireFrameDrawer>> m_wireFrameDrawerArray;
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_3D_H_