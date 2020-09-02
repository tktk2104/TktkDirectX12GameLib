#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12Game/DXGameResource/Sprite/SpriteTransformCbuffer.h"

namespace tktk
{
	SpriteDrawer::SpriteDrawer(float drawPriority, unsigned int spriteMaterialHandle, unsigned int useRtvDescriptorHeapHandle)
		: ComponentBase(drawPriority)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
		, m_spriteMaterialHandle(spriteMaterialHandle)
	{
	}

	void SpriteDrawer::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}

		// コピー用バッファを作り、そのハンドルを取得する
		m_createCopyTransformCbufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::SpriteTransform), SpriteTransformCbuffer());
	}

	void SpriteDrawer::onDestroy()
	{
		// コピー用バッファを削除する
		DX12GameManager::eraseCopyBuffer(m_createCopyTransformCbufferHandle);
	}

	void SpriteDrawer::draw() const
	{
		// 座標変換用の定数バッファの更新
		updateTransformCbuffer();

		SpriteMaterialDrawFuncArgs drawFuncArgs{};

		drawFuncArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		drawFuncArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapHandle	= m_useRtvDescriptorHeapHandle;

		DX12GameManager::drawSprite(m_spriteMaterialHandle, drawFuncArgs);
	}

	void SpriteDrawer::setSpriteMaterialHandle(unsigned int handle)
	{
		m_spriteMaterialHandle = handle;
	}

	void SpriteDrawer::setSpriteMaterialIdImpl(int id)
	{
		m_spriteMaterialHandle = DX12GameManager::getSpriteMaterialHandle(id);
	}

	void SpriteDrawer::updateTransformCbuffer() const
	{
		// スプライトの座標変換用定数バッファ形式
		SpriteTransformCbuffer transformBufferData{};

		auto worldMatrix = m_transform->calculateWorldMatrix();

		for (unsigned int i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			transformBufferData.worldMatrix[i] = worldMatrix.m[i / 4U][i % 4U];
		}

		// 定数バッファのコピー用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateCopyBuffer(m_createCopyTransformCbufferHandle, transformBufferData);

		// 座標変換用の定数バッファにコピーバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createCopyTransformCbufferHandle);
	}
}