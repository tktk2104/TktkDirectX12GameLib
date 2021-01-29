#include "Sht2D_Stage1Scene.h"

#include "../../GameObject/GamePlaySceneObjects/ObjectSpawner/Sht2D_ObjectSpawner.h"

void Sht2D_Stage1Scene::start()
{
  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│　下の「Sht2D_ObjectSpawner」をシングルクリック＆F12キーを入力してヘッダーファイルに飛んで下さい。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// ステージ１の情報でエネミー出現オブジェクトを作る
	Sht2D_ObjectSpawner::create("res/csv/Stage1.txt");
}
