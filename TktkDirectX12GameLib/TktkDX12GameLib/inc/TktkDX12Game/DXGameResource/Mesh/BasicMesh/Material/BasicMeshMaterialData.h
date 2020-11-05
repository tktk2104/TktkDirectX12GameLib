#ifndef BASIC_MESH_MATERIAL_DATA_H_
#define BASIC_MESH_MATERIAL_DATA_H_

#include <unordered_map>
#include "BasicMeshMaterialInitParam.h"
#include "../../Structs/MeshDrawFuncBaseArgs.h"
#include "BasicMeshMaterialAppendParam.h"

namespace tktk
{
	// �ʏ탁�b�V���̃}�e���A�������Ǘ�����N���X
	class BasicMeshMaterialData
	{
	public:

		explicit BasicMeshMaterialData(const BasicMeshMaterialInitParam& initParam);

		// �R�s�[�R���X�g���N�^
		// �� �um_appendParamMap�v�̗v�f�̓R�s�[����Ȃ��ivoid*�����邽�߁j
		BasicMeshMaterialData(const BasicMeshMaterialData& other);
		
		// ���[�u�R���X�g���N�^
		BasicMeshMaterialData(BasicMeshMaterialData&& other) noexcept;

		~BasicMeshMaterialData();

	public:

		// ���g�̃}�e���A�����ƃO���t�B�b�N�p�C�v���C�����R�}���h���X�g�ɐݒ肷��
		void setMaterialData() const;

		// ���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@�̃n���h���ƒl��ݒ肷��
		void addAppendParam(size_t cbufferHandle, size_t dataSize, void* dataTopPos);

		// ���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl���X�V����
		void updateAppendParam(size_t cbufferHandle, size_t dataSize, const void* dataTopPos);

	private:

		// �萔�o�b�t�@�̃R�s�[�p�o�b�t�@���X�V����
		void updateCopyBuffer() const;

	private:

		size_t			m_usePipeLineStateHandle	{ 0U };
		size_t			m_useDescriptorHeapHandle	{ 0U };
		size_t			m_createUploadBufferHandle	{ 0U };
		tktkMath::Color	m_materialAmbient;
		tktkMath::Color	m_materialDiffuse;
		tktkMath::Color	m_materialSpecular;
		tktkMath::Color	m_materialEmissive;
		float			m_materialShiniess;

		std::unordered_map<size_t, BasicMeshMaterialAppendParam> m_appendParamMap;
	};
}
#endif // !BASIC_MESH_MATERIAL_DATA_H_