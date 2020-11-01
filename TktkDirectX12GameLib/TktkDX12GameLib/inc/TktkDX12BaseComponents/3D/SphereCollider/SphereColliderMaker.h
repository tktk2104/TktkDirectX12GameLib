#ifndef SPHERE_COLLIDER_MAKER_H_
#define SPHERE_COLLIDER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "SphereCollider.h"

namespace tktk
{
	// SphereColliderのインスタンスを作成するクラス
	class SphereColliderMaker
	{
	private: /* プライベートコンストラクタ達 */

		SphereColliderMaker() = default;
		SphereColliderMaker(const SphereColliderMaker& other) = default;
		SphereColliderMaker& operator = (const SphereColliderMaker& other) = default;

	public:

		// インスタンス作成開始
		static SphereColliderMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static SphereColliderMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<SphereCollider> create();

		// 当たり判定のグループを設定
		template <class CollisionGroupType, is_idType<CollisionGroupType> = nullptr>
		SphereColliderMaker& collisionGroupType(CollisionGroupType value) { return collisionGroupTypeImpl(static_cast<int>(value)); }

		// 当たり判定の半径を設定
		SphereColliderMaker& radius(float value);

		// 当たり判定のローカル座標を設定
		SphereColliderMaker& localPosition(const tktkMath::Vector3& value);

		// 衝突相手を押し出す処理を行うか？
		SphereColliderMaker& isExtrude(bool value);

		// 押し出されやすさを設定（割合）
		SphereColliderMaker& extrudedRate(float value);

	private: /* 裏実装 */

		SphereColliderMaker& collisionGroupTypeImpl(int value);

	private:

		// 自身のポインタ
		static SphereColliderMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr		m_user				{ };
		std::vector<int>	m_targetState		{  };
		int					m_collisionGroupType{ 0 };
		float				m_radius			{ 1.0f };
		tktkMath::Vector3	m_localPosition		{ tktkMath::Vector3_v::zero };
		bool				m_isExtrude			{ false };
		float				m_extrudedRate		{ 0.0f };
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline SphereColliderMaker& SphereColliderMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !SPHERE_COLLIDER_MAKER_H_