#include "TktkDX12BaseComponents/3D/ColliderWireFrameDrawer3D/ColliderWireFrameDrawer3D.h"

#include <algorithm>
#include <TktkMath/MathHelper.h>
#include "TktkDX12BaseComponents/3D/SphereCollider/SphereCollider.h"
#include "TktkDX12BaseComponents/3D/BoxCollider/BoxCollider.h"

namespace tktk
{
	ColliderWireFrameDrawer3D::ColliderWireFrameDrawer3D(float drawPriority, const tktkMath::Color& lineColor, const SphereMeshDrawerUseResourceHandles& useResourceHandles)
		: m_drawPriority(drawPriority)
		, m_lineColor(lineColor)
		, m_useResourceHandles(useResourceHandles)
	{
	}

	void ColliderWireFrameDrawer3D::start()
	{
		auto circleColliderList = getComponents<SphereCollider>();

		for (const auto& sphereCollider : circleColliderList)
		{
			m_sphereMeshWireFrameDrawerArray.push_back(
				getGameObject()->createComponent<SphereMeshWireFrameDrawer>(
					m_drawPriority,
					sphereCollider->getBoundingSphere().getRadius(),
					sphereCollider->getBoundingSphere().getCenterPosition(),
					m_lineColor,
					m_useResourceHandles
					)
			);
		}

		auto boxColliderList = getComponents<BoxCollider>();

		BoxMeshDrawerUseResourceHandles boxMeshDrawerUseResourceHandles{};
		boxMeshDrawerUseResourceHandles.rtvDescriptorHeapHandle = m_useResourceHandles.rtvDescriptorHeapHandle;
		boxMeshDrawerUseResourceHandles.cameraHandle = m_useResourceHandles.cameraHandle;
		boxMeshDrawerUseResourceHandles.shadowMapCameraHandle = m_useResourceHandles.shadowMapCameraHandle;
		boxMeshDrawerUseResourceHandles.lightHandle = m_useResourceHandles.lightHandle;


		for (const auto& boxCollider : boxColliderList)
		{
			//auto firstVert = boxCollider->getBoundingMesh().getVertexs();

			auto firstVert = boxCollider->getTempVerts().at(0U);

			m_boxMeshWireFrameDrawerArray.push_back(
				getGameObject()->createComponent<BoxMeshWireFrameDrawer>(
					m_drawPriority,
					tktkMath::Vector3{ firstVert.x * -2.0f, firstVert.y * -2.0f, firstVert.z * -2.0f },
					tktkMath::Vector3_v::zero,
					m_lineColor,
					boxMeshDrawerUseResourceHandles
					)
			);
		}
	}

	void ColliderWireFrameDrawer3D::onEnable()
	{
		std::for_each(
			std::begin(m_sphereMeshWireFrameDrawerArray),
			std::end(m_sphereMeshWireFrameDrawerArray),
			[](const ComponentPtr<SphereMeshWireFrameDrawer>& wireFrameDrawer) { wireFrameDrawer->setActive(true); }
		);

		std::for_each(
			std::begin(m_boxMeshWireFrameDrawerArray),
			std::end(m_boxMeshWireFrameDrawerArray),
			[](const ComponentPtr<BoxMeshWireFrameDrawer>& wireFrameDrawer) { wireFrameDrawer->setActive(true); }
		);
	}

	void ColliderWireFrameDrawer3D::onDisable()
	{
		std::for_each(
			std::begin(m_sphereMeshWireFrameDrawerArray),
			std::end(m_sphereMeshWireFrameDrawerArray),
			[](const ComponentPtr<SphereMeshWireFrameDrawer>& wireFrameDrawer) { wireFrameDrawer->setActive(false); }
		);

		std::for_each(
			std::begin(m_boxMeshWireFrameDrawerArray),
			std::end(m_boxMeshWireFrameDrawerArray),
			[](const ComponentPtr<BoxMeshWireFrameDrawer>& wireFrameDrawer) { wireFrameDrawer->setActive(true); }
		);
	}
}