#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/MeshMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialCbuffer.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/MeshMaterialAppendParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialAppendParamInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialAppendParamUpdateFuncArgs.h"

namespace tktk
{
	MeshMaterialData::MeshMaterialData(const MeshMaterialInitParam& initParam)
		: m_usePipeLineStateHandle(initParam.usePipeLineStateHandle)
		, m_useDescriptorHeapHandle(initParam.useDescriptorHeapHandle)
		, m_materialAmbient(initParam.materialAmbient)
		, m_materialDiffuse(initParam.materialDiffuse)
		, m_materialSpecular(initParam.materialSpecular)
		, m_materialEmissive(initParam.materialEmissive)
		, m_materialShiniess(initParam.materialShiniess)
	{
		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadBufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::BasicMeshMaterial), MeshMaterialCbuffer()));
	}

	MeshMaterialData::MeshMaterialData(const MeshMaterialData& other)
		: m_usePipeLineStateHandle(other.m_usePipeLineStateHandle)
		, m_useDescriptorHeapHandle(other.m_useDescriptorHeapHandle)
		, m_materialAmbient(other.m_materialAmbient)
		, m_materialDiffuse(other.m_materialDiffuse)
		, m_materialSpecular(other.m_materialSpecular)
		, m_materialEmissive(other.m_materialEmissive)
		, m_materialShiniess(other.m_materialShiniess)
	{
		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadBufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::BasicMeshMaterial), MeshMaterialCbuffer()));
	}

	MeshMaterialData::MeshMaterialData(MeshMaterialData&& other) noexcept
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

	MeshMaterialData::~MeshMaterialData()
	{
		DX12GameManager::eraseUploadBuffer(m_createUploadBufferHandle);
	}

	void MeshMaterialData::setMaterialData() const
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

	void MeshMaterialData::addAppendParam(const MeshMaterialAppendParamInitParam& initParam)
	{
		m_appendParamMap.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(initParam.cbufferHandle),
			std::forward_as_tuple(initParam)
		);
	}

	void MeshMaterialData::updateAppendParam(const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs)
	{
		m_appendParamMap.at(updateFuncArgs.cbufferHandle).updateParam(updateFuncArgs);
	}

	void MeshMaterialData::updateCopyBuffer() const
	{
		MeshMaterialCbuffer materialBufferData{};

		materialBufferData.materialAmbient = m_materialAmbient;
		materialBufferData.materialDiffuse = m_materialDiffuse;
		materialBufferData.materialSpecular = m_materialSpecular;
		materialBufferData.materialEmissive = m_materialEmissive;
		materialBufferData.materialShiniess = m_materialShiniess;

		DX12GameManager::updateUploadBuffer(m_createUploadBufferHandle, materialBufferData);
	}
}