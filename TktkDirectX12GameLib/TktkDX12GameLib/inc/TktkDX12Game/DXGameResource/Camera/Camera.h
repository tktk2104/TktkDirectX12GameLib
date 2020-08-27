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
		unsigned int create();

		// �w��̃J�����̃r���[�s����擾����
		const tktkMath::Matrix4& getViewMatrix(unsigned int handle) const;

		// �w��̃J�����̃r���[�s���ݒ肷��
		void setViewMatrix(unsigned int handle, const tktkMath::Matrix4& view);

		// �w��̃J�����̃v���W�F�N�V�����s����擾����
		const tktkMath::Matrix4& getProjectionMatrix(unsigned int handle) const;

		// �v�w��̃J�����̃��W�F�N�V�����s���ݒ肷��
		void setProjectionMatrix(unsigned int handle, const tktkMath::Matrix4& projection);

	private:

		tktkContainer::ResourceContainer<CameraData> m_cameraArray;
	};
}
#endif // !CAMERA_H_