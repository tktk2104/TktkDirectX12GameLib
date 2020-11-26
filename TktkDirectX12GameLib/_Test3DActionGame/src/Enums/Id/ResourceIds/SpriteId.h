#ifndef SPRITE_ID_H_
#define SPRITE_ID_H_

// スプライトリソースサウンド
enum class SpriteId
{
	Black4x4,					// 黒

	HpBarFrame,					// HPバーの外枠
	HpBarBackGround,			// HPバーの背景
	PlayerHpBar,				// プレイヤーHPバー
	PlayerHpBarGuide,			// プレイヤーHPバーのガイド
	
	TitleSceneBackGround,		// タイトルシーンの背景
	GameClearSceneBackGround,	// ゲームクリアシーンの背景
	GameOverSceneBackGround,	// ゲームオーバーシーンの背景
};
#endif // !SPRITE_ID_H_