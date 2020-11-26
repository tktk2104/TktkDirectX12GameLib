#ifndef ACT_3D_END_DAMAGE_H_
#define ACT_3D_END_DAMAGE_H_

#include <TktkDX12GameLib.h>

class Act3D_PlayerEndDamage
	: public tktk::ComponentBase
{
public:

	void onEnable();
	void update();

private:

	// �_���[�W��Ԃ��I���܂ł̎���
	constexpr static float EndDamageTimeSec{ 0.6f };

private:

	float m_endDamageSecTimer{ 0.0f };
};
#endif // !ACT_3D_END_DAMAGE_H_