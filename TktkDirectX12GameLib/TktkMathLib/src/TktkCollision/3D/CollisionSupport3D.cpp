#include "TktkCollision/3D/CollisionSupport3D.h"

#include "TktkMath/MathHelper.h"
#include "TktkCollision/2D/CollisionSupport2D.h"
#include "TktkCollision/3D/BoundingSphere.h"
#include "TktkCollision/3D/BoundingMesh.h"

namespace tktkCollision
{
	CollisionSupport3D::LinePolygonHitInfo CollisionSupport3D::lineCollisionWithPolygon(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const std::vector<tktkMath::Vector3>& otherPolygon)
	{
		// 相手のポリゴンの頂点が３つより少ない場合、判定不可
		if (otherPolygon.size() < 3U) return LinePolygonHitInfo();

		// 第一頂点から第二頂点へのベクトルを計算する
		auto firstVertexToSecond = otherPolygon.at(1U) - otherPolygon.at(0U);

		// 第一頂点から第三頂点へのベクトルを計算する
		auto firstVertexToThird = otherPolygon.at(2U) - otherPolygon.at(0U);

		// ポリゴンの法線等を計算する
		tktkMath::Vector3 normal = tktkMath::Vector3::cross(firstVertexToSecond, firstVertexToThird).normalized();

		// 第一頂点から線分の開始点へのベクトルを計算する
		auto firstVertexToFirstPos = firstPos - otherPolygon.at(0U);

		// 第一頂点から線分の終了点へのベクトルを計算する
		auto firstVertexToSecondPos = secondPos - otherPolygon.at(0U);

		// “第一頂点から線分の開始点へのベクトル”と“ポリゴンの法線”の内積
		float firstVertToFirstPosNormalDot = tktkMath::Vector3::dot(firstVertexToFirstPos, normal);

		// “第一頂点から線分の終了点へのベクトル”と“ポリゴンの法線”の内積
		float firstVertToSecondPosNormalDot = tktkMath::Vector3::dot(firstVertexToSecondPos, normal);

		// 線分がポリゴンの延長面上に接触していなければ処理を終える
		if (firstVertToFirstPosNormalDot * firstVertToSecondPosNormalDot > 0.0f) return LinePolygonHitInfo();

		LinePolygonHitInfo result;

		// “ポリゴンの延長線上に”衝突しているフラグを立てる
		result.isExtensionPolyHit = true;

		// もしも“線分”が完全に“ポリゴンの延長面”上に存在していたら
		if (firstVertToFirstPosNormalDot == 0.0f && firstVertToSecondPosNormalDot == 0.0f)
		{
			// 線分とポリゴンの交差点は“線分の中心点”
			result.hitPos = firstPos + (secondPos - firstPos) / 2;
		}
		// もしも“線分の開始点”のみが“ポリゴンの延長面”上に存在していたら
		else if (firstVertToFirstPosNormalDot == 0.0f)
		{
			// 線分とポリゴンの交差点は“線分の開始点”
			result.hitPos = firstPos;
		}
		// もしも“線分の終了点”のみが“ポリゴンの延長面”上に存在していたら
		else if (firstVertToSecondPosNormalDot == 0.0f)
		{
			// 線分とポリゴンの交差点は“線分の終了点”
			result.hitPos = secondPos;
		}
		// もしも“線分”が“ポリゴンの延長面”と交差していたら
		else
		{
			// “線分”と“ポリゴンの延長面”が交差しているフラグを立てる
			result.isExtensionPolyCross = true;

			// 計算で使用する“内分比”を計算する 
			auto internalDivisionRatio = (normal * firstVertToFirstPosNormalDot).length() / ((normal * firstVertToFirstPosNormalDot).length() + (normal * firstVertToSecondPosNormalDot).length());

			// 第一頂点から線分の交差点へのベクトルを計算する
			auto firstVertexToCrossPos = (1 - internalDivisionRatio) * firstVertexToFirstPos + internalDivisionRatio * firstVertexToSecondPos;

			// 線分の交差点を計算する
			result.hitPos = otherPolygon.at(0U) + firstVertexToCrossPos;
		}

		for (size_t i = 0U; i < otherPolygon.size(); i++)
		{
			// ポリゴンの辺を構成する頂点２つ
			const auto& curVertPos = otherPolygon.at(i);
			const auto& nextVertPos = otherPolygon.at((i + 1U) % otherPolygon.size());

			// 現在の頂点から次の頂点へのベクトルを計算する
			auto curVertexToNext = nextVertPos - curVertPos;

			// 現在の頂点から線分の交差点へのベクトルを計算する
			auto curVertexToCrossPos = result.hitPos - curVertPos;

			// “次の頂点から線分の交差点へのベクトル”がゼロベクトルか、上の２つのベクトルが真逆の方向だったらポリゴンの辺上に線分が衝突している
			if (curVertexToCrossPos.length() < tktkMath::MathHelper::kEpsilon ||
				(curVertexToNext.normalized() - curVertexToCrossPos.normalized()).length() < tktkMath::MathHelper::kEpsilon)
			{
				result.isPolyEdgeHit = true;
			}

			// 上２つのベクトルの外積を求める
			auto testNormal = tktkMath::Vector3::cross(curVertexToNext, curVertexToCrossPos).normalized();

			// 外積がゼロベクトルだった場合、線分の交差点はポリゴンの辺上に存在する
			if (testNormal == tktkMath::Vector3_v::zero) continue;

			// 外積がポリゴンの法線と一致した場合、線分の交差点はポリゴンの中に存在する
			if (tktkMath::Vector3::distance(normal, testNormal) < tktkMath::MathHelper::kEpsilon) continue;

			// 線分がポリゴンに接触していなければ処理を終える
			return result;

			//if (!(tktkMath::Vector3::distance(normal, testNormal) < tktkMath::MathHelper::kEpsilon)) return result; //testNormal.length() < tktkMath::MathHelper::kEpsilon || 
		}
		// “完全に”衝突しているフラグを立てる
		result.isHit = true;
		return result;
	}

