#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteMaterialInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteTransformCbuffer.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteMaterialCbufferData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteMaterialDrawFuncArgs.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteCbufferUpdateFuncArgs.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteClippingParam.h"

namespace tktk
{
	SpriteMaterialData::SpriteMaterialData(const SpriteMaterialInitParam& initParam)
		: m_blendRate(initParam.blendRate)
		, m_textureUvOffset(initParam.textureUvOffset)
		, m_textureUvMulRate(initParam.textureUvMulRate)
	{
		// �f�B�X�N���v�^�q�[�v�����
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(3U);

		{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

			// �X�v���C�g�e�N�X�`���̂P���
			srvDescriptorParam.descriptorParamArray = {
				{ initParam.srvBufferType, initParam.useBufferHandle }
			};
		}

		{ /* �R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// �}�e���A���萔�o�b�t�@�ƍ��W�ϊ��萔�o�b�t�@�̂Q���
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::SpriteMaterialManager) },
				{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::SpriteTransform) }
			};
		}

		{ /* �R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// �}�e���A���萔�o�b�t�@�̂P���
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::SpriteMaterialManager) }
			};
		}

		tktkMath::Vector3 textureBufferSize = tktkMath::Vector3_v::zero;

		switch (initParam.srvBufferType)
		{
		case BufferType::texture:

			textureBufferSize = DX12GameManager::getTextureBufferSizePx(initParam.useBufferHandle);
			m_textureSize = { textureBufferSize.x, textureBufferSize.y };
			break;

		case BufferType::renderTarget:

			m_textureSize = DX12GameManager::getRtBufferSizePx(initParam.useBufferHandle);
			break;

		case BufferType::depthStencil:

			m_textureSize = DX12GameManager::getDsBufferSizePx(initParam.useBufferHandle);
			break;
		}

		m_createDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);

		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadBufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::SpriteMaterialManager), SpriteMaterialCbufferData()));
	}

	SpriteMaterialData::~SpriteMaterialData()
	{
		// ������f�B�X�N���v�^�q�[�v���폜����
		DX12GameManager::eraseBasicDescriptorHeap(m_createDescriptorHeapHandle);

		// �A�b�v���[�h�p�o�b�t�@���폜����
		DX12GameManager::eraseUploadBuffer(m_createUploadBufferHandle);
	}

	SpriteMaterialData::SpriteMaterialData(SpriteMaterialData&& other) noexcept
		: m_createDescriptorHeapHandle(other.m_createDescriptorHeapHandle)
		, m_createUploadBufferHandle(other.m_createUploadBufferHandle)
		, m_blendRate(other.m_blendRate)
		, m_textureUvOffset(other.m_textureUvOffset)
		, m_textureUvMulRate(other.m_textureUvMulRate)
		, m_textureSize(other.m_textureSize)
	{
		other.m_createDescriptorHeapHandle = 0U;
		other.m_createUploadBufferHandle = 0U;
	}

	void SpriteMaterialData::drawSprite(const SpriteMaterialDrawFuncArgs& drawFuncArgs) const
	{
		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		updateCopyBuffer();

		// �X�v���C�g�p�萔�o�b�t�@�ɃA�b�v���[�h�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createUploadBufferHandle);

		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(drawFuncArgs.viewportHandle);

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(drawFuncArgs.scissorRectHandle);

		// �����_�[�^�[�Q�b�g��ݒ肷��i�o�b�N�o�b�t�@�[�ɒ��ŕ`�悷��ꍇ�͓��ꏈ���j
		if (drawFuncArgs.rtvDescriptorHeapHandle == DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferView();
		}
		else
		{
			DX12GameManager::setRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}

		// �X�v���C�g�p�̃p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemHandle(SystemPipeLineStateType::Sprite));

		// �u�����h�t�@�N�^�[��ݒ肷��
		DX12GameManager::setBlendFactor({ 1.0f, 1.0f, 1.0f, 1.0f });

		// �X�v���C�g�p�̃f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_createDescriptorHeapHandle} });

		// �g���C�A���O���X�g���b�v�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(PrimitiveTopology::TriangleStrip);

		// �X�v���C�g�p�̒��_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemHandle(SystemVertexBufferType::Sprite));

		// �X�v���C�g�p�̃C���f�b�N�X�o�b�t�@��ݒ肷��
		DX12GameManager::setIndexBuffer(DX12GameManager::getSystemHandle(SystemIndexBufferType::Sprite));

		// �h���[�R�[��
		DX12GameManager::drawIndexedInstanced(4U, 1U, 0U, 0U, 0U);

		// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
		if (drawFuncArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}
	}

	void SpriteMaterialData::updateTransformCbuffer(size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs) const
	{
		// �X�v���C�g�̍��W�ϊ��p�萔�o�b�t�@�`��
		SpriteTransformCbuffer transformBufferData{};

		for (size_t i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			transformBufferData.worldMatrix[i] = cbufferUpdateArgs.worldMatrix.m[i / 4U][i % 4U];
		}
		transformBufferData.textureUvOffset		= m_textureUvOffset;
		transformBufferData.textureUvMulRate	= m_textureUvMulRate;
		transformBufferData.textureSize			= m_textureSize;
		transformBufferData.spriteCenterRate	= cbufferUpdateArgs.spriteCenterRate;

		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateUploadBuffer(copyBufferHandle, transformBufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�ɃA�b�v���[�h�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(copyBufferHandle);
	}

	void SpriteMaterialData::updateTransformCbufferUseClippingParam(size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs, const SpriteClippingParam& clippingParam) const
	{
		// �X�v���C�g�̍��W�ϊ��p�萔�o�b�t�@�`��
		SpriteTransformCbuffer transformBufferData{};

		for (size_t i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			transformBufferData.worldMatrix[i] = cbufferUpdateArgs.worldMatrix.m[i / 4U][i % 4U];
		}
		transformBufferData.textureUvOffset		= tktkMath::Vector2(clippingParam.leftTopPos.x / m_textureSize.x, clippingParam.leftTopPos.y / m_textureSize.y) + m_textureUvOffset;
		transformBufferData.textureUvMulRate	= tktkMath::Vector2(clippingParam.size.x / m_textureSize.x * m_textureUvMulRate.x, clippingParam.size.y / m_textureSize.y * m_textureUvMulRate.y);
		transformBufferData.textureSize			= clippingParam.size;
		transformBufferData.spriteCenterRate	= cbufferUpdateArgs.spriteCenterRate;

		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateUploadBuffer(copyBufferHandle, transformBufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�ɃA�b�v���[�h�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(copyBufferHandle);
	}

	// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
	void SpriteMaterialData::updateCopyBuffer() const
	{
		SpriteMaterialCbufferData constantBufferData;
		constantBufferData.blendRate		= m_blendRate;
		constantBufferData.screenSize		= DX12GameManager::getWindowSize();

		DX12GameManager::updateUploadBuffer(m_createUploadBufferHandle, constantBufferData);
	}
}