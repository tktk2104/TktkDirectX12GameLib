#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12Game/DXGameResource/Sprite/SpriteTransformCbuffer.h"

namespace tktk
{
	SpriteDrawer::SpriteDrawer(float drawPriority, size_t spriteMaterialHandle, size_t useRtvDescriptorHeapHandle, const tktkMath::Vector2& centerRate)
		: ComponentBase(drawPriority)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
		, m_spriteMaterialHandle(spriteMaterialHandle)
		, m_spriteCenterRate(centerRate)
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
		m_createUploadTransformCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::SpriteTransform), SpriteTransformCbuffer()));
	}

	void SpriteDrawer::onDestroy()
	{
		// アップロード用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
	}

	void SpriteDrawer::draw() const
	{
		// 座標変換用の定数バッファの更新
		DX12GameManager::updateSpriteTransformCbuffer(m_spriteMaterialHandle, m_createUploadTransformCbufferHandle, m_transform->calculateWorldMatrix(), m_spriteCenterRate);

		SpriteMaterialDrawFuncArgs drawFuncArgs{};
		drawFuncArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		drawFuncArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapHandle	= m_useRtvDescriptorHeapHandle;

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
}