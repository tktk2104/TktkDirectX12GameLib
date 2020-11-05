#ifndef BASIC_MESH_H_
#define BASIC_MESH_H_

#include <string>
#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "BasicMeshData.h"

namespace tktk
{
	// �uBasicMeshData�v���Ǘ�����N���X
	class BasicMesh
	{
	public:

		BasicMesh(const std::string& writeShadowMapVsFilePath, const tktkContainer::ResourceContainerInitParam& initParam);
		~BasicMesh() = default;
	
	public:

		// �uBasicMeshData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t craete(const BasicMeshInitParam& initParam);

		// �w��́uBasicMeshData�v�̃C���X�^���X�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t copy(size_t originalHandle);

		// �g�p���Ă���}�e���A�����X�V����
		void setMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle);

		// �w��̒ʏ탁�b�V���ŃV���h�E�}�b�v����������
		void writeShadowMap(size_t handle) const;

		// �w��̒ʏ탁�b�V����`�悷��
		void drawMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		// �V���h�E�}�b�v�������ݗp�̃��[�g�V�O�l�`�������
		void createWriteShadowMapRootSignature() const;

		// �V���h�E�}�b�v�������ݗp�̃p�C�v���C���X�e�[�g�����
		void createWriteShadowMapGraphicsPipeLineState(const std::string& writeShadowMapVsFilePath) const;

	private:

		tktkContainer::ResourceContainer<BasicMeshData> m_basicMeshArray;
	};
}
#endif // !BASIC_MESH_H_