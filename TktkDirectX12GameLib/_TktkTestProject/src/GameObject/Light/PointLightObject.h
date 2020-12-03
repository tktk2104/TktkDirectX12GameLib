#pragma once

#include <TktkDX12Game/TktkDX12Game.h>
#include <TktkDX12BaseComponents/Components.h>
#include "../../ResourceHandleCarrier/ResourceHandleCarrier.h"

struct PointLightObject
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position)
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::Transform3DMaker::makeStart(gameObject)
			.initPosition(position)
			.initRotation(tktkMath::Quaternion::createLookRotation(-position))
			.create();

		tktk::SphereMeshDrawerMaker::makeStart(gameObject)
			.albedoColor({ 1.0f, 1.0f, 0.0f, 1.0f })
			.useRtvDescriptorHeapHandle(ResourceHandleCarrier::getPostEffectRtvDescriptorHeapHandle())
			.create();

		tktk::OrthographicCameraControllerMaker::makeStart(gameObject)
			.initCameraWidth(100.0f)
			.initCameraHeight(100.0f)
			.initCameraHandle(tktk::DX12GameManager::getSystemHandle(tktk::SystemCameraType::DefaultShadowMapCamera))
			.create();

		tktk::PointLightControllerMaker::makeStart(gameObject)
			.initAmbient({ 0.5f, 1.0f })
			/*.initAmbient(tktkMath::Color_v::black)
			.initSpeqular(tktkMath::Color_v::white)
			.initDiffuse(tktkMath::Color_v::white)*/
			.create();

		return gameObject;
	}
};