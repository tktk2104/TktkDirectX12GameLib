#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteClippingDrawer.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteTransformCbuffer.h"
#include "TktkDX12BaseComponents/2D/Transform2D/Transform2D.h"

namespace tktk
{
	SpriteClippingDrawer::SpriteClippingDrawer(float drawPriority, size_t spriteMaterialHandle, size_t useRtvDescriptorHeapHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate, const SpriteClippingParam& clippingParam)
		: ComponentBase(drawPriority)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
		, m_spriteMaterialHandle(spriteMaterialHandle)
		, m_spriteCenterRate(centerRate)
		, m_blendRate(blendRate)
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

		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadTransformCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::SpriteTransform), SpriteTransformCbuffer()));
	}

	void SpriteClippingDrawer::onDestroy()
	{
		// �A�b�v���[�h�p�o�b�t�@���폜����
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
	}

	void SpriteClippingDrawer::draw() const
	{
		// ���W�ϊ��p�̒萔�o�b�t�@�̍X�V
		SpriteCbufferUpdateFuncArgs updateFuncArgs{};
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

	const tktkMath::Color& SpriteClippingDrawer::getBlendRate() const
	{
		return m_blendRate;
	}

	void SpriteClippingDrawer::setBlendRate(const tktkMath::Color& blendRate)
	{
		m_blendRate = blendRate;
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