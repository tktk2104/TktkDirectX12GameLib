#include "TktkCollision/2D/CollisionSupport2D.h"

#include <TktkMath/MathHelper.h>
#include "TktkCollision/2D/BoundingCircle.h"
#include "TktkCollision/2D/BoundingPolygon2D.h"

namespace
{
	// ポリゴンと点の当たり判定
	bool polygonCollisionWithPoint(const std::vector<tktkMath::Vector2>& selfVertexs, const tktkMath::Vector2& otherPoint)
	{
		for (size_t i = 0; i < selfVertexs.size(); i++)
		{
			// 現在参照している辺を構成する頂点達
			const auto& firstVert = selfVertexs.at(i);
			const auto& secondVert = selfVertexs.at((i + 1) % selfVertexs.size());

			// 二次元ポリゴンの辺の長さ、方向を表すベクトルを計算する
			tktkMath::Vector2 line = secondVert - firstVert;

			// 二次元ポリゴンの辺の一つ目の頂点から点の座標へのベクトルを計算する
			tktkMath::Vector2 firstVertToPoint = otherPoint - firstVert;

			// 上の２つのベクトルの外積を計算する
			float cross = tktkMath::Vector2::cross(firstVertToPoint, line);

			// 求めた外積が正の数なら衝突していない
			if (cross > 0.0f) return false;
		}
		return true;
	}
}

namespace tktkCollision
{
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

	CollisionSupport2D::LinePolygonHitInfo CollisionSupport2D::lineCollisionWithPolygon(const tktkMath::Vector2& firstPos, const tktkMath::Vector2& secondPos, const std::vector<tktkMath::Vector2>& otherVertexs)
	{
		// 判定結果
		LinePolygonHitInfo result{};

		// 引数の線分がポリゴン内に完全に入り込んでいたら
		if (polygonCollisionWithPoint(otherVertexs, firstPos) && polygonCollisionWithPoint(otherVertexs, secondPos))
		{
			result.isHit = true;
			return result;
		}

		// 交差点２個分のメモリを確保する
		result.crossPosArray.reserve(2U);

		// 相手のポリゴンの頂点を巡回する
		for (size_t i = 0U; i < otherVertexs.size(); i++)
		{
			// 辺を構成する頂点情報
			const auto& firstVert	= otherVertexs.at(i);
			const auto& secondVert	= otherVertexs.at((i + 1U) % otherVertexs.size());

			// “引数の線分”と“相手の衝突判定の辺”の交差判定を行う
			auto lineCrossResult = tktkCollision::CollisionSupport2D::lineCrossCheck(firstPos, secondPos, firstVert, secondVert);

			// 線分が交差していたら
			if (lineCrossResult.isHit)
			{
				// 衝突フラグを立てる
				result.isHit = true;

				// 交差点を追加する
				result.crossPosArray.push_back(lineCrossResult.crossPos);
			}
		}
		return result;
	}

	HitInfo2D CollisionSupport2D::circleCollisionWithCircle(const tktkMath::Vector2& selfCenterPos, float selfRadius, const tktkMath::Vector2& otherCenterPos, float otherRadius)
	{
		// 衝突判定結果
		auto result = HitInfo2D();
		
		// それぞれの中心座標の距離を計算する
		float posDist = tktkMath::Vector2::distance(selfCenterPos, otherCenterPos);

		// 衝突判定結果
		result.isHit = (posDist < selfRadius + otherRadius);
		
		// 自身を押し出す方向を計算する
		result.selfExtrudeVec = (selfCenterPos - otherCenterPos).normalized() * ((selfRadius + otherRadius) - posDist);

		return result;
	}

