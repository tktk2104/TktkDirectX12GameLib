#ifndef SHT_2D_PLAYER_H_
#define SHT_2D_PLAYER_H_

#include <TktkDX12GameLib.h>

// プレイヤーオブジェクト
struct Sht2D_Player
{
  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│下の「create()」をシングルクリック＆F12キーを入力してソースファイルに飛んで下さい。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	static tktk::GameObjectPtr create(const tktkMath::Vector2& position);
};
#endif // !SHT_2D_PLAYER_H_