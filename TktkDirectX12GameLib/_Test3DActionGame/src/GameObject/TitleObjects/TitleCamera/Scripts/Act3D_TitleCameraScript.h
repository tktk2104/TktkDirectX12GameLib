#ifndef ACT_3D_TITLE_CAMERA_SCRIPT_H_
#define ACT_3D_TITLE_CAMERA_SCRIPT_H_

#include <TktkDX12GameLib.h>

class Act3D_TitleCameraScript
	: public tktk::ComponentBase
{
public:

	Act3D_TitleCameraScript() = default;

public:

	void start();
	void update();

private:

	constexpr static float RotateSpeedPerSecDeg{ 10.0f };

private:

	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
};
#endif // !ACT_3D_TITLE_CAMERA_SCRIPT_H_
