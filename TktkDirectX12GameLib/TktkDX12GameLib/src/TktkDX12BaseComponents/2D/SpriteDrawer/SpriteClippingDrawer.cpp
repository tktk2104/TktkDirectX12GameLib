#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteClippingDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12Game/DXGameResource/Sprite/SpriteTransformCbuffer.h"

namespace tktk
{
	SpriteClippingDrawer::SpriteClippingDrawer(float drawPriority, size_t spriteMaterialHandle, size_t useRtvDescriptorHeapHandle, const tktkMath::Vector2& centerRate, const SpriteClippingParam& clippingParam)
		: ComponentBase(drawPriority)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
		, m_spriteMaterialHandle(spriteMaterialHandle)
		, m_spriteCenterRate(centerRate)
		, m_clippingParam(clippingParam)
	{
	}

	void SpriteClippingDrawer::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}

		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadTransformCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::SpriteTransform), SpriteTransformCbuffer()));
	}

	void SpriteClippingDrawer::onDestroy()
	{
		// アップロード用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
	}

	void SpriteClippingDrawer::draw() const
	{
		// 座標変換用の定数バッファの更新
		DX12GameManager::updateSpriteTransformCbufferUseClippingParam(m_spriteMaterialHandle, m_createUploadTransformCbufferHandle, m_transform->calculateWorldMatrix(), m_spriteCenterRate, m_clippingParam);

		SpriteMaterialDrawFuncArgs drawFuncArgs{};
		drawFuncArgs.viewportHandle = DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		drawFuncArgs.scissorRectHandle = DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapHandle = m_useRtvDescriptorHeapHandle;

		DX12GameManager::drawSprite(m_spriteMaterialHandle, drawFuncArgs);
	}

	void SpriteClippingDrawer::setSpriteMaterialHandle(size_t handle)
	{
		m_spriteMaterialHandle = handle;
	}

	void SpriteClippingDrawer::setSpriteMaterialId(ResourceIdCarrier id)
	{
		m_spriteMaterialHandle = DX12GameManager::getSpriteMaterialHandle(id);
	}

	void SpriteClippingDrawer::setCenterRate(const tktkMath::Vector2& centerRate)
	{
		m_spriteCenterRate = centerRate;
	}

	void SpriteClippingDrawer::setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos)
	{
		m_clippingParam.leftTopPos = leftTopPos;
	}

	void SpriteClippingDrawer::setClippingSize(const tktkMath::Vector2& size)
	{
		m_clippingParam.size = size;
	}
}