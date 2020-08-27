#include "TktkDX12BaseComponents/3D/ColliderWireFrameDrawer3D/ColliderWireFrameDrawer3D.h"

#include <algorithm>
#include <TktkMath/MathHelper.h>
#include "TktkDX12BaseComponents/3D/SphereCollider/SphereCollider.h"

namespace tktk
{
	ColliderWireFrameDrawer3D::ColliderWireFrameDrawer3D(
		float			drawPriority,
		unsigned int	cameraHandle,
		unsigned int	shadowMapCameraHandle,
		unsigned int	lightHandle,
		unsigned int	useRtvDescriptorHeapHandle,
		const tktkMath::Color& lineColor
	)
		: m_drawPriority(drawPriority)
		, m_cameraHandle(cameraHandle)
		, m_shadowMapCameraHandle(shadowMapCameraHandle)
		, m_lightHandle(lightHandle)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
		, m_lineColor(lineColor)
	{
	}

	void ColliderWireFrameDrawer3D::start()
	{
		auto circleColliderList = getComponents<SphereCollider>();

		for (const auto& sphereCollider : circleColliderList)
		{
			const tktkCollision::BoundingSphere& boundingCircle = static_cast<const tktkCollision::BoundingSphere&>(sphereCollider->getBodyBase());

			m_wireFrameDrawerArray.push_back(
				getGameObject()->createComponent<SphereMeshWireFrameDrawer>(
					m_drawPriority,
					boundingCircle.calculateRadius(),
					boundingCircle.getLocalMatrix().calculateTranslation(),
					m_lineColor,
					m_cameraHandle,
					m_shadowMapCameraHandle,
					m_lightHandle,
					m_useRtvDescriptorHeapHandle
					)
			);
		}
	}

	void ColliderWireFrameDrawer3D::onEnable()
	{
		std::for_each(
			std::begin(m_wireFrameDrawerArray),
			std::end(m_wireFrameDrawerArray),
			[](const ComponentPtr<SphereMeshWireFrameDrawer>& wireFrameDrawer) { wireFrameDrawer->setActive(true); }
		);
	}

	void ColliderWireFrameDrawer3D::onDisable()
	{
		std::for_each(
			std::begin(m_wireFrameDrawerArray),
			std::end(m_wireFrameDrawerArray),
			[](const ComponentPtr<SphereMeshWireFrameDrawer>& wireFrameDrawer) { wireFrameDrawer->setActive(false); }
		);
	}
}