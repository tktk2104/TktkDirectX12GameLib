#ifndef CIRCLE_COLLIDER_MAKER_H_
#define CIRCLE_COLLIDER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "CircleCollider.h"

namespace tktk
{
	// CircleColliderのインスタンスを作成するクラス
	class CircleColliderMaker
	{
	private: /* プライベートコンストラクタ達 */

		CircleColliderMaker() = default;
		CircleColliderMaker(const CircleColliderMaker& other) = default;
		CircleColliderMaker& operator = (const CircleColliderMaker& other) = default;

	public:

		// 作成開始
		static CircleColliderMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<CircleCollider> create();

		// 当たり判定のグループを設定
		template <class CollisionGroupType, is_idType<CollisionGroupType> = nullptr>
		CircleColliderMaker& collisionGroupType(CollisionGroupType value) { return collisionGroupTypeImpl(static_cast<int>(value)); }

		// 当たり判定の半径を設定
		CircleColliderMaker& radius(float value);

		// 当たり判定のローカル座標を設定
		CircleColliderMaker& localPosition(const tktkMath::Vector2& value);

		// 押し出されやすさを設定（割合）
		CircleColliderMaker& extrudedRate(float value);

	private: /* 裏実装 */

		CircleColliderMaker& collisionGroupTypeImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		// 自身のポインタ
		static CircleColliderMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user					{ };
		int					m_collisionGroupType	{ 0 };
		float				m_radius				{ 1.0f };
		tktkMath::Vector2	m_localPosition			{ tktkMath::Vector2_v::zero };
		float				m_extrudedRate			{ 0.0f };
	};
}
#endif // !CIRCLE_COLLIDER_MAKER_H_