#ifndef MESH_RESOURCE_H_
#define MESH_RESOURCE_H_

/* std::unique_ptr */
#include <memory>

/* std::string */
#include <string>

/* funcUseType */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Matrix4.h>
#include "Mesh/Loader/Structs/MeshLoadPmdReturnValue.h"
#include "Mesh/Loader/Structs/MeshLoadPmxReturnValue.h"

namespace tktk
{
	// �O���錾�B
	class SkeletonManager;
	class MotionManager;
	class MeshManager;
	class MeshMaterialManager;
	class BoxMeshMaker;
	class SphereMeshMaker;

	struct MeshResourceInitParam;
	struct SkeletonInitParam;
	struct MeshInitParam;
	struct MeshMaterialInitParam;
	struct MeshMaterialAppendParamInitParam;
	struct MeshMaterialAppendParamUpdateFuncArgs;
	struct MeshDrawFuncBaseArgs;
	struct MeshLoadPmdArgs;
	struct MeshLoadPmxArgs;
	struct MeshDrawFuncRunnerInitParam;
	struct CopySourceDataCarrier;

	// ���b�V���֌W�̃��\�[�X���Ǘ�����N���X
	class MeshResource
	{
	public:

		explicit MeshResource(const MeshResourceInitParam& initParam);
		~MeshResource();

	public: /* �X�P���g���֌W�̏��� */

		// �X�P���g�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createSkeleton(const SkeletonInitParam& initParam);

		// �X�P���g���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t copySkeleton(size_t originalHandle);

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
			float curFrame,
			float preFrame,
			float amount
		);

	public: /* ���b�V���֌W�̏��� */

		// �������瑶�݂��郁�b�V�������
		void createSystemMesh();

		// ���b�V�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createMesh(const MeshInitParam& initParam);

		// ���b�V���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t copyMesh(size_t originalHandle);

		// ���b�V���}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createMeshMaterial(const MeshMaterialInitParam& initParam);

		// ���b�V���}�e���A���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t copyMeshMaterial(size_t originalHandle);

		// �e�N�X�`����\���������̃��b�V�������A���̃n���h����Ԃ�
		size_t makeBoxMesh(size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// �X�J�C�{�b�N�X���b�V�������A���̃n���h����Ԃ�
		size_t makeSkyBoxMesh(size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// pmd�t�@�C�������[�h���ăQ�[���̊e�탊�\�[�X�N���X�����
		MeshLoadPmdReturnValue loadPmd(const MeshLoadPmdArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// pmx�t�@�C�������[�h���ăQ�[���̊e�탊�\�[�X�N���X�����
		MeshLoadPmxReturnValue loadPmx(const MeshLoadPmxArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// ���b�V�����g�p���Ă���}�e���A�����X�V����
		void setMaterialHandle(size_t meshHandle , size_t materialSlot, size_t materialHandle);

		// �w��̃��b�V���̃}�e���A�������O���t�B�b�N�p�C�v���C���ɐݒ肷��
		void setMaterialData(size_t handle) const;

		// �w��̃��b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl��ݒ肷��
		void addMaterialAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam);

		// �w��̃��b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl���X�V����
		void updateMaterialAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

		// �w��̃��b�V�����C���X�^���X�`�悷�鎞�Ɏg�p����l���폜����
		void clearInstanceParam(size_t handle);

		// �w��̃��b�V�����C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
		void addInstanceVertParam(size_t handle, const CopySourceDataCarrier& instanceParam);

		// �X�L�j���O���b�V�����C���X�^���X�`�悷�鎞�Ɏg�p���鍜�s���ǉ�����
		void addInstanceBoneMatrix(size_t meshHandle, size_t skeletonHandle);

		// �w��̃��b�V���ŃV���h�E�}�b�v����������
		void writeShadowMap(size_t handle) const;

		// �w��̃X�L�j���O���b�V���ŃV���h�E�}�b�v����������
		void writeShadowMapUseBone(size_t handle) const;

		// �w��̃��b�V�����C���X�^���X�`�悷��
		void draw(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

		// �X�L�j���O���b�V�����C���X�^���X�`�悷��
		void drawUseBone(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		std::unique_ptr<SkeletonManager>		m_skeleton;
		std::unique_ptr<MotionManager>			m_motion;
		std::unique_ptr<MeshManager>			m_meshManager;
		std::unique_ptr<MeshMaterialManager>	m_meshMaterialManager;
		std::unique_ptr<BoxMeshMaker>			m_boxMeshMaker;
		std::unique_ptr<SphereMeshMaker>		m_sphereMeshMaker;
	};
}
#endif // !MESH_RESOURCE_H_