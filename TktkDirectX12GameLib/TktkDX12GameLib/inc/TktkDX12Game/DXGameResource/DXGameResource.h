#ifndef DX_GAME_RESOURCE_H_
#define DX_GAME_RESOURCE_H_

#include <memory>
#include "DXGameResourceNum.h"
#include "DXGameBaseShaderFilePaths.h"
#include "DXGameResourceInitParamIncluder.h"
#include "DXGameResourceFuncArgsIncluder.h"

namespace tktk
{
	// �O���錾�B
	class SceneManager;
	class Sound;
	class PostEffectMaterial;
	class SpriteMaterial;
	class Line2DMaterial;
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

		// �V�[�����쐬���Ēǉ�����
		void createScene(unsigned int id, const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);

		// �V�[����L���ɂ���
		void enableScene(unsigned int id);

		// �V�[���𖳌��ɂ���
		void disableScene(unsigned int id);

		// �L���ɂȂ��Ă���V�[�����X�V����
		void updateScene();

	public: /* �T�E���h�֌W�̏��� */

		// �T�E���h���X�V����
		void updateSound();

		// �ǂݍ��񂾃T�E���h�����ׂč폜����
		void clearSound();

		// �V�����T�E���h��ǂݍ���
		// �����̊֐��œǂݍ��߂�T�E���h�̌`���́u.wav�v�̂�
		void loadSound(unsigned int id, const std::string& fileName);

		// �w�肵���T�E���h���Đ�����
		void playSound(unsigned int id, bool loopPlay);

		// �w�肵���T�E���h���~����
		void stopSound(unsigned int id);

		// �w�肵���T�E���h���ꎞ��~����
		void pauseSound(unsigned int id);

		// �匳�̉��ʂ�ύX����i0.0f�`1.0f�j
		void setMasterVolume(float volume);

	public: /* �|�X�g�G�t�F�N�g�֌W�̏��� */

		// �|�X�g�G�t�F�N�g�̃}�e���A�������
		void createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam);

		// �w��̃|�X�g�G�t�F�N�g��`�悷��
		void drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	public: /* �X�v���C�g�֌W�̏��� */

		// �X�v���C�g�}�e���A�������
		void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		// �w�肵���X�v���C�g��`�悷��
		void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

	public: /* 2D���C���֌W�̏��� */

		// �Q�c���C�������
		void createLine(unsigned int id);

		// ����`�悷��
		void drawLine(unsigned int id, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	public: /* ���b�V���֌W�̏��� */

		// �ʏ탁�b�V�������
		void createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam);

		// �ʏ탁�b�V���̃R�s�[�����
		void copyBasicMesh(unsigned int id, unsigned int originalId);

		// �ʏ탁�b�V���}�e���A�������
		void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		// �ʏ탁�b�V���}�e���A���̃R�s�[�����
		void copyBasicMeshMaterial(unsigned int id, unsigned int originalId);

		// �ʏ탁�b�V�����g�p���Ă���}�e���A�����X�V����
		void setMaterialId(unsigned int id, unsigned int materialSlot, unsigned int materialId);

		// �w��̒ʏ탁�b�V���ŃV���h�E�}�b�v����������
		void writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData) const;

		// �w��̒ʏ탁�b�V���̃}�e���A�������O���t�B�b�N�p�C�v���C���ɐݒ肷��
		void setMaterialData(unsigned int id) const;

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl��ݒ肷��
		void addMaterialAppendParam(unsigned int id, unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos);

		// �w��̒ʏ탁�b�V���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl���X�V����
		void updateMaterialAppendParam(unsigned int id, unsigned int cbufferHandle, unsigned int dataSize, const void* dataTopPos);

		// �w��̒ʏ탁�b�V����`�悷��
		void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs) const;

		// pmd�t�@�C�������[�h���ăQ�[���̊e�탊�\�[�X�N���X�����
		BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	public: /* �X�P���g���֘A�̏��� */

		// �X�P���g�����쐬����
		void createSkeleton(unsigned int id, const SkeletonInitParam& initParam);

		// �w��̃X�P���g�����g���č������Ǘ�����萔�o�b�t�@���X�V����
		void updateBoneMatrixCbuffer(unsigned int id) const;

		// �������Ǘ�����萔�o�b�t�@�ɒP�ʍs���ݒ肷��
		void resetBoneMatrixCbuffer() const;

	public: /* ���[�V�����֌W�̏��� */

		// vmd�t�@�C����ǂݍ���ŁuMotionData�v�̃C���X�^���X�����
		void loadMotion(unsigned int id, const std::string& motionFileName);

		// �w��̃��[�V�����̏I���L�[�̔ԍ����擾����
		unsigned int getMotionEndFrameNo(unsigned int id) const;

		// 2��ނ̃��[�V����������`�⊮���ăX�P���g�����X�V����
		// ���⊮�����̒l�́u0.0f��preFrame100%�v�A�u1.0f��curFrame100%�v�ƂȂ�
		void updateMotion(
			unsigned int skeletonId,
			unsigned int curMotionId,
			unsigned int preMotionId,
			unsigned int curFrame,
			unsigned int preFrame,
			float amount
		);

	public: /* �J�����֌W�̏��� */

		// �J���������
		void createCamera(unsigned int id);

		// �w��̃J�����̃r���[�s����擾����
		const tktkMath::Matrix4& getViewMatrix(unsigned int cameraId) const;

		// �w��̃J�����̃r���[�s���ݒ肷��
		void setViewMatrix(unsigned int cameraId, const tktkMath::Matrix4& view);

		// �w��̃J�����̃v���W�F�N�V�����s����擾����
		const tktkMath::Matrix4& getProjectionMatrix(unsigned int cameraId) const;

		// �w��̃J�����̃v���W�F�N�V�����s���ݒ肷��
		void setProjectionMatrix(unsigned int cameraId, const tktkMath::Matrix4& projection);

	public: /* ���C�g�֌W�̏��� */

		// ���C�g�����
		void createLight(
			unsigned int id,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ���C�g���̒萔�o�b�t�@���X�V����
		void updateLightCBuffer(unsigned int id) const;

		// �w��̃��C�g�̊�����ݒ肷��
		void setLightAmbient(unsigned int id, const tktkMath::Color& ambient);

		// �w��̃��C�g�̊g�U���ˌ���ݒ肷��
		void setLightDiffuse(unsigned int id, const tktkMath::Color& diffuse);

		// �w��̃��C�g�̋��ʔ��ˌ���ݒ肷��
		void setLightSpeqular(unsigned int id, const tktkMath::Color& speqular);

		// �w��̃��C�g�̍��W��ݒ肷��
		void setLightPosition(unsigned int id, const tktkMath::Vector3& position);

	private:

		std::unique_ptr<SceneManager>		m_sceneManager;
		std::unique_ptr<Sound>				m_sound;
		std::unique_ptr<PostEffectMaterial>	m_postEffectMaterial;
		std::unique_ptr<SpriteMaterial>		m_spriteMaterial;
		std::unique_ptr<Line2DMaterial>		m_line2DMaterial;
		std::unique_ptr<MeshResource>		m_meshResource;
		std::unique_ptr<Camera>				m_camera;
		std::unique_ptr<Light>				m_light;
	};
}
#endif // !DX_GAME_RESOURCE_H_
