#ifndef TRANSFORM_3D_MAKER_H_
#define TRANSFORM_3D_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "Transform3D.h"

namespace tktk
{
	// 「Transform3D」を作るヘルパークラス
	class Transform3DMaker
	{
	private: /* プライベートコンストラクタ達 */

		Transform3DMaker() = default;
		Transform3DMaker(const Transform3DMaker& other) = default;
		Transform3DMaker& operator = (const Transform3DMaker& other) = default;

	public:

		// 作成開始
		static Transform3DMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static Transform3DMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<Transform3D> create();

	public:  /* パラメータ設定関数 */

		// 初期座標を設定する
		Transform3DMaker& initPosition(const tktkMath::Vector3& value);

		// 初期スケールを設定する
		Transform3DMaker& initScaleRate(const tktkMath::Vector3& value);

		// 初期回転を設定する
		Transform3DMaker& initRotation(const tktkMath::Quaternion& value);

		// 初期回転を設定する（オイラー角）
		Transform3DMaker& initRotation(const tktkMath::Vector3& value);

		// 行列から初期パラメータを設定する（座標変換情報のみ）
		Transform3DMaker& setInitTransformFromMatrix(const tktkMath::Matrix4& value);

		// 親のTransform3Dとの関係性の種類を設定する
		Transform3DMaker& traceType(TraceParentType value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static Transform3DMaker m_self;

	private: /* 変数達 */

		GameObjectPtr			m_user			{  };
		std::vector<int>		m_targetState	{  };
		tktkMath::Vector3		m_initPosition	{ tktkMath::Vector3_v::zero };
		tktkMath::Vector3		m_initScaleRate	{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion	m_initRotation	{ tktkMath::Quaternion_v::identity };
		TraceParentType			m_traceType		{ TraceParentType::trace_All };
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline Transform3DMaker& Transform3DMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
	{
		// 作成開始処理を行う
		auto& result = makeStart(user);

		// 初期化子リストを配列に変換
		auto targetStateArray = std::vector<StateIdType>(targetState);

		// 対象のステートの階層数分のメモリを確保
		result.m_targetState.reserve(targetStateArray.size());

		// 対象のステートの階層を設定する
		for (const auto& node : targetStateArray) result.m_targetState.push_back(static_cast<int>(node));

		// 自身の参照を返す
		return result;
	}
}
#endif // !TRANSFORM_3D_MAKER_H_