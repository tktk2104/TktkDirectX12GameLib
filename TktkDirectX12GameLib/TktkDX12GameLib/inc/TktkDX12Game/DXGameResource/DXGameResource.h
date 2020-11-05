#ifndef DX_GAME_RESOURCE_H_
#define DX_GAME_RESOURCE_H_

#include <memory>
#include "DXGameResourceNum.h"
#include "DXGameBaseShaderFilePaths.h"
#include "DXGameResourceInitParamIncluder.h"
#include "DXGameResourceFuncArgsIncluder.h"
#include "../GameObject/GameObjectTagCarrier.h"

namespace tktk
{
	// �O���錾�B
	class SceneManager;
	class Sound;
	class PostEffectMaterial;
	class SpriteMaterial;
	class Line2DMaterial;
	class BillboardMaterial;
	class MeshResource;
	class Camera;
	class Light;

	// �Q�[���Ŏg�p���郊�\�[�X���Ǘ�����N���X
	class DXGameResource
	{
	public:

		DXGameResource(const DXGameResourceNum& resourceNum, const DXGameBaseShaderFilePaths& filePaths);
		~DXGameResource();

	public: /* �V�[���֌W�̏��� */

		// �V�[�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createScene(const SceneDataInitParam& initParam);

		// �V�[���̏I�����ɍ폜����Q�[���I�u�W�F�N�g�^�O��ݒ肷��
		void setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag);

		// �V�[����L���ɂ���
		void enableScene(size_t handle);

		// �V�[���𖳌��ɂ���
		void disableScene(size_t handle);

		// �L���ɂȂ��Ă���V�[�����X�V����
		void updateScene();

	public: /* �T�E���h�֌W�̏��� */

		// �T�E���h���X�V����
		void updateSound();

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
		void updateSpriteTransformCbuffer(size_t handle, size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate) const;

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����i�؂蔲���͈͎w��Łj
		void updateSpriteTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate, const SpriteClippingParam& clippingParam) const;
	
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

		// �w�肵���r���{�[�h��`�悷��
		void drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const;

		// �������\���R�s�[�o�b�t�@���g���Ē萔�o�b�t�@���X�V����
		void updateBillboardCbuffer(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs) const;

		// �������\���R�s�[�o�b�t�@���g���Ē萔�o�b�t�@���X�V����i�؂蔲���͈͎w��Łj
		void updateBillboardCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const;

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
		void setMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle);

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

		std::unique_ptr<SceneManager>		m_sceneManager;
		std::unique_ptr<Sound>				m_sound;
		std::unique_ptr<PostEffectMaterial>	m_postEffectMaterial;
		std::unique_ptr<SpriteMaterial>		m_spriteMaterial;
		std::unique_ptr<Line2DMaterial>		m_line2DMaterial;
		std::unique_ptr<BillboardMaterial>	m_billboardMaterial;
		std::unique_ptr<MeshResource>		m_meshResource;
		std::unique_ptr<Camera>				m_camera;
		std::unique_ptr<Light>				m_light;
	};
}
#endif // !DX_GAME_RESOURCE_H_
