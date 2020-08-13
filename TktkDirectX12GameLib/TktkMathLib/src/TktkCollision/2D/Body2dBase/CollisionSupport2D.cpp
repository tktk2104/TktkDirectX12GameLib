#include "TktkCollision/2D/Body2dBase/CollisionSupport2D.h"

#include <cmath>
#include <vector>
#include <algorithm>
#include <TktkMath/MathHelper.h>
#include "TktkCollision/2D/BoundingCircle.h"
#include "TktkCollision/2D/BoundingRect.h"
#include "TktkCollision/2D/BoundingPolygon2d.h"

bool CollisionSupport2D::collideCircleToCircle(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	const BoundingCircle& selfCircle = dynamic_cast<const BoundingCircle&>(self);
	const BoundingCircle& otherCircle = dynamic_cast<const BoundingCircle&>(other);

	tktkMath::Vector2 selfCenterPos = selfCircle.calculatePose().calculateTranslation();
	tktkMath::Vector2 otherCenterPos = otherCircle.calculatePose().calculateTranslation();

	float selfRadius = selfCircle.calculateRadius();
	float otherRadius = otherCircle.calculateRadius();

	tktkMath::Vector2 selfToOtherDirection = tktkMath::Vector2::normalize(selfCenterPos - otherCenterPos);
	tktkMath::Vector2 otherToSelfDirection = tktkMath::Vector2::normalize(otherCenterPos - selfCenterPos);

	hitinfo->selfPointClosestToOther = selfCenterPos + (selfToOtherDirection * otherRadius);
	hitinfo->otherPointClosestToSelf = otherCenterPos + (otherToSelfDirection * selfRadius);

	hitinfo->isHit = (tktkMath::Vector2::distance(selfCenterPos, otherCenterPos) < selfRadius + otherRadius);

	return hitinfo->isHit;
}

bool CollisionSupport2D::collideRectToRect(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	const BoundingRect& selfRect = dynamic_cast<const BoundingRect&>(self);
	const BoundingRect& otherRect = dynamic_cast<const BoundingRect&>(other);

	tktkMath::Vector2 selfCenterPos = selfRect.calculatePose().calculateTranslation();
	tktkMath::Vector2 otherCenterPos = otherRect.calculatePose().calculateTranslation();

	tktkMath::Vector2 selfMin = selfRect.calculateCornerPoint(BoundingRect::CornerType::Min);
	tktkMath::Vector2 selfMax = selfRect.calculateCornerPoint(BoundingRect::CornerType::Max);

	tktkMath::Vector2 otherMin = otherRect.calculateCornerPoint(BoundingRect::CornerType::Min);
	tktkMath::Vector2 otherMax = otherRect.calculateCornerPoint(BoundingRect::CornerType::Max);

	hitinfo->selfPointClosestToOther = tktkMath::Vector2::clamp(
		selfCenterPos, otherMin, otherMax
	);

	hitinfo->otherPointClosestToSelf = tktkMath::Vector2::clamp(
		otherCenterPos, selfMin, selfMax
	);

	bool selfMinPosXCheck = selfMin.x < otherMax.x;
	bool selfMinPosYCheck = selfMin.y < otherMax.y;

	bool selfMaxPosXCheck = selfMax.x > otherMin.x;
	bool selfMaxPosYCheck = selfMax.y > otherMin.y;

	// boolの説明変数を使わずに判定した方が比較の処理が減る（誤差の範囲内）
	hitinfo->isHit = (
		selfMinPosXCheck &&
		selfMinPosYCheck &&
		selfMaxPosXCheck &&
		selfMaxPosYCheck
		);

	return hitinfo->isHit;
}

