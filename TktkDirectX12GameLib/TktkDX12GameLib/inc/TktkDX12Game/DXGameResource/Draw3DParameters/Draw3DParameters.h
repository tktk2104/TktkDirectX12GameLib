#ifndef DRAW_3D_PARAMETERS_H_
#define DRAW_3D_PARAMETERS_H_

/* std::unique_ptr */
#include <memory>

/* funcUseType */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	class LightManager;
	class CameraManager;
	struct Draw3DParametersInitParam;

	// 3D�`��ɕK�v�ȃp�����[�^���Ǘ�����N���X
	class Draw3DParameters
	{
	public:

		explicit Draw3DParameters(const Draw3DParametersInitParam& initParam);
		~Draw3DParameters();

	public: /* �J�����֌W�̏��� */

		// �J���������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createCamera();

		// �w��̃J�����̃r���[�s����擾����
		const tktkMath::Matrix4& getViewMatrix(size_t handle) const;

		// �w��̃J�����̃r���[�s���ݒ肷��
		void setViewMatrix(size_t handle, const tktkMath::Matrix4& view);

		// �w��̃J�����̃v���W�F�N�V�����s����擾����
		const tktkMath::Matrix4& getProjectionMatrix(size_t handle) const;

		// �w��̃J�����̃v���W�F�N�V�����s���ݒ肷��
		void setProjectionMatrix(size_t handle, const tktkMath::Matrix4& projection);

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

		std::unique_ptr<LightManager>	m_light;
		std::unique_ptr<CameraManager> m_camera;
	};
}
#endif // !DRAW_3D_PARAMETERS_H_