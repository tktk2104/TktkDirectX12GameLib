#ifndef COLLIDER_WIRE_FRAME_DRAWER_2D_H_
#define COLLIDER_WIRE_FRAME_DRAWER_2D_H_

/* std::vector */
#include <vector>

/* class member */
#include <TktkMath/Structs/Color.h>

/* baseClass */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	/* class member */
	class Line2DDrawer;

	// �񎟌��Փ˔���̋��E����`�悷��R���|�[�l���g
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

		// �e�Փ˔���R���|�[�l���g���ɓ񎟌����`��R���|�[�l���g�����
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