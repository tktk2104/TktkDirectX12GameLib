#ifndef DX_GAME_SHADER_RESOUSE_H_
#define DX_GAME_SHADER_RESOUSE_H_

/* std::unique_ptr */
#include <memory>

/* funcUseType */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Matrix3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "MeshResouse/Mesh/Loader/MeshLoadPmdReturnValue.h"
#include "MeshResouse/Mesh/Loader/MeshLoadPmxReturnValue.h"


namespace tktk
{
	class PostEffectMaterialManager;
	class Line2DMaterialManager;
	class SpriteMaterialManager;
	class BillboardMaterialManager;
	class MeshResource;

	struct DXGameShaderResouseInitParam;
	struct PostEffectMaterialInitParam;
	struct PostEffectMaterialDrawFuncArgs;
	struct SpriteMaterialInitParam;
	struct SpriteMaterialDrawFuncArgs;
	struct SpriteCbufferUpdateFuncArgs;
	struct SpriteClippingParam;
	struct Line2DMaterialDrawFuncArgs;
	struct BillboardMaterialInitParam;
	struct BillboardDrawFuncBaseArgs;
	struct BillboardMaterialInstanceVertData;
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

	// �V�F�[�_�[�̃��W�X�^�ɂԂ����ޒl���Ǘ�����N���X
	class DXGameShaderResouse
	{
	public:

		DXGameShaderResouse(const DXGameShaderResouseInitParam& initParam);
		~DXGameShaderResouse();

	public: /* �|�X�g�G�t�F�N�g�֌W�̏��� */

	// �|�X�g�G�t�F�N�g�̃}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createPostEffectMaterial(const PostEffectMaterialInitParam& initParam);

		// �w��̃|�X�g�G�t�F�N�g��`�悷��
		void drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	public: /* �X�v���C�g�֌W�̏��� */

		// �X�v���C�g�}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createSpriteMaterial(const SpriteMaterialInitParam& initParam);

		// �w�肵���X�v���C�g��`�悷��
		void drawSprite(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����
		void updateSpriteTransformCbuffer(size_t handle, size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs) const;

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����i�؂蔲���͈͎w��Łj
		void updateSpriteTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs, const SpriteClippingParam& clippingParam) const;

	public: /* 2D���C���֌W�̏��� */

		// �Q�c���C�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createLine();

		// �Q�c���C�����폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseLine(size_t handle);

		// ����`�悷��
		void drawLine(size_t handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	public: /* �r���{�[�h�֌W�̏��� */

		// �r���{�[�h�}�e���A�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createBillboardMaterial(const BillboardMaterialInitParam& initParam);

		// �w�肵���r���{�[�h���g�p����e�N�X�`���̃T�C�Y���擾����
		const tktkMath::Vector2& getBillboardTextureSize(size_t handle) const;

		// �w�肵���r���{�[�h���C���X�^���X�`�悷�鎞�Ɏg�p����l���폜����
		void clearBillboardInstanceParam(size_t handle);

		// �w�肵���r���{�[�h���C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
		void addBillboardInstanceVertParam(size_t handle, const BillboardMaterialInstanceVertData& instanceParam);

		// �w�肵���r���{�[�h��`�悷��
		void drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const;

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
		void setMeshMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle);

		// �w��̃��b�V���̃}�e���A�������O���t�B�b�N�p�C�v���C���ɐݒ肷��
		void setMeshMaterialData(size_t handle) const;

		// �w��̃��b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl��ݒ肷��
		void addMeshMaterialAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam);

		// �w��̃��b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl���X�V����
		void updateMeshMaterialAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

		// �w��̃��b�V�����C���X�^���X�`�悷�鎞�Ɏg�p����l���폜����
		void clearMeshInstanceParam(size_t handle);

		// �w��̃��b�V�����C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
		void addMeshInstanceVertParam(size_t handle, const CopySourceDataCarrier& instanceParam);

		// �X�L�j���O���b�V�����C���X�^���X�`�悷�鎞�Ɏg�p���鍜�s���ǉ�����
		void addMeshInstanceBoneMatrix(size_t meshHandle, size_t skeletonHandle);

		// �w��̃��b�V���ŃV���h�E�}�b�v����������
		void writeMeshShadowMap(size_t handle) const;

		// �w��̃X�L�j���O���b�V���ŃV���h�E�}�b�v����������
		void writeMeshShadowMapUseBone(size_t handle) const;

		// �w��̃��b�V�����C���X�^���X�`�悷��
		void drawMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

		// �X�L�j���O���b�V�����C���X�^���X�`�悷��
		void drawMeshUseBone(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

	public: /* �X�P���g���֘A�̏��� */

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

	private:

		std::unique_ptr<PostEffectMaterialManager> m_postEffectMaterial;
		std::unique_ptr<Line2DMaterialManager>		m_line2DMaterial;
		std::unique_ptr<SpriteMaterialManager>		m_spriteMaterial;
		std::unique_ptr<BillboardMaterialManager>	m_billboardMaterial;
		std::unique_ptr<MeshResource>		m_meshResource;
	};
}
#endif // !DX_GAME_SHADER_RESOUSE_H_