	HitInfo2D CollisionSupport2D::polygonCollisionWithPolygon(const std::vector<tktkMath::Vector2>& selfVertexs, const std::vector<tktkMath::Vector2>& otherVertexs)
	{
		HitInfo2D result{};

		// 自身のポリゴンの中心座標を計算する
		auto selfPolyCenterPos = tktkMath::Vector2_v::zero;
		for (const auto& selfVert : selfVertexs) selfPolyCenterPos += selfVert;
		selfPolyCenterPos /= selfVertexs.size();

		// 相手のポリゴンの中心座標を計算する
		auto otherPolyCenterPos = tktkMath::Vector2_v::zero;
		for (const auto& otherVert : otherVertexs) otherPolyCenterPos += otherVert;
		otherPolyCenterPos /= otherVertexs.size();

		// 自身のポリゴンの中心座標が相手のポリゴン内にあったら
		if (polygonCollisionWithPoint(otherVertexs, selfPolyCenterPos))
		{
			// 衝突している
			result.isHit = true;
		}
		else
		{
			// 相手のポリゴンの中心座標が自身のポリゴン内にあったら
			if (polygonCollisionWithPoint(selfVertexs, otherPolyCenterPos))
			{
				// 衝突している
				result.isHit = true;
			}
			else
			{
				// 交差している辺が存在するか？
				bool findInclusionLine = false;

				// 相手のポリゴンを構成する頂点を巡回する
				for (size_t vertIndex = 0; vertIndex < otherVertexs.size(); vertIndex++)
				{
					// 相手のポリゴンの辺と自身のポリゴンで衝突判定を行う
					auto lineCollisionPolygonResult = lineCollisionWithPolygon(otherVertexs.at(vertIndex), otherVertexs.at((vertIndex + 1U) % otherVertexs.size()), selfVertexs);

					// “相手のポリゴンの辺と自身のポリゴン”が交差しているか？
					if (lineCollisionPolygonResult.isHit) findInclusionLine = true;
				}

				// 交差している辺が存在したら衝突している
				if (findInclusionLine) result.isHit = true;
			}
		}

		// 衝突していたら
		if (result.isHit)
		{
			// 相手のポリゴンの辺を使って求めた押し出し距離
			result.selfExtrudeVec = tktkMath::Vector2_v::positiveInfinity;

			// いずれかのポリゴンの中心から最も遠い頂点までの距離
			float maxCenterToVertDist = 0.0f;

			// 相手のポリゴンの頂点を巡回する
			for (const auto& node : otherVertexs)
			{
				// ポリゴンの中心点と頂点の距離を計算する
				float dist = tktkMath::Vector2::distance(otherPolyCenterPos, node);

				// 距離の長さを更新していたら値を更新する
				if (dist > maxCenterToVertDist) maxCenterToVertDist = dist;
			}

			// 自身のポリゴンの頂点を巡回する
			for (const auto& node : selfVertexs)
			{
				// ポリゴンの中心点と頂点の距離を計算する
				float dist = tktkMath::Vector2::distance(selfPolyCenterPos, node);

				// 距離の長さを更新していたら値を更新する
				if (dist > maxCenterToVertDist) maxCenterToVertDist = dist;
			}

			// 自身のポリゴンの頂点を巡回する
			for (size_t i = 0; i < selfVertexs.size(); i++)
			{
				const auto& firstVert = selfVertexs.at(i);
				const auto& secondVert = selfVertexs.at((i + 1U) % selfVertexs.size());

				// 自身のポリゴンの辺を構成する頂点が相手のポリゴン内に入っているか？
				bool firstVertInOtherPoly	= polygonCollisionWithPoint(otherVertexs, firstVert);
				bool secondVertInOtherPoly	= polygonCollisionWithPoint(otherVertexs, secondVert);

				// ２つの頂点がいずれも相手のポリゴン内に入って居なかったら次の要素へ
				if (!(firstVertInOtherPoly || secondVertInOtherPoly)) continue;
			
				// 自身のポリゴンの辺のベクトル
				auto selfPolyLineVec = secondVert - firstVert;
			
				// 自身のポリゴンの辺の逆法線を計算する
				auto selfLineInverseNormal = tktkMath::Vector2::perpendicular(selfPolyLineVec.normalized());

				// 線分の開始点のオフセット（めり込み時の補正）
				auto collideLineStartOffset = -selfLineInverseNormal * 8.0f;

				// 線分の終点に向かうベクトルを計算する
				auto collideLineVec = selfLineInverseNormal * maxCenterToVertDist * 2.0f;
			
				// ２つ頂点それぞれの押し出し幅の内最大の物を代入する変数
				auto maxExtrudeVec = tktkMath::Vector2_v::zero;

				// 押し出し幅を更新したか？
				bool updatedExtrudeVec = false;
			
				// １つ目の頂点が相手のポリゴン内に入っていたら
				if (firstVertInOtherPoly)
				{
					// 自身の１つ目の頂点から辺の法線方向へ伸びた線分と相手のポリゴンで衝突判定をする
					auto firstVertNormalLineColResult = lineCollisionWithPolygon(firstVert + collideLineStartOffset, firstVert + collideLineVec, otherVertexs);

					// 交差点の数によって分岐
					if (firstVertNormalLineColResult.crossPosArray.size() == 1U)
					{
						// 押し出し幅を更新する
						maxExtrudeVec = firstVertNormalLineColResult.crossPosArray.at(0U) - firstVert;

						updatedExtrudeVec = true;
					}
					else if (firstVertNormalLineColResult.crossPosArray.size() > 1U)
					{
						for (const auto& crossPos : firstVertNormalLineColResult.crossPosArray)
						{
							auto tempExtrudeVec = crossPos - firstVert;

							// 押し出し幅の最大値を更新していたら値を更新する
							if (tempExtrudeVec.length() > maxExtrudeVec.length()) maxExtrudeVec = tempExtrudeVec;
						}
						updatedExtrudeVec = true;
					}
				}

				// ２つ目の頂点が相手のポリゴン内に入っていたら
				if (secondVertInOtherPoly)
				{
					// 自身の２つ目の頂点から辺の法線方向へ伸びた線分と相手のポリゴンで衝突判定をする
					auto secondVertNormalLineColResult = lineCollisionWithPolygon(secondVert + collideLineStartOffset, secondVert + collideLineVec, otherVertexs);

					// 交差点の数によって分岐
					if (secondVertNormalLineColResult.crossPosArray.size() == 1U)
					{
						auto tempExtrudeVec = secondVertNormalLineColResult.crossPosArray.at(0U) - secondVert;

						// 押し出し幅の最大値を更新していたら値を更新する
						if (tempExtrudeVec.length() > maxExtrudeVec.length()) maxExtrudeVec = tempExtrudeVec;

						updatedExtrudeVec = true;
					}
					else if (secondVertNormalLineColResult.crossPosArray.size() > 1U)
					{
						for (const auto& crossPos : secondVertNormalLineColResult.crossPosArray)
						{
							auto tempExtrudeVec = crossPos - secondVert;

							// 押し出し幅の最大値を更新していたら値を更新する
							if (tempExtrudeVec.length() > maxExtrudeVec.length()) maxExtrudeVec = tempExtrudeVec;
						}
						updatedExtrudeVec = true;
					}
				}
			
				// 辺ごとの最大押し出し距離の中で最小の押し出し距離を探す
				if (updatedExtrudeVec && maxExtrudeVec.length() < result.selfExtrudeVec.length()) result.selfExtrudeVec = maxExtrudeVec;
			}

			// 相手のポリゴンの頂点を巡回する
			for (size_t i = 0; i < otherVertexs.size(); i++)
			{
				const auto& firstVert = otherVertexs.at(i);
				const auto& secondVert = otherVertexs.at((i + 1U) % otherVertexs.size());
			
				// 相手のポリゴンの辺を構成する頂点が自身のポリゴン内に入っているか？
				bool firstVertInOtherPoly	= polygonCollisionWithPoint(selfVertexs, firstVert);
				bool secondVertInOtherPoly	= polygonCollisionWithPoint(selfVertexs, secondVert);

				// ２つの頂点がいずれも自身のポリゴン内に入って居なかったら次の要素へ
				if (!(firstVertInOtherPoly || secondVertInOtherPoly)) continue;

				// 相手のポリゴンの辺のベクトル
				auto otherPolyLineVec = secondVert - firstVert;
			
				// 相手のポリゴンの辺の逆法線を計算する
				auto otherLineInverseNormal = tktkMath::Vector2::perpendicular(otherPolyLineVec.normalized());
			
				// 線分の開始点のオフセット（めり込み時の補正）
				auto collideLineStartOffset = -otherLineInverseNormal * 8.0f;

				// 線分の終点に向かうベクトルを計算する
				auto lineEndPosVec = otherLineInverseNormal * maxCenterToVertDist * 2.0f;
			
				// ２つ頂点それぞれの押し出し幅の内最大の物を代入する変数
				auto maxExtrudeVec = tktkMath::Vector2_v::zero;
			
				// 押し出し幅を更新したか？
				bool updatedExtrudeVec = false;

				// １つ目の頂点が相手のポリゴン内に入っていたら
				if (firstVertInOtherPoly)
				{
					// 相手の１つ目の頂点から辺の法線方向へ伸びた線分と自身のポリゴンで衝突判定をする
					auto firstVertNormalLineColResult = lineCollisionWithPolygon(firstVert + collideLineStartOffset, firstVert + lineEndPosVec, selfVertexs);

					// 交差点の数によって分岐
					if (firstVertNormalLineColResult.crossPosArray.size() == 1U)
					{
						// 押し出し幅を更新する
						maxExtrudeVec = firstVertNormalLineColResult.crossPosArray.at(0U) - firstVert;

						updatedExtrudeVec = true;
					}
					else if (firstVertNormalLineColResult.crossPosArray.size() > 1U)
					{
						for (const auto& crossPos : firstVertNormalLineColResult.crossPosArray)
						{
							auto tempExtrudeVec = crossPos - firstVert;

							// 押し出し幅の最大値を更新していたら値を更新する
							if (tempExtrudeVec.length() > maxExtrudeVec.length()) maxExtrudeVec = tempExtrudeVec;
						}

						updatedExtrudeVec = true;
					}
				}

				// ２つ目の頂点が相手のポリゴン内に入っていたら
				if (secondVertInOtherPoly)
				{
					// 相手の２つ目の頂点から辺の法線方向へ伸びた線分と自身のポリゴンで衝突判定をする
					auto secondVertNormalLineColResult = lineCollisionWithPolygon(secondVert + collideLineStartOffset, secondVert + lineEndPosVec, selfVertexs);

					// 交差点の数によって分岐
					if (secondVertNormalLineColResult.crossPosArray.size() == 1U)
					{
						auto tempExtrudeVec = secondVertNormalLineColResult.crossPosArray.at(0U) - secondVert;

						// 押し出し幅の最大値を更新していたら値を更新する
						if (tempExtrudeVec.length() > maxExtrudeVec.length()) maxExtrudeVec = tempExtrudeVec;

						updatedExtrudeVec = true;
					}
					else if (secondVertNormalLineColResult.crossPosArray.size() > 1U)
					{
						for (const auto& crossPos : secondVertNormalLineColResult.crossPosArray)
						{
							auto tempExtrudeVec = crossPos - secondVert;

							// 押し出し幅の最大値を更新していたら値を更新する
							if (tempExtrudeVec.length() > maxExtrudeVec.length()) maxExtrudeVec = tempExtrudeVec;
						}

						updatedExtrudeVec = true;
					}
				}
				
				// 辺ごとの最大押し出し距離の中で最小の押し出し距離を探す
				if (updatedExtrudeVec && maxExtrudeVec.length() < result.selfExtrudeVec.length()) result.selfExtrudeVec = maxExtrudeVec * -1.0f;
			}

			// 押し出し幅が取得できなければ押し出さない結果を返す
			if (result.selfExtrudeVec == tktkMath::Vector2_v::positiveInfinity) result.selfExtrudeVec = tktkMath::Vector2_v::zero;
		}

		return result;
	}

