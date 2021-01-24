#ifndef SHT_2D_PLAYER_BOMB_CREATOR_H_
#define SHT_2D_PLAYER_BOMB_CREATOR_H_

#include <TktkDX12GameLib.h>
#include "Sht2D_PlayerBulletCount.h"

class Sht2D_PlayerBombCreator
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerBombCreator() = default;

public:

	void start();
	void update();

private:

	void createBomb();

	void explodeBomb();

private:

	constexpr static float				BombSpeedPerSec		{ 256.0f };

	constexpr static float				BombActiveTimeSec	{ 1.0f };

	constexpr static float				ShotIntervalTimeSec	{ 1.0f };

private:

	float m_shotIntervalSecTimer{ 0.0f };

	tktk::ComponentPtr<tktk::Transform2D> m_transform;

	tktk::ComponentPtr<Sht2D_PlayerBulletCount> m_playerBulletCount;

	tktk::GameObjectPtr m_targetBombObject;
};
#endif // !SHT_2D_PLAYER_BOMB_CREATOR_H_