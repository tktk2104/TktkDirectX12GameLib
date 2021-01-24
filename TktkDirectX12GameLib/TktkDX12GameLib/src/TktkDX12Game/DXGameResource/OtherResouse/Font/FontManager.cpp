#include "TktkDX12Game/DXGameResource/OtherResouse/Font/FontManager.h"

#include "TktkDX12Game/DXGameResource/OtherResouse/Font/FontData.h"
#include "TktkDX12Game/DXGameResource/OtherResouse/Font/Structs/FontManagerInitParam.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	FontManager::FontManager(const FontManagerInitParam& initParam)
		: m_fontDataContainer(initParam.containerInitParam)
		, m_fontHeight(initParam.fontHeight)
		, m_textTextureWidth(initParam.textTextureWidth)
		, m_textSpriteMaxInstanceCount(initParam.textSpriteMaxInstanceCount)
	{
	}

	// デストラクタを非インライン化する
	FontManager::~FontManager() = default;

	void FontManager::createFontBaseResource()
	{
		TexBufFormatParam formatParam{};
		formatParam.resourceDimension	= D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		formatParam.format				= DXGI_FORMAT_R8G8B8A8_UNORM;
		formatParam.arraySize			= 1U;
		formatParam.mipLevels			= 1U;
		formatParam.sampleDescCount		= 1U;
		formatParam.sampleDescQuality	= 0U;

		TexBuffData dataParam{};
		dataParam.textureData	= std::vector<unsigned char>(static_cast<size_t>(m_textTextureWidth * m_fontHeight * m_textSpriteMaxInstanceCount * 4U));
		dataParam.width			= static_cast<unsigned int>(m_textTextureWidth);
		dataParam.height		= static_cast<unsigned int>(m_fontHeight * m_textSpriteMaxInstanceCount);
		dataParam.depth			= 1;

		// テキスト描画用のテクスチャバッファを作る
		auto textureBufferHandle = DX12GameManager::createTextureBuffer(formatParam, dataParam);

		DX12GameManager::setSystemHandle(SystemTextureBufferType::Text, textureBufferHandle);

		SpriteMaterialInitParam spriteMaterialInitParam{};
		spriteMaterialInitParam.srvBufferType		= BufferType::texture;
		spriteMaterialInitParam.useBufferHandle		= textureBufferHandle;
		spriteMaterialInitParam.maxInstanceCount	= m_textSpriteMaxInstanceCount;

		// テキスト描画用のスプライトマテリアルを作る
		DX12GameManager::setSystemHandle(SystemSpriteType::Text, DX12GameManager::createSpriteMaterial(spriteMaterialInitParam, SpriteDrawFuncRunnerInitParam::create().drawPriority(9000.0f)));
	
		// テキスト描画用のテクスチャバッファのアップロードバッファを作る
		DX12GameManager::setSystemHandle(SystemUploadBufferType::TextTexture, DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::texture, textureBufferHandle, dataParam.textureData)));
	}

	size_t FontManager::create(const std::string& systemFontName, float fontThicknessRate)
	{
		return m_fontDataContainer.create(systemFontName, m_fontHeight, fontThicknessRate);
	}

	size_t FontManager::create(const std::string& fontFilePath, const std::string& fontName, float fontThicknessRate)
	{
		return m_fontDataContainer.create(fontFilePath, fontName, m_fontHeight, fontThicknessRate);
	}

	size_t FontManager::updateTextTextureData(size_t handle, const std::string& text, std::vector<unsigned char>* data)
	{
		return m_fontDataContainer.getMatchHandlePtr(handle)->updateTextTextureData(text, m_fontHeight, m_textTextureWidth, data);
	}

	unsigned int FontManager::getTextTextureLineDataSize() const
	{
		return m_textTextureWidth * m_fontHeight * 4U;
	}

	//size_t FontManager::updateTextTextureUploadBuffData(size_t handle, const std::string& text)
	//{
	//	return m_fontDataContainer.getMatchHandlePtr(handle)->updateTextTextureUploadBuffData(text, m_fontHeight, m_textTextureWidth);
	//}

	void FontManager::copyTextTextureUploadBuffer()
	{
		DX12GameManager::copyBuffer(DX12GameManager::getSystemHandle(SystemUploadBufferType::TextTexture));
	}
}