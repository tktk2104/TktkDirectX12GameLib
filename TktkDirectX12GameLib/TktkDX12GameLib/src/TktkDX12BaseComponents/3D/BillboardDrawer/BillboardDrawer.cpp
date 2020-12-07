#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawer.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"

namespace tktk
{
	BillboardDrawer::BillboardDrawer(size_t billboardMaterialHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate, const tktkMath::Vector2& clippingLeftTopPos, const tktkMath::Vector2& clippingSize)
		: m_billboardMaterialHandle(billboardMaterialHandle)
		, m_centerRate(centerRate)
		, m_blendRate(blendRate)
		, m_clippingLeftTopPos(clippingLeftTopPos)
		, m_clippingSize(clippingSize)
	{
	}

	void BillboardDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BillboardDrawer not found Transform3D");
		}
	}

	void BillboardDrawer::afterCollide()
	{
		const auto& selfScale = m_transform->getWorldScaleRate();

		BillboardMaterialInstanceVertData instanceVertData{};
		instanceVertData.billboardPosition	= m_transform->getWorldPosition();
		instanceVertData.billboardAngle		= m_transform->calculateWorldEulerAngles().z;
		instanceVertData.billboardScale		= { selfScale.x, selfScale.y };;
		instanceVertData.textureUvOffset	= tktkMath::Vector2(m_clippingLeftTopPos.x, m_clippingLeftTopPos.y);
		instanceVertData.textureUvMulRate	= tktkMath::Vector2(m_clippingSize.x, m_clippingSize.y);
		instanceVertData.textureCenterRate	= m_centerRate;
		instanceVertData.blendRate			= m_blendRate;

		// 指定のビルボードをインスタンス描画する時に使用する値を追加する
		DX12GameManager::addBillboardInstanceVertParam(m_billboardMaterialHandle, instanceVertData);
	}

	void BillboardDrawer::setBillboardMaterialHandle(size_t handle)
	{
		m_billboardMaterialHandle = handle;
	}

	void BillboardDrawer::setBillboardMaterialId(ResourceIdCarrier id)
	{
		m_billboardMaterialHandle = DX12GameManager::getBillboardMaterialHandle(id);
	}

	void BillboardDrawer::setCenterRate(const tktkMath::Vector2& centerRate)
	{
		m_centerRate = centerRate;
	}

	void BillboardDrawer::setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos)
	{
		m_clippingLeftTopPos = leftTopPos;
	}

	void BillboardDrawer::setClippingSize(const tktkMath::Vector2& size)
	{
		m_clippingSize = size;
	}

	void BillboardDrawer::setClippingLeftTopPosRate(const tktkMath::Vector2& leftTopPosRate)
	{
		const auto& textureSize = DX12GameManager::getBillboardTextureSize(m_billboardMaterialHandle);

		m_clippingLeftTopPos = tktkMath::Vector2::scale(textureSize, leftTopPosRate);
	}

	void BillboardDrawer::setClippingSizeRate(const tktkMath::Vector2& sizeRate)
	{
		const auto& textureSize = DX12GameManager::getBillboardTextureSize(m_billboardMaterialHandle);

		m_clippingSize = tktkMath::Vector2::scale(textureSize, sizeRate);
	}
}