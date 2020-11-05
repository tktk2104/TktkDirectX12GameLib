#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Material/BasicMeshMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Structs/BasicMeshMaterialCbuffer.h"

namespace tktk
{
	BasicMeshMaterialData::BasicMeshMaterialData(const BasicMeshMaterialInitParam& initParam)
		: m_usePipeLineStateHandle(initParam.usePipeLineStateHandle)
		, m_useDescriptorHeapHandle(initParam.useDescriptorHeapHandle)
		, m_materialAmbient(initParam.materialAmbient)
		, m_materialDiffuse(initParam.materialDiffuse)
		, m_materialSpecular(initParam.materialSpecular)
		, m_materialEmissive(initParam.materialEmissive)
		, m_materialShiniess(initParam.materialShiniess)
	{
		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadBufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::BasicMeshMaterial), BasicMeshMaterialCbuffer()));
	}

	BasicMeshMaterialData::BasicMeshMaterialData(const BasicMeshMaterialData& other)
		: m_usePipeLineStateHandle(other.m_usePipeLineStateHandle)
		, m_useDescriptorHeapHandle(other.m_useDescriptorHeapHandle)
		, m_materialAmbient(other.m_materialAmbient)
		, m_materialDiffuse(other.m_materialDiffuse)
		, m_materialSpecular(other.m_materialSpecular)
		, m_materialEmissive(other.m_materialEmissive)
		, m_materialShiniess(other.m_materialShiniess)
	{
		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadBufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::BasicMeshMaterial), BasicMeshMaterialCbuffer()));
	}

	BasicMeshMaterialData::BasicMeshMaterialData(BasicMeshMaterialData&& other) noexcept
		: m_usePipeLineStateHandle(other.m_usePipeLineStateHandle)
		, m_useDescriptorHeapHandle(other.m_useDescriptorHeapHandle)
		, m_createUploadBufferHandle(other.m_createUploadBufferHandle)
		, m_materialAmbient(other.m_materialAmbient)
		, m_materialDiffuse(other.m_materialDiffuse)
		, m_materialSpecular(other.m_materialSpecular)
		, m_materialEmissive(other.m_materialEmissive)
		, m_materialShiniess(other.m_materialShiniess)
		, m_appendParamMap(std::move(other.m_appendParamMap))
	{
		other.m_createUploadBufferHandle = 0U;
	}

	BasicMeshMaterialData::~BasicMeshMaterialData()
	{
		DX12GameManager::eraseUploadBuffer(m_createUploadBufferHandle);
	}

	void BasicMeshMaterialData::setMaterialData() const
	{
		// �}�e���A�����g�p����p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(m_usePipeLineStateHandle);

		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		updateCopyBuffer();

		// �}�e���A���p�萔�o�b�t�@�ɃA�b�v���[�h�p�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createUploadBufferHandle);

		for (const auto& pair : m_appendParamMap)
		{
			pair.second.updateCbuffer();
		}

		// �w��̃f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_useDescriptorHeapHandle } });
	}

	void BasicMeshMaterialData::addAppendParam(size_t cbufferHandle, size_t dataSize, void* dataTopPos)
	{
		m_appendParamMap.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(cbufferHandle),
			std::forward_as_tuple(cbufferHandle, dataSize, dataTopPos)
		);
	}

	void BasicMeshMaterialData::updateAppendParam(size_t cbufferHandle, size_t dataSize, const void* dataTopPos)
	{
		m_appendParamMap.at(cbufferHandle).updateParam(dataSize, dataTopPos);
	}

	void BasicMeshMaterialData::updateCopyBuffer() const
	{
		BasicMeshMaterialCbuffer materialBufferData{};

		materialBufferData.materialAmbient = m_materialAmbient;
		materialBufferData.materialDiffuse = m_materialDiffuse;
		materialBufferData.materialSpecular = m_materialSpecular;
		materialBufferData.materialEmissive = m_materialEmissive;
		materialBufferData.materialShiniess = m_materialShiniess;

		DX12GameManager::updateUploadBuffer(m_createUploadBufferHandle, materialBufferData);
	}
}