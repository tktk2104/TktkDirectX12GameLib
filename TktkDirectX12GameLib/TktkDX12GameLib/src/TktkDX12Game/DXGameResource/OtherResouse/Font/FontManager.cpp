#include "TktkDX12Game/DXGameResource/OtherResouse/Font/FontManager.h"

#include "TktkDX12Game/DXGameResource/OtherResouse/Font/FontData.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	FontManager::FontManager(const tktkContainer::ResourceContainerInitParam& initParam, const tktkMath::Vector2& textTextureSize)
		: m_fontDataContainer(initParam)
		, m_textTextureSize(textTextureSize)
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
		dataParam.textureData	= std::vector<unsigned char>(static_cast<size_t>(m_textTextureSize.x * m_textTextureSize.y * 4U));
		dataParam.width			= static_cast<unsigned int>(m_textTextureSize.x);
		dataParam.height		= static_cast<unsigned int>(m_textTextureSize.y);
		dataParam.depth			= 1;

		// テキスト描画用のテクスチャバッファを作る
		auto textureBufferHandle = DX12GameManager::cpuPriorityCreateTextureBuffer(formatParam, dataParam);

		DX12GameManager::setSystemHandle(SystemTextureBufferType::Text, textureBufferHandle);

		SpriteMaterialInitParam spriteMaterialInitParam{};
		spriteMaterialInitParam.srvBufferType	= BufferType::texture;
		spriteMaterialInitParam.useBufferHandle = textureBufferHandle;

		DX12GameManager::setSystemHandle(SystemSpriteType::Text, DX12GameManager::createSpriteMaterial(spriteMaterialInitParam));
	}

	size_t FontManager::create(const std::string& systemFontName, int fontSize, float fontThicknessRate)
	{
		return m_fontDataContainer.create(systemFontName, fontSize, fontThicknessRate);
	}

	size_t FontManager::create(const std::string& fontFilePath, const std::string& fontName, int fontSize, float fontThicknessRate)
	{
		return m_fontDataContainer.create(fontFilePath, fontName, fontSize, fontThicknessRate);
	}

	size_t FontManager::updateTextTextureUploadBuffData(size_t handle, size_t uploadBufferHandle, const std::string& text)
	{
		return m_fontDataContainer.getMatchHandlePtr(handle)->updateTextTextureUploadBuffData(uploadBufferHandle, text, m_textTextureSize);
	}

	size_t FontManager::createUploadBuffer()
	{
		auto uploadTextureData = std::vector<unsigned char>(static_cast<size_t>(m_textTextureSize.x * m_textTextureSize.y * 4U));

		return DX12GameManager::createUploadBuffer(
			UploadBufferInitParam::create(BufferType::texture, DX12GameManager::getSystemHandle(SystemTextureBufferType::Text), uploadTextureData)
		);
	}
}