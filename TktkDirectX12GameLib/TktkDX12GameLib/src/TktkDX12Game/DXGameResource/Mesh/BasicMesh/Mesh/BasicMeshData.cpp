#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Mesh/BasicMeshData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BasicMeshData::BasicMeshData(const BasicMeshInitParam& initParam)
		: m_useVertexBufferHandle(initParam.useVertexBufferHandle)
		, m_useIndexBufferHandle(initParam.useIndexBufferHandle)
		, m_indexNum(initParam.indexNum)
		, m_primitiveTopology(initParam.primitiveTopology)
		, m_materialSlots(initParam.materialSlots)
	{
		
	}

	BasicMeshData::BasicMeshData(const BasicMeshData& other)
		: m_useVertexBufferHandle(other.m_useVertexBufferHandle)
		, m_useIndexBufferHandle(other.m_useIndexBufferHandle)
		, m_indexNum(other.m_indexNum)
		, m_primitiveTopology(other.m_primitiveTopology)
		, m_materialSlots(other.m_materialSlots)
	{
		
	}

	BasicMeshData::BasicMeshData(BasicMeshData&& other) noexcept
		: m_useVertexBufferHandle(other.m_useVertexBufferHandle)
		, m_useIndexBufferHandle(other.m_useIndexBufferHandle)
		, m_indexNum(other.m_indexNum)
		, m_primitiveTopology(other.m_primitiveTopology)
		, m_materialSlots(std::move(other.m_materialSlots))
	{
	}

	void BasicMeshData::setMaterialHandle(size_t materialSlot, size_t materialHandle)
	{
		m_materialSlots.at(materialSlot).useMaterialHandle = materialHandle;
	}

	void BasicMeshData::writeShadowMap() const
	{
		// �V���h�E�}�b�v�`��p�̐[�x�o�b�t�@�[�g�̂݁h��ݒ肷��
		DX12GameManager::setOnlyDsv(DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::ShadowMap));

		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(DX12GameManager::getSystemHandle(SystemViewportType::Basic));

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(DX12GameManager::getSystemHandle(SystemScissorRectType::Basic));

		// �ʏ탁�b�V���ŃV���h�E�}�b�v�`��p�̃p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemHandle(SystemPipeLineStateType::ShadowMap));

		// �ʏ탁�b�V���ŃV���h�E�}�b�v�`��p�̃f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::BasicMeshShadowMap) } });

		// �w��̃g�|���W�[�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(static_cast<D3D_PRIMITIVE_TOPOLOGY>(m_primitiveTopology));

		// �`��Ŏg�p���钸�_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(m_useVertexBufferHandle);

		// �`��Ŏg�p����C���f�b�N�X�o�b�t�@��ݒ肷��
		DX12GameManager::setIndexBuffer(m_useIndexBufferHandle);

		// �h���[�R�[��
		DX12GameManager::drawIndexedInstanced(m_indexNum, 1U, 0U, 0U, 0U);

		// �[�x�X�e���V���o�b�t�@�[���V�F�[�_�[�Ŏg�����Ԃɂ���
		DX12GameManager::unSetDsv(DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::ShadowMap));
	}

	void BasicMeshData::drawMesh(const MeshDrawFuncBaseArgs& baseArgs) const
	{
		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(baseArgs.viewportHandle);

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(baseArgs.scissorRectHandle);

		// �w��̃g�|���W�[�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(static_cast<D3D_PRIMITIVE_TOPOLOGY>(m_primitiveTopology));

		// �`��Ŏg�p���钸�_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(m_useVertexBufferHandle);

		// �`��Ŏg�p����C���f�b�N�X�o�b�t�@��ݒ肷��
		DX12GameManager::setIndexBuffer(m_useIndexBufferHandle);

		// �����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V����ݒ肷��i�o�b�N�o�b�t�@�[�ɒ��ŕ`�悷��ꍇ�͓��ꏈ���j
		if (baseArgs.rtvDescriptorHeapHandle == DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferViewAndDsv(baseArgs.dsvDescriptorHeapHandle);
		}
		else
		{
			DX12GameManager::setRtvAndDsv(baseArgs.rtvDescriptorHeapHandle, baseArgs.dsvDescriptorHeapHandle, 0U, 1U);
		}

		// �}�e���A���̐������`�悷��
		for (const auto& node : m_materialSlots)
		{
			// �}�e���A���̏���ݒ肷��
			DX12GameManager::setMaterialData(node.useMaterialHandle);

			// �h���[�R�[��
			DX12GameManager::drawIndexedInstanced(node.indexBufferUseCount, 1U, node.indexBufferStartPos, 0U, 0U);
		}

		// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
		if (baseArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(baseArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}

		// �[�x�X�e���V���o�b�t�@�[���V�F�[�_�[�Ŏg�����Ԃɂ���
		DX12GameManager::unSetDsv(baseArgs.dsvDescriptorHeapHandle);
	}
}