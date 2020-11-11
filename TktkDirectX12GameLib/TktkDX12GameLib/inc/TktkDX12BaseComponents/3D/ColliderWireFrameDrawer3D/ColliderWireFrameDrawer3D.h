#ifndef COLLIDER_WIRE_FRAME_DRAWER_3D_H_
#define COLLIDER_WIRE_FRAME_DRAWER_3D_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

// TODO : ���`��R���|�[�l���g�ɕԂ�
#include "TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshDrawerUseResourceHandles.h"

/* class member */
#include <vector>
#include <TktkMath/Structs/Color.h>

namespace tktk
{
	/* class member */
	class BoxMeshWireFrameDrawer;
	class SphereMeshWireFrameDrawer;

	// �O�����Փ˔���̋��E����\������R���|�[�l���g
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