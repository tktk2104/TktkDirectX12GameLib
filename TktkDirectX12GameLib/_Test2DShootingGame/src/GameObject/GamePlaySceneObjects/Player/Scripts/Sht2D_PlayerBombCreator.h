#ifndef SHT_2D_PLAYER_BOMB_CREATOR_H_
#define SHT_2D_PLAYER_BOMB_CREATOR_H_

#include <TktkDX12GameLib.h>
#include "Sht2D_PlayerBulletCount.h"

// プレイヤーボム発射コンポーネント
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

	// 毎秒のボムの移動速度
	constexpr static float				BombSpeedPerSec		{ 256.0f };

	// ボムが起爆可能になるまでの時間（秒）
	constexpr static float				BombActiveTimeSec	{ 1.0f };

	// ボムの発射間隔（秒）
	constexpr static float				ShotIntervalTimeSec	{ 1.0f };

private:

	// ボムの発射間隔タイマー
	float m_shotIntervalSecTimer{ 0.0f };

	// ボムを起爆する為のオブジェクトポインタ
	tktk::GameObjectPtr m_targetBombObject;

	tktk::ComponentPtr<tktk::Transform2D> m_transform;

	tktk::ComponentPtr<Sht2D_PlayerBulletCount> m_playerBulletCount;
};
#endif // !SHT_2D_PLAYER_BOMB_CREATOR_H_