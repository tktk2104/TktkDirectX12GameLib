#ifndef MESH_MANAGER_H_
#define MESH_MANAGER_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

/* funcUseType */
#include <string>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	class MeshData;

	struct DrawMeshShaderFilePaths;
	struct MeshInitParam;
	struct CopySourceDataCarrier;
	struct MeshDrawFuncBaseArgs;

	// �uMeshData�v���Ǘ�����N���X
	class MeshManager
	{
	public:

		explicit MeshManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~MeshManager();
	
	public:

		// �uMeshData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t craete(const MeshInitParam& initParam);

		// �w��́uMeshData�v�̃C���X�^���X�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t copy(size_t originalHandle);

		// �g�p���Ă���}�e���A�����X�V����
		void setMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle);

		// �w��̃��b�V�����C���X�^���X�`�悷�鎞�Ɏg�p����l���폜����
		void clearInstanceParam(size_t handle);

		// �w��̃��b�V�����C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
		void addInstanceVertParam(size_t handle, const CopySourceDataCarrier& instanceParam);

		// �X�L�j���O���b�V�����C���X�^���X�`�悷�鎞�Ɏg�p���鍜�s���ǉ�����
		void addInstanceBoneMatrix(size_t handle, const std::array<tktkMath::Matrix4, 128>& boneMatrix);

		// �w��̃��b�V���ŃV���h�E�}�b�v����������
		void writeShadowMap(size_t handle) const;

		// �w��̃X�L�j���O���b�V���ŃV���h�E�}�b�v����������
		void writeShadowMapUseBone(size_t handle) const;

		// �w��̃��b�V�����C���X�^���X�`�悷��
		void draw(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

		// �X�L�j���O���b�V�����C���X�^���X�`�悷��
		void drawUseBone(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		tktkContainer::ResourceContainer<MeshData> m_basicMeshArray;
	};
}
#endif // !MESH_MANAGER_H_