	bool CollisionSupport3D::pointCollisionWithMesh(const tktkMath::Vector3& point, const BoundingMesh& otherBody, const tktkMath::Matrix4& otherWorldMatrix)
	{
		// メッシュの頂点を計算する
		std::vector<std::vector<tktkMath::Vector3>> otherMesh;
		otherMesh.resize(otherBody.getVertexs().size());
		for (size_t i = 0U; i < otherBody.getVertexs().size(); i++)
		{
			otherMesh.at(i).reserve(otherBody.getVertexs().at(i).size());

			for (size_t j = 0U; j < otherBody.getVertexs().at(i).size(); j++)
			{
				otherMesh.at(i).push_back(otherBody.getVertexs().at(i).at(j) * otherWorldMatrix);
			}
		}

		// 相手のポリゴンを巡回する
		for (const auto& otherPoly : otherMesh)
		{
			// 相手のポリゴンの頂点が３つより少ない場合、判定不可なので次のポリゴンの判定へ
			if (otherPoly.size() < 3U) continue;

			// 第一頂点から第二頂点へのベクトルを計算する
			auto firstVertexToSecond = otherPoly.at(1U) - otherPoly.at(0U);

			// 第一頂点から第三頂点へのベクトルを計算する
			auto firstVertexToThird = otherPoly.at(2U) - otherPoly.at(0U);

			// ポリゴンの法線等を計算する
			tktkMath::Vector3 normal = tktkMath::Vector3::cross(firstVertexToSecond, firstVertexToThird).normalized();

			// 第一頂点から点へのベクトルを計算する
			auto firstVertexToPoint = point - otherPoly.at(0U);

			// “第一頂点から点へのベクトル”と“ポリゴンの法線”の内積
			float firstVertToPointNormalDot = tktkMath::Vector3::dot(firstVertexToPoint, normal);

			if (firstVertToPointNormalDot > 0.0f) return false;
		}
		return true;
	}

	CollisionSupport3D::LineMeshHitInfo CollisionSupport3D::lineCollisionWithMesh(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const BoundingMesh& otherBody, const tktkMath::Matrix4& otherWorldMatrix)
	{
		// メッシュの頂点を計算する
		std::vector<std::vector<tktkMath::Vector3>> otherMesh;
		otherMesh.resize(otherBody.getVertexs().size());
		for (size_t i = 0U; i < otherBody.getVertexs().size(); i++)
		{
			otherMesh.at(i).reserve(otherBody.getVertexs().at(i).size());

			for (size_t j = 0U; j < otherBody.getVertexs().at(i).size(); j++)
			{
				otherMesh.at(i).push_back(otherBody.getVertexs().at(i).at(j) * otherWorldMatrix);
			}
		}

		LineMeshHitInfo result;

		// 相手のポリゴンを巡回する
		for (const auto& otherPoly : otherMesh)
		{
			// 相手のポリゴンの頂点が３つより少ない場合、判定不可なので次のポリゴンの判定へ
			if (otherPoly.size() < 3U) continue;

			// ポリゴンと線分で衝突判定を行う
			auto polygonHitInfo = lineCollisionWithPolygon(firstPos, secondPos, otherPoly);

			// ポリゴンと線分が衝突していれば衝突結果を返す
			if (polygonHitInfo.isHit)
			{
				result.isHit = true;
				result.linePolyCrossDataArray.push_back({ polygonHitInfo.isExtensionPolyCross, polygonHitInfo.isPolyEdgeHit, polygonHitInfo.hitPos, otherPoly });
			}
		}
		return result;
	}

