#ifndef ACT_3D_INPUT_TO_START_DODGE_H_
#define ACT_3D_INPUT_TO_START_DODGE_H_

#include <TktkDX12GameLib.h>

class Act3D_InputToStartDodge
	: public tktk::ComponentBase
{
public:

	Act3D_InputToStartDodge() = default;

public:

	void start();
	void update();

private:

	// 回避のインターバル
	constexpr static float DodgeIntervalTimeSec{ 0.7f };

	// 回避移動の初速
	constexpr static float DodgeMovePower{ 6.0f };

private:

	float m_dodgeIntervelSecTimer{ 0.0f };
	tktk::ComponentPtr<tktk::MeshDrawer>			m_meshDrawer;
	tktk::ComponentPtr<tktk::Transform3D>			m_transform;
	tktk::ComponentPtr<tktk::InertialMovement3D>	m_inertialMovement;
};
#endif // !ACT_3D_INPUT_TO_START_DODGE_H_