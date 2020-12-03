#ifndef ACT_3D_PLAYER_DAMAGER_H_
#define ACT_3D_PLAYER_DAMAGER_H_

#include <TktkDX12GameLib.h>
#include "Act3D_PlayerParam.h"

// プレイヤーのダメージ処理コンポーネント
class Act3D_PlayerDamager
	: public tktk::ComponentBase
{
public:

	Act3D_PlayerDamager() = default;

public:

	void start();
	void handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment);

private:

	// プレイヤーの能力値のコンポーネント
	tktk::ComponentPtr<Act3D_PlayerParam> m_selfParam;
};
#endif // !ACT_3D_PLAYER_DAMAGER_H_