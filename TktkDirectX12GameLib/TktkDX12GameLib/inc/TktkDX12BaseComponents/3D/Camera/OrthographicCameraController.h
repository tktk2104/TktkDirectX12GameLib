#ifndef ORTHOGRAPHIC_CAMERA_CONTROLLER_H_
#define ORTHOGRAPHIC_CAMERA_CONTROLLER_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// 平行投射カメラ制御コンポーネント
	// 【必須コンポーネント：Transform3D】
	class OrthographicCameraController
		: public ComponentBase
	{
	public:

		OrthographicCameraController(
			unsigned int cameraHandle,
			float cameraWidth,
			float cameraHeight,
			float cameraNear,
			float cameraFar
		);

	public:

		void start();
		void afterCollide();

	private:

		// ビュー行列とプロジェクション行列を「Transform3D」を使って更新する
		void updateCameraMat();

	private:

		unsigned int				m_cameraHandle;
		float						m_cameraWidth;
		float						m_cameraHeight;
		float						m_cameraNear;
		float						m_cameraFar;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !ORTHOGRAPHIC_CAMERA_CONTROLLER_H_