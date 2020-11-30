#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/MeshData.h"

#include <limits>
#include <vector>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/Subset.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshDrawFuncBaseArgs.h"

namespace tktk
{
	MeshData::MeshData(const MeshInitParam& initParam)
		: m_useVertexBufferHandle(initParam.useVertexBufferHandle)
		, m_useIndexBufferHandle(initParam.useIndexBufferHandle)
		, m_indexNum(initParam.indexNum)
		, m_primitiveTopology(initParam.primitiveTopology)
		, m_materialSlots(initParam.materialSlots)
		, m_instanceVertParamTypeSize(initParam.instanceVertParam.typeSize)
		, m_maxInstanceCount(initParam.instanceVertParam.dataCount)
	{
		// �C���X�^���X�`��p�̒��_�o�b�t�@�����
		m_instanceParamVertexBufferHandle = DX12GameManager::createVertexBuffer(initParam.instanceVertParam);

		// �����e�N�X�`���X�V�p�̃A�b�v���[�h�o�b�t�@�����
		m_boneMatrixTextureBufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(
			BufferType::texture,
			DX12GameManager::getSystemHandle(SystemTextureBufferType::MeshBoneMatrix),
			std::vector<unsigned char>(sizeof(tktkMath::Matrix4) * 128U * 128, 0U)
		));
	}

	MeshData::MeshData(const MeshData& other)
		: m_useVertexBufferHandle(other.m_useVertexBufferHandle)
		, m_useIndexBufferHandle(other.m_useIndexBufferHandle)
		, m_indexNum(other.m_indexNum)
		, m_primitiveTopology(other.m_primitiveTopology)
		, m_materialSlots(other.m_materialSlots)
		, m_instanceVertParamTypeSize(other.m_instanceVertParamTypeSize)
		, m_maxInstanceCount(other.m_maxInstanceCount)
	{
		// �C���X�^���X�`��p�̒��_�o�b�t�@�����o�C�i���`���ŏ������ރ������̈�����
		auto rawVertBufferData = std::vector<unsigned char>(m_instanceVertParamTypeSize * m_maxInstanceCount, 0U);

		// ���_�o�b�t�@�̓��ꕨ�����
		auto vertBufferData = VertexDataCarrier(m_instanceVertParamTypeSize, m_maxInstanceCount, rawVertBufferData.data());

		// �C���X�^���X�`��p�̒��_�o�b�t�@�����
		m_instanceParamVertexBufferHandle = DX12GameManager::createVertexBuffer(vertBufferData);

		// �����e�N�X�`���X�V�p�̃A�b�v���[�h�o�b�t�@�����
		m_boneMatrixTextureBufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(
			BufferType::texture,
			DX12GameManager::getSystemHandle(SystemTextureBufferType::MeshBoneMatrix),
			std::vector<unsigned char>(sizeof(tktkMath::Matrix4) * 128U * 128)
		));
	}

	MeshData::MeshData(MeshData&& other) noexcept
		: m_useVertexBufferHandle(other.m_useVertexBufferHandle)
		, m_useIndexBufferHandle(other.m_useIndexBufferHandle)
		, m_instanceParamVertexBufferHandle(other.m_instanceParamVertexBufferHandle)
		, m_boneMatrixTextureBufferHandle(other.m_boneMatrixTextureBufferHandle)
		, m_indexNum(other.m_indexNum)
		, m_primitiveTopology(other.m_primitiveTopology)
		, m_materialSlots(std::move(other.m_materialSlots))
		, m_instanceVertParamTypeSize(other.m_instanceVertParamTypeSize)
		, m_maxInstanceCount(other.m_maxInstanceCount)
	{
		other.m_instanceParamVertexBufferHandle = 0U;
		other.m_boneMatrixTextureBufferHandle	= 0U;
	}

	void MeshData::setMaterialHandle(size_t materialSlot, size_t materialHandle)
	{
		m_materialSlots.at(materialSlot).useMaterialHandle = materialHandle;
	}

	void MeshData::clearInstanceParam()
	{
		// �C���X�^���X���̃��X�g���N���A����
		m_instanceVertParamList.clear();
		m_instanceBoneMatrixList.clear();

		// �C���X�^���X��������������
		m_instanceCount = 0U;
	}

	void MeshData::addInstanceVertParam(const CopySourceDataCarrier& instanceParam)
	{
		// �s���ȃT�C�Y�̒��_�o�b�t�@��񂪑��݂����狭���I��
		if (instanceParam.dataSize != m_instanceVertParamTypeSize) return;

		// �C���X�^���X���̏���ɒB���Ă����ꍇ�A�����I��
		if (m_instanceCount == m_maxInstanceCount) return;

		// �C���X�^���X�`��p�̒��_�o�b�t�@�̃o�C�i���f�[�^�����X�g�ɒǉ�����
		auto rawInstanceParam = std::vector<unsigned char>(instanceParam.dataSize, 0U);
		memcpy(rawInstanceParam.data(), instanceParam.dataTopPos, instanceParam.dataSize);
		m_instanceVertParamList.push_front(rawInstanceParam);

		// �C���X�^���X�����C���N�������g
		m_instanceCount++;
	}

	void MeshData::addInstanceBoneMatrix(const std::array<tktkMath::Matrix4, 128>& boneMatrix)
	{
		auto invertBoneMatrix = boneMatrix;

		for (auto& matrix : invertBoneMatrix)
		{
			matrix = tktkMath::Matrix4(
				matrix.m[0][0], matrix.m[1][0], matrix.m[2][0], matrix.m[3][0],
				matrix.m[0][1], matrix.m[1][1], matrix.m[2][1], matrix.m[3][1],
				matrix.m[0][2], matrix.m[1][2], matrix.m[2][2], matrix.m[3][2],
				matrix.m[0][3], matrix.m[1][3], matrix.m[2][3], matrix.m[3][3]
			);
		}

		m_instanceBoneMatrixList.push_front(invertBoneMatrix);
	}

	void MeshData::updateInstanceParamVertBuffer() const
	{
		// �C���X�^���X�`��p�̒��_�o�b�t�@�����o�C�i���`���ŏ������ރ������̈�����
		auto rawVertBufferData = std::vector<unsigned char>(m_instanceVertParamTypeSize * m_maxInstanceCount, 0U);

		size_t curIndex = m_instanceCount - 1U;

		for (const auto& instanceVertParam : m_instanceVertParamList)
		{
			// �C���f�b�N�X���I�[�o�[�t���[�����狭���I��
			if (curIndex == std::numeric_limits<size_t>::max()) return;

			// �C���X�^���X�`��p�̒��_�o�b�t�@�����o�C�i���`���ŃR�s�[����
			memcpy(&rawVertBufferData.at(m_instanceVertParamTypeSize * curIndex), instanceVertParam.data(), m_instanceVertParamTypeSize);

			// �C���f�b�N�X���f�N�������g
			--curIndex;
		}

		// �������S�Ă̏������ł��Ă��Ȃ���΋����I��
		if (curIndex != std::numeric_limits<size_t>::max()) return;

		// ���_�o�b�t�@�̓��ꕨ�����
		auto vertBufferData = VertexDataCarrier(m_instanceVertParamTypeSize, m_maxInstanceCount, rawVertBufferData.data());

		// �C���X�^���X�`��p�̒��_�o�b�t�@���X�V����
		DX12GameManager::updateVertexBuffer(m_instanceParamVertexBufferHandle, vertBufferData);
	}

	void MeshData::updateBoneMatrixTextureBuffer() const
	{
		auto boneMatData = std::vector<unsigned char>(sizeof(tktkMath::Matrix4) * 128U * 128, 0U);

		size_t curIndex = m_instanceCount - 1U;

		for (const auto& instanceBoneMatrix : m_instanceBoneMatrixList)
		{
			// �C���f�b�N�X���I�[�o�[�t���[�����狭���I��
			if (curIndex == std::numeric_limits<size_t>::max()) return;

			// �C���X�^���X�`��p�̒��_�o�b�t�@�����o�C�i���`���ŃR�s�[����
			memcpy(&boneMatData.at(sizeof(tktkMath::Matrix4) * 128U * curIndex), instanceBoneMatrix.data(), sizeof(tktkMath::Matrix4) * 128U);

			// �C���f�b�N�X���f�N�������g
			--curIndex;
		}

		// �������S�Ă̏������ł��Ă��Ȃ���΋����I��
		if (curIndex != std::numeric_limits<size_t>::max()) return;

		DX12GameManager::updateUploadBuffer(m_boneMatrixTextureBufferHandle, CopySourceDataCarrier(boneMatData.size(), boneMatData.data()));
	}

	void MeshData::writeShadowMap() const
	{
		// �����A�C���X�^���X�`��p�̒l���ݒ肳��Ă��Ȃ���Ή������Ȃ�
		if (m_instanceCount == 0U) return;

		// �C���X�^���X�`������������_�o�b�t�@���X�V����
		updateInstanceParamVertBuffer();

		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(DX12GameManager::getSystemHandle(SystemViewportType::WriteShadow));

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(DX12GameManager::getSystemHandle(SystemScissorRectType::WriteShadow));

		// �w��̃g�|���W�[�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(m_primitiveTopology);

		// �`��Ŏg�p���钸�_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(m_useVertexBufferHandle, m_instanceParamVertexBufferHandle);

		// �`��Ŏg�p����C���f�b�N�X�o�b�t�@��ݒ肷��
		DX12GameManager::setIndexBuffer(m_useIndexBufferHandle);

		// �V���h�E�}�b�v�`��p�̐[�x�o�b�t�@�[�g�̂݁h��ݒ肷��
		DX12GameManager::setOnlyDsv(DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::ShadowMap));

		// �V���v�����b�V���ŃV���h�E�}�b�v�`��p�̃p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemHandle(SystemPipeLineStateType::SimpleMeshShadowMap));

		// �V���v�����b�V���ŃV���h�E�}�b�v�`��p�̃f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::SimpleMeshShadowMap) } });

		// �h���[�R�[��
		DX12GameManager::drawIndexedInstanced(m_indexNum, m_instanceCount, 0U, 0U, 0U);

		// �[�x�X�e���V���o�b�t�@�[���V�F�[�_�[�Ŏg�����Ԃɂ���
		DX12GameManager::unSetDsv(DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::ShadowMap));
	}

	void MeshData::writeShadowMapUseBone() const
	{
		// �����A�C���X�^���X�`��p�̒l���ݒ肳��Ă��Ȃ���Ή������Ȃ�
		if (m_instanceCount == 0U) return;

		// �C���X�^���X�`������������_�o�b�t�@���X�V����
		updateInstanceParamVertBuffer();

		// �C���X�^���X�`��̍��s��̃e�N�X�`�����X�V����
		updateBoneMatrixTextureBuffer();

		// �����̃e�N�X�`���o�b�t�@���X�V����
		DX12GameManager::copyBuffer(m_boneMatrixTextureBufferHandle);

		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(DX12GameManager::getSystemHandle(SystemViewportType::WriteShadow));

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(DX12GameManager::getSystemHandle(SystemScissorRectType::WriteShadow));

		// �w��̃g�|���W�[�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(m_primitiveTopology);

		// �`��Ŏg�p���钸�_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(m_useVertexBufferHandle, m_instanceParamVertexBufferHandle);

		// �`��Ŏg�p����C���f�b�N�X�o�b�t�@��ݒ肷��
		DX12GameManager::setIndexBuffer(m_useIndexBufferHandle);

		// �V���h�E�}�b�v�`��p�̐[�x�o�b�t�@�[�g�̂݁h��ݒ肷��
		DX12GameManager::setOnlyDsv(DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::ShadowMap));

		// �X�L�j���O���b�V���ŃV���h�E�}�b�v�`��p�̃p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemHandle(SystemPipeLineStateType::SkinningMeshShadowMap));

		// �X�L�j���O���b�V���ŃV���h�E�}�b�v�`��p�̃f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::SkinningMeshShadowMap) } });

		// �h���[�R�[��
		DX12GameManager::drawIndexedInstanced(m_indexNum, m_instanceCount, 0U, 0U, 0U);

		// �[�x�X�e���V���o�b�t�@�[���V�F�[�_�[�Ŏg�����Ԃɂ���
		DX12GameManager::unSetDsv(DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::ShadowMap));
	}

	//void MeshData::drawMesh(const MeshDrawFuncBaseArgs& baseArgs) const
	//{
	//	// �r���[�|�[�g��ݒ肷��
	//	DX12GameManager::setViewport(baseArgs.viewportHandle);
	//
	//	// �V�U�[��`��ݒ肷��
	//	DX12GameManager::setScissorRect(baseArgs.scissorRectHandle);
	//
	//	// �w��̃g�|���W�[�ŕ`����s��
	//	DX12GameManager::setPrimitiveTopology(static_cast<PrimitiveTopology>(m_primitiveTopology));
	//
	//	// �`��Ŏg�p���钸�_�o�b�t�@��ݒ肷��
	//	DX12GameManager::setVertexBuffer(m_useVertexBufferHandle);
	//
	//	// �`��Ŏg�p����C���f�b�N�X�o�b�t�@��ݒ肷��
	//	DX12GameManager::setIndexBuffer(m_useIndexBufferHandle);
	//
	//	// �����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V����ݒ肷��i�o�b�N�o�b�t�@�[�ɒ��ŕ`�悷��ꍇ�͓��ꏈ���j
	//	if (baseArgs.rtvDescriptorHeapHandle == DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
	//	{
	//		DX12GameManager::setBackBufferViewAndDsv(baseArgs.dsvDescriptorHeapHandle);
	//	}
	//	else
	//	{
	//		DX12GameManager::setRtvAndDsv(baseArgs.rtvDescriptorHeapHandle, baseArgs.dsvDescriptorHeapHandle, 0U, 1U);
	//	}
	//
	//	// �}�e���A���̐������`�悷��
	//	for (const auto& node : m_materialSlots)
	//	{
	//		// �}�e���A���̏���ݒ肷��
	//		DX12GameManager::setMaterialData(node.useMaterialHandle);
	//
	//		// �h���[�R�[��
	//		DX12GameManager::drawIndexedInstanced(node.indexBufferUseCount, 1U, node.indexBufferStartPos, 0U, 0U);
	//	}
	//
	//	// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
	//	if (baseArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
	//	{
	//		DX12GameManager::unSetRtv(baseArgs.rtvDescriptorHeapHandle, 0U, 1U);
	//	}
	//
	//	// �[�x�X�e���V���o�b�t�@�[���V�F�[�_�[�Ŏg�����Ԃɂ���
	//	DX12GameManager::unSetDsv(baseArgs.dsvDescriptorHeapHandle);
	//}

	void MeshData::draw(const MeshDrawFuncBaseArgs& baseArgs) const
	{
		// �����A�C���X�^���X�`��p�̒l���ݒ肳��Ă��Ȃ���Ή������Ȃ�
		if (m_instanceCount == 0U) return;

		// �C���X�^���X�`������������_�o�b�t�@���X�V����
		updateInstanceParamVertBuffer();

		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(baseArgs.viewportHandle);

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(baseArgs.scissorRectHandle);

		// �w��̃g�|���W�[�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(m_primitiveTopology);

		// �`��Ŏg�p���钸�_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(m_useVertexBufferHandle, m_instanceParamVertexBufferHandle);

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
			DX12GameManager::setMeshMaterialData(node.useMaterialHandle);

			// �h���[�R�[��
			DX12GameManager::drawIndexedInstanced(node.indexBufferUseCount, m_instanceCount, node.indexBufferStartPos, 0U, 0U);
		}

		// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
		if (baseArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(baseArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}

		// �[�x�X�e���V���o�b�t�@�[���V�F�[�_�[�Ŏg�����Ԃɂ���
		DX12GameManager::unSetDsv(baseArgs.dsvDescriptorHeapHandle);
	}

	void MeshData::drawUseBone(const MeshDrawFuncBaseArgs& baseArgs) const
	{
		// �����A�C���X�^���X�`��p�̒l���ݒ肳��Ă��Ȃ���Ή������Ȃ�
		if (m_instanceCount == 0U) return;

		// �C���X�^���X�`������������_�o�b�t�@���X�V����
		updateInstanceParamVertBuffer();

		// �C���X�^���X�`��̍��s��̃e�N�X�`�����X�V����
		updateBoneMatrixTextureBuffer();

		// �����̃e�N�X�`���o�b�t�@���X�V����
		DX12GameManager::copyBuffer(m_boneMatrixTextureBufferHandle);

		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(baseArgs.viewportHandle);

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(baseArgs.scissorRectHandle);

		// �w��̃g�|���W�[�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(m_primitiveTopology);

		// �`��Ŏg�p���钸�_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(m_useVertexBufferHandle, m_instanceParamVertexBufferHandle);

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
			DX12GameManager::setMeshMaterialData(node.useMaterialHandle);

			// �h���[�R�[��
			DX12GameManager::drawIndexedInstanced(node.indexBufferUseCount, m_instanceCount, node.indexBufferStartPos, 0U, 0U);
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