#ifndef MESH_MATERIAL_MANAGER_H_
#define MESH_MATERIAL_MANAGER_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

/* funcUseType */
#include <string>

namespace tktk
{
	struct MeshMaterialManagerInitParam;
	struct ShaderFilePaths;
	struct MeshMaterialInitParam;
	class MeshMaterialData;
	struct MeshMaterialAppendParamInitParam;
	struct MeshMaterialAppendParamUpdateFuncArgs;

	// �uMeshMaterialData�v���Ǘ�����N���X
	class MeshMaterialManager
	{
	public:

		MeshMaterialManager(const MeshMaterialManagerInitParam& initParam);
		~MeshMaterialManager();

	public:

		// �uMeshMaterialData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(const MeshMaterialInitParam& initParam);

		// �w��́uBasicMeshMaterialData�v�̃C���X�^���X�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t copy(size_t originalHandle);

		// �w��̒ʏ탁�b�V���̃}�e���A�������O���t�B�b�N�p�C�v���C���ɐݒ肷��
		void setMaterialData(size_t handle)  const;

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@�̃n���h���ƒl��ݒ肷��
		void addAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam);

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@�̃n���h���ƒl���X�V����
		void updateAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

	private:

		// �ʏ탁�b�V���}�e���A���`��p�̃��[�g�V�O�l�`�������
		void createRootSignature() const;

		// �ʏ탁�b�V���}�e���A���`��p�̃p�C�v���C���X�e�[�g�����
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths, const std::string& monoColorShaderPsFilePath) const;

	private:

		tktkContainer::ResourceContainer<MeshMaterialData> m_basicMeshMaterialArray;
	};
}
#endif // !MESH_MATERIAL_MANAGER_H_