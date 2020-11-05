#ifndef CAMERA_H_
#define CAMERA_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "CameraData.h"

namespace tktk
{
	// �uCameraData�v���Ǘ�����N���X
	class Camera
	{
	public:

		explicit Camera(const tktkContainer::ResourceContainerInitParam& initParam);
		~Camera() = default;

	public:

		// �uCameraData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create();

		// �w��̃J�����̃r���[�s����擾����
		const tktkMath::Matrix4& getViewMatrix(size_t handle) const;

		// �w��̃J�����̃r���[�s���ݒ肷��
		void setViewMatrix(size_t handle, const tktkMath::Matrix4& view);

		// �w��̃J�����̃v���W�F�N�V�����s����擾����
		const tktkMath::Matrix4& getProjectionMatrix(size_t handle) const;

		// �v�w��̃J�����̃��W�F�N�V�����s���ݒ肷��
		void setProjectionMatrix(size_t handle, const tktkMath::Matrix4& projection);

	private:

		tktkContainer::ResourceContainer<CameraData> m_cameraArray;
	};
}
#endif // !CAMERA_H_