#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/Structs/SpriteMaterialInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/Structs/SpriteMaterialDrawFuncArgs.h"

namespace tktk
{
	SpriteMaterialData::SpriteMaterialData(const SpriteMaterialInitParam& initParam)
		: m_maxInstanceCount(initParam.maxInstanceCount)
	{
		// �f�B�X�N���v�^�q�[�v�����
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(2U);

		{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

			// �X�v���C�g�e�N�X�`���̂P���
			srvDescriptorParam.descriptorParamArray = { { initParam.srvBufferType, initParam.useBufferHandle } };
		}

		{ /* �R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// �X�N���[���T�C�Y�o�b�t�@�̂P���
			cbufferViewDescriptorParam.descriptorParamArray = { { BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::DrawGameAreaSize) } };
		}

		// switch���̒��ŕϐ��錾�ł��Ȃ����̕��Q
		const tktkMath::Vector3* textureBufferSize = nullptr;

		switch (initParam.srvBufferType)
		{
		case BufferType::texture:

			textureBufferSize = &DX12GameManager::getTextureBufferSizePx(initParam.useBufferHandle);
			m_textureSize = { textureBufferSize->x, textureBufferSize->y };
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
		m_instanceParamVertexBufferHandle = DX12GameManager::createVertexBuffer(std::vector<SpriteMaterialInstanceData>(m_maxInstanceCount));
	}

	SpriteMaterialData::~SpriteMaterialData()
	{
		// ������f�B�X�N���v�^�q�[�v���폜����
		DX12GameManager::eraseBasicDescriptorHeap(m_createDescriptorHeapHandle);
	}

	SpriteMaterialData::SpriteMaterialData(SpriteMaterialData&& other) noexcept
		: m_createDescriptorHeapHandle(other.m_createDescriptorHeapHandle)
		, m_maxInstanceCount(other.m_maxInstanceCount)
		, m_textureSize(other.m_textureSize)
	{
		other.m_createDescriptorHeapHandle = 0U;
	}

	const tktkMath::Vector2& SpriteMaterialData::getSpriteTextureSize() const
	{
		return m_textureSize;
	}

	size_t SpriteMaterialData::getMaxInstanceCount() const
	{
		return m_maxInstanceCount;
	}

	size_t SpriteMaterialData::getCurInstanceCount() const
	{
		return m_instanceCount;
	}

	void SpriteMaterialData::clearInstanceParam()
	{
		// �C���X�^���X���̃��X�g���N���A����
		m_instanceParamList.clear();

		// �C���X�^���X��������������
		m_instanceCount = 0U;
	}

	void SpriteMaterialData::addInstanceParam(float drawPriority, const TempSpriteMaterialInstanceData& instanceParam)
	{
		// �C���X�^���X���̏���ɒB���Ă����ꍇ�A�����I��
		if (m_instanceCount == m_maxInstanceCount) return;

		SpriteMaterialInstanceData spriteInstanceParam;

		for (size_t i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			spriteInstanceParam.worldMatrix[i] = instanceParam.worldMatrix.m[i / 4U][i % 4U];
		}

		spriteInstanceParam.textureSize			= instanceParam.texturePixelCount;
		spriteInstanceParam.textureUvOffset		= { instanceParam.texturePixelOffset.x		/ m_textureSize.x,	instanceParam.texturePixelOffset.y		/ m_textureSize.y };
		spriteInstanceParam.textureUvMulRate	= { instanceParam.texturePixelCount.x		/ m_textureSize.x,	instanceParam.texturePixelCount.y		/ m_textureSize.y };
		spriteInstanceParam.textureUvMulRate	= tktkMath::Vector2::scale(spriteInstanceParam.textureUvMulRate, instanceParam.textureUvMulRate);
		spriteInstanceParam.textureCenterRate	= instanceParam.textureCenterRate;
		spriteInstanceParam.blendRate			= instanceParam.blendRate;

		// �C���X�^���X�`��p�̒��_�o�b�t�@�����X�g�ɒǉ�����
		m_instanceParamList.emplace(drawPriority, spriteInstanceParam);

		// �C���X�^���X�����C���N�������g
		m_instanceCount++;
	}

	void SpriteMaterialData::updateInstanceParam()
	{
		// �����A�C���X�^���X�`��p�̒l���ݒ肳��Ă��Ȃ���Ή������Ȃ�
		if (m_instanceCount == 0U) return;

		auto vertBufferData = std::vector<SpriteMaterialInstanceData>(m_maxInstanceCount);

		size_t curIndex = m_instanceCount - 1U;

		for (const auto& instanceVertParam : m_instanceParamList)
		{
			// �C���f�b�N�X���I�[�o�[�t���[�����狭���I��
			if (curIndex == std::numeric_limits<size_t>::max()) return;

			// �C���X�^���X�`��p�̒��_�o�b�t�@�����R�s�[����
			vertBufferData.at(curIndex) = instanceVertParam.second;

			// �C���f�b�N�X���f�N�������g
			--curIndex;
		}

		// �������S�Ă̏������ł��Ă��Ȃ���΋����I��
		if (curIndex != std::numeric_limits<size_t>::max()) return;

		// �C���X�^���X�`��p�̒��_�o�b�t�@���X�V����
		DX12GameManager::updateVertexBuffer(m_instanceParamVertexBufferHandle, vertBufferData);
	}

	void SpriteMaterialData::draw(const SpriteMaterialDrawFuncArgs& drawFuncArgs) const
	{
		// �����A�C���X�^���X�`��p�̒l���ݒ肳��Ă��Ȃ���Ή������Ȃ�
		if (m_instanceCount == 0U) return;

		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(drawFuncArgs.viewportHandle);

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(drawFuncArgs.scissorRectHandle);

		// �g���C�A���O���X�g���b�v�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(PrimitiveTopology::TriangleStrip);

		// �X�v���C�g�p�̒��_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemHandle(SystemVertexBufferType::Sprite), m_instanceParamVertexBufferHandle);

		// �X�v���C�g�p�̃C���f�b�N�X�o�b�t�@��ݒ肷��
		DX12GameManager::setIndexBuffer(DX12GameManager::getSystemHandle(SystemIndexBufferType::Sprite));

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

		// �h���[�R�[��
		DX12GameManager::drawIndexedInstanced(4U, m_instanceCount, 0U, 0U, 0U);

		// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
		if (drawFuncArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}
	}
}