bool CollisionSupport2D::collidePolygonToPolygon(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	const BoundingPolygon2d& selfPolygon = dynamic_cast<const BoundingPolygon2d&>(self);
	const BoundingPolygon2d& otherPolygon = dynamic_cast<const BoundingPolygon2d&>(other);

	std::vector<tktkMath::Vector2> selfVertexs = selfPolygon.calculateVertexs();
	std::vector<tktkMath::Vector2> otherVertexs = otherPolygon.calculateVertexs();

	tktkMath::Vector2 selfMinPos	= tktkMath::Vector2_v::positiveInfinity;
	tktkMath::Vector2 selfMaxPos	= tktkMath::Vector2_v::negativeInfinity;
	tktkMath::Vector2 otherMinPos	= tktkMath::Vector2_v::positiveInfinity;
	tktkMath::Vector2 otherMaxPos	= tktkMath::Vector2_v::negativeInfinity;

	std::for_each(
		std::begin(selfVertexs),
		std::end(selfVertexs),
		[&selfMinPos, &selfMaxPos](const tktkMath::Vector2& node)
		{
			if (selfMinPos.x > node.x) selfMinPos.x = node.x;
			if (selfMaxPos.x < node.x) selfMaxPos.x = node.x;
			if (selfMinPos.y > node.y) selfMinPos.y = node.y;
			if (selfMaxPos.y < node.y) selfMaxPos.y = node.y;
		}
	);

	std::for_each(
		std::begin(otherVertexs),
		std::end(otherVertexs),
		[&otherMinPos, &otherMaxPos](const tktkMath::Vector2& node)
		{
			if (otherMinPos.x > node.x) otherMinPos.x = node.x;
			if (otherMaxPos.x < node.x) otherMaxPos.x = node.x;
			if (otherMinPos.y > node.y) otherMinPos.y = node.y;
			if (otherMaxPos.y < node.y) otherMaxPos.y = node.y;
		}
	);

	tktkMath::Vector2 selfCenterPos = selfMinPos + (selfMaxPos - selfMinPos) / 2;
	tktkMath::Vector2 otherCenterPos = otherMinPos + (otherMaxPos - otherMinPos) / 2;

	if (collidePolygonToPoint(self, otherCenterPos)) return true;
	if (collidePolygonToPoint(other, selfCenterPos)) return true;

	for (size_t i = 0; i < otherVertexs.size(); i++)
	{
		bool isHit = true;

		for (size_t j = 0; j < selfVertexs.size(); j++)
		{
			tktkMath::Vector2 line = selfVertexs.at((j + 1) % selfVertexs.size()) - selfVertexs.at(j);

			tktkMath::Vector2 selfToOther = otherVertexs.at(i) - selfVertexs.at(j);

			float cross = tktkMath::Vector2::cross(selfToOther, line);

			if (cross > 0.0f) isHit = false;
		}

		if (isHit)
		{
			hitinfo->isHit = true;
			return hitinfo->isHit;
		}
	}

	for (size_t i = 0; i < selfVertexs.size(); i++)
	{
		bool isHit = true;

		for (size_t j = 0; j < otherVertexs.size(); j++)
		{
			tktkMath::Vector2 line = otherVertexs.at((j + 1) % otherVertexs.size()) - otherVertexs.at(j);

			tktkMath::Vector2 otherToSelf = selfVertexs.at(i) - otherVertexs.at(j);

			float cross = tktkMath::Vector2::cross(otherToSelf, line);

			if (cross > 0.0f) isHit = false;
		}

		if (isHit)
		{
			hitinfo->isHit = true;
			return hitinfo->isHit;
		}
	}

	return false;
}

bool CollisionSupport2D::collideCircleToRect(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	const BoundingCircle& selfCircle = dynamic_cast<const BoundingCircle&>(self);
	const BoundingRect& otherRect = dynamic_cast<const BoundingRect&>(other);

	tktkMath::Vector2 selfCenterPos = selfCircle.calculatePose().calculateTranslation();
	tktkMath::Vector2 otherCenterPos = otherRect.calculatePose().calculateTranslation();

	tktkMath::Vector2 otherMin = otherRect.calculateCornerPoint(BoundingRect::CornerType::Min);
	tktkMath::Vector2 otherMax = otherRect.calculateCornerPoint(BoundingRect::CornerType::Max);

	hitinfo->selfPointClosestToOther = tktkMath::Vector2::clamp(
		selfCenterPos, otherMin, otherMax
	);

	float selfRadius = selfCircle.calculateRadius();

	// 自分の当たり判定の中心から見た相手の当たり判定の中心の方向
	tktkMath::Vector2 selfToOtherDirection = tktkMath::Vector2::normalize(otherCenterPos - selfCenterPos);

	hitinfo->otherPointClosestToSelf = selfCenterPos 
		+ (selfToOtherDirection * tktkMath::MathHelper::clamp((otherCenterPos - selfCenterPos).length(), 0.0f, selfRadius));

	hitinfo->isHit = (tktkMath::Vector2::distance(selfCenterPos, hitinfo->selfPointClosestToOther) < selfRadius);

	return hitinfo->isHit;
}

