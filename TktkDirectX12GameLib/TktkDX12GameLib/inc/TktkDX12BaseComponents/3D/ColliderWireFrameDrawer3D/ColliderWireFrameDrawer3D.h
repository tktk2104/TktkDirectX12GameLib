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
			unsigned int	cameraHandle,
			unsigned int	shadowMapCameraHandle,
			unsigned int	lightHandle,
			unsigned int	useRtvDescriptorHeapHandle,
			const tktkMath::Color& lineColor
		);

	public:

		void start();
		void onEnable();
		void onDisable();

	private:

		float			m_drawPriority;
		unsigned int	m_cameraHandle;
		unsigned int	m_shadowMapCameraHandle;
		unsigned int	m_lightHandle;
		unsigned int	m_useRtvDescriptorHeapHandle;
		tktkMath::Color	m_lineColor;
		std::vector<tktk::ComponentPtr<SphereMeshWireFrameDrawer>> m_wireFrameDrawerArray;
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_3D_H_