#include "TktkCollision/2D/CollisionSupport2D.h"

#include <vector>
#include <TktkMath/MathHelper.h>
#include "TktkCollision/2D/BoundingCircle.h"
#include "TktkCollision/2D/BoundingPolygon2D.h"

namespace tktkCollision
{
	bool CollisionSupport2D::collidePolygonToPolygon(const BoundingPolygon2D& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix)
	{
		// それぞれの二次元ポリゴンの頂点を計算する
		std::vector<tktkMath::Vector2> selfVertexs;
		std::vector<tktkMath::Vector2> otherVertexs;
		selfVertexs.reserve(selfBody.getVertexs().size());
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : selfBody.getVertexs())	selfVertexs.push_back(vertex * selfWorldMatrix);
		for (const auto& vertex : otherBody.getVertexs())	otherVertexs.push_back(vertex * otherWorldMatrix);

		// 衝突判定で使用する頂点の最小、最大値を計算する
		tktkMath::Vector2 selfMinPos	= tktkMath::Vector2_v::positiveInfinity;
		tktkMath::Vector2 selfMaxPos	= tktkMath::Vector2_v::negativeInfinity;
		tktkMath::Vector2 otherMinPos	= tktkMath::Vector2_v::positiveInfinity;
		tktkMath::Vector2 otherMaxPos	= tktkMath::Vector2_v::negativeInfinity;
		for (const auto& vertex : selfVertexs)
		{
			if (selfMinPos.x > vertex.x) selfMinPos.x = vertex.x;
			if (selfMaxPos.x < vertex.x) selfMaxPos.x = vertex.x;
			if (selfMinPos.y > vertex.y) selfMinPos.y = vertex.y;
			if (selfMaxPos.y < vertex.y) selfMaxPos.y = vertex.y;
		}
		for (const auto& vertex : otherVertexs)
		{
			if (otherMinPos.x > vertex.x) otherMinPos.x = vertex.x;
			if (otherMaxPos.x < vertex.x) otherMaxPos.x = vertex.x;
			if (otherMinPos.y > vertex.y) otherMinPos.y = vertex.y;
			if (otherMaxPos.y < vertex.y) otherMaxPos.y = vertex.y;
		}

		// それぞれの二次元ポリゴンの中心座標を計算する
		tktkMath::Vector2 selfCenterPos		= selfMinPos + (selfMaxPos - selfMinPos) / 2;
		tktkMath::Vector2 otherCenterPos	= otherMinPos + (otherMaxPos - otherMinPos) / 2;

		// それぞれの二次元ポリゴンの中心座標が相手の二次元ポリゴン内に入っていたら衝突している
		if (collidePolygonToPoint(selfBody, otherCenterPos, selfWorldMatrix))	return true;
		if (collidePolygonToPoint(otherBody, selfCenterPos, otherWorldMatrix))	return true;

		// それぞれの二次元ポリゴンの頂点が相手の二次元ポリゴン内に入っていたら衝突している
		for (const auto& vertex : otherVertexs) if (collidePolygonToPoint(selfBody, vertex, selfWorldMatrix))	return true;
		for (const auto& vertex : selfVertexs)	if (collidePolygonToPoint(otherBody, vertex, otherWorldMatrix)) return true;

