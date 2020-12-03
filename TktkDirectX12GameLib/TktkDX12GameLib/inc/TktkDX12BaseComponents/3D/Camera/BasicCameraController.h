#ifndef BASIC_CAMERA_CONTROLLER_H_
#define BASIC_CAMERA_CONTROLLER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	/* class member */
	class Transform3D;

	// �ʏ�J��������R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform3D�z
	class BasicCameraController
		: public ComponentBase
	{
	public:

		BasicCameraController(
			size_t cameraHandle,
			float camerafov,
			float cameraAspect,
			float cameraNear,
			float cameraFar
		);

	public:

		void start();
		void afterCollide();

	private:

		// �r���[�s��ƃv���W�F�N�V�����s����uTransform3D�v���g���čX�V����
		void updateCameraMat();

	private:

		size_t						m_cameraHandle;
		float						m_cameraFov;
		float						m_cameraAspect;
		float						m_cameraNear;
		float						m_cameraFar;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !BASIC_CAMERA_CONTROLLER_H_