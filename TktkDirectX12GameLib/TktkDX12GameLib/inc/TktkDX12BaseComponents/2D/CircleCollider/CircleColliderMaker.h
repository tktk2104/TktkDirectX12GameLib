#ifndef CIRCLE_COLLIDER_MAKER_H_
#define CIRCLE_COLLIDER_MAKER_H_

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
		CircleColliderMaker& collisionGroupType(int value);

		// 当たり判定の半径を設定
		CircleColliderMaker& radius(float value);

		// 当たり判定のローカル座標を設定
		CircleColliderMaker& localPosition(const tktkMath::Vector2& value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		// 自身のポインタ
		static CircleColliderMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user					{ };
		int					m_collisionGroupType	{ 0 };
		float				m_radius				{ 1.0f };
		tktkMath::Vector2	m_localPosition			{ tktkMath::vec2Zero };
	};
}
#endif // !CIRCLE_COLLIDER_MAKER_H_