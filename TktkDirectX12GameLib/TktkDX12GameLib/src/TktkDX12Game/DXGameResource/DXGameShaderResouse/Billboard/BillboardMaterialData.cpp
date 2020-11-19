#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardMaterialInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardDrawFuncBaseArgs.h"

namespace tktk
{
	BillboardMaterialData::BillboardMaterialData(const BillboardMaterialInitParam& initParam)
		: m_maxInstanceCount(initParam.maxInstanceCount)
	{
		// �f�B�X�N���v�^�q�[�v�����
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(2U);

		{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

			// �r���{�[�h�e�N�X�`���̂P���
			srvDescriptorParam.descriptorParamArray = { { initParam.srvBufferType, initParam.useBufferHandle } };
		}

		{ /* �R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// �J�����o�b�t�@�̂P���
			cbufferViewDescriptorParam.descriptorParamArray = { { BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera) } };
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


		// �C���X�^���X�`��p�̒��_�o�b�t�@�����
		m_instanceParamVertexBufferHandle = DX12GameManager::createVertexBuffer(std::vector<BillboardMaterialInstanceVertData>(m_maxInstanceCount));
	}

	BillboardMaterialData::~BillboardMaterialData()
	{
		// ������f�B�X�N���v�^�q�[�v���폜����
		DX12GameManager::eraseBasicDescriptorHeap(m_createDescriptorHeapHandle);
	}

	BillboardMaterialData::BillboardMaterialData(BillboardMaterialData&& other) noexcept
		: m_createDescriptorHeapHandle(other.m_createDescriptorHeapHandle)
		, m_maxInstanceCount(other.m_maxInstanceCount)
		, m_textureSize(other.m_textureSize)
	{
		other.m_createDescriptorHeapHandle = 0U;
	}

	const tktkMath::Vector2& BillboardMaterialData::getBillboardTextureSize() const
	{
		return m_textureSize;
	}

	void BillboardMaterialData::clearInstanceParam()
	{
		// �C���X�^���X���̃��X�g���N���A����
		m_instanceVertParamList.clear();

		// �C���X�^���X��������������
		m_instanceCount = 0U;
	}

	void BillboardMaterialData::addInstanceVertParam(const BillboardMaterialInstanceVertData& instanceParam)
	{
		// �C���X�^���X���̏���ɒB���Ă����ꍇ�A�����I��
		if (m_instanceCount == m_maxInstanceCount) return;

		auto tempInstanceParam = instanceParam;
		tempInstanceParam.textureSize = m_textureSize;
		tempInstanceParam.textureUvOffset = { tempInstanceParam.textureUvOffset.x / m_textureSize.x,	tempInstanceParam.textureUvOffset.y / m_textureSize.y };
		tempInstanceParam.textureUvMulRate = { tempInstanceParam.textureUvMulRate.x / m_textureSize.x,	tempInstanceParam.textureUvMulRate.y / m_textureSize.y };
		
		// �C���X�^���X�`��p�̒��_�o�b�t�@�����X�g�ɒǉ�����
		m_instanceVertParamList.push_front(tempInstanceParam);

		// �C���X�^���X�����C���N�������g
		m_instanceCount++;
	}

	void BillboardMaterialData::updateInstanceParamVertBuffer() const
	{
		auto vertBufferData = std::vector<BillboardMaterialInstanceVertData>(m_maxInstanceCount);
	
		size_t curIndex = m_instanceCount - 1U;

		for (const auto& instanceVertParam : m_instanceVertParamList)
		{
			// �C���f�b�N�X���I�[�o�[�t���[�����狭���I��
			if (curIndex == std::numeric_limits<size_t>::max()) return;

			// �C���X�^���X�`��p�̒��_�o�b�t�@�����R�s�[����
			vertBufferData.at(curIndex) = instanceVertParam;

			// �C���f�b�N�X���f�N�������g
			--curIndex;
		}

		// �������S�Ă̏������ł��Ă��Ȃ���΋����I��
		if (curIndex != std::numeric_limits<size_t>::max()) return;
	
		// �C���X�^���X�`��p�̒��_�o�b�t�@���X�V����
		DX12GameManager::updateVertexBuffer(m_instanceParamVertexBufferHandle, vertBufferData);
	}

	void BillboardMaterialData::draw(const BillboardDrawFuncBaseArgs& drawFuncArgs) const
	{
		// �����A�C���X�^���X�`��p�̒l���ݒ肳��Ă��Ȃ���Ή������Ȃ�
		if (m_instanceCount == 0U) return;

		// �C���X�^���X�`������������_�o�b�t�@���X�V����
		updateInstanceParamVertBuffer();

		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(drawFuncArgs.viewportHandle);

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(drawFuncArgs.scissorRectHandle);

		// �g���C�A���O���X�g���b�v�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(PrimitiveTopology::TriangleStrip);

		// �r���{�[�h�p�̒��_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemHandle(SystemVertexBufferType::Sprite), m_instanceParamVertexBufferHandle);

		// �r���{�[�h�p�̃C���f�b�N�X�o�b�t�@��ݒ肷��
		DX12GameManager::setIndexBuffer(DX12GameManager::getSystemHandle(SystemIndexBufferType::Sprite));

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

		// �h���[�R�[��
		DX12GameManager::drawIndexedInstanced(4U, m_instanceCount, 0U, 0U, 0U);

		// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
		if (drawFuncArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}

		// �[�x�X�e���V���o�b�t�@�[���V�F�[�_�[�Ŏg�����Ԃɂ���
		DX12GameManager::unSetDsv(drawFuncArgs.dsvDescriptorHeapHandle);
	}

	//void BillboardMaterialData::updateTransformCbuffer(size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs) const
	//{
	//	// �r���{�[�h�̍��W�ϊ��p�萔�o�b�t�@�`��
	//	BillboardCbufferData transformBufferData{};

	//	transformBufferData.billboardPosition	= updateArgs.billboardPosition;
	//	transformBufferData.billboardAngle		= updateArgs.billboardAngle;
	//	transformBufferData.billboardScale		= updateArgs.billboardScale;
	//	transformBufferData.textureUvOffset		= tktkMath::Vector2_v::zero;
	//	transformBufferData.textureUvMulRate	= tktkMath::Vector2_v::one;
	//	transformBufferData.textureSize			= m_textureSize;
	//	transformBufferData.textureCenterRate	= updateArgs.textureCenterRate;
	//	transformBufferData.viewMatrix			= updateArgs.viewMatrix;
	//	transformBufferData.projectionMatrix	= updateArgs.projectionMatrix;
	//	transformBufferData.blendRate			= updateArgs.blendRate;

	//	// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
	//	// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
	//	DX12GameManager::updateUploadBuffer(copyBufferHandle, transformBufferData);

	//	// ���W�ϊ��p�̒萔�o�b�t�@�ɃR�s�[�o�b�t�@�̏����R�s�[����
	//	DX12GameManager::copyBuffer(copyBufferHandle);
	//}

	//void BillboardMaterialData::updateTransformCbufferUseClippingParam(size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const
	//{
	//	// �r���{�[�h�̍��W�ϊ��p�萔�o�b�t�@�`��
	//	BillboardCbufferData transformBufferData{};

	//	transformBufferData.billboardPosition	= updateArgs.billboardPosition;
	//	transformBufferData.billboardAngle		= updateArgs.billboardAngle;
	//	transformBufferData.billboardScale		= updateArgs.billboardScale;
	//	transformBufferData.textureUvOffset		= tktkMath::Vector2(clippingParam.leftTopPos.x / m_textureSize.x,	clippingParam.leftTopPos.y / m_textureSize.y) +
	//	transformBufferData.textureUvMulRate	= tktkMath::Vector2(clippingParam.size.x / m_textureSize.x,			clippingParam.size.y / m_textureSize.y);
	//	transformBufferData.textureSize			= clippingParam.size;
	//	transformBufferData.textureCenterRate	= updateArgs.textureCenterRate;
	//	transformBufferData.viewMatrix			= updateArgs.viewMatrix;
	//	transformBufferData.projectionMatrix	= updateArgs.projectionMatrix;
	//	transformBufferData.blendRate			= updateArgs.blendRate;

	//	// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
	//	// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
	//	DX12GameManager::updateUploadBuffer(copyBufferHandle, transformBufferData);

	//	// ���W�ϊ��p�̒萔�o�b�t�@�ɃR�s�[�o�b�t�@�̏����R�s�[����
	//	DX12GameManager::copyBuffer(copyBufferHandle);
	//}
}