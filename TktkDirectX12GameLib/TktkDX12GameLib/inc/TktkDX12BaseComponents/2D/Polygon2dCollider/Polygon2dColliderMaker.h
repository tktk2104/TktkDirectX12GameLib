#ifndef POLYGON_2D_COLLIDER_MAKER_H_
#define POLYGON_2D_COLLIDER_MAKER_H_

#include "Polygon2dCollider.h"

namespace tktk
{
	// RectColliderのインスタンスを作成するクラス
	class Polygon2dColliderMaker
	{
	private: /* プライベートコンストラクタ達 */

		Polygon2dColliderMaker() = default;
		Polygon2dColliderMaker(const Polygon2dColliderMaker& other) = default;
		Polygon2dColliderMaker& operator = (const Polygon2dColliderMaker& other) = default;

	public:

		// インスタンス作成開始
		static Polygon2dColliderMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<Polygon2dCollider> create();

		// 当たり判定のグループを設定
		Polygon2dColliderMaker& collisionGroupType(int value);

		// 当たり判定の大きさを設定
		Polygon2dColliderMaker& vertexs(const std::vector<tktkMath::Vector2>& value);

		// 当たり判定のローカル座標を設定
		Polygon2dColliderMaker& localPosition(const tktkMath::Vector2& value);

	private:

		// 自身のポインタ
		static Polygon2dColliderMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr					m_user					{ };
		int								m_collisionGroupType	{ 0 };
		std::vector<tktkMath::Vector2>	m_vertexs				{};
		tktkMath::Vector2				m_localPosition			{ tktkMath::Vector2_v::zero };
	};
}
#endif // !POLYGON_2D_COLLIDER_MAKER_H_