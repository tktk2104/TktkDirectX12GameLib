#ifndef BILLBOARD_SHRINK_EFFECT_CREATOR_MAKER_H_
#define BILLBOARD_SHRINK_EFFECT_CREATOR_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "BillboardShrinkEffectCreator.h"

namespace tktk
{
	class BillboardShrinkEffectCreatorMaker
	{
	private: /* プライベートコンストラクタ達 */

		BillboardShrinkEffectCreatorMaker() = default;
		BillboardShrinkEffectCreatorMaker(const BillboardShrinkEffectCreatorMaker& other) = default;
		BillboardShrinkEffectCreatorMaker& operator = (const BillboardShrinkEffectCreatorMaker& other) = default;

	public:

		// 作成開始
		static BillboardShrinkEffectCreatorMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<BillboardShrinkEffectCreator> create();

	public:  /* パラメータ設定関数 */

		// 収縮点座標を設定する
		BillboardShrinkEffectCreatorMaker& shrinkTargetPos(const tktkMath::Vector3 & value);

		// 収縮点座標のぶれを設定する
		BillboardShrinkEffectCreatorMaker& shrinkTargetPosRandomRange(const tktkMath::Vector3 & value);

		// 最初の生成時間（秒）
		BillboardShrinkEffectCreatorMaker& firstGenerateTimeSec(float value);

		// 生成頻度を設定する（秒）
		BillboardShrinkEffectCreatorMaker& generateIntervalTimeSec(float value);

		// 生成頻度のぶれを設定する
		BillboardShrinkEffectCreatorMaker& generateIntervalTimeRandomRange(float value);

		// １度に何個生成するかを設定する（秒）
		BillboardShrinkEffectCreatorMaker& generateNumPerOnce(int value);

		// １度に生成する個数のぶれを設定する
		BillboardShrinkEffectCreatorMaker& generateNumPerOnceRandomRange(int value);

		// 最大何個生成するかを設定する
		BillboardShrinkEffectCreatorMaker& totalGenerateNum(int value);

		// アクティブフラグ変更時に状態をリセットするかを設定する
		BillboardShrinkEffectCreatorMaker& changeAvtiveToReset(bool value);

		// 使用するビルボードマテリアルハンドルを設定する
		BillboardShrinkEffectCreatorMaker& billboardMaterialHandle(size_t value);

		// 使用するビルボードマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		BillboardShrinkEffectCreatorMaker& billboardMaterialId(ResourceIdCarrier value);

		// ビルボードのスケールを設定する
		BillboardShrinkEffectCreatorMaker& billboardScale(const tktkMath::Vector2 & value);

		// ビルボードのスケールのぶれを設定する
		BillboardShrinkEffectCreatorMaker& billboardScaleRandomRange(const tktkMath::Vector2 & value);

		// ビルボードのブレンドレートを設定する
		BillboardShrinkEffectCreatorMaker& billboardBlendRate(const tktkMath::Color & value);

		// 子要素として扱うかを設定する
		BillboardShrinkEffectCreatorMaker& setChild(bool value);

		// 生存時間を設定する（秒）
		BillboardShrinkEffectCreatorMaker& lifeTimeSec(float value);

		// 生存時間のぶれを設定する
		BillboardShrinkEffectCreatorMaker& lifeTimeSecRandomRange(float value);

		// 移動速度を設定する（秒）
		BillboardShrinkEffectCreatorMaker& moveSpeedPerSec(float value);

		// 移動速度のぶれを設定する
		BillboardShrinkEffectCreatorMaker& moveSpeedPerSecRandomRange(float value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BillboardShrinkEffectCreatorMaker m_self;

	private: /* 変数達 */

		GameObjectPtr				m_user{  };
		BillboardShrinkEffectParam	m_param{ };
	};
}
#endif // !BILLBOARD_SHRINK_EFFECT_CREATOR_MAKER_H_