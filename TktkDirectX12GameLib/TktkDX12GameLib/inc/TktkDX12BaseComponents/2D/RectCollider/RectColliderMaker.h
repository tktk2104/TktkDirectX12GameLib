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
		int					m_collisionGroupType{ 0 };
		tktkMath::Vector2	m_rectSize			{ tktkMath::Vector2_v::one };
		tktkMath::Vector2	m_localPosition		{ tktkMath::Vector2_v::zero };
		float				m_extrudedRate		{ 0.0f };
	};
}
#endif // !RECT_COLLIDER_MAKER_H_