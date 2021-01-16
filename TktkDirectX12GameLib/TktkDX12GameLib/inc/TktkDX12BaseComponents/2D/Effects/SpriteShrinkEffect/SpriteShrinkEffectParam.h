#ifndef SPRITE_SHRINK_EFFECT_PARAM_H_
#define SPRITE_SHRINK_EFFECT_PARAM_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	struct SpriteShrinkEffectParam
	{
		//************************************************************
		/* 生成情報 */

		// 収縮点座標
		tktkMath::Vector2 shrinkTargetPos				{ tktkMath::Vector2_v::zero };
		// 収縮点座標のぶれ
		tktkMath::Vector2 shrinkTargetPosRandomRange	{ tktkMath::Vector2_v::zero };

		// 最初の生成時間（秒）
		float	firstGenerateTimeSec					{ 0.0f };

		// 生成頻度（秒）
		float	generateIntervalTimeSec					{ 0.1f };
		// 生成頻度のぶれ
		float	generateIntervalTimeRandomRange			{ 0.0f};

		// １度に何個生成するか？
		int		generateNumPerOnce						{ 3 };
		// １度に生成する個数のぶれ
		int		generateNumPerOnceRandomRange			{ 0 };

		// 最大何個生成するか？
		int		totalGenerateNum						{ -1 };

		// アクティブフラグ変更時に状態をリセットするか？
		bool	changeAvtiveToReset						{ false };

		//************************************************************
		/* パーティクル情報 */

		// 使用するスプライトのハンドル
		size_t	useSpriteHandle						{ 0U };

		// スプライトのスケール
		tktkMath::Vector2 spriteScale				{ tktkMath::Vector2_v::one };
		// スプライトのスケールのぶれ
		tktkMath::Vector2 spriteScaleRandomRange	{ tktkMath::Vector2_v::zero };

		// スプライトのブレンドレート
		tktkMath::Color spriteBlendRate				{ tktkMath::Color_v::white };

		// 子要素として扱うか？
		bool	setChild							{ false };

		// 生存時間（秒）
		float	lifeTimeSec							{ 0.5f };
		// 生存時間のぶれ
		float	lifeTimeSecRandomRange				{ 0.0f };

		// 移動速度（毎秒）
		float	moveSpeedPerSec						{ 256.0f };
		// 移動速度のぶれ
		float	moveSpeedPerSecRandomRange			{ 0.0f };

		//************************************************************
		/* パーティクルアニメーション情報 */

		// アニメーションを使用するか？
		bool				useAnimation{ false };

		// アニメーションがループするか？
		bool				isLoop{ false };

		// アニメーションの初期フレーム
		float				initFrame{ 0.0f };

		// アニメーションの再生速度割合
		float				animSpeedRate{ 1.0f };

		// アニメーション１フレームあたりにかける時間（秒）
		float				animFramePerSec{ 0.1f };

		// アニメーションの総フレーム数
		unsigned int		totalAnimFrameSize{ 1U };
	};
}
#endif // !SPRITE_SHRINK_EFFECT_PARAM_H_