#ifndef MESH_RESOURCE_H_
#define MESH_RESOURCE_H_

#include <memory>
#include "MeshResourceNum.h"
#include "MeshResourceShaderFilePaths.h"
#include "MeshResourceInitParamIncluder.h"
#include "MeshResourceFuncArgsIncluder.h"

namespace tktk
{
	// �O���錾�B
	class Skeleton;
	class Motion;
	class BasicMesh;
	class BasicMeshMaterial;

	// ���b�V���֌W�̃��\�[�X���Ǘ�����N���X
	class MeshResource
	{
	public:

		MeshResource(const MeshResourceNum& resourceNum, const MeshResourceShaderFilePaths& shaderFilePaths);
		~MeshResource();

	public: /* �X�P���g���֌W�̏��� */

		// �X�P���g�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createSkeleton(const SkeletonInitParam& initParam);

		// �X�P���g���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t copySkeleton(size_t originalHandle);

		// �w��̃X�P���g���̍����̒萔�o�b�t�@�̒l�ɃA�b�v���[�h���邽�߂̃o�b�t�@�����A���̃n���h����Ԃ�
		// �����̊֐��Ŏ擾�����n���h���͎g�p��ɁuDX12GameManager::eraseUploadBuffer(handle)�v��K���ǂ�Ńo�b�t�@���폜���Ă�������
		size_t createSkeletonUploadBufferHandle(size_t handle) const;

		// �w��̃X�P���g�����g���Ĉ������\���R�s�[�o�b�t�@���g���������Ǘ�����萔�o�b�t�@���X�V����
		void updateBoneMatrixCbuffer(size_t handle, size_t copyBufferHandle) const;

		// �������Ǘ�����萔�o�b�t�@�ɒP�ʍs���ݒ肷��
		void resetBoneMatrixCbuffer() const;

	public: /* ���[�V�����֌W�̏��� */

		// vmd�t�@�C����ǂݍ���ŁuMotionData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t loadMotion(const std::string& motionFileName);

		// �w��̃��[�V�����̏I���L�[�̔ԍ����擾����
		size_t getMotionEndFrameNo(size_t handle) const;

		// 2��ނ̃��[�V����������`�⊮���ăX�P���g�����X�V����
		// ���⊮�����̒l�́u0.0f��preFrame100%�v�A�u1.0f��curFrame100%�v�ƂȂ�
		void updateMotion(
			size_t skeletonHandle,
			size_t curMotionHandle,
			size_t preMotionHandle,
			size_t curFrame,
			size_t preFrame,
			float amount
		);

	public: /* ���b�V���֌W�̏��� */

		// �ʏ탁�b�V�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createBasicMesh(const BasicMeshInitParam& initParam);

		// �ʏ탁�b�V���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t copyBasicMesh(size_t originalHandle);

		// �ʏ탁�b�V���}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam);

		// �ʏ탁�b�V���}�e���A���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t copyBasicMeshMaterial(size_t originalHandle);

		// �ʏ탁�b�V�����g�p���Ă���}�e���A�����X�V����
		void setMaterialHandle(size_t meshHandle , size_t materialSlot, size_t materialHandle);

		// �w��̒ʏ탁�b�V���ŃV���h�E�}�b�v����������
		void writeBasicMeshShadowMap(size_t handle) const;

		// �w��̒ʏ탁�b�V���̃}�e���A�������O���t�B�b�N�p�C�v���C���ɐݒ肷��
		void setMaterialData(size_t handle) const;

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl��ݒ肷��
		void addMaterialAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, void* dataTopPos);

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl���X�V����
		void updateMaterialAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, const void* dataTopPos);

		// �w��̒ʏ탁�b�V����`�悷��
		void drawBasicMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

		// pmd�t�@�C�������[�h���ăQ�[���̊e�탊�\�[�X�N���X�����
		BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

		// pmx�t�@�C�������[�h���ăQ�[���̊e�탊�\�[�X�N���X�����
		BasicMeshLoadPmxReturnValue loadPmx(const BasicMeshLoadPmxArgs& args);

	private:

		std::unique_ptr<Skeleton>			m_skeleton;
		std::unique_ptr<Motion>				m_motion;
		std::unique_ptr<BasicMesh>			m_basicMesh;
		std::unique_ptr<BasicMeshMaterial>	m_basicMeshMaterial;
	};
}
#endif // !MESH_RESOURCE_H_