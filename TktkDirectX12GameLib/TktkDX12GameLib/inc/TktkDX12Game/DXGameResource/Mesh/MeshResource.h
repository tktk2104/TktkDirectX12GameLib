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
		unsigned int createSkeleton(const SkeletonInitParam& initParam);

		// �X�P���g���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int copySkeleton(unsigned int originalHandle);

		// �w��̃X�P���g���̍����̒萔�o�b�t�@�̒l�ɃR�s�[���邽�߂̃o�b�t�@�����A���̃n���h����Ԃ�
		// �����̊֐��Ŏ擾�����n���h���͎g�p��ɁuDX12GameManager::eraseCopyBuffer(handle)�v��K���ǂ�Ńo�b�t�@���폜���Ă�������
		unsigned int createSkeletonCopyBufferHandle(unsigned int handle) const;

		// �w��̃X�P���g�����g���Ĉ������\���R�s�[�o�b�t�@���g���������Ǘ�����萔�o�b�t�@���X�V����
		void updateBoneMatrixCbuffer(unsigned int handle, unsigned int copyBufferHandle) const;

		// �������Ǘ�����萔�o�b�t�@�ɒP�ʍs���ݒ肷��
		void resetBoneMatrixCbuffer() const;

	public: /* ���[�V�����֌W�̏��� */

		// vmd�t�@�C����ǂݍ���ŁuMotionData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int loadMotion(const std::string& motionFileName);

		// �w��̃��[�V�����̏I���L�[�̔ԍ����擾����
		unsigned int getMotionEndFrameNo(unsigned int handle) const;

		// 2��ނ̃��[�V����������`�⊮���ăX�P���g�����X�V����
		// ���⊮�����̒l�́u0.0f��preFrame100%�v�A�u1.0f��curFrame100%�v�ƂȂ�
		void updateMotion(
			unsigned int skeletonHandle,
			unsigned int curMotionHandle,
			unsigned int preMotionHandle,
			unsigned int curFrame,
			unsigned int preFrame,
			float amount
		);

	public: /* ���b�V���֌W�̏��� */

		// �ʏ탁�b�V�������A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createBasicMesh(const BasicMeshInitParam& initParam);

		// �ʏ탁�b�V���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int copyBasicMesh(unsigned int originalHandle);

		// �ʏ탁�b�V���}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam);

		// �ʏ탁�b�V���}�e���A���̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int copyBasicMeshMaterial(unsigned int originalHandle);

		// �ʏ탁�b�V�����g�p���Ă���}�e���A�����X�V����
		void setMaterialHandle(unsigned int meshHandle , unsigned int materialSlot, unsigned int materialHandle);

		// �w��̒ʏ탁�b�V���ŃV���h�E�}�b�v����������
		void writeBasicMeshShadowMap(unsigned int handle) const;

		// �w��̒ʏ탁�b�V���̃}�e���A�������O���t�B�b�N�p�C�v���C���ɐݒ肷��
		void setMaterialData(unsigned int handle) const;

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl��ݒ肷��
		void addMaterialAppendParam(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos);

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl���X�V����
		void updateMaterialAppendParam(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, const void* dataTopPos);

		// �w��̒ʏ탁�b�V����`�悷��
		void drawBasicMesh(unsigned int handle, const MeshDrawFuncBaseArgs& baseArgs) const;

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