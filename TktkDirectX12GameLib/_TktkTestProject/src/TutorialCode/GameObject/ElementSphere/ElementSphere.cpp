#include "ElementSphere.h"

#include <TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h>
#include <TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshDrawerMaker.h>
#include <TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshWireFrameDrawerMaker.h>

#include "../../../Enum/_ResourceIds/ResourceIds.h"

tktk::GameObjectPtr ElementSphere::create(const tktkMath::Vector3 & position, const tktkMath::Color & color)
{
	tktk::GameObjectPtr gameObject = tktk::DX12GameManager::createGameObject();

	tktk::Transform3DMaker::makeStart(gameObject)
		.initPosition(position)
		.initScaleRate({ 0.1f })
		.create();

	tktk::SphereMeshDrawerMaker::makeStart(gameObject)
		.drawPriority(0.0f)
		.albedoColor(color)
		.cameraId(CameraId::Basic)
		.shadowMapCameraId(CameraId::ShadowMap)
		.lightId(LightId::Basic)
		.create();

	return gameObject;
}
