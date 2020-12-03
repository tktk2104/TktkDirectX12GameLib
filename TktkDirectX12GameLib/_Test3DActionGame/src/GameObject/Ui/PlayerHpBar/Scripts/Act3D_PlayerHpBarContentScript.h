#ifndef ACT_3D_PLAYER_HP_BAR_CONTENT_SCRIPT_H_
#define ACT_3D_PLAYER_HP_BAR_CONTENT_SCRIPT_H_

#include <TktkDX12GameLib.h>
#include "../../../MainSceneObjects/PlayerObjects/Player/Scripts/Act3D_PlayerParam.h"

class Act3D_PlayerHpBarContentScript
	: public tktk::ComponentBase
{
public:

	Act3D_PlayerHpBarContentScript() = default;

public:

	void start();
	void update();

private:

	// プレイヤーの能力値のコンポーネント
	tktk::ComponentPtr<Act3D_PlayerParam> m_playerParam;

	// 座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !ACT_3D_PLAYER_HP_BAR_CONTENT_SCRIPT_H_
