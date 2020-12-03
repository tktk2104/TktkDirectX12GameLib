#ifndef MIKU_H_
#define MIKU_H_

#include <TktkDX12BaseComponents/Components.h>
#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h>
#include <TktkDX12BaseComponents/3D/MeshDrawer/BasicMeshDrawerMaker.h>
#include <TktkDX12BaseComponents/3D/ShadowMapWriter/BasicMeshShadowMapWriterMaker.h>
#include <TktkDX12BaseComponents/3D/MeshAnimator/MeshAnimatorMaker.h>

#include "MikuScript.h"
#include "../../ResourceHandleCarrier/ResourceHandleCarrier.h"
#include "../../Enum/_ResourceIds/ResourceIds.h"

struct Miku
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position)
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::Transform3DMaker::makeStart(gameObject)
			.initPosition(position)
			.create();

		/*tktk::BoxMeshDrawerMaker::makeStart(gameObject)
			.albedoColor(tktkMath::Color_v::white)
			.useRtvDescriptorHeapHandle(ResourceHandleCarrier::getPostEffectRtvDescriptorHeapHandle())
			.create();*/

		/*tktk::SphereMeshDrawerMaker::makeStart(gameObject)
			.albedoColor(tktkMath::Color_v::white)
			.useRtvDescriptorHeapHandle(ResourceHandleCarrier::getPostEffectRtvDescriptorHeapHandle())
			.create();*/

		tktk::BasicMeshDrawerMaker::makeStart(gameObject)
			.drawPriority(0.0f)
			.meshId(BasicMeshId::Miku)
			.skeletonId(SkeletonId::Miku)
			.useRtvDescriptorHeapHandle(ResourceHandleCarrier::getPostEffectRtvDescriptorHeapHandle())
			.create();

		/*tktk::BasicMeshShadowMapWriterMaker::makeStart(gameObject)
			.drawPriority(-10.0f)
			.meshId(BasicMeshId::Miku)
			.skeletonId(SkeletonId::Miku)
			.create();*/

		tktk::MeshAnimatorMaker::makeStart(gameObject)
			.isLoop(false)
			.initMotionId(MotionId::motion2)
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

		/*tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
			.lineColor(tktkMath::Color_v::blue)
			.useRtvDescriptorHeapHandle(ResourceHandleCarrier::getPostEffectRtvDescriptorHeapHandle())
			.create();*/

		gameObject->createComponent<MikuScript>();

		return gameObject;
	}
};
#endif // !MIKU_H_
