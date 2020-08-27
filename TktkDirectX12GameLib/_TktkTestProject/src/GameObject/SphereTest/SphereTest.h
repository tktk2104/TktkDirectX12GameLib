#ifndef SPHERE_TEST_H_
#define SPHERE_TEST_H_

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h>
#include <TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshDrawerMaker.h>

#include "../../ResourceHandleCarrier/ResourceHandleCarrier.h"

struct SphereTest
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position)
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::Transform3DMaker::makeStart(gameObject)
			.initPosition(position)
			//.initScaleRate({ 100.0f })
			.create();

		tktk::SphereMeshDrawerMaker::makeStart(gameObject)
			.drawPriority(0.0f)
			.useRtvDescriptorHeapHandle(ResourceHandleCarrier::getPostEffectRtvDescriptorHeapHandle())
			.cameraId(0U)
			.shadowMapCameraId(1U)
			.lightId(0U)
			.create();

		return gameObject;
	}
};
#endif // !SPHERE_TEST_H_
