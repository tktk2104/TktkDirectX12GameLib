#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12BaseComponents/2D/Transform2D/Transform2D.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/Structs/SpriteTransformCBufferData.h"

namespace tktk
{
	SpriteDrawer::SpriteDrawer(float drawPriority, size_t spriteMaterialHandle, size_t useRtvDescriptorHeapHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate, const SpriteClippingParam& clippingParam)
		: ComponentBase(drawPriority)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
		, m_spriteMaterialHandle(spriteMaterialHandle)
		, m_spriteCenterRate(centerRate)
		, m_blendRate(blendRate)
		, m_clippingParam(clippingParam)
	{
	}

	void SpriteDrawer::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}

		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadTransformCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::SpriteTransform), SpriteTransformCBufferData()));
	}

	void SpriteDrawer::onDestroy()
	{
		// アップロード用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
	}

	void SpriteDrawer::draw() const
	{
		// 座標変換用の定数バッファの更新
		SpriteCBufferUpdateFuncArgs updateFuncArgs{};
		updateFuncArgs.worldMatrix = m_transform->calculateWorldMatrix();
		updateFuncArgs.spriteCenterRate = m_spriteCenterRate;
		DX12GameManager::updateSpriteTransformCbufferUseClippingParam(m_spriteMaterialHandle, m_createUploadTransformCbufferHandle, updateFuncArgs, m_clippingParam);

		SpriteMaterialDrawFuncArgs drawFuncArgs{};
		drawFuncArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		drawFuncArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapHandle	= m_useRtvDescriptorHeapHandle;
		drawFuncArgs.blendRate					= m_blendRate;

		DX12GameManager::drawSprite(m_spriteMaterialHandle, drawFuncArgs);
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
		m_spriteCenterRate = centerRate;
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
		m_clippingParam.leftTopPos = leftTopPos;
	}

	void SpriteDrawer::setClippingSize(const tktkMath::Vector2& size)
	{
		m_clippingParam.size = size;
	}

	void SpriteDrawer::setClippingLeftTopPosRate(const tktkMath::Vector2& leftTopPosRate)
	{
		const auto& textureSize = DX12GameManager::getSpriteTextureSize(m_spriteMaterialHandle);

		m_clippingParam.leftTopPos = tktkMath::Vector2::scale(textureSize, leftTopPosRate);
	}

	void SpriteDrawer::setClippingSizeRate(const tktkMath::Vector2& sizeRate)
	{
		const auto& textureSize = DX12GameManager::getSpriteTextureSize(m_spriteMaterialHandle);

		m_clippingParam.size = tktkMath::Vector2::scale(textureSize, sizeRate);
	}
}