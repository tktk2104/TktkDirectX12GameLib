#ifndef SPRITE_SHRINK_EFFECT_CREATOR_MAKER_H_
#define SPRITE_SHRINK_EFFECT_CREATOR_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "SpriteShrinkEffectCreator.h"

namespace tktk
{
	class SpriteShrinkEffectCreatorMaker
	{
	private: /* プライベートコンストラクタ達 */

		SpriteShrinkEffectCreatorMaker() = default;
		SpriteShrinkEffectCreatorMaker(const SpriteShrinkEffectCreatorMaker& other) = default;
		SpriteShrinkEffectCreatorMaker& operator = (const SpriteShrinkEffectCreatorMaker& other) = default;

	public:

		// 作成開始
		static SpriteShrinkEffectCreatorMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<SpriteShrinkEffectCreator> create();

	public:  /* パラメータ設定関数 */

		// 収縮点座標を設定する
		SpriteShrinkEffectCreatorMaker& shrinkTargetPos(const tktkMath::Vector2 & value);

		// 収縮点座標のぶれを設定する
		SpriteShrinkEffectCreatorMaker& shrinkTargetPosRandomRange(const tktkMath::Vector2 & value);

		// 最初の生成時間（秒）
		SpriteShrinkEffectCreatorMaker& firstGenerateTimeSec(float value);

		// 生成頻度を設定する（秒）
		SpriteShrinkEffectCreatorMaker& generateIntervalTimeSec(float value);

		// 生成頻度のぶれを設定する
		SpriteShrinkEffectCreatorMaker& generateIntervalTimeRandomRange(float value);

		// １度に何個生成するかを設定する（秒）
		SpriteShrinkEffectCreatorMaker& generateNumPerOnce(int value);

		// １度に生成する個数のぶれを設定する
		SpriteShrinkEffectCreatorMaker& generateNumPerOnceRandomRange(int value);

		// 最大何個生成するかを設定する
		SpriteShrinkEffectCreatorMaker& totalGenerateNum(int value);

		// アクティブフラグ変更時に状態をリセットするかを設定する
		SpriteShrinkEffectCreatorMaker& changeAvtiveToReset(bool value);

		// 使用するスプライトマテリアルハンドルを設定する
		SpriteShrinkEffectCreatorMaker& spriteMaterialHandle(size_t value);

		// 使用するスプライトマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		SpriteShrinkEffectCreatorMaker& spriteMaterialId(ResourceIdCarrier value);

		// スプライトのスケールを設定する
		SpriteShrinkEffectCreatorMaker& spriteScale(const tktkMath::Vector2 & value);

		// スプライトのスケールのぶれを設定する
		SpriteShrinkEffectCreatorMaker& spriteScaleRandomRange(const tktkMath::Vector2 & value);

		// スプライトのブレンドレートを設定する
		SpriteShrinkEffectCreatorMaker& spriteBlendRate(const tktkMath::Color & value);

		// 子要素として扱うかを設定する
		SpriteShrinkEffectCreatorMaker& setChild(bool value);

		// 生存時間を設定する（秒）
		SpriteShrinkEffectCreatorMaker& lifeTimeSec(float value);

		// 生存時間のぶれを設定する
		SpriteShrinkEffectCreatorMaker& lifeTimeSecRandomRange(float value);

		// 移動速度を設定する（秒）
		SpriteShrinkEffectCreatorMaker& moveSpeedPerSec(float value);

		// 移動速度のぶれを設定する
		SpriteShrinkEffectCreatorMaker& moveSpeedPerSecRandomRange(float value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SpriteShrinkEffectCreatorMaker m_self;

	private: /* 変数達 */

		GameObjectPtr			m_user{  };
		SpriteShrinkEffectParam	m_param{ };
	};
}
#endif // !SPRITE_SHRINK_EFFECT_CREATOR_MAKER_H_