#ifndef SOUND_ID_H_
#define SOUND_ID_H_

// サウンドリソースID
enum class SoundId
{
	/* BGM */
	TitleBGM,		// タイトルBGM
	GamePlayBGM,	// ゲームプレイBGM
	ResultBGM,		// リザルトBGM

	/* SE */
	ShotSE,			// 弾発射SE
	ExplosionSE,	// 爆発音SE
};
#endif // !SOUND_ID_H_