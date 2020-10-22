#include "TktkCollision/3D/CollisionSupport3D.h"

#include "TktkMath/MathHelper.h"
#include "TktkCollision/2D/CollisionSupport2D.h"
#include "TktkCollision/3D/BoundingSphere.h"
#include "TktkCollision/3D/BoundingMesh.h"

namespace tktkCollision
{
	CollisionSupport3D::LinePolygonHitInfo CollisionSupport3D::lineCollisionWithPolygon(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const std::array<tktkMath::Vector3, 3U>& otherVertexs)
	{
		// 第一頂点から第二頂点へのベクトルを計算する
		auto firstVertexToSecond = otherVertexs.at(1U) - otherVertexs.at(0U);

		// 第一頂点から第三頂点へのベクトルを計算する
		auto firstVertexToThird = otherVertexs.at(2U) - otherVertexs.at(0U);

		// ポリゴンの法線等を計算する
		tktkMath::Vector3 normal = tktkMath::Vector3::cross(firstVertexToSecond, firstVertexToThird);

		//tktkMath::Vector3 tangent;
		//tktkMath::Vector3 binormal;
		//tktkMath::Vector3::orthoNormalize(&normal, &tangent, &binormal);
		//
		//// ポリゴンの接空間に変換するための行列を計算する
		//tktkMath::Matrix4 matTBN{
		//	tangent.x,	binormal.x,	normal.x,	0.0f,
		//	tangent.y,	binormal.y,	normal.y,	0.0f,
		//	tangent.z,	binormal.z,	normal.z,	0.0f,
		//	0.0f,		0.0f,		0.0f,		1.0f
		//};
		//
		//// ポリゴンの接空間に変換するための行列を計算する
		//tktkMath::Matrix4 matTBN{
		//	tangent.x,	tangent.y,	tangent.z,	0.0f,
		//	binormal.x, binormal.y, binormal.z, 0.0f,
		//	normal.x,	normal.y,	normal.z,	0.0f,
		//	0.0f,		0.0f,		0.0f,		1.0f
		//};
		//
		//// 接空間に座標変換した線の開始座標
		//auto tSpaceFirstPos = firstPos * matTBN;
		//
		//// 接空間に座標変換した線の終了座標
		//auto tSpaceSecondPos = secondPos * matTBN;
		//
		//// 接空間に座標変換したポリゴンの頂点
		//std::array<tktkMath::Vector3, 3U> tSpaceVertexs;
		//for (size_t i = 0U; i < otherVertexs.size(); i++)
		//{
		//	tSpaceVertexs.at(i) = otherVertexs.at(i) * matTBN;
		//}

		// 第一頂点から線分の開始点へのベクトルを計算する
		auto firstVertexToFirstPos = firstPos - otherVertexs.at(0U);

		// 第一頂点から線分の終了点へのベクトルを計算する
		auto firstVertexToSecondPos = secondPos - otherVertexs.at(0U);

		// “第一頂点から線分の開始点へのベクトル”と“ポリゴンの法線”の内積
		float firstVertToFirstPosNormalDot = tktkMath::Vector3::dot(firstVertexToFirstPos, normal);

		// “第一頂点から線分の終了点へのベクトル”と“ポリゴンの法線”の内積
		float firstVertToSecondPosNormalDot = tktkMath::Vector3::dot(firstVertexToSecondPos, normal);

		// 計算で使用する“内分比”を計算する 
		auto internalDivisionRatio = (normal * firstVertToFirstPosNormalDot).length() / ((normal * firstVertToFirstPosNormalDot).length() + (normal * firstVertToSecondPosNormalDot).length());

		// 第一頂点から線分の交差点へのベクトルを計算する
		auto firstVertexToCrossPos = (1 - internalDivisionRatio) * firstVertexToFirstPos + internalDivisionRatio * firstVertexToSecondPos;

		LinePolygonHitInfo result;

		// 線分の交差点を計算する
		result.crossPos = otherVertexs.at(0U) + firstVertexToCrossPos;

		// 線分がポリゴンの延長面上に接触していなければ処理を終える
		if (firstVertToFirstPosNormalDot * firstVertToSecondPosNormalDot > 0.0f)
		{
			result.crossPos = result.crossPos;// *matTBN.calculateInvert();
			return result;
		}

		for (size_t i = 0U; i < otherVertexs.size(); i++)
		{
			// ポリゴンの辺を構成する頂点２つ
			const auto& curVertPos = otherVertexs.at(i);
			const auto& nextVertPos = otherVertexs.at((i + 1U) % otherVertexs.size());

			// 現在の頂点から次の頂点へのベクトルを計算する
			auto curVertexToNext = nextVertPos - curVertPos;

			// 次の頂点から線分の交差点へのベクトルを計算する
			auto curVertexToCrossPos = result.crossPos - curVertPos;

			// 上２つのベクトルの外積を求める
			auto testNormal = tktkMath::Vector3::cross(curVertexToNext, curVertexToCrossPos).normalized();

			// 線分がポリゴンに接触していなければ処理を終える
			if (!(testNormal.length() < tktkMath::MathHelper::kEpsilon || tktkMath::Vector3::distance(normal, testNormal) < 1.0f)) // <- float計算誤差の関係上遊びを大きめに
			{
				result.crossPos = result.crossPos;// *matTBN.calculateInvert();
				return result;
			}
		}
		result.crossPos = result.crossPos;// *matTBN.calculateInvert();
		result.isHit = true;
		return result;
	}

