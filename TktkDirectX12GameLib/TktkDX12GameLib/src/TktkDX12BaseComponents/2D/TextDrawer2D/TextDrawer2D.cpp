#include "TktkDX12BaseComponents/2D/TextDrawer2D/TextDrawer2D.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12BaseComponents/2D/Transform2D/Transform2D.h"

namespace tktk
{
	TextDrawer2D::TextDrawer2D(float drawPriority, size_t fontHandle, const std::string& initText, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate)
		: m_drawPriority(drawPriority)
		, m_fontHandle(fontHandle)
		, m_tempText(initText)
		, m_centerRate(centerRate)
		, m_blendRate(blendRate)
	{
	}

	void TextDrawer2D::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
	}

	void TextDrawer2D::afterCollide()
	{
		if (m_tempText.empty()) return;

		size_t curInstanceCount = DX12GameManager::getCurSpriteInstanceCount((DX12GameManager::getSystemHandle(SystemSpriteType::Text)));

		size_t maxInstanceCount = DX12GameManager::getMaxSpriteInstanceCount((DX12GameManager::getSystemHandle(SystemSpriteType::Text)));

		if (curInstanceCount >= maxInstanceCount) return;

		TempSpriteMaterialInstanceData instanceVertData{};

		auto size = DX12GameManager::updateTextTextureUploadBuffData(m_fontHandle, m_tempText);

		instanceVertData.worldMatrix			= m_transform->calculateWorldMatrix();
		instanceVertData.texturePixelOffset		= tktkMath::Vector2(0.0f,						64.0f * curInstanceCount);//
		instanceVertData.texturePixelCount		= tktkMath::Vector2(static_cast<float>(size),	64.0f);
		instanceVertData.textureUvMulRate		= tktkMath::Vector2_v::one;
		instanceVertData.textureCenterRate		= m_centerRate;
		instanceVertData.blendRate				= m_blendRate;

		// テキストスプライトをインスタンス描画する時に使用する値を追加する
		DX12GameManager::addSpriteInstanceParam(DX12GameManager::getSystemHandle(SystemSpriteType::Text), m_drawPriority, instanceVertData);

		//m_tempText.clear();
	}

	//void TextDrawer2D::draw() const
	//{
	//	// 座標変換用の定数バッファの更新
	//	SpriteCBufferUpdateFuncArgs updateFuncArgs{};
	//	updateFuncArgs.worldMatrix		= m_transform->calculateWorldMatrix();
	//	updateFuncArgs.spriteCenterRate = m_spriteCenterRate;
	//	DX12GameManager::updateSpriteTransformCbufferUseClippingParam(DX12GameManager::getSystemHandle(SystemSpriteType::Text), m_createUploadTransformCbufferHandle, updateFuncArgs, m_clippingParam);
	//
	//	// フォントテクスチャのアップロード
	//	DX12GameManager::copyBuffer(m_createUploadTextureBufferHandle);
	//
	//	SpriteMaterialDrawFuncArgs drawFuncArgs{};
	//	drawFuncArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
	//	drawFuncArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
	//	drawFuncArgs.rtvDescriptorHeapHandle	= m_useRtvDescriptorHeapHandle;
	//	drawFuncArgs.blendRate					= m_blendRate;
	//
	//	DX12GameManager::drawSprite(DX12GameManager::getSystemHandle(SystemSpriteType::Text), drawFuncArgs);
	//}
}