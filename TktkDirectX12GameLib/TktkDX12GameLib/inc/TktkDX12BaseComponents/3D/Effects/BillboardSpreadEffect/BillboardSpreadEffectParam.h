#ifndef BILLBOARD_SPREAD_EFFECT_PARAM_H_
#define BILLBOARD_SPREAD_EFFECT_PARAM_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	struct BillboardSpreadEffectParam
	{
		//************************************************************
		/* 生成情報 */

		// 生成ローカル座標
		tktkMath::Vector3 generateLocalPos				{ tktkMath::Vector3_v::zero };
		// 生成ローカル座標のぶれ
		tktkMath::Vector3 generateLocalPosRandomRange	{ tktkMath::Vector3_v::zero };

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

		// 使用するビルボードのハンドル
		size_t	useBillboardHandle						{ 0U };

		// ビルボードのスケール
		tktkMath::Vector2 billboardScale				{ 0.1f, 0.1f };
		// ビルボードのスケールのぶれ
		tktkMath::Vector2 billboardScaleRandomRange		{ tktkMath::Vector2_v::zero };

		// ビルボードのブレンドレート
		tktkMath::Color billboardBlendRate				{ tktkMath::Color_v::white };

		// 子要素として扱うか？
		bool	setChild								{ false };

		// 生存時間（秒）
		float	lifeTimeSec								{ 0.5f };
		// 生存時間のぶれ
		float	lifeTimeSecRandomRange					{ 0.0f };

		// 移動速度（毎秒）
		float	moveSpeedPerSec							{ 10.0f };
		// 移動速度のぶれ
		float	moveSpeedPerSecRandomRange				{ 0.0f };
	};
}
#endif // !BILLBOARD_SPREAD_EFFECT_PARAM_H_