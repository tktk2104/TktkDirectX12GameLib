#ifndef ACT_3D_PLAYER_END_DODGE_H_
#define ACT_3D_PLAYER_END_DODGE_H_

#include <TktkDX12GameLib.h>

class Act3D_PlayerEndDodge
	: public tktk::ComponentBase
{
public:

	void start();
	void onEnable();
	void update();

private:

	// ‰ñ”ğó‘Ô‚ªI‚í‚é‚Ü‚Å‚ÌŠÔ
	static constexpr float EndDodgeTimeSec{ 1.0f };

private:

	float m_endDodgeSecTimer{ 0.0f };
	tktk::ComponentPtr<tktk::MeshDrawer>	m_meshDrawer;
};
#endif // !ACT_3D_PLAYER_END_DODGE_H_