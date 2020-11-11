#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardCbufferData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardMaterialInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardDrawFuncBaseArgs.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardCbufferUpdateFuncArgs.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardClippingParam.h"

namespace tktk
{
	BillboardMaterialData::BillboardMaterialData(const BillboardMaterialInitParam& initParam)
		: m_textureUvOffset(initParam.textureUvOffset)
		, m_textureUvMulRate(initParam.textureUvMulRate)
	{
		// �f�B�X�N���v�^�q�[�v�����
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(2U);

		{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

			// �r���{�[�h�e�N�X�`���̂P���
			srvDescriptorParam.descriptorParamArray = {
				{ initParam.srvBufferType, initParam.useBufferHandle }
			};
		}

		{ /* �R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// �萔�o�b�t�@�P���
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Billboard) }
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
	}

	BillboardMaterialData::~BillboardMaterialData()
	{
		// ������f�B�X�N���v�^�q�[�v���폜����
		DX12GameManager::eraseBasicDescriptorHeap(m_createDescriptorHeapHandle);
	}

	BillboardMaterialData::BillboardMaterialData(BillboardMaterialData&& other) noexcept
		: m_createDescriptorHeapHandle(other.m_createDescriptorHeapHandle)
		, m_textureUvOffset(other.m_textureUvOffset)
		, m_textureUvMulRate(other.m_textureUvMulRate)
		, m_textureSize(other.m_textureSize)
	{
		other.m_createDescriptorHeapHandle = 0U;
	}

	void BillboardMaterialData::drawBillboard(const BillboardDrawFuncBaseArgs& drawFuncArgs) const
	{
		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(drawFuncArgs.viewportHandle);

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(drawFuncArgs.scissorRectHandle);

		// �����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V����ݒ肷��i�o�b�N�o�b�t�@�[�ɒ��ŕ`�悷��ꍇ�͓��ꏈ���j
		if (drawFuncArgs.rtvDescriptorHeapHandle == DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferViewAndDsv(drawFuncArgs.dsvDescriptorHeapHandle);
		}
		else
		{
			DX12GameManager::setRtvAndDsv(drawFuncArgs.rtvDescriptorHeapHandle, drawFuncArgs.dsvDescriptorHeapHandle, 0U, 1U);
		}

		// �r���{�[�h�p�̃p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemHandle(SystemPipeLineStateType::Billboard));

		// �u�����h�t�@�N�^�[��ݒ肷��
		DX12GameManager::setBlendFactor({ 1.0f, 1.0f, 1.0f, 1.0f });

		// �r���{�[�h�p�̃f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_createDescriptorHeapHandle} });

		// �g���C�A���O���X�g���b�v�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(PrimitiveTopology::TriangleStrip);

		// �r���{�[�h�p�̒��_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemHandle(SystemVertexBufferType::Sprite));

		// �r���{�[�h�p�̃C���f�b�N�X�o�b�t�@��ݒ肷��
		DX12GameManager::setIndexBuffer(DX12GameManager::getSystemHandle(SystemIndexBufferType::Sprite));

		// �h���[�R�[��
		DX12GameManager::drawIndexedInstanced(4U, 1U, 0U, 0U, 0U);

		// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
		if (drawFuncArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}

		// �[�x�X�e���V���o�b�t�@�[���V�F�[�_�[�Ŏg�����Ԃɂ���
		DX12GameManager::unSetDsv(drawFuncArgs.dsvDescriptorHeapHandle);
	}

	void BillboardMaterialData::updateTransformCbuffer(size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs) const
	{
		// �r���{�[�h�̍��W�ϊ��p�萔�o�b�t�@�`��
		BillboardCbufferData transformBufferData{};

		transformBufferData.billboardPosition	= updateArgs.billboardPosition;
		transformBufferData.billboardAngle		= updateArgs.billboardAngle;
		transformBufferData.billboardScale		= updateArgs.billboardScale;
		transformBufferData.textureUvOffset		= m_textureUvOffset;
		transformBufferData.textureUvMulRate	= m_textureUvMulRate;
		transformBufferData.textureSize			= m_textureSize;
		transformBufferData.textureCenterRate	= updateArgs.textureCenterRate;
		transformBufferData.viewMatrix			= updateArgs.viewMatrix;
		transformBufferData.projectionMatrix	= updateArgs.projectionMatrix;
		transformBufferData.blendRate			= updateArgs.blendRate;

		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateUploadBuffer(copyBufferHandle, transformBufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�ɃR�s�[�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(copyBufferHandle);
	}

	void BillboardMaterialData::updateTransformCbufferUseClippingParam(size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const
	{
		// �r���{�[�h�̍��W�ϊ��p�萔�o�b�t�@�`��
		BillboardCbufferData transformBufferData{};

		transformBufferData.billboardPosition	= updateArgs.billboardPosition;
		transformBufferData.billboardAngle		= updateArgs.billboardAngle;
		transformBufferData.billboardScale		= updateArgs.billboardScale;
		transformBufferData.textureUvOffset		= tktkMath::Vector2(clippingParam.leftTopPos.x / m_textureSize.x, clippingParam.leftTopPos.y / m_textureSize.y) +
		transformBufferData.textureUvMulRate	= tktkMath::Vector2(clippingParam.size.x / m_textureSize.x * m_textureUvMulRate.x, clippingParam.size.y / m_textureSize.y * m_textureUvMulRate.y);
		transformBufferData.textureSize			= clippingParam.size;
		transformBufferData.textureCenterRate	= updateArgs.textureCenterRate;
		transformBufferData.viewMatrix			= updateArgs.viewMatrix;
		transformBufferData.projectionMatrix	= updateArgs.projectionMatrix;
		transformBufferData.blendRate			= updateArgs.blendRate;

		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateUploadBuffer(copyBufferHandle, transformBufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�ɃR�s�[�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(copyBufferHandle);
	}
}