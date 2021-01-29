#include "Sht2D_GamePlayScene.h"

#include "../GameObject/GamePlaySceneObjects/Ui/PlayerHpBar/Sht2D_PlayerHpBar.h"
#include "../GameObject/GamePlaySceneObjects/Ui/PlayerMissileCounter/Sht2D_PlayerMissileCounter.h"
#include "../GameObject/GamePlaySceneObjects/Ui/PlayerBombCounter/Sht2D_PlayerBombCounter.h"
#include "../GameObject/GamePlaySceneObjects/Player/Sht2D_Player.h"
#include "../GameObject/GameRuleObject/Sht2D_GameRuleObject.h"

void Sht2D_GamePlayScene::start()
{
  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│　下の「Sht2D_Player」をシングルクリック＆F12キーを入力してヘッダーファイルに飛んで下さい。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// プレイヤーオブジェクトを作る
	Sht2D_Player::create(tktk::DX12Game::getDrawGameAreaSize() * 0.5f + tktkMath::Vector2(0.0f, 256.0f));


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│　下の「Sht2D_PlayerHpBar」をシングルクリック＆F12キーを入力してヘッダーファイルに飛んで下さい。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// プレイヤーのHpを表示するUiを作る
	Sht2D_PlayerHpBar::create(tktkMath::Vector2(tktk::DX12Game::getScreenSize().x / 2.0f - 128.0f, 1000.0f));


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│　下の「Sht2D_PlayerBombCounter」をシングルクリック＆F12キーを入力してヘッダーファイルに飛んで下さい。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// プレイヤーのボム残数カウンタUIを作る
	Sht2D_PlayerBombCounter::create(tktkMath::Vector2(128.0f, 1000.0f));


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│　下の「Sht2D_PlayerMissileCounter」をシングルクリック＆F12キーを入力してヘッダーファイルに飛んで下さい。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// プレイヤーのミサイル残数カウンタUIを作る
	Sht2D_PlayerMissileCounter::create(tktkMath::Vector2(tktk::DX12Game::getScreenSize().x - 128.0f, 1000.0f));


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│　下の「Sht2D_GameRuleObject」をシングルクリック＆F12キーを入力してヘッダーファイルに飛んで下さい。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// ゲームルールオブジェクトを作る
	Sht2D_GameRuleObject::create();
}