bool CollisionSupport2D::collideRectToCircle(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	bool result = collideCircleToRect(other, self, hitinfo);

	auto tempSelfPoint = hitinfo->selfPointClosestToOther;
	hitinfo->selfPointClosestToOther = hitinfo->otherPointClosestToSelf;
	hitinfo->otherPointClosestToSelf = tempSelfPoint;

	return result;
}

bool CollisionSupport2D::collideCircleToPolygon(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	const BoundingCircle& selfCircle = dynamic_cast<const BoundingCircle&>(self);
	const BoundingPolygon2d& otherPolygon = dynamic_cast<const BoundingPolygon2d&>(other);

	tktkMath::Vector2 selfCenterPos = selfCircle.calculatePose().calculateTranslation();

	float selfRadius = selfCircle.calculateRadius();
	std::vector<tktkMath::Vector2> otherVertexs = otherPolygon.calculateVertexs();

	for (size_t i = 0; i < otherVertexs.size(); i++)
	{
		if (tktkMath::Vector2::distanceSquared(otherVertexs.at(i), selfCenterPos) <= selfRadius * selfRadius)
		{
			hitinfo->isHit = true;
			return hitinfo->isHit;
		}
	}

	for (size_t i = 0; i < otherVertexs.size(); i++)
	{
		tktkMath::Vector2 line = otherVertexs.at((i + 1) % otherVertexs.size()) - otherVertexs.at(i);

		tktkMath::Vector2 lineBeginToCircleCenter = selfCenterPos - otherVertexs.at(i);
		tktkMath::Vector2 lineEndToCircleCenter = selfCenterPos - otherVertexs.at((i + 1) % otherVertexs.size());

		float distance = std::abs(tktkMath::Vector2::cross(lineBeginToCircleCenter, line.normalized()));

		if (distance <= selfRadius && tktkMath::Vector2::dot(lineBeginToCircleCenter, line) * tktkMath::Vector2::dot(lineEndToCircleCenter, line) < 0.0f)
		{
			hitinfo->isHit = true;
			return hitinfo->isHit;
		}
	}

	for (size_t i = 0; i < otherVertexs.size(); i++)
	{
		tktkMath::Vector2 line = otherVertexs.at((i + 1) % otherVertexs.size()) - otherVertexs.at(i);
		tktkMath::Vector2 otherVertexToSelfCenter = selfCenterPos - otherVertexs.at(i);
		if (tktkMath::Vector2::cross(otherVertexToSelfCenter, line) > 0)
		{
			hitinfo->isHit = false;
			return hitinfo->isHit;
		}
	}
	hitinfo->isHit = true;
	return hitinfo->isHit;
}

bool CollisionSupport2D::collidePolygonToCircle(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	bool result = collideCircleToPolygon(other, self, hitinfo);

	auto tempSelfPoint = hitinfo->selfPointClosestToOther;
	hitinfo->selfPointClosestToOther = hitinfo->otherPointClosestToSelf;
	hitinfo->otherPointClosestToSelf = tempSelfPoint;

	return result;
}

bool CollisionSupport2D::collideRectToPolygon(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	return false;
}

bool CollisionSupport2D::collidePolygonToRect(const Body2dBase & self, const Body2dBase & other, HitInfo2D * hitinfo)
{
	bool result = collideRectToPolygon(other, self, hitinfo);

	auto tempSelfPoint = hitinfo->selfPointClosestToOther;
	hitinfo->selfPointClosestToOther = hitinfo->otherPointClosestToSelf;
	hitinfo->otherPointClosestToSelf = tempSelfPoint;

	return result;
}

bool CollisionSupport2D::collidePolygonToPoint(const Body2dBase & self, const tktkMath::Vector2 & other)
{
	const BoundingPolygon2d& selfPolygon = dynamic_cast<const BoundingPolygon2d&>(self);
	std::vector<tktkMath::Vector2> selfVertexs = selfPolygon.calculateVertexs();

	for (size_t i = 0; i < selfVertexs.size(); i++)
	{
		tktkMath::Vector2 line = selfVertexs.at((i + 1) % selfVertexs.size()) - selfVertexs.at(i);

		tktkMath::Vector2 selfToOther = other - selfVertexs.at(i);

		float cross = tktkMath::Vector2::cross(selfToOther, line);

		if (cross > 0.0f) return false;
	}
	return true;
}
