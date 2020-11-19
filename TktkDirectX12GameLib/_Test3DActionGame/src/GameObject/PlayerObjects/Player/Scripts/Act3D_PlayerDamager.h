#ifndef ACT_3D_PLAYER_DAMAGER_H_
#define ACT_3D_PLAYER_DAMAGER_H_

#include <TktkDX12GameLib.h>

class Act3D_PlayerDamager
	: public tktk::ComponentBase
{
public:

	Act3D_PlayerDamager() = default;

public:

	void handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment);
};
#endif // !ACT_3D_PLAYER_DAMAGER_H_