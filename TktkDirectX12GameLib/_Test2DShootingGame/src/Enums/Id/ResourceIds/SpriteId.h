#ifndef SPRITE_ID_H_
#define SPRITE_ID_H_

// スプライトリソースサウンド
enum class SpriteId
{
	Player,				// プレイヤー画像
	PlayerNormalBullet,	// プレイヤー通常弾画像

	Missile,			// ミサイル画像
	BompFrame,			// ボムの外枠画像
	BompCore,			// ボムのコア画像

	TankEnemyBase,		// 戦車エネミーの胴体画像
	TankEnemyTop,		// 戦車エネミーの砲塔画像

	SpreadBulletEnemy,	// 拡散弾エネミー画像

	Flame,				// 炎の画像

	Spark,				// 汎用エフェクト画像
	Explosion,			// 爆発画像

	LockOnTarget,		// ロックオン対象画像
	LockOnReady,		// ロックオン完了画像

	StreamingLine,		// 背景の星

	BackGround_Base_1,	// 基地背景画像１
	BackGround_Base_2,	// 基地背景画像２

	HpBarBackGround,	// 体力バーの背景画像
	HpBarFrame,			// 体力バーの外枠画像
	HpBarContent,		// 体力バーの中身画像

	MissileCounterIcon,	// ミサイルの残数画像
	BompCounterIcon,	// ボムの残数画像
};
#endif // !SPRITE_ID_H_