	CollisionSupport3D::LineMeshHitInfo CollisionSupport3D::lineCollisionWithMesh(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const BoundingMesh& otherBody, const tktkMath::Matrix4& otherWorldMatrix)
	{
		// メッシュの頂点を計算する
		std::vector<tktkMath::Vector3> otherVertexs;
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : otherBody.getVertexs()) otherVertexs.push_back(vertex * otherWorldMatrix);

		float minDist = std::numeric_limits<float>::max();

		LineMeshHitInfo result;

		// ポリゴンごとに巡回
		for (size_t i = 0U; i < otherVertexs.size(); i += 3U)
		{
			// 配列外参照保険
			if (i + 2U >= otherVertexs.size()) break;

			// 判定するポリゴンの頂点を取得
			std::array<tktkMath::Vector3, 3U> otherPolygon{ otherVertexs.at(i), otherVertexs.at(i + 1U), otherVertexs.at(i + 2U) };

			// ポリゴンと線分で衝突判定を行う
			auto polygonHitInfo = lineCollisionWithPolygon(firstPos, secondPos, otherPolygon);

			// 線分の開始位置からポリゴンへの交差点へのベクトル
			auto firstPosToCrossPos = polygonHitInfo.crossPos - firstPos;

			// ポリゴンと線分が衝突していれば衝突結果を返す
			if (polygonHitInfo.isHit && firstPosToCrossPos.length() < minDist)
			{
				result.isHit		= true;
				result.crossPos		= polygonHitInfo.crossPos;
				result.otherVertexs = otherPolygon;
				minDist				= firstPosToCrossPos.length();
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
		// それぞれの衝突判定の座標を取得
		auto selfPos = selfWorldMatrix.calculateTranslation();
		auto otherPos = otherWorldMatrix.calculateTranslation();

		// メッシュの頂点を計算する
		std::vector<tktkMath::Vector3> selfVertexs;
		selfVertexs.reserve(selfBody.getVertexs().size());
		for (const auto& vertex : selfBody.getVertexs()) selfVertexs.push_back(vertex * selfWorldMatrix);
		std::vector<tktkMath::Vector3> otherVertexs;
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : otherBody.getVertexs()) otherVertexs.push_back(vertex * otherWorldMatrix);

		// 衝突中に片方の中心座標がもう片方の辺から最も離れた時の距離を計算する
		float mostFarDistance = 0.0f;
		for (const auto& vertex : selfVertexs)
		{
			float dist = tktkMath::Vector3::distance(selfWorldMatrix.calculateTranslation(), vertex);
			if (dist > mostFarDistance) mostFarDistance = dist;
		}
		for (const auto& vertex : otherVertexs)
		{
			float dist = tktkMath::Vector3::distance(otherWorldMatrix.calculateTranslation(), vertex);
			if (dist > mostFarDistance) mostFarDistance = dist;
		}

		// “自身の座標から相手の座標の線”と“相手のメッシュ”で衝突判定を行う
		// ※自身の座標が相手の衝突判定の中に入り込んでいる可能性を考慮して値が補正されている
		auto selfPosColOtherMeshResult = lineCollisionWithMesh(
			selfPos - (tktkMath::Vector3::normalize(otherPos - selfPos) * mostFarDistance),	// めり込み想定補正 
			otherPos,
			otherBody,
			otherWorldMatrix
		);

		// 直前に行った衝突判定の結果が“衝突していない”だったら相手のポリゴンが閉じていない為、判定不可
		if (!selfPosColOtherMeshResult.isHit) return HitInfo3D();


		//**************************************************
		// “相手の座標からの自身の座標の線”と“自身のメッシュ”で衝突判定を行う
		// ※相手の座標が自身の衝突判定の中に入り込んでいる可能性を考慮して値が補正されている
		auto otherPosColSelfMeshResult = lineCollisionWithMesh(
			otherPos - (tktkMath::Vector3::normalize(selfPos - otherPos) * mostFarDistance),	// めり込み想定補正 
			selfPos,
			selfBody,
			selfWorldMatrix
		);

		// 直前に行った衝突判定の結果が“衝突していない”だったら自身のポリゴンが閉じていない為、判定不可
		if (!otherPosColSelfMeshResult.isHit) return HitInfo3D();
		//**************************************************


		// 自身の座標から最も近い相手の衝突判定の面から外側に垂直に伸びたベクトル（長さは１）を計算する
		auto firstVertexToSecond = selfPosColOtherMeshResult.otherVertexs.at(1U) - selfPosColOtherMeshResult.otherVertexs.at(0U);
		auto firstVertexToThird = selfPosColOtherMeshResult.otherVertexs.at(2U) - selfPosColOtherMeshResult.otherVertexs.at(0U);
		tktkMath::Vector3 selfExtrudeDirection = tktkMath::Vector3::cross(firstVertexToSecond, firstVertexToThird);

		//// “相手の衝突判定の面上の点から面を基準として内側に垂直に伸びた線”と“自身のメッシュ”で衝突判定を行う
		//auto otherLineColSelfPolyResult = lineCollisionWithMesh(
		//	selfPosColOtherMeshResult.crossPos - (otherColliderPolyVerticalLineDirection * mostFarDistance),	// めり込み想定補正
		//	selfPosColOtherMeshResult.crossPos + (otherColliderPolyVerticalLineDirection * mostFarDistance),	// めり込み想定補正
		//	selfBody,
		//	selfWorldMatrix
		//);
		//
		//// 直前に行った衝突判定の結果が“衝突していない”だったら相手のポリゴンと衝突していない
		//if (!otherLineColSelfPolyResult.isHit) return HitInfo3D();

		HitInfo3D result{};

		// 衝突判定で使用する自身のポリゴンの頂点をループする
		for (const auto& selfVert : otherPosColSelfMeshResult.otherVertexs)
		{
			// 現在の自身の頂点から押し出し方向に向かったベクトルと相手のポリゴンで衝突判定を呼ぶ
			auto lineCrossCheckResult = lineCollisionWithPolygon(
				selfVert,
				selfVert + (selfExtrudeDirection * mostFarDistance),
				selfPosColOtherMeshResult.otherVertexs
			);

			// 直前に行った衝突判定が当たっている状態だったら
			if (lineCrossCheckResult.isHit)
			{
				// 今回の場合の押し出しベクトルを計算する
				auto tempPushVec = lineCrossCheckResult.crossPos - selfVert;

				// 押し出しベクトルの長さを更新していて、方向が押し出し方向と一致した場合、
				if (tempPushVec.length() > result.selfExtrudeVec.length() && tempPushVec.normalized().equals(selfExtrudeDirection))
				{
					// 新たな押し出しベクトルとして保持する
					result.selfExtrudeVec = tempPushVec;
				}
			}
		}

		// 衝突判定で使用する相手のポリゴンの頂点をループする
		for (const auto& otherVert : selfPosColOtherMeshResult.otherVertexs)
		{
			// 現在の相手の頂点から押し出し方向と“真逆”に向かったベクトルと自身のポリゴンで衝突判定を呼ぶ
			auto lineCrossCheckResult = lineCollisionWithPolygon(
				otherVert,
				otherVert - (selfExtrudeDirection * mostFarDistance),
				otherPosColSelfMeshResult.otherVertexs
			);

			// 直前に行った衝突判定が当たっている状態だったら
			if (lineCrossCheckResult.isHit)
			{
				// 今回の場合の押し出しベクトルを計算する
				auto tempPushVec = lineCrossCheckResult.crossPos - otherVert;

				// 押し出しベクトルの長さを更新していて、方向が押し出し方向の“真逆”と一致した場合、新たな押し出しベクトルとして保持する
				if (tempPushVec.length() > result.selfExtrudeVec.length() && tempPushVec.normalized().equals(-selfExtrudeDirection))
				{
					// 新たな押し出しベクトルとして保持する
					result.selfExtrudeVec = -tempPushVec;
				}
			}
		}

		//for (const auto& selfVertex : otherLineColSelfPolyResult.otherVertexs)
		//{
		//	// 自身の押し出しに使用する辺の一つ目の頂点を基準に押し出しをした時の押し出し座標を計算
		//	auto lineCrossCheckResult = lineCollisionWithPolygon(
		//		selfVertex,
		//		selfVertex - (otherColliderPolyVerticalLineDirection * mostFarDistance),
		//		selfPosColOtherMeshResult.otherVertexs
		//	);
		//
		//	// 自身の押し出しに使用する辺の一つ目の頂点を基準に押し出しをした時の押し出しベクトルを計算する
		//	auto tempPushVec = lineCrossCheckResult.crossPos - selfVertex;
		//
		//	// 自身を押し出す方向を表すベクトルが衝突相手のポリゴンの内側に向かっていなければ
		//	if (result.selfExtrudeVec.length() < tempPushVec.length() && !tempPushVec.normalized().equals(otherColliderPolyVerticalLineDirection))
		//	{
		//		// 自身の押し出しに使用する辺の一つ目の頂点を基準に押し出しをした時の押し出しベクトルを計算し代入する
		//		result.selfExtrudeVec = tempPushVec;
		//	}
		//}

		//for (const auto& otherVertex : selfPosColOtherMeshResult.otherVertexs)
		//{
		//	// 自身の押し出しに使用する辺の一つ目の頂点を基準に押し出しをした時の押し出し座標を計算
		//	auto lineCrossCheckResult = lineCollisionWithPolygon(
		//		otherVertex - (otherColliderPolyVerticalLineDirection * mostFarDistance),
		//		otherVertex + (otherColliderPolyVerticalLineDirection * mostFarDistance),
		//		otherPosColSelfMeshResult.otherVertexs
		//	);
		//
		//	// 自身の押し出しに使用する辺の一つ目の頂点を基準に押し出しをした時の押し出しベクトルを計算する
		//	auto tempPushVec = lineCrossCheckResult.crossPos - otherVertex;
		//
		//	// 自身を押し出す方向を表すベクトルが衝突相手のポリゴンの内側に向かっていなければ
		//	if (result.selfExtrudeVec.length() > tempPushVec.length() && !tempPushVec.normalized().equals(otherColliderPolyVerticalLineDirection))
		//	{
		//		// 自身の押し出しに使用する辺の一つ目の頂点を基準に押し出しをした時の押し出しベクトルを計算し代入する
		//		result.selfExtrudeVec = tempPushVec;
		//	}
		//}
		//
		//for (const auto& selfVertex : otherPosColSelfMeshResult.otherVertexs)
		//{
		//	// 自身の押し出しに使用する辺の一つ目の頂点を基準に押し出しをした時の押し出し座標を計算
		//	auto lineCrossCheckResult = lineCollisionWithPolygon(
		//		selfVertex - (otherColliderPolyVerticalLineDirection * mostFarDistance),
		//		selfVertex + (otherColliderPolyVerticalLineDirection * mostFarDistance),
		//		selfPosColOtherMeshResult.otherVertexs
		//	);
		//
		//	// 自身の押し出しに使用する辺の一つ目の頂点を基準に押し出しをした時の押し出しベクトルを計算する
		//	auto tempPushVec = lineCrossCheckResult.crossPos - selfVertex;
		//
		//	// 自身を押し出す方向を表すベクトルが衝突相手のポリゴンの内側に向かっていなければ
		//	if (result.selfExtrudeVec.length() > tempPushVec.length() && !tempPushVec.normalized().equals(otherColliderPolyVerticalLineDirection))
		//	{
		//		// 自身の押し出しに使用する辺の一つ目の頂点を基準に押し出しをした時の押し出しベクトルを計算し代入する
		//		result.selfExtrudeVec = tempPushVec;
		//	}
		//}

		// 押し出す距離がゼロでなければ衝突していると判断する
		result.isHit = (!result.selfExtrudeVec.equals(tktkMath::Vector3_v::zero));

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