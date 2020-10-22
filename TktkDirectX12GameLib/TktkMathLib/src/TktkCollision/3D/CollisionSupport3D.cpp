#include "TktkCollision/3D/CollisionSupport3D.h"

#include "TktkMath/MathHelper.h"
#include "TktkCollision/2D/CollisionSupport2D.h"
#include "TktkCollision/3D/BoundingSphere.h"
#include "TktkCollision/3D/BoundingMesh.h"

namespace tktkCollision
{
	CollisionSupport3D::LinePolygonHitInfo CollisionSupport3D::lineCollisionWithPolygon(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const std::array<tktkMath::Vector3, 3U>& otherVertexs)
	{
		// ��꒸�_�����񒸓_�ւ̃x�N�g�����v�Z����
		auto firstVertexToSecond = otherVertexs.at(1U) - otherVertexs.at(0U);

		// ��꒸�_�����O���_�ւ̃x�N�g�����v�Z����
		auto firstVertexToThird = otherVertexs.at(2U) - otherVertexs.at(0U);

		// �|���S���̖@�������v�Z����
		tktkMath::Vector3 normal = tktkMath::Vector3::cross(firstVertexToSecond, firstVertexToThird);

		//tktkMath::Vector3 tangent;
		//tktkMath::Vector3 binormal;
		//tktkMath::Vector3::orthoNormalize(&normal, &tangent, &binormal);
		//
		//// �|���S���̐ڋ�Ԃɕϊ����邽�߂̍s����v�Z����
		//tktkMath::Matrix4 matTBN{
		//	tangent.x,	binormal.x,	normal.x,	0.0f,
		//	tangent.y,	binormal.y,	normal.y,	0.0f,
		//	tangent.z,	binormal.z,	normal.z,	0.0f,
		//	0.0f,		0.0f,		0.0f,		1.0f
		//};
		//
		//// �|���S���̐ڋ�Ԃɕϊ����邽�߂̍s����v�Z����
		//tktkMath::Matrix4 matTBN{
		//	tangent.x,	tangent.y,	tangent.z,	0.0f,
		//	binormal.x, binormal.y, binormal.z, 0.0f,
		//	normal.x,	normal.y,	normal.z,	0.0f,
		//	0.0f,		0.0f,		0.0f,		1.0f
		//};
		//
		//// �ڋ�Ԃɍ��W�ϊ��������̊J�n���W
		//auto tSpaceFirstPos = firstPos * matTBN;
		//
		//// �ڋ�Ԃɍ��W�ϊ��������̏I�����W
		//auto tSpaceSecondPos = secondPos * matTBN;
		//
		//// �ڋ�Ԃɍ��W�ϊ������|���S���̒��_
		//std::array<tktkMath::Vector3, 3U> tSpaceVertexs;
		//for (size_t i = 0U; i < otherVertexs.size(); i++)
		//{
		//	tSpaceVertexs.at(i) = otherVertexs.at(i) * matTBN;
		//}

		// ��꒸�_��������̊J�n�_�ւ̃x�N�g�����v�Z����
		auto firstVertexToFirstPos = firstPos - otherVertexs.at(0U);

		// ��꒸�_��������̏I���_�ւ̃x�N�g�����v�Z����
		auto firstVertexToSecondPos = secondPos - otherVertexs.at(0U);

		// �g��꒸�_��������̊J�n�_�ւ̃x�N�g���h�Ɓg�|���S���̖@���h�̓���
		float firstVertToFirstPosNormalDot = tktkMath::Vector3::dot(firstVertexToFirstPos, normal);

		// �g��꒸�_��������̏I���_�ւ̃x�N�g���h�Ɓg�|���S���̖@���h�̓���
		float firstVertToSecondPosNormalDot = tktkMath::Vector3::dot(firstVertexToSecondPos, normal);

		// �v�Z�Ŏg�p����g������h���v�Z���� 
		auto internalDivisionRatio = (normal * firstVertToFirstPosNormalDot).length() / ((normal * firstVertToFirstPosNormalDot).length() + (normal * firstVertToSecondPosNormalDot).length());

		// ��꒸�_��������̌����_�ւ̃x�N�g�����v�Z����
		auto firstVertexToCrossPos = (1 - internalDivisionRatio) * firstVertexToFirstPos + internalDivisionRatio * firstVertexToSecondPos;

		LinePolygonHitInfo result;

		// �����̌����_���v�Z����
		result.crossPos = otherVertexs.at(0U) + firstVertexToCrossPos;

		// �������|���S���̉����ʏ�ɐڐG���Ă��Ȃ���Ώ������I����
		if (firstVertToFirstPosNormalDot * firstVertToSecondPosNormalDot > 0.0f)
		{
			result.crossPos = result.crossPos;// *matTBN.calculateInvert();
			return result;
		}

		for (size_t i = 0U; i < otherVertexs.size(); i++)
		{
			// �|���S���̕ӂ��\�����钸�_�Q��
			const auto& curVertPos = otherVertexs.at(i);
			const auto& nextVertPos = otherVertexs.at((i + 1U) % otherVertexs.size());

			// ���݂̒��_���玟�̒��_�ւ̃x�N�g�����v�Z����
			auto curVertexToNext = nextVertPos - curVertPos;

			// ���̒��_��������̌����_�ւ̃x�N�g�����v�Z����
			auto curVertexToCrossPos = result.crossPos - curVertPos;

			// ��Q�̃x�N�g���̊O�ς����߂�
			auto testNormal = tktkMath::Vector3::cross(curVertexToNext, curVertexToCrossPos).normalized();

			// �������|���S���ɐڐG���Ă��Ȃ���Ώ������I����
			if (!(testNormal.length() < tktkMath::MathHelper::kEpsilon || tktkMath::Vector3::distance(normal, testNormal) < 1.0f)) // <- float�v�Z�덷�̊֌W��V�т�傫�߂�
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
		// ���b�V���̒��_���v�Z����
		std::vector<tktkMath::Vector3> otherVertexs;
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : otherBody.getVertexs()) otherVertexs.push_back(vertex * otherWorldMatrix);

		float minDist = std::numeric_limits<float>::max();

		LineMeshHitInfo result;

		// �|���S�����Ƃɏ���
		for (size_t i = 0U; i < otherVertexs.size(); i += 3U)
		{
			// �z��O�Q�ƕی�
			if (i + 2U >= otherVertexs.size()) break;

			// ���肷��|���S���̒��_���擾
			std::array<tktkMath::Vector3, 3U> otherPolygon{ otherVertexs.at(i), otherVertexs.at(i + 1U), otherVertexs.at(i + 2U) };

			// �|���S���Ɛ����ŏՓ˔�����s��
			auto polygonHitInfo = lineCollisionWithPolygon(firstPos, secondPos, otherPolygon);

			// �����̊J�n�ʒu����|���S���ւ̌����_�ւ̃x�N�g��
			auto firstPosToCrossPos = polygonHitInfo.crossPos - firstPos;

			// �|���S���Ɛ������Փ˂��Ă���ΏՓˌ��ʂ�Ԃ�
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
		// ���ꂼ��̏Փ˔���̍��W���擾
		auto selfPos = selfWorldMatrix.calculateTranslation();
		auto otherPos = otherWorldMatrix.calculateTranslation();

		// ���b�V���̒��_���v�Z����
		std::vector<tktkMath::Vector3> selfVertexs;
		selfVertexs.reserve(selfBody.getVertexs().size());
		for (const auto& vertex : selfBody.getVertexs()) selfVertexs.push_back(vertex * selfWorldMatrix);
		std::vector<tktkMath::Vector3> otherVertexs;
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : otherBody.getVertexs()) otherVertexs.push_back(vertex * otherWorldMatrix);

		// �Փ˒��ɕЕ��̒��S���W�������Е��̕ӂ���ł����ꂽ���̋������v�Z����
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

		// �g���g�̍��W���瑊��̍��W�̐��h�Ɓg����̃��b�V���h�ŏՓ˔�����s��
		// �����g�̍��W������̏Փ˔���̒��ɓ��荞��ł���\�����l�����Ēl���␳����Ă���
		auto selfPosColOtherMeshResult = lineCollisionWithMesh(
			selfPos - (tktkMath::Vector3::normalize(otherPos - selfPos) * mostFarDistance),	// �߂荞�ݑz��␳ 
			otherPos,
			otherBody,
			otherWorldMatrix
		);

		// ���O�ɍs�����Փ˔���̌��ʂ��g�Փ˂��Ă��Ȃ��h�������瑊��̃|���S�������Ă��Ȃ��ׁA����s��
		if (!selfPosColOtherMeshResult.isHit) return HitInfo3D();


		//**************************************************
		// �g����̍��W����̎��g�̍��W�̐��h�Ɓg���g�̃��b�V���h�ŏՓ˔�����s��
		// ������̍��W�����g�̏Փ˔���̒��ɓ��荞��ł���\�����l�����Ēl���␳����Ă���
		auto otherPosColSelfMeshResult = lineCollisionWithMesh(
			otherPos - (tktkMath::Vector3::normalize(selfPos - otherPos) * mostFarDistance),	// �߂荞�ݑz��␳ 
			selfPos,
			selfBody,
			selfWorldMatrix
		);

		// ���O�ɍs�����Փ˔���̌��ʂ��g�Փ˂��Ă��Ȃ��h�������玩�g�̃|���S�������Ă��Ȃ��ׁA����s��
		if (!otherPosColSelfMeshResult.isHit) return HitInfo3D();
		//**************************************************


		// ���g�̍��W����ł��߂�����̏Փ˔���̖ʂ���O���ɐ����ɐL�т��x�N�g���i�����͂P�j���v�Z����
		auto firstVertexToSecond = selfPosColOtherMeshResult.otherVertexs.at(1U) - selfPosColOtherMeshResult.otherVertexs.at(0U);
		auto firstVertexToThird = selfPosColOtherMeshResult.otherVertexs.at(2U) - selfPosColOtherMeshResult.otherVertexs.at(0U);
		tktkMath::Vector3 selfExtrudeDirection = tktkMath::Vector3::cross(firstVertexToSecond, firstVertexToThird);

		//// �g����̏Փ˔���̖ʏ�̓_����ʂ���Ƃ��ē����ɐ����ɐL�т����h�Ɓg���g�̃��b�V���h�ŏՓ˔�����s��
		//auto otherLineColSelfPolyResult = lineCollisionWithMesh(
		//	selfPosColOtherMeshResult.crossPos - (otherColliderPolyVerticalLineDirection * mostFarDistance),	// �߂荞�ݑz��␳
		//	selfPosColOtherMeshResult.crossPos + (otherColliderPolyVerticalLineDirection * mostFarDistance),	// �߂荞�ݑz��␳
		//	selfBody,
		//	selfWorldMatrix
		//);
		//
		//// ���O�ɍs�����Փ˔���̌��ʂ��g�Փ˂��Ă��Ȃ��h�������瑊��̃|���S���ƏՓ˂��Ă��Ȃ�
		//if (!otherLineColSelfPolyResult.isHit) return HitInfo3D();

		HitInfo3D result{};

		// �Փ˔���Ŏg�p���鎩�g�̃|���S���̒��_�����[�v����
		for (const auto& selfVert : otherPosColSelfMeshResult.otherVertexs)
		{
			// ���݂̎��g�̒��_���牟���o�������Ɍ��������x�N�g���Ƒ���̃|���S���ŏՓ˔�����Ă�
			auto lineCrossCheckResult = lineCollisionWithPolygon(
				selfVert,
				selfVert + (selfExtrudeDirection * mostFarDistance),
				selfPosColOtherMeshResult.otherVertexs
			);

			// ���O�ɍs�����Փ˔��肪�������Ă����Ԃ�������
			if (lineCrossCheckResult.isHit)
			{
				// ����̏ꍇ�̉����o���x�N�g�����v�Z����
				auto tempPushVec = lineCrossCheckResult.crossPos - selfVert;

				// �����o���x�N�g���̒������X�V���Ă��āA�����������o�������ƈ�v�����ꍇ�A
				if (tempPushVec.length() > result.selfExtrudeVec.length() && tempPushVec.normalized().equals(selfExtrudeDirection))
				{
					// �V���ȉ����o���x�N�g���Ƃ��ĕێ�����
					result.selfExtrudeVec = tempPushVec;
				}
			}
		}

		// �Փ˔���Ŏg�p���鑊��̃|���S���̒��_�����[�v����
		for (const auto& otherVert : selfPosColOtherMeshResult.otherVertexs)
		{
			// ���݂̑���̒��_���牟���o�������Ɓg�^�t�h�Ɍ��������x�N�g���Ǝ��g�̃|���S���ŏՓ˔�����Ă�
			auto lineCrossCheckResult = lineCollisionWithPolygon(
				otherVert,
				otherVert - (selfExtrudeDirection * mostFarDistance),
				otherPosColSelfMeshResult.otherVertexs
			);

			// ���O�ɍs�����Փ˔��肪�������Ă����Ԃ�������
			if (lineCrossCheckResult.isHit)
			{
				// ����̏ꍇ�̉����o���x�N�g�����v�Z����
				auto tempPushVec = lineCrossCheckResult.crossPos - otherVert;

				// �����o���x�N�g���̒������X�V���Ă��āA�����������o�������́g�^�t�h�ƈ�v�����ꍇ�A�V���ȉ����o���x�N�g���Ƃ��ĕێ�����
				if (tempPushVec.length() > result.selfExtrudeVec.length() && tempPushVec.normalized().equals(-selfExtrudeDirection))
				{
					// �V���ȉ����o���x�N�g���Ƃ��ĕێ�����
					result.selfExtrudeVec = -tempPushVec;
				}
			}
		}

		//for (const auto& selfVertex : otherLineColSelfPolyResult.otherVertexs)
		//{
		//	// ���g�̉����o���Ɏg�p����ӂ̈�ڂ̒��_����ɉ����o�����������̉����o�����W���v�Z
		//	auto lineCrossCheckResult = lineCollisionWithPolygon(
		//		selfVertex,
		//		selfVertex - (otherColliderPolyVerticalLineDirection * mostFarDistance),
		//		selfPosColOtherMeshResult.otherVertexs
		//	);
		//
		//	// ���g�̉����o���Ɏg�p����ӂ̈�ڂ̒��_����ɉ����o�����������̉����o���x�N�g�����v�Z����
		//	auto tempPushVec = lineCrossCheckResult.crossPos - selfVertex;
		//
		//	// ���g�������o��������\���x�N�g�����Փˑ���̃|���S���̓����Ɍ������Ă��Ȃ����
		//	if (result.selfExtrudeVec.length() < tempPushVec.length() && !tempPushVec.normalized().equals(otherColliderPolyVerticalLineDirection))
		//	{
		//		// ���g�̉����o���Ɏg�p����ӂ̈�ڂ̒��_����ɉ����o�����������̉����o���x�N�g�����v�Z���������
		//		result.selfExtrudeVec = tempPushVec;
		//	}
		//}

		//for (const auto& otherVertex : selfPosColOtherMeshResult.otherVertexs)
		//{
		//	// ���g�̉����o���Ɏg�p����ӂ̈�ڂ̒��_����ɉ����o�����������̉����o�����W���v�Z
		//	auto lineCrossCheckResult = lineCollisionWithPolygon(
		//		otherVertex - (otherColliderPolyVerticalLineDirection * mostFarDistance),
		//		otherVertex + (otherColliderPolyVerticalLineDirection * mostFarDistance),
		//		otherPosColSelfMeshResult.otherVertexs
		//	);
		//
		//	// ���g�̉����o���Ɏg�p����ӂ̈�ڂ̒��_����ɉ����o�����������̉����o���x�N�g�����v�Z����
		//	auto tempPushVec = lineCrossCheckResult.crossPos - otherVertex;
		//
		//	// ���g�������o��������\���x�N�g�����Փˑ���̃|���S���̓����Ɍ������Ă��Ȃ����
		//	if (result.selfExtrudeVec.length() > tempPushVec.length() && !tempPushVec.normalized().equals(otherColliderPolyVerticalLineDirection))
		//	{
		//		// ���g�̉����o���Ɏg�p����ӂ̈�ڂ̒��_����ɉ����o�����������̉����o���x�N�g�����v�Z���������
		//		result.selfExtrudeVec = tempPushVec;
		//	}
		//}
		//
		//for (const auto& selfVertex : otherPosColSelfMeshResult.otherVertexs)
		//{
		//	// ���g�̉����o���Ɏg�p����ӂ̈�ڂ̒��_����ɉ����o�����������̉����o�����W���v�Z
		//	auto lineCrossCheckResult = lineCollisionWithPolygon(
		//		selfVertex - (otherColliderPolyVerticalLineDirection * mostFarDistance),
		//		selfVertex + (otherColliderPolyVerticalLineDirection * mostFarDistance),
		//		selfPosColOtherMeshResult.otherVertexs
		//	);
		//
		//	// ���g�̉����o���Ɏg�p����ӂ̈�ڂ̒��_����ɉ����o�����������̉����o���x�N�g�����v�Z����
		//	auto tempPushVec = lineCrossCheckResult.crossPos - selfVertex;
		//
		//	// ���g�������o��������\���x�N�g�����Փˑ���̃|���S���̓����Ɍ������Ă��Ȃ����
		//	if (result.selfExtrudeVec.length() > tempPushVec.length() && !tempPushVec.normalized().equals(otherColliderPolyVerticalLineDirection))
		//	{
		//		// ���g�̉����o���Ɏg�p����ӂ̈�ڂ̒��_����ɉ����o�����������̉����o���x�N�g�����v�Z���������
		//		result.selfExtrudeVec = tempPushVec;
		//	}
		//}

		// �����o���������[���łȂ���ΏՓ˂��Ă���Ɣ��f����
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