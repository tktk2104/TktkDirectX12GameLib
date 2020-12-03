#ifndef SHADOW_MAP_CAMERA_H_
#define SHADOW_MAP_CAMERA_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* class member */
#include <TktkMath/Structs/Vector3.h>

#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObjectTagCarrier.h"

namespace tktk
{
	/* class member */
	class Transform3D;

	// シャドウマップカメラコンポーネント
	class ShadowMapCameraController
		: public ComponentBase
	{
	public:

		ShadowMapCameraController(
			size_t cameraHandle,
			GameObjectTagCarrier targetTag,
			const tktkMath::Vector3& direction,
			float cameraWidth,
			float cameraHeight,
			float cameraNear,
			float cameraFar
		);

	public:

		void afterCollide();

	private:

		void findTargetTransform();

	private:

		size_t						m_cameraHandle;
		GameObjectTagCarrier		m_targetTag;
		tktkMath::Vector3			m_direction;
		float						m_cameraWidth;
		float						m_cameraHeight;
		float						m_cameraNear;
		float						m_cameraFar;
		ComponentPtr<Transform3D>	m_targetTransform{};
	};
}
#endif // !SHADOW_MAP_CAMERA_H_