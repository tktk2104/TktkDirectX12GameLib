#ifndef COLLIDE_3D_TEST_H_
#define COLLIDE_3D_TEST_H_

#include <TktkMath/Structs/Vector3.h>
#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h>
#include <TktkDX12BaseComponents/3D/SphereCollider/SphereColliderMaker.h>
#include <TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshWireFrameDrawerMaker.h>
#include <TktkDX12BaseComponents/3D/ColliderWireFrameDrawer3D/ColliderWireFrameDrawer3DMaker.h>

#include "../../Enum/_ResourceIds/ResourceIds.h"
#include "Collide3DTestScript.h"

struct Collide3DTest
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position, float moveSpeed, unsigned int collisionGroup)
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::Transform3DMaker::makeStart(gameObject)
			.initPosition(position)
			.traceType(tktk::TraceParentType::notTrace)
			.create();

		tktk::SphereColliderMaker::makeStart(gameObject)
			.radius(1.0f)
			.collisionGroupType(collisionGroup)
			.create();

		tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
			.drawPriority(0.0f)
			.lineColor(tktkMath::Color_v::white)
			.cameraId(CameraId::Basic)
			.shadowMapCameraId(CameraId::ShadowMap)
			.lightId(LightId::Basic)
			.create();

		gameObject->createComponent<Collide3DTestScript>(
			moveSpeed
			);

		return gameObject;
	}
};
#endif // !COLLIDE_3D_TEST_H_