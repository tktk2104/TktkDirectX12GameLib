#ifndef RECT_COLLIDER_EXTRUSION_H_
#define RECT_COLLIDER_EXTRUSION_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../RectCollider/RectCollider.h"

namespace tktk
{
	class RectColliderExtrusion
		: public ComponentBase
	{
	public:

		RectColliderExtrusion() = default;

	public:

		// <PolymorphismFunc>
		void onCollisionStay(const tktk::GameObjectPtr& other);

	private:

		// TODO : Utilty‚ÉˆÚ“®‚·‚é
		bool lineCrossCheck(
			const tktkMath::Vector2& firstLinePosOne,
			const tktkMath::Vector2& firstLinePosTwo,
			const tktkMath::Vector2& secondLinePosOne,
			const tktkMath::Vector2& secondLinePosTwo,
			float* dR,
			float* dS,
			tktkMath::Vector2* crossPos
		);
	};
}
#endif // !RECT_COLLIDER_EXTRUSION_H_