		return false;
	}

	bool CollisionSupport2D::collideCircleToPolygon(const BoundingCircle& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix)
	{
		// 円の中心座標を計算する
		tktkMath::Vector2 selfCenterPos = selfBody.getCenterPosition() * selfWorldMatrix;

		// 円の半径を求める
		float selfRadius = (tktkMath::Vector2(selfBody.getRadius()) * selfWorldMatrix).x;

		// 二次元ポリゴンの頂点の最小、最大値を計算する
		tktkMath::Vector2 otherMinPos = tktkMath::Vector2_v::positiveInfinity;
		tktkMath::Vector2 otherMaxPos = tktkMath::Vector2_v::negativeInfinity;
		for (const auto& vertex : otherBody.getVertexs())
		{
			if (otherMinPos.x > vertex.x) otherMinPos.x = vertex.x;
			if (otherMaxPos.x < vertex.x) otherMaxPos.x = vertex.x;
			if (otherMinPos.y > vertex.y) otherMinPos.y = vertex.y;
			if (otherMaxPos.y < vertex.y) otherMaxPos.y = vertex.y;
		}

		// 二次元ポリゴンの中心座標を計算する
		tktkMath::Vector2 otherCenterPos = otherMinPos + (otherMaxPos - otherMinPos) / 2;

		// 二次元ポリゴンの頂点情報を取得し、円の半径の長さだけ拡大する
		std::vector<tktkMath::Vector2> otherVertexs;
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : otherBody.getVertexs())
		{
			otherVertexs.push_back((vertex + tktkMath::Vector2::normalize(vertex - otherCenterPos) * selfRadius) * otherWorldMatrix);
		}

		for (size_t i = 0; i < otherVertexs.size(); i++)
		{
			// 二次元ポリゴンの辺の長さ、方向を表すベクトルを計算する
			tktkMath::Vector2 line = otherVertexs.at((i + 1) % otherVertexs.size()) - otherVertexs.at(i);

			// 二次元ポリゴンの辺の一つ目の頂点から円の中心座標へのベクトルを計算する
			tktkMath::Vector2 selfToOther = selfCenterPos - otherVertexs.at(i);

			// 上の２つのベクトルの外積が正の数なら衝突していない
			if (tktkMath::Vector2::cross(selfToOther, line) > 0.0f) return false;
		}
		return true;
	}

	bool CollisionSupport2D::collidePolygonToPoint(const BoundingPolygon2D& selfBody, const tktkMath::Vector2& otherPoint, const tktkMath::Matrix3& selfWorldMatrix)
	{
		// 二次元ポリゴンの頂点を計算する
		std::vector<tktkMath::Vector2> selfVertexs;
		selfVertexs.reserve(selfBody.getVertexs().size());
		for (const auto& vertex : selfBody.getVertexs()) selfVertexs.push_back(vertex * selfWorldMatrix);

		for (size_t i = 0; i < selfVertexs.size(); i++)
		{
			// 二次元ポリゴンの辺の長さ、方向を表すベクトルを計算する
			tktkMath::Vector2 line = selfVertexs.at((i + 1) % selfVertexs.size()) - selfVertexs.at(i);

			// 二次元ポリゴンの辺の一つ目の頂点から点の座標へのベクトルを計算する
			tktkMath::Vector2 selfToOther = otherPoint - selfVertexs.at(i);

			// 上の２つのベクトルの外積が正の数なら衝突していない
			if (tktkMath::Vector2::cross(selfToOther, line) > 0.0f) return false;
		}
		return true;
	}

	// 参考にしたサイト「https://www.hiramine.com/programming/graphics/2d_segmentintersection.html」
	CollisionSupport2D::LineCrossCheckResult CollisionSupport2D::lineCrossCheck(const tktkMath::Vector2& firstLinePosOne, const tktkMath::Vector2& firstLinePosTwo, const tktkMath::Vector2& secondLinePosOne, const tktkMath::Vector2& secondLinePosTwo)
	{
		// 判定結果
		LineCrossCheckResult result;

		// 交差判定で使用する分母の値
		float denominator = (firstLinePosTwo.x - firstLinePosOne.x) * (secondLinePosTwo.y - secondLinePosOne.y) - (firstLinePosTwo.y - firstLinePosOne.y) * (secondLinePosTwo.x - secondLinePosOne.x);

		// ゼロで割ろうとした時は直線としても衝突していない
		if (denominator == 0.0f) return result;

		// それぞれの線分の一つ目の点間のベクトルを計算する
		auto vecEachLinePosOne = secondLinePosOne - firstLinePosOne;

		// 一つ目の線分上で見た線分の交点の位置（交差していれば0～1の間の値となる）
		float firstLineCrossPosRate = ((secondLinePosTwo.y - secondLinePosOne.y) * vecEachLinePosOne.x - (secondLinePosTwo.x - secondLinePosOne.x) * vecEachLinePosOne.y) / denominator;

		// 二つ目の線分上で見た線分の交点の位置（交差していれば0～1の間の値となる）
		float secondLineCrossPosRate = ((firstLinePosTwo.y - firstLinePosOne.y) * vecEachLinePosOne.x - (firstLinePosTwo.x - firstLinePosOne.x) * vecEachLinePosOne.y) / denominator;

		// 線分が交差しているか判定する
		result.isHit = (firstLineCrossPosRate <= 1.0f && secondLineCrossPosRate <= 1.0f && firstLineCrossPosRate >= 0.0f && secondLineCrossPosRate >= 0.0f);

		// 交差点を計算する
		result.crossPos = firstLinePosOne + (firstLinePosTwo - firstLinePosOne) * firstLineCrossPosRate;

		return result;
	}

	CollisionSupport2D::LinePolygonHitInfo CollisionSupport2D::lineCollisionWithPolygon(const tktkMath::Vector2& firstPos, const tktkMath::Vector2& secondPos, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& otherWorldMatrix)
	{
		// 二次元ポリゴンの頂点を計算する
		std::vector<tktkMath::Vector2> otherVertexs;
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : otherBody.getVertexs())
		{
			otherVertexs.push_back(vertex * otherWorldMatrix);
		}

		// 基準値（最も長さの差が小さい）
		float minDist = std::numeric_limits<float>::max();

		// 判定結果
		LinePolygonHitInfo result{};

		// “自身の座標から相手の座標へのベクトル”と“自身の座標から最も近い相手の衝突判定の辺”の交差点を求める
		for (size_t i = 0U; i < otherVertexs.size(); i++)
		{
			// 辺を構成する頂点情報
			const auto& firstVert	= otherVertexs.at(i);
			const auto& secondVert	= otherVertexs.at((i + 1U) % otherVertexs.size());

			// “引数の線”と“相手の衝突判定の辺”の交差判定を行う
			auto lineCrossResult = tktkCollision::CollisionSupport2D::lineCrossCheck(firstPos, secondPos, firstVert, secondVert);

			// 線分が交差していなかったら次の辺の判定に進む
			if (!lineCrossResult.isHit) continue;

			// 衝突フラグを立てる
			result.isHit = true;

			// 自身の座標と線分の交差点の距離を計算する
			float dist = tktkMath::Vector2::distance(lineCrossResult.crossPos, firstPos);

			// “自身の座標と線分の交差点の距離”の短さを更新していたら
			if (dist < minDist)
			{
				// 基準値を更新
				minDist = dist;

				// 交差点を更新
				result.selfExtrudePos		= lineCrossResult.crossPos;

				// 交差した相手の辺の頂点を更新
				result.hitLineFirstVert		= firstVert;
				result.hitLineSecondVert	= secondVert;
			}
		}
		return result;
	}

	HitInfo2D CollisionSupport2D::circleCollisionWithCircle(const BoundingCircle& selfBody, const BoundingCircle& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix)
	{
		// それぞれの円の中心座標を計算する
		tktkMath::Vector2 selfCenterPos = selfBody.getCenterPosition() * selfWorldMatrix;
		tktkMath::Vector2 otherCenterPos = otherBody.getCenterPosition() * otherWorldMatrix;
		
		// それぞれの円の半径を求める
		float selfRadius	= selfBody.getRadius()	* selfWorldMatrix.calculateScale().x;
		float otherRadius	= otherBody.getRadius() * otherWorldMatrix.calculateScale().x;
		
		// 衝突判定結果
		HitInfo2D result{};
		
		// それぞれの円の中心点の差がそれぞれの円の半径の合計よりも小さければ衝突している
		result.isHit = tktkMath::Vector2::distance(selfCenterPos, otherCenterPos) < selfRadius + otherRadius;
		
		// もしも衝突していたら
		if (result.isHit)
		{
			result.selfExtrudeVec = otherCenterPos - (selfCenterPos + (otherCenterPos - selfCenterPos).normalized() * (selfRadius + otherRadius));
			return result;
		}
		return result;
	}

	HitInfo2D CollisionSupport2D::polygonCollisionWithPolygon(const BoundingPolygon2D& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix)
	{
		// それぞれの衝突判定の座標を取得
		auto selfPos	= selfWorldMatrix.calculateTranslation();
		auto otherPos	= otherWorldMatrix.calculateTranslation();

		// 二次元ポリゴンの頂点を計算する
		std::vector<tktkMath::Vector2> selfVertexs;
		selfVertexs.reserve(selfBody.getVertexs().size());
		for (const auto& vertex : selfBody.getVertexs()) selfVertexs.push_back(vertex * selfWorldMatrix);
		std::vector<tktkMath::Vector2> otherVertexs;
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : otherBody.getVertexs()) otherVertexs.push_back(vertex * otherWorldMatrix);

		// 衝突中に片方の中心座標がもう片方の辺から最も離れた時の距離を計算する
		float mostFarDistance = 0.0f;
		for (const auto& vertex : selfVertexs)
		{
			float dist = tktkMath::Vector2::distance(selfWorldMatrix.calculateTranslation(), vertex);
			if (dist > mostFarDistance) mostFarDistance = dist;
		}
		for (const auto& vertex : otherVertexs)
		{
			float dist = tktkMath::Vector2::distance(otherWorldMatrix.calculateTranslation(), vertex);
			if (dist > mostFarDistance) mostFarDistance = dist;
		}

		HitInfo2D result{};

		// “自身の座標から相手の座標の線”と“相手のポリゴン”で衝突判定を行う
		// ※自身の座標が相手の衝突判定の中に入り込んでいる可能性を考慮して値が補正されている
		auto selfPosColOtherPolyResult = lineCollisionWithPolygon(
			selfPos - (tktkMath::Vector2::normalize(otherPos - selfPos) * mostFarDistance),	// めり込み想定補正
			otherPos,
			otherBody,
			otherWorldMatrix
		);

		// 直前に行った衝突判定の結果が“衝突していない”だったら相手のポリゴンが閉じていない為、判定不可
		if (!selfPosColOtherPolyResult.isHit) return result;

		// 自身の座標から最も近い相手の衝突判定の辺から内側に垂直に伸びたベクトル（長さは１）を計算する
		auto otherColliderLineVerticalLineDirection = tktkMath::Vector2::perpendicular((selfPosColOtherPolyResult.hitLineSecondVert - selfPosColOtherPolyResult.hitLineFirstVert).normalized());

		// “相手の衝突判定の辺上の点から辺を基準として内側に垂直に伸びた線”と“自身のポリゴン”で衝突判定を行う
		auto otherLineColSelfPolyResult = lineCollisionWithPolygon(
			selfPosColOtherPolyResult.selfExtrudePos,
			selfPosColOtherPolyResult.selfExtrudePos + (otherColliderLineVerticalLineDirection * mostFarDistance),	// めり込み想定補正
			selfBody,
			selfWorldMatrix
		);

		// 直前に行った衝突判定の結果が“衝突していない”だったら相手のポリゴンと衝突していない
		if (!otherLineColSelfPolyResult.isHit) return result;

		{
			// 自身の押し出しに使用する辺の一つ目の頂点を基準に押し出しをした時の押し出し座標を計算
			auto lineCrossCheckResult = tktkCollision::CollisionSupport2D::lineCrossCheck(
				otherLineColSelfPolyResult.hitLineFirstVert,
				otherLineColSelfPolyResult.hitLineFirstVert + otherColliderLineVerticalLineDirection,
				selfPosColOtherPolyResult.hitLineFirstVert,
				selfPosColOtherPolyResult.hitLineSecondVert
			);

			// 自身の押し出しに使用する辺の二つ目の頂点を基準に押し出しをした時の押し出しベクトルを計算する
			auto tempPushVec = lineCrossCheckResult.crossPos - otherLineColSelfPolyResult.hitLineSecondVert;

			// 自身を押し出す方向を表すベクトルが衝突相手のポリゴンの内側に向かっていなければ
			if (!tempPushVec.normalized().equals(otherColliderLineVerticalLineDirection))
			{
				// 自身の押し出しに使用する辺の一つ目の頂点を基準に押し出しをした時の押し出しベクトルを計算し代入する
				result.selfExtrudeVec = lineCrossCheckResult.crossPos - otherLineColSelfPolyResult.hitLineFirstVert;
			}
		}

		{
			// 自身の押し出しに使用する辺の二つ目の頂点を基準に押し出しをした時の押し出し座標を計算
			auto lineCrossCheckResult = tktkCollision::CollisionSupport2D::lineCrossCheck(
				otherLineColSelfPolyResult.hitLineSecondVert,
				otherLineColSelfPolyResult.hitLineSecondVert + otherColliderLineVerticalLineDirection,
				selfPosColOtherPolyResult.hitLineFirstVert,
				selfPosColOtherPolyResult.hitLineSecondVert
			);

			// 自身の押し出しに使用する辺の二つ目の頂点を基準に押し出しをした時の押し出しベクトルを計算する
			auto tempPushVec = lineCrossCheckResult.crossPos - otherLineColSelfPolyResult.hitLineSecondVert;

			// “一つ目の頂点を基準にした押し出しベクトル”が“二つ目の頂点を基準にした押し出しベクトル”よりも短い上、自身を押し出す方向を表すベクトルが衝突相手のポリゴンの内側に向かっていなければ
			if (result.selfExtrudeVec.length() < tempPushVec.length() && tempPushVec.normalized().equals(otherColliderLineVerticalLineDirection))
			{
				// 押し出すベクトルを更新する
				result.selfExtrudeVec = tempPushVec;
			}
		}

		// 押し出す距離がゼロでなければ衝突していると判断する
		result.isHit = (!result.selfExtrudeVec.equals(tktkMath::Vector2_v::zero));

		return result;
	}

	HitInfo2D CollisionSupport2D::circleCollisionWithPolygon(const BoundingCircle& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix)
	{
		// それぞれの衝突判定の座標を取得
		auto selfPos = selfWorldMatrix.calculateTranslation();
		auto otherPos = otherWorldMatrix.calculateTranslation();

		// 円の半径を求める
		float selfRadius = selfBody.getRadius() * selfWorldMatrix.calculateScale().x;

		// ポリゴンの頂点を計算する
		std::vector<tktkMath::Vector2> otherVertexs;
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : otherBody.getVertexs()) otherVertexs.push_back(vertex * otherWorldMatrix);

		// 衝突中に片方の中心座標がもう片方の衝突判定の境界線から最も離れた時の距離を計算する
		float mostFarDistance = selfRadius;
		for (const auto& vertex : otherVertexs)
		{
			float dist = tktkMath::Vector2::distance(otherWorldMatrix.calculateTranslation(), vertex);
			if (dist > mostFarDistance) mostFarDistance = dist;
		}

		HitInfo2D result{};

		// ポリゴンのそれぞれの頂点の中で最も円の中心に近い頂点を探す
		size_t mostNearVertIndex = 0;

		for (size_t i = 1; i < otherVertexs.size(); i++)
		{
			if ((otherVertexs.at(i) - selfPos).length() < (otherVertexs.at(mostNearVertIndex) - selfPos).length())
			{
				mostNearVertIndex = i;
			}
		}

		auto lineCrossCheckResult_1 = tktkCollision::CollisionSupport2D::lineCrossCheck(
			otherVertexs.at((mostNearVertIndex - 1U) % otherVertexs.size()),
			otherVertexs.at(mostNearVertIndex),
			selfPos,
			selfPos + (tktkMath::Vector2::perpendicular(otherVertexs.at(mostNearVertIndex) - otherVertexs.at((mostNearVertIndex - 1U) % otherVertexs.size())) * selfRadius)
		);

		auto lineCrossCheckResult_2 = tktkCollision::CollisionSupport2D::lineCrossCheck(
			otherVertexs.at(mostNearVertIndex),
			otherVertexs.at((mostNearVertIndex + 1U) % otherVertexs.size()),
			selfPos,
			selfPos + (tktkMath::Vector2::perpendicular(otherVertexs.at((mostNearVertIndex + 1U) % otherVertexs.size()) - otherVertexs.at(mostNearVertIndex)) * selfRadius)
		);

		if (!lineCrossCheckResult_1.isHit && !lineCrossCheckResult_2.isHit)
		{
			if (tktkMath::Vector2::distance(selfPos, otherVertexs.at(mostNearVertIndex)) > selfRadius) return result;

			result.isHit = true;
			result.selfExtrudeVec = (selfPos - otherVertexs.at(mostNearVertIndex)).normalized() * (selfRadius - (selfPos - otherVertexs.at(mostNearVertIndex)).length());
			return result;
		}

		// “自身の座標から相手の座標の線”と“相手のポリゴン”で衝突判定を行う
		// ※自身の座標が相手の衝突判定の中に入り込んでいる可能性を考慮して値が補正されている
		auto selfPosColOtherPolyResult = lineCollisionWithPolygon(
			selfPos - (tktkMath::Vector2::normalize(otherPos - selfPos) * mostFarDistance),	// めり込み想定補正
			otherPos,
			otherBody,
			otherWorldMatrix
		);

		// 直前に行った衝突判定の結果が“衝突していない”だったら相手のポリゴンが閉じていない為、判定不可
		if (!selfPosColOtherPolyResult.isHit) return result;

		// “自身の座標から最も近い相手の衝突判定の辺”のベクトル（長さは１）を計算する
		auto otherColliderLineDirection = (selfPosColOtherPolyResult.hitLineFirstVert - selfPosColOtherPolyResult.hitLineSecondVert).normalized();
		
		// “自身の座標から最も近い相手の衝突判定の辺”から外側に垂直に伸びたベクトル（長さは１）を計算する
		auto otherColliderLineVerticalLineDirection = tktkMath::Vector2::perpendicular(otherColliderLineDirection);
		
		// “自身の座標から最も近い相手の衝突判定の辺に平行で自身の座標を通る線”と“自身の座標から最も近い相手の衝突判定の辺から外側に垂直に伸びた線”で衝突判定を行う
		auto lineCrossCheckResult = tktkCollision::CollisionSupport2D::lineCrossCheck(
			selfPosColOtherPolyResult.selfExtrudePos,
			selfPosColOtherPolyResult.selfExtrudePos + otherColliderLineVerticalLineDirection,
			selfPos,
			selfPos + otherColliderLineDirection
		);
		
		// “ポリゴンの辺から垂直に延ばした線”と“ポリゴンの辺に並行で円の中心を通る線”の交点と“ポリゴンの辺から垂直に延ばした線の開始点”の間のベクトル
		auto otherColliderLineToCircleCenterPassVec = lineCrossCheckResult.crossPos - selfPosColOtherPolyResult.selfExtrudePos;
		
		// 上のベクトルが円の半径よりも短ければ衝突している
		result.isHit = (otherColliderLineToCircleCenterPassVec.length() < selfRadius);
		
		// 衝突していたら
		if (result.isHit)
		{
			result.selfExtrudeVec = otherColliderLineToCircleCenterPassVec.normalized() * (selfRadius - otherColliderLineToCircleCenterPassVec.length());
		}
		return result;
	}

	HitInfo2D CollisionSupport2D::polygonCollisionWithCircle(const BoundingPolygon2D& selfBody, const BoundingCircle& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix)
	{
		auto result = circleCollisionWithPolygon(otherBody, selfBody, otherWorldMatrix, selfWorldMatrix);
		result.selfExtrudeVec *= -1.0f;
		return result;
	}
}