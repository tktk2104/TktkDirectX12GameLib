#ifndef BASIC_MESH_MATERIAL_H_
#define BASIC_MESH_MATERIAL_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "BasicMeshMaterialData.h"

namespace tktk
{
	// �uBasicMeshMaterialData�v���Ǘ�����N���X
	class BasicMeshMaterial
	{
	public:

		BasicMeshMaterial(const ShaderFilePaths& basicShaderFilePaths, const std::string& monoColorShaderPsFilePath, const tktkContainer::ResourceContainerInitParam& initParam);
		~BasicMeshMaterial() = default;

	public:

		// �uBasicMeshMaterialData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(const BasicMeshMaterialInitParam& initParam);

		// �w��́uBasicMeshMaterialData�v�̃C���X�^���X�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t copy(size_t originalHandle);

		// �w��̒ʏ탁�b�V���̃}�e���A�������O���t�B�b�N�p�C�v���C���ɐݒ肷��
		void setMaterialData(size_t handle)  const;

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@�̃n���h���ƒl��ݒ肷��
		void addAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, void* dataTopPos);

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@�̃n���h���ƒl���X�V����
		void updateAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, const void* dataTopPos);

	private:

		// �ʏ탁�b�V���}�e���A���`��p�̃��[�g�V�O�l�`�������
		void createRootSignature() const;

		// �ʏ탁�b�V���}�e���A���`��p�̃p�C�v���C���X�e�[�g�����
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths, const std::string& monoColorShaderPsFilePath) const;

	private:

		tktkContainer::ResourceContainer<BasicMeshMaterialData> m_basicMeshMaterialArray;
	};
}
#endif // !BASIC_MESH_MATERIAL_H_