	HitInfo3D CollisionSupport3D::polygonCollisionWithMesh(const std::vector<tktkMath::Vector3>& polygon, const BoundingMesh& otherBody, const tktkMath::Matrix4& otherWorldMatrix)
	{
		// 自身のポリゴンの頂点が３つより少ない場合、判定不可
		if (polygon.size() < 3U) return HitInfo3D();

		// メッシュの頂点を計算する
		std::vector<std::vector<tktkMath::Vector3>> otherMesh;
		otherMesh.resize(otherBody.getVertexs().size());
		for (size_t i = 0U; i < otherBody.getVertexs().size(); i++)
		{
			otherMesh.at(i).reserve(otherBody.getVertexs().at(i).size());

			for (size_t j = 0U; j < otherBody.getVertexs().at(i).size(); j++)
			{
				otherMesh.at(i).push_back(otherBody.getVertexs().at(i).at(j) * otherWorldMatrix);
			}
		}

		// 自身のポリゴンの法線を計算する
		tktkMath::Vector3 polygonNormal = tktkMath::Vector3::cross(polygon.at(1U) - polygon.at(0U), polygon.at(2U) - polygon.at(0)).normalized();

		HitInfo3D result{};

		// 自身のポリゴンから最も遠い相手の頂点までの距離
		float mostFarOtherVertLen = 0.0f;

		// 自身のポリゴンから最も遠い“押し出しに使用できる”相手の頂点までの距離
		float mostFarCollideUseOtherVertLen = -1.0f;

		// 相手のポリゴンを巡回する
		for (const auto& otherPoly : otherMesh)
		{
			// 相手のポリゴンを構成する頂点を巡回する
			for (const auto& otherVert : otherPoly)
			{
				// 相手の頂点を開始点とする自身のポリゴンの反転法線ベクトルの長さ
				auto otherVertToExtensionPolyCrossVecLen = tktkMath::Vector3::dot(polygon.at(0U) - otherVert, polygonNormal);

				// “相手の頂点を開始点とする自身のポリゴンの反転法線ベクトルの長さ”の絶対値
				float absOtherVertToExtensionPolyCrossVecLen = std::abs(otherVertToExtensionPolyCrossVecLen);

				// “自身のポリゴンから最も遠い相手の頂点までの距離”の遠さを更新していたら、基準値を更新する
				if (absOtherVertToExtensionPolyCrossVecLen > mostFarOtherVertLen) mostFarOtherVertLen = absOtherVertToExtensionPolyCrossVecLen;

				// 法線ベクトルの長さが０より小さい（自身のポリゴンと衝突していない）場合は次の頂点に
				if (otherVertToExtensionPolyCrossVecLen < 0.0f) continue;

				// “相手の頂点を開始点とする自身のポリゴンの反転法線ベクトル”と“自身のポリゴンの面”の交差点
				auto crossPos = otherVert + (polygonNormal * otherVertToExtensionPolyCrossVecLen);

				// “自身のポリゴン”に“相手の頂点を開始点とする自身のポリゴンの反転法線ベクトル”が衝突しているか？
				bool isHitPolygon = true;

				// 自身のポリゴンを巡回する
				for (size_t i = 0U; i < polygon.size(); i++)
				{
					// 自身のポリゴンの辺を構成する頂点２つ
					const auto& curVertPos	= polygon.at(i);
					const auto& nextVertPos = polygon.at((i + 1U) % polygon.size());

					// 現在の頂点から次の頂点へのベクトルを計算する
					auto curVertexToNext = nextVertPos - curVertPos;

					// 現在の頂点から線分の交差点へのベクトルを計算する
					auto curVertexToCrossPos = crossPos - curVertPos;

					if (curVertexToCrossPos.y < tktkMath::MathHelper::kEpsilon) curVertexToCrossPos.y = 0.0f;

					// 上２つのベクトルの外積を求める
					auto testNormal = tktkMath::Vector3::cross(curVertexToNext.normalized(), curVertexToCrossPos.normalized()).normalized();

					// 外積がゼロベクトルだった場合、線分の交差点は自身のポリゴンの辺上に存在する
					if (testNormal == tktkMath::Vector3_v::zero) continue;

					// 外積が自身のポリゴンの法線と一致した場合、線分の交差点はポリゴンの中に存在する
					if (tktkMath::Vector3::distance(polygonNormal, testNormal) < tktkMath::MathHelper::kEpsilon) continue;

					// 線分がポリゴンに接触していない
					isHitPolygon = false;
				}

				// “自身のポリゴン”に“相手の頂点を開始点とする自身のポリゴンの反転法線ベクトル”が衝突していない場合は次の頂点に
				if (!isHitPolygon) continue;

				// もし、“相手の頂点を開始点とする自身のポリゴンの反転法線ベクトルの長さ”の絶対値の大きさを更新していたら
				if (otherVertToExtensionPolyCrossVecLen > mostFarCollideUseOtherVertLen)
				{
					// 衝突フラグを立てる
					result.isHit = true;

					// 基準値を更新
					mostFarCollideUseOtherVertLen = otherVertToExtensionPolyCrossVecLen;

					// 自身の押し出し方向を更新
					result.selfExtrudeVec = polygonNormal * otherVertToExtensionPolyCrossVecLen;
				}
			}
		}

		// 自身のポリゴンを構成する頂点を巡回する
		for (const auto& selfVert : polygon)
		{
			// “自身のポリゴンの頂点から自身のポリゴンの反転法線方向に延びた線分”と“相手のメッシュ”で衝突判定を行う
			auto lineCrossResult = lineCollisionWithMesh(selfVert, selfVert - (polygonNormal * mostFarOtherVertLen), otherBody, otherWorldMatrix);

			// “自身のポリゴンの頂点から自身のポリゴンの反転法線方向に延びた線分”と“相手のメッシュ”が衝突していなかったら次の頂点へ
			if (!lineCrossResult.isHit) continue;

			// “自身のポリゴンの頂点から自身のポリゴンの法線方向に延びた線分”と“相手のメッシュ”の衝突点を巡回する
			for (const auto& linePolyCrossData : lineCrossResult.linePolyCrossDataArray)
			{
				// “自身のポリゴンの頂点から自身のポリゴンの法線方向に延びた線分と相手のメッシュの衝突点”から“自身のポリゴンの頂点”へのベクトル
				auto hitPosToSelfVert = selfVert - linePolyCrossData.hitPos;

				// もし、“相手の頂点を開始点とする自身のポリゴンの反転法線ベクトルの長さ”の絶対値の大きさを更新していたら
				if (hitPosToSelfVert.length() > mostFarCollideUseOtherVertLen)
				{
					// 衝突フラグを立てる
					result.isHit = true;

					// 基準値を更新
					mostFarCollideUseOtherVertLen = hitPosToSelfVert.length();

					// 自身の押し出し方向を更新
					result.selfExtrudeVec = hitPosToSelfVert;
				}
			}
		}

		return result;
	}

