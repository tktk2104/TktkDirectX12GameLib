#ifndef COLLISION_SUPPORT_2D_H_
#define COLLISION_SUPPORT_2D_H_

#include "HitInfo2D.h"

class Body2dBase;
struct tktkMath::Vector2;

class CollisionSupport2D
{
public:

	// 円と円の当たり判定
	static bool collideCircleToCircle(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// 長方形と長方形の当たり判定
	static bool collideRectToRect(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// ポリゴンとポリゴンの当たり判定
	static bool collidePolygonToPolygon(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// 円と長方形の当たり判定
	static bool collideCircleToRect(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// 長方形と円の当たり判定（collideCircleToRect()の処理を行った後、HitInfoのselfとotherを入れ替える）
	static bool collideRectToCircle(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// 円とポリゴンの当たり判定
	static bool collideCircleToPolygon(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// ポリゴンと円の当たり判定（collideCircleToPolygon()の処理を行った後、HitInfoのselfとotherを入れ替える）
	static bool collidePolygonToCircle(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// 長方形とポリゴンの当たり判定
	static bool collideRectToPolygon(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// ポリゴンと長方形の当たり判定（collideRectToPolygon()の処理を行った後、HitInfoのselfとotherを入れ替える）
	static bool collidePolygonToRect(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// ポリゴンと点の当たり判定
	static bool collidePolygonToPoint(const Body2dBase& self, const tktkMath::Vector2& other);
};

#endif // !COLLISION_SUPPORT_2D_H_