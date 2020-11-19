#ifndef DX_GAME_RESOURCE_H_
#define DX_GAME_RESOURCE_H_

/* std::unique_ptr */
#include <memory>

/* std::string */
#include <string>

/* std::type_index */
#include <typeindex>

/* std::forward_list */
#include <forward_list>

/* funcUseType */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "GameObjectResouse/GameObject/GameObjectPtr.h"
#include "GameObjectResouse/GameObject/GameObjectTagCarrier.h"
#include "GameObjectResouse/Component/ComponentBasePtr.h"
#include "GameObjectResouse/Component/ComponentCollisionFunc/CollisionGroupTypeCarrier.h"
#include "DXGameShaderResouse/MeshResouse/Mesh/Loader/MeshLoadPmdReturnValue.h"
#include "DXGameShaderResouse/MeshResouse/Mesh/Loader/MeshLoadPmxReturnValue.h"
#include "../EventMessage/MessageTypeCarrier.h"

namespace tktk
{
	/* SelfInitParam */
	struct DXGameResourceInitParam;

	/* class member */
	class Draw3DParameters;
	class DXGameShaderResouse;
	class GameObjectResouse;
	class OtherResouse;

	/* funcUseType */
	class MessageAttachment;
	struct ComponentVTableBundle;
	struct ComponentListVTable;
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
	struct SceneInitParam;

	// �Q�[���Ŏg�p���郊�\�[�X���Ǘ�����N���X
	class DXGameResource
	{
	public:

		explicit DXGameResource(const DXGameResourceInitParam& initParam);
		~DXGameResource();

	public:

		// �X�V����
		void update();

		// ���񂾃C���X�^���X���폜����
		void removeDeadInstance();

		// �`�揈��
		void draw();

	public: /* �V�[���֌W�̏��� */

		// �V�[�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createScene(const SceneInitParam& initParam);

		// �V�[���̏I�����ɍ폜����Q�[���I�u�W�F�N�g�^�O��ݒ肷��
		void setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag);

		// �V�[����L���ɂ���
		void enableScene(size_t handle);

		// �V�[���𖳌��ɂ���
		void disableScene(size_t handle);

	public: /* �T�E���h�֌W�̏��� */

		// �ǂݍ��񂾃T�E���h�����ׂč폜����
		void clearSound();

		// �V�����T�E���h��ǂݍ��݁A���̃��\�[�X�̃n���h����Ԃ�
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		size_t loadSound(const std::string& fileName);

		// �w�肵���T�E���h���Đ�����
		void playSound(size_t handle, bool loopPlay);

		// �w�肵���T�E���h���~����
		void stopSound(size_t handle);

		// �w�肵���T�E���h���ꎞ��~����
		void pauseSound(size_t handle);

		// �匳�̉��ʂ�ύX����i0.0f�`1.0f�j
		void setMasterVolume(float volume);

	public: /* �Q�[���I�u�W�F�N�g�֌W�̏��� */

		// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
		void runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment);

		// �Q�[���I�u�W�F�N�g���쐬���A���̃|�C���^��Ԃ�
		GameObjectPtr createGameObject();

		// �����̃^�O���������Q�[���I�u�W�F�N�g���擾����
		// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
		GameObjectPtr findGameObjectWithTag(GameObjectTagCarrier tag) const;

		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagCarrier tag) const;

		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�č폜����
		void destroyGameObjectsWithTag(GameObjectTagCarrier tag);

	public: /* �R���|�[�l���g�֌W�̏��� */

		// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x��ݒ肷��
		// ���f�t�H���g�i0.0f�j�Œl�����������A�������s�����
		void addRunFuncPriority(std::type_index type, float priority);

		// �Փ˔���̑g�ݍ��킹��ǉ�����
		void addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup);

		// �����̃R���|�[�l���g��ǉ�����
		ComponentBasePtr addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const GameObjectPtr& user, const std::shared_ptr<ComponentBase>& componentPtr);

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

	public: /* �J�����֌W�̏��� */

		// �J���������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createCamera();

		// �w��̃J�����̃r���[�s����擾����
		const tktkMath::Matrix4& getViewMatrix(size_t cameraHandle) const;

		// �w��̃J�����̃r���[�s���ݒ肷��
		void setViewMatrix(size_t cameraHandle, const tktkMath::Matrix4& view);

		// �w��̃J�����̃v���W�F�N�V�����s����擾����
		const tktkMath::Matrix4& getProjectionMatrix(size_t cameraHandle) const;

		// �w��̃J�����̃v���W�F�N�V�����s���ݒ肷��
		void setProjectionMatrix(size_t cameraHandle, const tktkMath::Matrix4& projection);

	public: /* ���C�g�֌W�̏��� */

		// ���C�g�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createLight(
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ���C�g���̒萔�o�b�t�@���X�V����
		void updateLightCBuffer(size_t handle) const;

		// �w��̃��C�g�̊�����ݒ肷��
		void setLightAmbient(size_t handle, const tktkMath::Color& ambient);

		// �w��̃��C�g�̊g�U���ˌ���ݒ肷��
		void setLightDiffuse(size_t handle, const tktkMath::Color& diffuse);

		// �w��̃��C�g�̋��ʔ��ˌ���ݒ肷��
		void setLightSpeqular(size_t handle, const tktkMath::Color& speqular);

		// �w��̃��C�g�̍��W��ݒ肷��
		void setLightPosition(size_t handle, const tktkMath::Vector3& position);

	private:

		std::unique_ptr<Draw3DParameters>		m_draw3DParameters;
		std::unique_ptr<DXGameShaderResouse>	m_dxGameShaderResouse;
		std::unique_ptr<GameObjectResouse>		m_gameObjectResouse;
		std::unique_ptr<OtherResouse>			m_otherResouse;
	};
}
#endif // !DX_GAME_RESOURCE_H_