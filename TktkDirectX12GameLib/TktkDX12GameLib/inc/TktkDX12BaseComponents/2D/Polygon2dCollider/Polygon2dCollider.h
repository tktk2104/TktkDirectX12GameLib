#ifndef POLYGON_2D_COLLIDER_H_
#define POLYGON_2D_COLLIDER_H_

#include <TktkMath/Structs/Vector2.h>
#include <TktkCollision/2D/BoundingPolygon2d.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform2D/Transform2D.h"

namespace tktk
{
	// 多角形の当たり判定のコンポーネント
	// 【前提コンポーネント：Transform2D】
	class Polygon2dCollider
		: public ComponentBase
	{
	public:

		Polygon2dCollider(
			int collisionGroupType,							// 当たり判定のグループ番号
			const std::vector<tktkMath::Vector2>& vertexs,	// 当たり判定を構成する頂点の座標（時計回り）
			const tktkMath::Vector2& localPosition			// 当たり判定のローカル座標
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();
		bool isCollide(const ComponentBasePtr& other);

	public:

		// 当たり判定のクラスを取得
		const Body2dBase& getBodyBase() const;

		// 直前の衝突判定の結果を取得
		const HitInfo2D& getHitInfo2D() const;

	private:

		// 衝突判定結果
		HitInfo2D m_hitInfo;

		// ２次元ポリゴンの衝突判定クラス
		BoundingPolygon2d m_boundingPolygon2d;

		// 自身の２次元座標コンポーネント
		ComponentPtr<Transform2D> m_transform2D;
	};
}
#endif // !POLYGON_2D_COLLIDER_H_