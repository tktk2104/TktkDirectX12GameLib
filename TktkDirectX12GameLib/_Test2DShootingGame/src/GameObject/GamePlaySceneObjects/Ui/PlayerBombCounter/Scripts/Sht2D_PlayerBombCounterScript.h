#ifndef SHT_2D_PLAYER_BOMB_COUNTER_SCRIPT_H_
#define SHT_2D_PLAYER_BOMB_COUNTER_SCRIPT_H_

#include <vector>
#include <TktkDX12GameLib.h>
#include "../../../Player/Scripts/Sht2D_PlayerBulletCount.h"

class Sht2D_PlayerBombCounterScript
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerBombCounterScript() = default;

public:

	void start();
	void update();

private:

	constexpr static float BombIconXInterval{ 80.0f };

private:

	tktk::ComponentPtr<Sht2D_PlayerBulletCount> m_playerBulletCount;

	std::vector<tktk::GameObjectPtr> m_bombIconObjectArray;
};
#endif // !SHT_2D_PLAYER_BOMB_COUNTER_SCRIPT_H_