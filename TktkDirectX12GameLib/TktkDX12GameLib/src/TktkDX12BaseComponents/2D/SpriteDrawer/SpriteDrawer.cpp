#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12Game/DXGameResource/Sprite/SpriteTransformCbuffer.h"

namespace tktk
{
	SpriteDrawer::SpriteDrawer(float drawPriority, unsigned int spriteMaterialHandle, unsigned int useRtvDescriptorHeapHandle, const tktkMath::Vector2& centerRate)
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

		// �R�s�[�p�o�b�t�@�����A���̃n���h�����擾����
		m_createCopyTransformCbufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::SpriteTransform), SpriteTransformCbuffer());
	}

	void SpriteDrawer::onDestroy()
	{
		// �R�s�[�p�o�b�t�@���폜����
		DX12GameManager::eraseCopyBuffer(m_createCopyTransformCbufferHandle);
	}

	void SpriteDrawer::draw() const
	{
		// ���W�ϊ��p�̒萔�o�b�t�@�̍X�V
		DX12GameManager::updateSpriteTransformCbuffer(m_spriteMaterialHandle, m_createCopyTransformCbufferHandle, m_transform->calculateWorldMatrix(), m_spriteCenterRate);

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

	void SpriteDrawer::setCenterRate(const tktkMath::Vector2& centerRate)
	{
		m_spriteCenterRate = centerRate;
	}

	void SpriteDrawer::setSpriteMaterialIdImpl(int id)
	{
		m_spriteMaterialHandle = DX12GameManager::getSpriteMaterialHandle(id);
	}
}