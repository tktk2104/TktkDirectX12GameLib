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
		// �X�v���C�g�̍��W�ϊ��p�萔�o�b�t�@�`��
		SpriteTransformCbuffer transformBufferData{};

		auto worldMatrix = m_transform->calculateWorldMatrix();

		for (unsigned int i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			transformBufferData.worldMatrix[i] = worldMatrix.m[i / 4U][i % 4U];
		}

		// �萔�o�b�t�@�̃R�s�[�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateCopyBuffer(m_createCopyTransformCbufferHandle, transformBufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�ɃR�s�[�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createCopyTransformCbufferHandle);
	}
}