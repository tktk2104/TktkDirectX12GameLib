#include "Sht2D_LoadingScene.h"

#include "../Enums/Id/ResourceIds.h"

void Sht2D_LoadingScene::start()
{
  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│フォントを読み込む処理は「tktk::DX12Game::createFont(fontId, fontFilePath, fontName)」で行えます。
	│　読み込めるフォントファイルの種類は「.ttf」と「.otf」形式です。
	│　※「FontId」は自分で作る列挙型です。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// フォントを読み込む（フォントID、フォントファイルパス、フォント名）
	tktk::DX12Game::createFont(FontId::Basic, "res/font/x12y20pxScanLine.ttf", "x12y20pxScanLine");


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│テクスチャからスプライトを作る処理は「tktk::DX12Game::loadSprite(spriteId, drawPriority, textureFilePath)」で行えます。
	│　読み込めるテクスチャファイルの種類は「.png」と「.dds」形式です。
	│　※「SpriteId」は自分で作る列挙型です。
	│　※第２引数の値が小さい程奥側のレイヤーに描画されます。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// スプライトを読み込む（スプライトID、描画優先度、画像ファイルパス）
	tktk::DX12Game::loadSprite(SpriteId::Player,				20.0f,		"res/image/Sht2D_Player.png");
	tktk::DX12Game::loadSprite(SpriteId::PlayerNormalBullet,	10.0f,		"res/image/Sht2D_PlayerNormalBullet.png");
	tktk::DX12Game::loadSprite(SpriteId::Missile,				10.0f,		"res/image/Sht2D_Missile.png");
	tktk::DX12Game::loadSprite(SpriteId::BompFrame,				10.0f,		"res/image/Sht2D_Bomb_Frame.png");
	tktk::DX12Game::loadSprite(SpriteId::BompCore,				11.0f,		"res/image/Sht2D_Bomb_Core.png");
	tktk::DX12Game::loadSprite(SpriteId::TankEnemyBase,			0.0f,		"res/image/Sht2D_TankEnemy_Base.png");
	tktk::DX12Game::loadSprite(SpriteId::TankEnemyTop,			1.0f,		"res/image/Sht2D_TankEnemy_Top.png");
	tktk::DX12Game::loadSprite(SpriteId::SpreadBulletEnemy,		0.0f,		"res/image/Sht2D_SpreadBulletEnemy.png");
	tktk::DX12Game::loadSprite(SpriteId::Flame,					-10.0f,		"res/image/Sht2D_Flame.png");
	tktk::DX12Game::loadSprite(SpriteId::Spark,					30.0f,		"res/image/spark.png");
	tktk::DX12Game::loadSprite(SpriteId::Explosion,				40.0f,		"res/image/explosion.png");
	tktk::DX12Game::loadSprite(SpriteId::LockOnTarget,			90.0f,		"res/image/Sht2D_LockOnTarget.png");
	tktk::DX12Game::loadSprite(SpriteId::LockOnReady,			90.0f,		"res/image/Sht2D_LockOnReady.png");
	tktk::DX12Game::loadSprite(SpriteId::HpBarBackGround,		100.0f,		"res/image/Sht2D_HpBar_BackGround.png");
	tktk::DX12Game::loadSprite(SpriteId::HpBarContent,			101.0f,		"res/image/Sht2D_HpBar_Content.png");
	tktk::DX12Game::loadSprite(SpriteId::HpBarFrame,			102.0f,		"res/image/Sht2D_HpBar_Frame.png");
	tktk::DX12Game::loadSprite(SpriteId::StreamingLine,			-110.0f,	"res/image/spark.png");
	tktk::DX12Game::loadSprite(SpriteId::BackGround_Base_1,		-100.0f,	"res/image/Sht2D_BackGround_EnemyBase_1.png");
	tktk::DX12Game::loadSprite(SpriteId::BackGround_Base_2,		-100.0f,	"res/image/Sht2D_BackGround_EnemyBase_2.png");
	tktk::DX12Game::loadSprite(SpriteId::MissileCounterIcon,	100.0f,		"res/image/Sht2D_Missile.png");
	tktk::DX12Game::loadSprite(SpriteId::BompCounterIcon,		100.0f,		"res/image/Sht2D_Bomb_Frame.png");


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│サウンドを読み込む処理は「tktk::DX12Game::loadSound(soundId, soundFilePath)」で行えます。
	│　読み込めるサウンドファイルの種類は「.wav」形式です。
	│　※「SoundId」は自分で作る列挙型です。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// サウンドを読み込む（サウンドID、サウンドファイルパス）
	tktk::DX12Game::loadSound(SoundId::ShotSE,	"res/sound/Sht2D_Shot.wav");


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│シーンを無効にするには「tktk::DX12Game::disableScene(sceneId)」で行えます。
	│　また、「tktk::DX12GameManager::disableScene(tktk::DX12GameManager::getSceneHandle(sceneId)」でも行えます。
	│　※このフレームワークは複数のシーンを同時に起動できる仕様なため、シーンの無効処理をしっかりと書く必要があります。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// 読み込みシーンを無効にする
	tktk::DX12Game::disableScene(SceneId::Loading);

	// タイトルシーンを有効にする
	tktk::DX12Game::enableScene(SceneId::Title);
}
