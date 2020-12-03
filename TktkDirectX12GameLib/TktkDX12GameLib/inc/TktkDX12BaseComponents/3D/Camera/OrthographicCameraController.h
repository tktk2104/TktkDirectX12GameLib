#ifndef ORTHOGRAPHIC_CAMERA_CONTROLLER_H_
#define ORTHOGRAPHIC_CAMERA_CONTROLLER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	/* class member */
	class Transform3D;

	// 平行投射カメラ制御コンポーネント
	// 【必須コンポーネント：Transform3D】
	class OrthographicCameraController
		: public ComponentBase
	{
	public:

		OrthographicCameraController(
			size_t cameraHandle,
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

		size_t						m_cameraHandle;
		float						m_cameraWidth;
		float						m_cameraHeight;
		float						m_cameraNear;
		float						m_cameraFar;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !ORTHOGRAPHIC_CAMERA_CONTROLLER_H_