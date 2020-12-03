#ifndef BILLBOARD_SPREAD_EFFECT_CREATOR_MAKER_H_
#define BILLBOARD_SPREAD_EFFECT_CREATOR_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "BillboardSpreadEffectCreator.h"

namespace tktk
{
	class BillboardSpreadEffectCreatorMaker
	{
	private: /* プライベートコンストラクタ達 */

		BillboardSpreadEffectCreatorMaker() = default;
		BillboardSpreadEffectCreatorMaker(const BillboardSpreadEffectCreatorMaker& other) = default;
		BillboardSpreadEffectCreatorMaker& operator = (const BillboardSpreadEffectCreatorMaker& other) = default;

	public:

		// 作成開始
		static BillboardSpreadEffectCreatorMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<BillboardSpreadEffectCreator> create();

	public:  /* パラメータ設定関数 */

		// 生成ローカル座標を設定する
		BillboardSpreadEffectCreatorMaker& generateLocalPos(const tktkMath::Vector3& value);

		// 生成ローカル座標のぶれを設定する
		BillboardSpreadEffectCreatorMaker& generateLocalPosRandomRange(const tktkMath::Vector3& value);

		// 最初の生成時間（秒）
		BillboardSpreadEffectCreatorMaker& firstGenerateTimeSec(float value);

		// 生成頻度を設定する（秒）
		BillboardSpreadEffectCreatorMaker& generateIntervalTimeSec(float value);

		// 生成頻度のぶれを設定する
		BillboardSpreadEffectCreatorMaker& generateIntervalTimeRandomRange(float value);

		// １度に何個生成するかを設定する（秒）
		BillboardSpreadEffectCreatorMaker& generateNumPerOnce(int value);

		// １度に生成する個数のぶれを設定する
		BillboardSpreadEffectCreatorMaker& generateNumPerOnceRandomRange(int value);

		// 最大何個生成するかを設定する
		BillboardSpreadEffectCreatorMaker& totalGenerateNum(int value);

		// アクティブフラグ変更時に状態をリセットするかを設定する
		BillboardSpreadEffectCreatorMaker& changeAvtiveToReset(bool value);

		// 使用するビルボードマテリアルハンドルを設定する
		BillboardSpreadEffectCreatorMaker& billboardMaterialHandle(size_t value);

		// 使用するビルボードマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		BillboardSpreadEffectCreatorMaker& billboardMaterialId(ResourceIdCarrier value);

		// ビルボードのスケールを設定する
		BillboardSpreadEffectCreatorMaker& billboardScale(const tktkMath::Vector2& value);

		// ビルボードのスケールのぶれを設定する
		BillboardSpreadEffectCreatorMaker& billboardScaleRandomRange(const tktkMath::Vector2& value);

		// ビルボードのブレンドレートを設定する
		BillboardSpreadEffectCreatorMaker& billboardBlendRate(const tktkMath::Color& value);

		// 子要素として扱うかを設定する
		BillboardSpreadEffectCreatorMaker& setChild(bool value);

		// 生存時間を設定する（秒）
		BillboardSpreadEffectCreatorMaker& lifeTimeSec(float value);

		// 生存時間のぶれを設定する
		BillboardSpreadEffectCreatorMaker& lifeTimeSecRandomRange(float value);

		// 移動速度を設定する（秒）
		BillboardSpreadEffectCreatorMaker& moveSpeedPerSec(float value);

		// 移動速度のぶれを設定する
		BillboardSpreadEffectCreatorMaker& moveSpeedPerSecRandomRange(float value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BillboardSpreadEffectCreatorMaker m_self;

	private: /* 変数達 */

		GameObjectPtr				m_user{  };
		BillboardSpreadEffectParam	m_param{ };
	};
}
#endif // !BILLBOARD_SPREAD_EFFECT_CREATOR_MAKER_H_