	HitInfo2D CollisionSupport2D::circleCollisionWithPolygon(const tktkMath::Vector2& selfCenterPos, float selfRadius, const std::vector<tktkMath::Vector2>& otherVertexs)
	{
		float minDist = std::numeric_limits<float>::max();

		HitInfo2D result{};

		// 相手のポリゴンを構成する頂点を巡回する
		for (size_t vertIndex = 0; vertIndex < otherVertexs.size(); vertIndex++)
		{
			// ポリゴンの辺のベクトルを計算する
			auto firstVertexToSecond = otherVertexs.at((vertIndex + 1U) % otherVertexs.size()) - otherVertexs.at(vertIndex);

			// ポリゴンの辺の法線を計算する
			auto normal = -tktkMath::Vector2::perpendicular(firstVertexToSecond).normalized();

			// ポリゴンの辺の法線の逆方向に半径分だけ移動した座標
			auto circleMostFarSurface = (selfCenterPos - normal * selfRadius);

			// 辺の開始点から座標へのベクトルを計算する
			auto firstVertexToPoint = circleMostFarSurface - otherVertexs.at(vertIndex);

			// “辺の開始点から座標へのベクトル”と“ポリゴンの辺の法線”の内積
			float firstVertToPointNormalDot = tktkMath::Vector2::dot(firstVertexToPoint, normal);

			if (firstVertToPointNormalDot > 0.0f) return HitInfo2D();

			if (-firstVertToPointNormalDot < minDist)
			{
				minDist = -firstVertToPointNormalDot;
				result.selfExtrudeVec = -firstVertToPointNormalDot * normal;
			}
		}
		result.isHit = true;
		return result;
	}

	HitInfo2D CollisionSupport2D::polygonCollisionWithCircle(const std::vector<tktkMath::Vector2>& selfVertexs, const tktkMath::Vector2& otherCenterPos, float otherRadius)
	{
		auto result = circleCollisionWithPolygon(otherCenterPos, otherRadius, selfVertexs);
		result.selfExtrudeVec *= -1.0f;
		return result;
	}
}