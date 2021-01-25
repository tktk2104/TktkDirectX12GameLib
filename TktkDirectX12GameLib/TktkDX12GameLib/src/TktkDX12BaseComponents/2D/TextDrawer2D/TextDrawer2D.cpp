#include "TktkDX12BaseComponents/2D/TextDrawer2D/TextDrawer2D.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12BaseComponents/2D/Transform2D/Transform2D.h"

namespace tktk
{
	TextDrawer2D::TextDrawer2D(float drawPriority, size_t fontHandle, const std::string& initText, const tktkMath::Vector2& localPosition, const tktkMath::Vector2& localScale, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate)
		: m_drawPriority(drawPriority)
		, m_fontHandle(fontHandle)
		, m_tempText(initText)
		, m_localPosition(localPosition)
		, m_localScale(localScale)
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
		size_t curInstanceCount = DX12GameManager::getCurSpriteInstanceCount((DX12GameManager::getSystemHandle(SystemSpriteType::Text)));

		size_t maxInstanceCount = DX12GameManager::getMaxSpriteInstanceCount((DX12GameManager::getSystemHandle(SystemSpriteType::Text)));

		if (curInstanceCount >= maxInstanceCount) return;

		if (!m_tempText.empty())
		{
			m_useTextureDataWidth = static_cast<float>(DX12GameManager::updateTextTextureData(m_fontHandle, m_tempText, &m_textureData));
			m_tempText.clear();
		}

		DX12GameManager::updateUploadBuffer(DX12GameManager::getSystemHandle(SystemUploadBufferType::TextTexture), CopySourceDataCarrier(m_textureData.size(), m_textureData.data(), DX12GameManager::getTextTextureLineDataSize() * curInstanceCount));

		TempSpriteMaterialInstanceData instanceVertData{};

		instanceVertData.worldMatrix			= tktkMath::Matrix3::createScale(m_localScale) * tktkMath::Matrix3::createTranslation(m_localPosition) * m_transform->calculateWorldMatrix();
		instanceVertData.texturePixelOffset		= tktkMath::Vector2(0.0f,					64.0f * curInstanceCount);
		instanceVertData.texturePixelCount		= tktkMath::Vector2(m_useTextureDataWidth,	64.0f);
		instanceVertData.textureUvMulRate		= tktkMath::Vector2_v::one;
		instanceVertData.textureCenterRate		= m_centerRate;
		instanceVertData.blendRate				= m_blendRate;

		// テキストスプライトをインスタンス描画する時に使用する値を追加する
		DX12GameManager::addSpriteInstanceParam(DX12GameManager::getSystemHandle(SystemSpriteType::Text), m_drawPriority, instanceVertData);
	}

	void TextDrawer2D::setFontId(ResourceIdCarrier fontId)
	{
		m_fontHandle = DX12GameManager::getFontHandle(fontId);
	}

	void TextDrawer2D::updateText(const std::string& text)
	{
		m_tempText = text;
	}

	void TextDrawer2D::setLocalPosition(const tktkMath::Vector2& localPosition)
	{
		m_localPosition = localPosition;
	}

	void TextDrawer2D::setLocalScale(const tktkMath::Vector2& localScale)
	{
		m_localScale = localScale;
	}

	void TextDrawer2D::setCenterRate(const tktkMath::Vector2& centerRate)
	{
		m_centerRate = centerRate;
	}

	void TextDrawer2D::setBlendRate(const tktkMath::Color& blendRate)
	{
		m_blendRate = blendRate;
	}
}