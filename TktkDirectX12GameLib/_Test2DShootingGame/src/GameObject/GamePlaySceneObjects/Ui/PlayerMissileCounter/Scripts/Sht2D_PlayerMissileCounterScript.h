#ifndef SHT_2D_PLAYER_MISSILE_COUNTER_SCRIPT_H_
#define SHT_2D_PLAYER_MISSILE_COUNTER_SCRIPT_H_

#include <vector>
#include <TktkDX12GameLib.h>
#include "../../../Player/Scripts/Sht2D_PlayerBulletCount.h"

// プレイヤーミサイルの残弾数だけアイコンを表示するコンポーネント
class Sht2D_PlayerMissileCounterScript
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerMissileCounterScript() = default;

public:

	void start();
	void update();

private:

	// プレイヤーミサイルの残弾アイコンの描画ｘ座標間隔
	constexpr static float MissileIconXInterval{ -40.0f };

private:

	// プレイヤーの残弾数のコンポーネント
	tktk::ComponentPtr<Sht2D_PlayerBulletCount> m_playerBulletCount;

	// プレイヤーミサイルの残弾アイコンオブジェクト配列
	std::vector<tktk::GameObjectPtr> m_missileIconObjectArray;
};
#endif // !SHT_2D_PLAYER_MISSILE_COUNTER_SCRIPT_H_
