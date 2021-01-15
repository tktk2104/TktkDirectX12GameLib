#ifndef SPRITE_SPREAD_EFFECT_CREATOR_MAKER_H_
#define SPRITE_SPREAD_EFFECT_CREATOR_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "SpriteSpreadEffectCreator.h"

namespace tktk
{
	class SpriteSpreadEffectCreatorMaker
	{
	private: /* プライベートコンストラクタ達 */

		SpriteSpreadEffectCreatorMaker() = default;
		SpriteSpreadEffectCreatorMaker(const SpriteSpreadEffectCreatorMaker& other) = default;
		SpriteSpreadEffectCreatorMaker& operator = (const SpriteSpreadEffectCreatorMaker& other) = default;

	public:

		// 作成開始
		static SpriteSpreadEffectCreatorMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<SpriteSpreadEffectCreator> create();

	public:  /* パラメータ設定関数 */

		// 生成ローカル座標を設定する
		SpriteSpreadEffectCreatorMaker& generateLocalPos(const tktkMath::Vector2 & value);

		// 生成ローカル座標のぶれを設定する
		SpriteSpreadEffectCreatorMaker& generateLocalPosRandomRange(const tktkMath::Vector2 & value);

		// 最小の生成角度（度数法）
		SpriteSpreadEffectCreatorMaker& minGenerateAngleDeg(float value);

		// 最大の生成角度（度数法）
		SpriteSpreadEffectCreatorMaker& maxGenerateAngleDeg(float value);

		// 最初の生成時間（秒）
		SpriteSpreadEffectCreatorMaker& firstGenerateTimeSec(float value);

		// 生成頻度を設定する（秒）
		SpriteSpreadEffectCreatorMaker& generateIntervalTimeSec(float value);

		// 生成頻度のぶれを設定する
		SpriteSpreadEffectCreatorMaker& generateIntervalTimeRandomRange(float value);

		// １度に何個生成するかを設定する（秒）
		SpriteSpreadEffectCreatorMaker& generateNumPerOnce(int value);

		// １度に生成する個数のぶれを設定する
		SpriteSpreadEffectCreatorMaker& generateNumPerOnceRandomRange(int value);

		// 最大何個生成するかを設定する
		SpriteSpreadEffectCreatorMaker& totalGenerateNum(int value);

		// アクティブフラグ変更時に状態をリセットするかを設定する
		SpriteSpreadEffectCreatorMaker& changeAvtiveToReset(bool value);

		// 使用するスプライトマテリアルハンドルを設定する
		SpriteSpreadEffectCreatorMaker& spriteMaterialHandle(size_t value);

		// 使用するスプライトマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		SpriteSpreadEffectCreatorMaker& spriteMaterialId(ResourceIdCarrier value);

		// スプライトのスケールを設定する
		SpriteSpreadEffectCreatorMaker& spriteScale(const tktkMath::Vector2 & value);

		// スプライトのスケールのぶれを設定する
		SpriteSpreadEffectCreatorMaker& spriteScaleRandomRange(const tktkMath::Vector2 & value);

		// スプライトのブレンドレートを設定する
		SpriteSpreadEffectCreatorMaker& spriteBlendRate(const tktkMath::Color & value);

		// 子要素として扱うかを設定する
		SpriteSpreadEffectCreatorMaker& setChild(bool value);

		// 生存時間を設定する（秒）
		SpriteSpreadEffectCreatorMaker& lifeTimeSec(float value);

		// 生存時間のぶれを設定する
		SpriteSpreadEffectCreatorMaker& lifeTimeSecRandomRange(float value);

		// 移動速度を設定する（秒）
		SpriteSpreadEffectCreatorMaker& moveSpeedPerSec(float value);

		// 移動速度のぶれを設定する
		SpriteSpreadEffectCreatorMaker& moveSpeedPerSecRandomRange(float value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SpriteSpreadEffectCreatorMaker m_self;

	private: /* 変数達 */

		GameObjectPtr			m_user{  };
		SpriteSpreadEffectParam	m_param{ };
	};
}
#endif // !SPRITE_SPREAD_EFFECT_CREATOR_MAKER_H_