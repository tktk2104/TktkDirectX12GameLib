#ifndef SHT_2D_PLAYER_COLLISION_REACTION_H_
#define SHT_2D_PLAYER_COLLISION_REACTION_H_

#include <TktkDX12GameLib.h>

// プレイヤーの衝突判定リアクションコンポーネント
class Sht2D_PlayerCollisionReaction
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerCollisionReaction() = default;

public:

	void update();


  /*┌────────────────────────────────────────────────────────────────────────────────────────
    │「onCollisionEnter(otherObject)」、「onCollisionStay(otherObject)」、「onCollisionExit(otherObject)」で衝突時の処理を実装できます。
	│　それぞれ、「衝突開始時」、「衝突中」、「衝突終了時」のタイミングで呼ばれ、引数で衝突相手のオブジェクトが取得できます。
    └────────────────────────────────────────────────────────────────────────────────────────*/

	void onCollisionEnter(const tktk::GameObjectPtr & other);
	void onCollisionStay(const tktk::GameObjectPtr & other);

private:

	// 爆発エフェクトの出現間隔（秒）
	constexpr static float CreateExplosionIntervalTimeSec{ 0.5f };

private:

	// 爆発エフェクトの出現間隔タイマー（秒）
	float m_createExplosionIntervalSecTimer{ 0.0f };
};
#endif // !SHT_2D_PLAYER_COLLISION_REACTION_H_
