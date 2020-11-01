#ifndef RECT_COLLIDER_MAKER_H_
#define RECT_COLLIDER_MAKER_H_

#include "RectCollider.h"

namespace tktk
{
	// RectColliderのインスタンスを作成するクラス
	class RectColliderMaker
	{
	private: /* プライベートコンストラクタ達 */

		RectColliderMaker() = default;
		RectColliderMaker(const RectColliderMaker& other) = default;
		RectColliderMaker& operator = (const RectColliderMaker& other) = default;

	public:

		// インスタンス作成開始
		static RectColliderMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static RectColliderMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<RectCollider> create();

		// 当たり判定のグループを設定
		template <class CollisionGroupType, is_idType<CollisionGroupType> = nullptr>
		RectColliderMaker& collisionGroupType(CollisionGroupType value) { return collisionGroupTypeImpl(static_cast<int>(value)); }

		// 当たり判定の大きさを設定
		RectColliderMaker& rectSize(const tktkMath::Vector2& value);

		// 当たり判定のローカル座標を設定
		RectColliderMaker& localPosition(const tktkMath::Vector2& value);

		// 衝突相手を押し出す処理を行うか？
		RectColliderMaker& isExtrude(bool value);

		// 押し出されやすさを設定（割合）
		RectColliderMaker& extrudedRate(float value);

	private: /* 裏実装 */

		RectColliderMaker& collisionGroupTypeImpl(int value);

	private:

		// 自身のポインタ
		static RectColliderMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr		m_user				{ };
		std::vector<int>	m_targetState		{  };
		int					m_collisionGroupType{ 0 };
		tktkMath::Vector2	m_rectSize			{ tktkMath::Vector2_v::one };
		tktkMath::Vector2	m_localPosition		{ tktkMath::Vector2_v::zero };
		bool				m_isExtrude			{ false };
		float				m_extrudedRate		{ 0.0f };
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline RectColliderMaker& RectColliderMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !RECT_COLLIDER_MAKER_H_