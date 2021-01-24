#ifndef PLAYER_STATE_TYPE_H_
#define PLAYER_STATE_TYPE_H_

// プレイヤーの状態の種類
enum class PlayerStateType
{
	Ready,	// 準備ステート
	Alive,	// 生存ステート
	Dead,	// 死亡ステート
};
#endif // !PLAYER_STATE_TYPE_H_