#ifndef ACT_3D_TITLE_CAMERA_SCRIPT_H_
#define ACT_3D_TITLE_CAMERA_SCRIPT_H_

#include <TktkDX12GameLib.h>

// タイトルカメラ移動コンポーネント
class Act3D_TitleCameraScript
	: public tktk::ComponentBase
{
public:

	Act3D_TitleCameraScript() = default;

public:

	void start();
	void update();

private:

	// 毎秒の回転角度（度数法）
	constexpr static float RotateSpeedPerSecDeg{ 10.0f };

private:

	// 座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
};
#endif // !ACT_3D_TITLE_CAMERA_SCRIPT_H_
