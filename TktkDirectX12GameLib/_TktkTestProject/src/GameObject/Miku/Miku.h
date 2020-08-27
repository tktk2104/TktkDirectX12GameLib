#ifndef MIKU_H_
#define MIKU_H_

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h>
#include <TktkDX12BaseComponents/3D/MeshDrawer/BasicMeshDrawerMaker.h>
#include <TktkDX12BaseComponents/3D/ShadowMapWriter/BasicMeshShadowMapWriterMaker.h>
#include <TktkDX12BaseComponents/3D/MeshAnimator/MeshAnimatorMaker.h>

#include "MikuScript.h"
#include "../../ResourceHandleCarrier/ResourceHandleCarrier.h"

struct Miku
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position)
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::Transform3DMaker::makeStart(gameObject)
			.initPosition(position)
			.create();

		tktk::BasicMeshDrawerMaker::makeStart(gameObject)
			.drawPriority(0.0f)
			.meshId(0U)
			.skeletonId(0U)
			.useRtvDescriptorHeapHandle(ResourceHandleCarrier::getPostEffectRtvDescriptorHeapHandle())
			.cameraId(0U)
			.shadowMapCameraId(1U)
			.lightId(0U)
			.create();

		tktk::BasicMeshShadowMapWriterMaker::makeStart(gameObject)
			.drawPriority(-10.0f)
			.meshId(0U)
			.skeletonId(0U)
			.cameraId(1U)
			.create();

		tktk::MeshAnimatorMaker::makeStart(gameObject)
			.isLoop(false)
			.initMotionId(1U)
			.create();

		tktk::SphereColliderMaker::makeStart(gameObject)
			.collisionGroupType(1)
			.radius(2.0f)
			.localPosition({ 0.0f, 2.0f, 0.0f })
			.create();

		tktk::SphereColliderMaker::makeStart(gameObject)
			.collisionGroupType(1)
			.radius(2.0f)
			.localPosition({ 0.0f, 6.0f, 0.0f })
			.create();

		tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
			.lineColor(tktkMath::Color_v::blue)
			.useRtvDescriptorHeapHandle(ResourceHandleCarrier::getPostEffectRtvDescriptorHeapHandle())
			.lightId(0U)
			.cameraId(0U)
			.shadowMapCameraId(1U)
			.create();

		gameObject->createComponent<MikuScript>();

		return gameObject;
	}
};
#endif // !MIKU_H_
