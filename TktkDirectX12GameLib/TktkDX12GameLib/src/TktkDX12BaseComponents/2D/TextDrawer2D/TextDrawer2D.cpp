#include "TktkDX12BaseComponents/2D/TextDrawer2D/TextDrawer2D.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12BaseComponents/2D/Transform2D/Transform2D.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/Structs/SpriteTransformCBufferData.h"

namespace tktk
{
	TextDrawer2D::TextDrawer2D(float drawPriority, size_t fontHandle, const std::string& initText, size_t useRtvDescriptorHeapHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate)
		: ComponentBase(drawPriority)
		, m_fontHandle(fontHandle)
		, m_tempText(initText)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
		, m_spriteCenterRate(centerRate)
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

		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadTransformCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::SpriteTransform), SpriteTransformCBufferData()));
		
		// �e�L�X�g�`��p�A�b�v���[�h�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadTextureBufferHandle = DX12GameManager::createTextTextureUploadBuffer();
	}

	void TextDrawer2D::onDestroy()
	{
		// �A�b�v���[�h�p�o�b�t�@���폜����
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
		DX12GameManager::eraseUploadBuffer(m_createUploadTextureBufferHandle);
	}

	void TextDrawer2D::afterCollide()
	{
		if (m_tempText.empty()) return;

		auto size = DX12GameManager::updateTextTextureUploadBuffData(m_fontHandle, m_createUploadTextureBufferHandle, m_tempText);

		m_clippingParam.leftTopPos = tktkMath::Vector2_v::zero;
		m_clippingParam.size = { static_cast<float>(size), 64.0f };

		m_tempText.clear();
	}

	void TextDrawer2D::draw() const
	{
		// ���W�ϊ��p�̒萔�o�b�t�@�̍X�V
		SpriteCBufferUpdateFuncArgs updateFuncArgs{};
		updateFuncArgs.worldMatrix		= m_transform->calculateWorldMatrix();
		updateFuncArgs.spriteCenterRate = m_spriteCenterRate;
		DX12GameManager::updateSpriteTransformCbufferUseClippingParam(DX12GameManager::getSystemHandle(SystemSpriteType::Text), m_createUploadTransformCbufferHandle, updateFuncArgs, m_clippingParam);

		// �t�H���g�e�N�X�`���̃A�b�v���[�h
		DX12GameManager::copyBuffer(m_createUploadTextureBufferHandle);

		SpriteMaterialDrawFuncArgs drawFuncArgs{};
		drawFuncArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		drawFuncArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapHandle	= m_useRtvDescriptorHeapHandle;
		drawFuncArgs.blendRate					= m_blendRate;

		DX12GameManager::drawSprite(DX12GameManager::getSystemHandle(SystemSpriteType::Text), drawFuncArgs);
	}
}