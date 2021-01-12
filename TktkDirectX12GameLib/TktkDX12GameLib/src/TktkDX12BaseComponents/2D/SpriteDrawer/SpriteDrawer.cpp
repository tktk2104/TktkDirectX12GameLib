#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12BaseComponents/2D/Transform2D/Transform2D.h"

namespace tktk
{
	SpriteDrawer::SpriteDrawer(float drawPriority, size_t spriteMaterialHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate, const tktkMath::Vector2& clippingLeftTopPos, const tktkMath::Vector2& clippingSize)
		: ComponentBase(drawPriority)
		, m_spriteMaterialHandle(spriteMaterialHandle)
		, m_centerRate(centerRate)
		, m_blendRate(blendRate)
		, m_clippingLeftTopPos(clippingLeftTopPos)
		, m_clippingSize(clippingSize)
	{
	}

	void SpriteDrawer::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
	}

	void SpriteDrawer::afterCollide()
	{
		const auto& selfScale = m_transform->getWorldScaleRate();

		TempSpriteMaterialInstanceData instanceVertData{};

		auto worldMatrix = m_transform->calculateWorldMatrix();

		instanceVertData.worldMatrix		= worldMatrix;
		instanceVertData.texturePixelOffset = tktkMath::Vector2(m_clippingLeftTopPos.x, m_clippingLeftTopPos.y);
		instanceVertData.texturePixelCount	= tktkMath::Vector2(m_clippingSize.x, m_clippingSize.y);
		instanceVertData.textureUvMulRate	= tktkMath::Vector2_v::one;
		instanceVertData.textureCenterRate	= m_centerRate;
		instanceVertData.blendRate			= m_blendRate;

		// 指定のスプライトをインスタンス描画する時に使用する値を追加する
		DX12GameManager::addSpriteInstanceParam(m_spriteMaterialHandle, m_drawPriority, instanceVertData);
	}

	void SpriteDrawer::setSpriteMaterialHandle(size_t handle)
	{
		m_spriteMaterialHandle = handle;
	}

	void SpriteDrawer::setSpriteMaterialId(ResourceIdCarrier id)
	{
		m_spriteMaterialHandle = DX12GameManager::getSpriteMaterialHandle(id);
	}

	void SpriteDrawer::setCenterRate(const tktkMath::Vector2& centerRate)
	{
		m_centerRate = centerRate;
	}

	const tktkMath::Color& SpriteDrawer::getBlendRate() const
	{
		return m_blendRate;
	}

	void SpriteDrawer::setBlendRate(const tktkMath::Color& blendRate)
	{
		m_blendRate = blendRate;
	}

	void SpriteDrawer::setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos)
	{
		m_clippingLeftTopPos = leftTopPos;
	}

	void SpriteDrawer::setClippingSize(const tktkMath::Vector2& size)
	{
		m_clippingSize = size;
	}

	void SpriteDrawer::setClippingLeftTopPosRate(const tktkMath::Vector2& leftTopPosRate)
	{
		const auto& textureSize = DX12GameManager::getSpriteTextureSize(m_spriteMaterialHandle);

		m_clippingLeftTopPos = tktkMath::Vector2::scale(textureSize, leftTopPosRate);
	}

	void SpriteDrawer::setClippingSizeRate(const tktkMath::Vector2& sizeRate)
	{
		const auto& textureSize = DX12GameManager::getSpriteTextureSize(m_spriteMaterialHandle);

		m_clippingSize = tktkMath::Vector2::scale(textureSize, sizeRate);
	}
}