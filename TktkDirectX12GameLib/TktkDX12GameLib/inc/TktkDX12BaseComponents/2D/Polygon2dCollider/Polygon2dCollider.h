#ifndef POLYGON_2D_COLLIDER_H_
#define POLYGON_2D_COLLIDER_H_

#include <forward_list>
#include <TktkMath/Structs/Vector2.h>
#include <TktkCollision/2D/BoundingPolygon2D.h>
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
			CollisionGroupTypeCarrier collisionGroupType,	// 当たり判定のグループ番号
			const std::vector<tktkMath::Vector2>& vertexs,	// 当たり判定を構成する頂点の座標（時計回り）
			bool isExtrude,									// 衝突相手を押し出す処理を行うか？
			float extrudedRate								// 押し出されやすさ（割合）
		);

	public:

		// <PolymorphismFunc>
		void start();
		bool isCollide(const ComponentBasePtr& other);
		void afterCollide();

	public:

		// 当たり判定のクラスを取得
		const tktkCollision::BoundingPolygon2D& getBoundingPolygon2d() const;

		// 衝突相手を押し出す処理を行うか？
		bool isExtrud() const;

		// 押し出されやすさを取得
		float getExtrudedRate() const;

		// 座標管理コンポーネントを取得
		const ComponentPtr<Transform2D>& getTransform() const;

	private:

		// 自身の押し出し処理
		void extrusion();

	private:

		struct HitInfo
		{
			GameObjectPtr				otherObject;

			bool						isExtrude;

			float						otherExtrudedRate;

			tktkCollision::HitInfo2D	hitInfo;
		};

	private:

		// ２次元ポリゴンの衝突判定クラス
		tktkCollision::BoundingPolygon2D	m_boundingPolygon2d;

		// 衝突相手を押し出す処理を行うか？
		bool								m_isExtrude;

		// 押し出されやすさ（割合）
		float								m_extrudedRate;

		// 衝突相手と衝突結果を保持するリスト
		std::forward_list<HitInfo>			m_hitInfo2dPairList;

		// 自身の２次元座標コンポーネント
		ComponentPtr<Transform2D>			m_transform2D;
	};
}
#endif // !POLYGON_2D_COLLIDER_H_