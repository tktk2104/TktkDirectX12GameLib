#ifndef TRANSFORM_2D_MAKER_H_
#define TRANSFORM_2D_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "Transform2D.h"

namespace tktk
{
	// 「Transform2D」を作るヘルパークラス
	class Transform2DMaker
	{
	private: /* プライベートコンストラクタ達 */

		Transform2DMaker() = default;
		Transform2DMaker(const Transform2DMaker& other) = default;
		Transform2DMaker& operator = (const Transform2DMaker& other) = default;

	public:

		// 作成開始
		static Transform2DMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static Transform2DMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<Transform2D> create();

	public:  /* パラメータ設定関数 */

		// 初期座標を設定する
		Transform2DMaker& initPosition(const tktkMath::Vector2& value);

		// 初期スケールを設定する
		Transform2DMaker& initScaleRate(const tktkMath::Vector2& value);

		// 初期回転を設定する
		Transform2DMaker& initRotationDeg(float value);

		// 親のTransform2Dとの関係性の種類を設定する
		Transform2DMaker& traceType(TraceParentType value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static Transform2DMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user				{  };
		std::vector<int>	m_targetState		{  };
		tktkMath::Vector2	m_initPosition		{ tktkMath::Vector2_v::zero };
		tktkMath::Vector2	m_initScaleRate		{ tktkMath::Vector2_v::one };
		float				m_initRotationDeg	{ 0.0f };
		TraceParentType		m_traceType			{ TraceParentType::trace_All };
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline Transform2DMaker& Transform2DMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !TRANSFORM_2D_MAKER_H_