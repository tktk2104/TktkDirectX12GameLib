#ifndef POLYGON_2D_COLLIDER_MAKER_H_
#define POLYGON_2D_COLLIDER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
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
		template <class CollisionGroupType, is_idType<CollisionGroupType> = nullptr>
		Polygon2dColliderMaker& collisionGroupType(CollisionGroupType value) { return collisionGroupTypeImpl(static_cast<int>(value)); }

		// 当たり判定の大きさを設定
		Polygon2dColliderMaker& vertexs(const std::vector<tktkMath::Vector2>& value);

		// 押し出されやすさを設定（割合）
		Polygon2dColliderMaker& extrudedRate(float value);

	private: /* 裏実装 */

		Polygon2dColliderMaker& collisionGroupTypeImpl(int value);

	private:

		// 自身のポインタ
		static Polygon2dColliderMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr					m_user					{ };
		int								m_collisionGroupType	{ 0 };
		std::vector<tktkMath::Vector2>	m_vertexs				{};
		float							m_extrudedRate			{ 0.0f };
	};
}
#endif // !POLYGON_2D_COLLIDER_MAKER_H_