	HitInfo3D CollisionSupport3D::sphereCollisionWithSphere(const BoundingSphere& selfBody, const BoundingSphere& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix)
	{
		return HitInfo3D();
	}

	HitInfo3D CollisionSupport3D::meshCollisionWithMesh(const BoundingMesh& selfBody, const BoundingMesh& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix)
	{
		// メッシュの頂点
		std::vector<std::vector<tktkMath::Vector3>> selfVertexs;
		std::vector<std::vector<tktkMath::Vector3>> otherVertexs;

		// メッシュの頂点を計算する
		selfVertexs.resize(selfBody.getVertexs().size());
		for (size_t i = 0U; i < selfBody.getVertexs().size(); i++)
		{
			selfVertexs.at(i).reserve(selfBody.getVertexs().at(i).size());

			for (size_t j = 0U; j < selfBody.getVertexs().at(i).size(); j++)
			{
				selfVertexs.at(i).push_back(selfBody.getVertexs().at(i).at(j) * selfWorldMatrix);
			}
		}
		otherVertexs.resize(otherBody.getVertexs().size());
		for (size_t i = 0U; i < otherBody.getVertexs().size(); i++)
		{
			otherVertexs.at(i).reserve(otherBody.getVertexs().at(i).size());

			for (size_t j = 0U; j < otherBody.getVertexs().at(i).size(); j++)
			{
				otherVertexs.at(i).push_back(otherBody.getVertexs().at(i).at(j) * otherWorldMatrix);
			}
		}

		//**************************************************
		// 衝突相手のポリゴン内に接触している辺があるかどうかのフラグ

		HitInfo3D result{};
		result.selfExtrudeVec = { std::numeric_limits<float>::max() / 2.0f };

		// 相手のポリゴンを巡回する
		for (const auto& otherPoly : otherVertexs)
		{
			// 相手のポリゴンの頂点が３つより少ない場合、判定不可なので次のポリゴンの判定へ
			if (otherPoly.size() < 3U) continue;

			// 相手のポリゴンの中心座標を計算する
			auto otherPolyCenterPos = tktkMath::Vector3_v::zero;
			for (const auto& otherVert : otherPoly) otherPolyCenterPos += otherVert;
			otherPolyCenterPos /= otherPoly.size();

			// 相手のポリゴンの中心座標が自身のメッシュ内にあるか判定する
			bool findInclusionLine = pointCollisionWithMesh(otherPolyCenterPos, selfBody, selfWorldMatrix);

			// 相手のポリゴンを構成する頂点を巡回する
			for (size_t vertIndex = 0; vertIndex < otherPoly.size(); vertIndex++)
			{
				// 自身のポリゴンの辺と相手のメッシュで衝突判定を行う
				auto lineCollisionMeshResult = lineCollisionWithMesh(otherPoly.at(vertIndex), otherPoly.at((vertIndex + 1U) % otherPoly.size()), selfBody, selfWorldMatrix);

				// もし“自身のポリゴンの辺と相手のメッシュ”が衝突していたら
				if (lineCollisionMeshResult.isHit) findInclusionLine = true;
			}

			if (!findInclusionLine) continue;

			result.isHit = true;

			auto polyHitResult = polygonCollisionWithMesh(otherPoly, selfBody, selfWorldMatrix);

			if (!polyHitResult.isHit) continue;

			// 押し出し方向の距離の短さを更新していたら
			if (polyHitResult.selfExtrudeVec.length() < result.selfExtrudeVec.length())
			{
				// 押し出し方向を更新する
				result.selfExtrudeVec = polyHitResult.selfExtrudeVec;
			}
		}

		// 自身のポリゴンを巡回する
		for (const auto& selfPoly : selfVertexs)
		{
			// 自身のポリゴンの頂点が３つより少ない場合、判定不可なので次のポリゴンの判定へ
			if (selfPoly.size() < 3U) continue;

			// 自身のポリゴンの中心座標を計算する
			auto selfPolyCenterPos = tktkMath::Vector3_v::zero;
			for (const auto& selfVert : selfPoly) selfPolyCenterPos += selfVert;
			selfPolyCenterPos /= selfPoly.size();

			// 自身のポリゴンの中心座標が相手のメッシュ内にあるか判定する
			bool findInclusionLine = pointCollisionWithMesh(selfPolyCenterPos, otherBody, otherWorldMatrix);

			// 自身のポリゴンを構成する頂点を巡回する
			for (size_t vertIndex = 0; vertIndex < selfPoly.size(); vertIndex++)
			{
				// 自身のポリゴンの辺と相手のメッシュで衝突判定を行う
				auto lineCollisionMeshResult = lineCollisionWithMesh(selfPoly.at(vertIndex), selfPoly.at((vertIndex + 1U) % selfPoly.size()), otherBody, otherWorldMatrix);

				// もし“自身のポリゴンの辺と相手のメッシュ”が衝突していたら
				if (lineCollisionMeshResult.isHit) findInclusionLine = true;
			}

			if (!findInclusionLine) continue;

			result.isHit = true;

			auto polyHitResult = polygonCollisionWithMesh(selfPoly, otherBody, otherWorldMatrix);

			if (!polyHitResult.isHit) continue;

			// 押し出し方向の距離の短さを更新していたら
			if (polyHitResult.selfExtrudeVec.length() < result.selfExtrudeVec.length())
			{
				// 押し出し方向を更新する
				result.selfExtrudeVec = -polyHitResult.selfExtrudeVec;
			}
		}

		if (result.selfExtrudeVec == tktkMath::Vector3{ std::numeric_limits<float>::max() / 2.0f }) result.selfExtrudeVec = tktkMath::Vector3_v::zero;

		return result;
	}

	HitInfo3D CollisionSupport3D::sphereCollisionWithMesh(const BoundingSphere& selfBody, const BoundingMesh& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix)
	{
		return HitInfo3D();
	}

	HitInfo3D CollisionSupport3D::meshCollisionWithSphere(const BoundingMesh& selfBody, const BoundingSphere& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix)
	{
		return HitInfo3D();
	}
}