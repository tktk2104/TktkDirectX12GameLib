#include "TktkDX12BaseComponents/3D/ColliderWireFrameDrawer3D/ColliderWireFrameDrawer3D.h"

#include <algorithm>
#include <TktkMath/MathHelper.h>
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include "TktkDX12BaseComponents/3D/SphereCollider/SphereCollider.h"
#include "TktkDX12BaseComponents/3D/BoxCollider/BoxCollider.h"
#include "TktkDX12BaseComponents/3D/MeshDrawer/MonoColorMeshDrawerMaker.h"

namespace tktk
{
	ColliderWireFrameDrawer3D::ColliderWireFrameDrawer3D(const tktkMath::Color& lineColor)
		: m_lineColor(lineColor)
	{
	}

	void ColliderWireFrameDrawer3D::start()
	{
		auto circleColliderList = getComponents<SphereCollider>();

		for (const auto& sphereCollider : circleColliderList)
		{
			m_wireFrameDrawerArray.push_back(
				MonoColorMeshDrawerMaker::makeStart(getGameObject())
				.setSphereMeshWireFrame()
				.baseScale(sphereCollider->getBoundingSphere().getBaseRadius() * 2)
				.basePosition(sphereCollider->getBoundingSphere().getBaseCenterPosition())
				.albedoColor(m_lineColor)
				.create()
			);
		}

		auto boxColliderList = getComponents<BoxCollider>();

		for (const auto& boxCollider : boxColliderList)
		{
			const auto& firstVert = boxCollider->getTempVerts().at(0U);
			const auto& secondVert = boxCollider->getTempVerts().at(11U);
			auto centerPos = (firstVert + secondVert) / 2.0f;

			auto scale = tktkMath::Vector3{
				(centerPos.x - firstVert.x) / 0.5f,
				(centerPos.y - firstVert.y) / 0.5f,
				(centerPos.z - firstVert.z) / 0.5f
			};

			m_wireFrameDrawerArray.push_back(
				MonoColorMeshDrawerMaker::makeStart(getGameObject())
				.setBoxMeshWireFrame()
				.baseScale(scale)
				.basePosition(centerPos)
				.albedoColor(m_lineColor)
				.create()
			);
		}
	}

	void ColliderWireFrameDrawer3D::onEnable()
	{
		std::for_each(
			std::begin(m_wireFrameDrawerArray),
			std::end(m_wireFrameDrawerArray),
			[](const ComponentPtr<MonoColorMeshDrawer>& wireFrameDrawer) { wireFrameDrawer->setActive(true); }
		);
	}

	void ColliderWireFrameDrawer3D::onDisable()
	{
		std::for_each(
			std::begin(m_wireFrameDrawerArray),
			std::end(m_wireFrameDrawerArray),
			[](const ComponentPtr<MonoColorMeshDrawer>& wireFrameDrawer) { wireFrameDrawer->setActive(false); }
		);
	}
}