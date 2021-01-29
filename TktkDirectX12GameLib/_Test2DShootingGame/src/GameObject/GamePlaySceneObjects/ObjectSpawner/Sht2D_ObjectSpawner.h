#ifndef SHT_2D_OBJECT_SPAWNER_H_
#define SHT_2D_OBJECT_SPAWNER_H_

#include <TktkDX12GameLib.h>

// エネミー出現オブジェクト
struct Sht2D_ObjectSpawner
{
  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│下の「create()」をシングルクリック＆F12キーを入力してソースファイルに飛んで下さい。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	static tktk::GameObjectPtr create(const std::string& csvFilePath);
};
#endif // !SHT_2D_OBJECT_SPAWNER_H_
