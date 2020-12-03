#pragma once

#include <TktkDX12Game/TktkDX12Game.h>
#include <TktkDX12BaseComponents/Components.h>
#include "../../ResourceHandleCarrier/ResourceHandleCarrier.h"
#include "../../Enum/_ResourceIds/ResourceIds.h"

struct BillboardTest
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position)
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::Transform3DMaker::makeStart(gameObject)
			.initPosition(position)
			.initScaleRate(10)
			.create();

		tktk::SphereMeshDrawerMaker::makeStart(gameObject)
			.radius(0.5f)
			.localPosition({ 2.0f, 0.0f, 0.0f })
			.create();

		tktk::BillboardDrawerMaker::makeStart(gameObject)
			.drawPriority(1.0f)
			.billboardMaterialId(BillboardId::test)
			.blendRate(tktkMath::Color_v::blue)
			//.useRtvDescriptorHeapHandle(ResourceHandleCarrier::getPostEffectRtvDescriptorHeapHandle())
			.create();

		return gameObject;
	}
};