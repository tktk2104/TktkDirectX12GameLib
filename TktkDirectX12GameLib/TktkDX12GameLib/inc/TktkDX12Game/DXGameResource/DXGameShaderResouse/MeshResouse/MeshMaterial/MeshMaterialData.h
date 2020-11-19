#ifndef BASIC_MESH_MATERIAL_DATA_H_
#define BASIC_MESH_MATERIAL_DATA_H_

/* std::unordered_map */
#include <unordered_map>

/* class member */
#include <TktkMath/Structs/Color.h>

namespace tktk
{
	struct MeshMaterialInitParam;
	class MeshMaterialAppendParam;
	struct MeshMaterialAppendParamInitParam;
	struct MeshMaterialAppendParamUpdateFuncArgs;

	// �ʏ탁�b�V���̃}�e���A�������Ǘ�����N���X
	class MeshMaterialData
	{
	public:

		explicit MeshMaterialData(const MeshMaterialInitParam& initParam);

		// �R�s�[�R���X�g���N�^
		// �� �um_appendParamMap�v�̗v�f�̓R�s�[����Ȃ��ivoid*�����邽�߁j
		MeshMaterialData(const MeshMaterialData& other);
		
		// ���[�u�R���X�g���N�^
		MeshMaterialData(MeshMaterialData&& other) noexcept;

		~MeshMaterialData();

	public:

		// ���g�̃}�e���A�����ƃO���t�B�b�N�p�C�v���C�����R�}���h���X�g�ɐݒ肷��
		void setMaterialData() const;

		// ���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@�̃n���h���ƒl��ݒ肷��
		void addAppendParam(const MeshMaterialAppendParamInitParam& initParam);

		// ���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl���X�V����
		void updateAppendParam(const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

	private:

		// �萔�o�b�t�@�̃R�s�[�p�o�b�t�@���X�V����
		void updateCopyBuffer() const;

	private:

		size_t			m_usePipeLineStateHandle	{ 0U };
		size_t			m_useDescriptorHeapHandle	{ 0U };
		size_t			m_createUploadBufferHandle	{ 0U };
		//tktkMath::Color	m_materialAmbient;
		//tktkMath::Color	m_materialDiffuse;
		//tktkMath::Color	m_materialSpecular;
		//tktkMath::Color	m_materialEmissive;
		//float			m_materialShiniess;

		std::unordered_map<size_t, MeshMaterialAppendParam> m_appendParamMap;
	};
}
#endif // !BASIC_MESH_MATERIAL_DATA_H_