#ifndef MESH_MANAGER_H_
#define MESH_MANAGER_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

/* funcUseType */
#include <string>

namespace tktk
{
	struct MeshManagerInitParam;
	class MeshData;
	struct MeshInitParam;
	struct MeshDrawFuncBaseArgs;

	// �uMeshData�v���Ǘ�����N���X
	class MeshManager
	{
	public:

		MeshManager(const MeshManagerInitParam& initParam);
		~MeshManager();
	
	public:

		// �uMeshData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t craete(const MeshInitParam& initParam);

		// �w��́uMeshData�v�̃C���X�^���X�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
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

		tktkContainer::ResourceContainer<MeshData> m_basicMeshArray;
	};
}
#endif // !MESH_MANAGER_H_