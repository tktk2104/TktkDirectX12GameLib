#include "TktkCollision/2D/CollisionSupport2D.h"

#include <vector>
#include <TktkMath/MathHelper.h>
#include "TktkCollision/2D/BoundingCircle.h"
#include "TktkCollision/2D/BoundingPolygon2D.h"

namespace tktkCollision
{
	bool CollisionSupport2D::collidePolygonToPolygon(const BoundingPolygon2D& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix)
	{
		// ���ꂼ��̓񎟌��|���S���̒��_���v�Z����
		std::vector<tktkMath::Vector2> selfVertexs;
		std::vector<tktkMath::Vector2> otherVertexs;
		selfVertexs.reserve(selfBody.getVertexs().size());
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : selfBody.getVertexs())	selfVertexs.push_back(vertex * selfWorldMatrix);
		for (const auto& vertex : otherBody.getVertexs())	otherVertexs.push_back(vertex * otherWorldMatrix);

		// �Փ˔���Ŏg�p���钸�_�̍ŏ��A�ő�l���v�Z����
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

		// ���ꂼ��̓񎟌��|���S���̒��S���W���v�Z����
		tktkMath::Vector2 selfCenterPos		= selfMinPos + (selfMaxPos - selfMinPos) / 2;
		tktkMath::Vector2 otherCenterPos	= otherMinPos + (otherMaxPos - otherMinPos) / 2;

		// ���ꂼ��̓񎟌��|���S���̒��S���W������̓񎟌��|���S�����ɓ����Ă�����Փ˂��Ă���
		if (collidePolygonToPoint(selfBody, otherCenterPos, selfWorldMatrix))	return true;
		if (collidePolygonToPoint(otherBody, selfCenterPos, otherWorldMatrix))	return true;

		// ���ꂼ��̓񎟌��|���S���̒��_������̓񎟌��|���S�����ɓ����Ă�����Փ˂��Ă���
		for (const auto& vertex : otherVertexs) if (collidePolygonToPoint(selfBody, vertex, selfWorldMatrix))	return true;
		for (const auto& vertex : selfVertexs)	if (collidePolygonToPoint(otherBody, vertex, otherWorldMatrix)) return true;

		return false;
	}

	bool CollisionSupport2D::collideCircleToPolygon(const BoundingCircle& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix)
	{
		// �~�̒��S���W���v�Z����
		tktkMath::Vector2 selfCenterPos = selfBody.getCenterPosition() * selfWorldMatrix;

		// �~�̔��a�����߂�
		float selfRadius = (tktkMath::Vector2(selfBody.getRadius()) * selfWorldMatrix).x;

		// �񎟌��|���S���̒��_�̍ŏ��A�ő�l���v�Z����
		tktkMath::Vector2 otherMinPos = tktkMath::Vector2_v::positiveInfinity;
		tktkMath::Vector2 otherMaxPos = tktkMath::Vector2_v::negativeInfinity;
		for (const auto& vertex : otherBody.getVertexs())
		{
			if (otherMinPos.x > vertex.x) otherMinPos.x = vertex.x;
			if (otherMaxPos.x < vertex.x) otherMaxPos.x = vertex.x;
			if (otherMinPos.y > vertex.y) otherMinPos.y = vertex.y;
			if (otherMaxPos.y < vertex.y) otherMaxPos.y = vertex.y;
		}

		// �񎟌��|���S���̒��S���W���v�Z����
		tktkMath::Vector2 otherCenterPos = otherMinPos + (otherMaxPos - otherMinPos) / 2;

		// �񎟌��|���S���̒��_�����擾���A�~�̔��a�̒��������g�傷��
		std::vector<tktkMath::Vector2> otherVertexs;
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : otherBody.getVertexs())
		{
			otherVertexs.push_back((vertex + tktkMath::Vector2::normalize(vertex - otherCenterPos) * selfRadius) * otherWorldMatrix);
		}

		for (size_t i = 0; i < otherVertexs.size(); i++)
		{
			// �񎟌��|���S���̕ӂ̒����A������\���x�N�g�����v�Z����
			tktkMath::Vector2 line = otherVertexs.at((i + 1) % otherVertexs.size()) - otherVertexs.at(i);

			// �񎟌��|���S���̕ӂ̈�ڂ̒��_����~�̒��S���W�ւ̃x�N�g�����v�Z����
			tktkMath::Vector2 selfToOther = selfCenterPos - otherVertexs.at(i);

			// ��̂Q�̃x�N�g���̊O�ς����̐��Ȃ�Փ˂��Ă��Ȃ�
			if (tktkMath::Vector2::cross(selfToOther, line) > 0.0f) return false;
		}
		return true;
	}

	bool CollisionSupport2D::collidePolygonToPoint(const BoundingPolygon2D& selfBody, const tktkMath::Vector2& otherPoint, const tktkMath::Matrix3& selfWorldMatrix)
	{
		// �񎟌��|���S���̒��_���v�Z����
		std::vector<tktkMath::Vector2> selfVertexs;
		selfVertexs.reserve(selfBody.getVertexs().size());
		for (const auto& vertex : selfBody.getVertexs()) selfVertexs.push_back(vertex * selfWorldMatrix);

		for (size_t i = 0; i < selfVertexs.size(); i++)
		{
			// �񎟌��|���S���̕ӂ̒����A������\���x�N�g�����v�Z����
			tktkMath::Vector2 line = selfVertexs.at((i + 1) % selfVertexs.size()) - selfVertexs.at(i);

			// �񎟌��|���S���̕ӂ̈�ڂ̒��_����_�̍��W�ւ̃x�N�g�����v�Z����
			tktkMath::Vector2 selfToOther = otherPoint - selfVertexs.at(i);

			// ��̂Q�̃x�N�g���̊O�ς����̐��Ȃ�Փ˂��Ă��Ȃ�
			if (tktkMath::Vector2::cross(selfToOther, line) > 0.0f) return false;
		}
		return true;
	}

	// �Q�l�ɂ����T�C�g�uhttps://www.hiramine.com/programming/graphics/2d_segmentintersection.html�v
	CollisionSupport2D::LineCrossCheckResult CollisionSupport2D::lineCrossCheck(const tktkMath::Vector2& firstLinePosOne, const tktkMath::Vector2& firstLinePosTwo, const tktkMath::Vector2& secondLinePosOne, const tktkMath::Vector2& secondLinePosTwo)
	{
		// ���茋��
		LineCrossCheckResult result;

		// ��������Ŏg�p���镪��̒l
		float denominator = (firstLinePosTwo.x - firstLinePosOne.x) * (secondLinePosTwo.y - secondLinePosOne.y) - (firstLinePosTwo.y - firstLinePosOne.y) * (secondLinePosTwo.x - secondLinePosOne.x);

		// �[���Ŋ��낤�Ƃ������͒����Ƃ��Ă��Փ˂��Ă��Ȃ�
		if (denominator == 0.0f) return result;

		// ���ꂼ��̐����̈�ڂ̓_�Ԃ̃x�N�g�����v�Z����
		auto vecEachLinePosOne = secondLinePosOne - firstLinePosOne;

		// ��ڂ̐�����Ō��������̌�_�̈ʒu�i�������Ă����0�`1�̊Ԃ̒l�ƂȂ�j
		float firstLineCrossPosRate = ((secondLinePosTwo.y - secondLinePosOne.y) * vecEachLinePosOne.x - (secondLinePosTwo.x - secondLinePosOne.x) * vecEachLinePosOne.y) / denominator;

		// ��ڂ̐�����Ō��������̌�_�̈ʒu�i�������Ă����0�`1�̊Ԃ̒l�ƂȂ�j
		float secondLineCrossPosRate = ((firstLinePosTwo.y - firstLinePosOne.y) * vecEachLinePosOne.x - (firstLinePosTwo.x - firstLinePosOne.x) * vecEachLinePosOne.y) / denominator;

		// �������������Ă��邩���肷��
		result.isHit = (firstLineCrossPosRate <= 1.0f && secondLineCrossPosRate <= 1.0f && firstLineCrossPosRate >= 0.0f && secondLineCrossPosRate >= 0.0f);

		// �����_���v�Z����
		result.crossPos = firstLinePosOne + (firstLinePosTwo - firstLinePosOne) * firstLineCrossPosRate;

		return result;
	}

	CollisionSupport2D::LinePolygonHitInfo CollisionSupport2D::lineCollisionWithPolygon(const tktkMath::Vector2& firstPos, const tktkMath::Vector2& secondPos, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& otherWorldMatrix)
	{
		// �񎟌��|���S���̒��_���v�Z����
		std::vector<tktkMath::Vector2> otherVertexs;
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : otherBody.getVertexs())
		{
			otherVertexs.push_back(vertex * otherWorldMatrix);
		}

		// ��l�i�ł������̍����������j
		float minDist = std::numeric_limits<float>::max();

		// ���茋��
		LinePolygonHitInfo result{};

		// �g���g�̍��W���瑊��̍��W�ւ̃x�N�g���h�Ɓg���g�̍��W����ł��߂�����̏Փ˔���̕Ӂh�̌����_�����߂�
		for (size_t i = 0U; i < otherVertexs.size(); i++)
		{
			// �ӂ��\�����钸�_���
			const auto& firstVert	= otherVertexs.at(i);
			const auto& secondVert	= otherVertexs.at((i + 1U) % otherVertexs.size());

			// �g�����̐��h�Ɓg����̏Փ˔���̕Ӂh�̌���������s��
			auto lineCrossResult = tktkCollision::CollisionSupport2D::lineCrossCheck(firstPos, secondPos, firstVert, secondVert);

			// �������������Ă��Ȃ������玟�̕ӂ̔���ɐi��
			if (!lineCrossResult.isHit) continue;

			// �Փ˃t���O�𗧂Ă�
			result.isHit = true;

			// ���g�̍��W�Ɛ����̌����_�̋������v�Z����
			float dist = tktkMath::Vector2::distance(lineCrossResult.crossPos, firstPos);

			// �g���g�̍��W�Ɛ����̌����_�̋����h�̒Z�����X�V���Ă�����
			if (dist < minDist)
			{
				// ��l���X�V
				minDist = dist;

				// �����_���X�V
				result.selfExtrudePos		= lineCrossResult.crossPos;

				// ������������̕ӂ̒��_���X�V
				result.hitLineFirstVert		= firstVert;
				result.hitLineSecondVert	= secondVert;
			}
		}
		return result;
	}

	HitInfo2D CollisionSupport2D::circleCollisionWithCircle(const BoundingCircle& selfBody, const BoundingCircle& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix)
	{
		// ���ꂼ��̉~�̒��S���W���v�Z����
		tktkMath::Vector2 selfCenterPos = selfBody.getCenterPosition() * selfWorldMatrix;
		tktkMath::Vector2 otherCenterPos = otherBody.getCenterPosition() * otherWorldMatrix;
		
		// ���ꂼ��̉~�̔��a�����߂�
		float selfRadius	= selfBody.getRadius()	* selfWorldMatrix.calculateScale().x;
		float otherRadius	= otherBody.getRadius() * otherWorldMatrix.calculateScale().x;
		
		// �Փ˔��茋��
		HitInfo2D result{};
		
		// ���ꂼ��̉~�̒��S�_�̍������ꂼ��̉~�̔��a�̍��v������������ΏՓ˂��Ă���
		result.isHit = tktkMath::Vector2::distance(selfCenterPos, otherCenterPos) < selfRadius + otherRadius;
		
		// �������Փ˂��Ă�����
		if (result.isHit)
		{
			result.selfExtrudeVec = otherCenterPos - (selfCenterPos + (otherCenterPos - selfCenterPos).normalized() * (selfRadius + otherRadius));
			return result;
		}
		return result;
	}

	HitInfo2D CollisionSupport2D::polygonCollisionWithPolygon(const BoundingPolygon2D& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix)
	{
		// ���ꂼ��̏Փ˔���̍��W���擾
		auto selfPos	= selfWorldMatrix.calculateTranslation();
		auto otherPos	= otherWorldMatrix.calculateTranslation();

		// �񎟌��|���S���̒��_���v�Z����
		std::vector<tktkMath::Vector2> selfVertexs;
		selfVertexs.reserve(selfBody.getVertexs().size());
		for (const auto& vertex : selfBody.getVertexs()) selfVertexs.push_back(vertex * selfWorldMatrix);
		std::vector<tktkMath::Vector2> otherVertexs;
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : otherBody.getVertexs()) otherVertexs.push_back(vertex * otherWorldMatrix);

		// �Փ˒��ɕЕ��̒��S���W�������Е��̕ӂ���ł����ꂽ���̋������v�Z����
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

		// �g���g�̍��W���瑊��̍��W�̐��h�Ɓg����̃|���S���h�ŏՓ˔�����s��
		// �����g�̍��W������̏Փ˔���̒��ɓ��荞��ł���\�����l�����Ēl���␳����Ă���
		auto selfPosColOtherPolyResult = lineCollisionWithPolygon(
			selfPos - (tktkMath::Vector2::normalize(otherPos - selfPos) * mostFarDistance),	// �߂荞�ݑz��␳
			otherPos,
			otherBody,
			otherWorldMatrix
		);

		// ���O�ɍs�����Փ˔���̌��ʂ��g�Փ˂��Ă��Ȃ��h�������瑊��̃|���S�������Ă��Ȃ��ׁA����s��
		if (!selfPosColOtherPolyResult.isHit) return result;

		// ���g�̍��W����ł��߂�����̏Փ˔���̕ӂ�������ɐ����ɐL�т��x�N�g���i�����͂P�j���v�Z����
		auto otherColliderLineVerticalLineDirection = tktkMath::Vector2::perpendicular((selfPosColOtherPolyResult.hitLineSecondVert - selfPosColOtherPolyResult.hitLineFirstVert).normalized());

		// �g����̏Փ˔���̕ӏ�̓_����ӂ���Ƃ��ē����ɐ����ɐL�т����h�Ɓg���g�̃|���S���h�ŏՓ˔�����s��
		auto otherLineColSelfPolyResult = lineCollisionWithPolygon(
			selfPosColOtherPolyResult.selfExtrudePos,
			selfPosColOtherPolyResult.selfExtrudePos + (otherColliderLineVerticalLineDirection * mostFarDistance),	// �߂荞�ݑz��␳
			selfBody,
			selfWorldMatrix
		);

		// ���O�ɍs�����Փ˔���̌��ʂ��g�Փ˂��Ă��Ȃ��h�������瑊��̃|���S���ƏՓ˂��Ă��Ȃ�
		if (!otherLineColSelfPolyResult.isHit) return result;

		{
			// ���g�̉����o���Ɏg�p����ӂ̈�ڂ̒��_����ɉ����o�����������̉����o�����W���v�Z
			auto lineCrossCheckResult = tktkCollision::CollisionSupport2D::lineCrossCheck(
				otherLineColSelfPolyResult.hitLineFirstVert,
				otherLineColSelfPolyResult.hitLineFirstVert + otherColliderLineVerticalLineDirection,
				selfPosColOtherPolyResult.hitLineFirstVert,
				selfPosColOtherPolyResult.hitLineSecondVert
			);

			// ���g�̉����o���Ɏg�p����ӂ̓�ڂ̒��_����ɉ����o�����������̉����o���x�N�g�����v�Z����
			auto tempPushVec = lineCrossCheckResult.crossPos - otherLineColSelfPolyResult.hitLineSecondVert;

			// ���g�������o��������\���x�N�g�����Փˑ���̃|���S���̓����Ɍ������Ă��Ȃ����
			if (!tempPushVec.normalized().equals(otherColliderLineVerticalLineDirection))
			{
				// ���g�̉����o���Ɏg�p����ӂ̈�ڂ̒��_����ɉ����o�����������̉����o���x�N�g�����v�Z���������
				result.selfExtrudeVec = lineCrossCheckResult.crossPos - otherLineColSelfPolyResult.hitLineFirstVert;
			}
		}

		{
			// ���g�̉����o���Ɏg�p����ӂ̓�ڂ̒��_����ɉ����o�����������̉����o�����W���v�Z
			auto lineCrossCheckResult = tktkCollision::CollisionSupport2D::lineCrossCheck(
				otherLineColSelfPolyResult.hitLineSecondVert,
				otherLineColSelfPolyResult.hitLineSecondVert + otherColliderLineVerticalLineDirection,
				selfPosColOtherPolyResult.hitLineFirstVert,
				selfPosColOtherPolyResult.hitLineSecondVert
			);

			// ���g�̉����o���Ɏg�p����ӂ̓�ڂ̒��_����ɉ����o�����������̉����o���x�N�g�����v�Z����
			auto tempPushVec = lineCrossCheckResult.crossPos - otherLineColSelfPolyResult.hitLineSecondVert;

			// �g��ڂ̒��_����ɂ��������o���x�N�g���h���g��ڂ̒��_����ɂ��������o���x�N�g���h�����Z����A���g�������o��������\���x�N�g�����Փˑ���̃|���S���̓����Ɍ������Ă��Ȃ����
			if (result.selfExtrudeVec.length() < tempPushVec.length() && tempPushVec.normalized().equals(otherColliderLineVerticalLineDirection))
			{
				// �����o���x�N�g�����X�V����
				result.selfExtrudeVec = tempPushVec;
			}
		}

		// �����o���������[���łȂ���ΏՓ˂��Ă���Ɣ��f����
		result.isHit = (!result.selfExtrudeVec.equals(tktkMath::Vector2_v::zero));

		return result;
	}

	HitInfo2D CollisionSupport2D::circleCollisionWithPolygon(const BoundingCircle& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix)
	{
		// ���ꂼ��̏Փ˔���̍��W���擾
		auto selfPos = selfWorldMatrix.calculateTranslation();
		auto otherPos = otherWorldMatrix.calculateTranslation();

		// �~�̔��a�����߂�
		float selfRadius = selfBody.getRadius() * selfWorldMatrix.calculateScale().x;

		// �|���S���̒��_���v�Z����
		std::vector<tktkMath::Vector2> otherVertexs;
		otherVertexs.reserve(otherBody.getVertexs().size());
		for (const auto& vertex : otherBody.getVertexs()) otherVertexs.push_back(vertex * otherWorldMatrix);

		// �Փ˒��ɕЕ��̒��S���W�������Е��̏Փ˔���̋��E������ł����ꂽ���̋������v�Z����
		float mostFarDistance = selfRadius;
		for (const auto& vertex : otherVertexs)
		{
			float dist = tktkMath::Vector2::distance(otherWorldMatrix.calculateTranslation(), vertex);
			if (dist > mostFarDistance) mostFarDistance = dist;
		}

		HitInfo2D result{};

		// �|���S���̂��ꂼ��̒��_�̒��ōł��~�̒��S�ɋ߂����_��T��
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

		// �g���g�̍��W���瑊��̍��W�̐��h�Ɓg����̃|���S���h�ŏՓ˔�����s��
		// �����g�̍��W������̏Փ˔���̒��ɓ��荞��ł���\�����l�����Ēl���␳����Ă���
		auto selfPosColOtherPolyResult = lineCollisionWithPolygon(
			selfPos - (tktkMath::Vector2::normalize(otherPos - selfPos) * mostFarDistance),	// �߂荞�ݑz��␳
			otherPos,
			otherBody,
			otherWorldMatrix
		);

		// ���O�ɍs�����Փ˔���̌��ʂ��g�Փ˂��Ă��Ȃ��h�������瑊��̃|���S�������Ă��Ȃ��ׁA����s��
		if (!selfPosColOtherPolyResult.isHit) return result;

		// �g���g�̍��W����ł��߂�����̏Փ˔���̕Ӂh�̃x�N�g���i�����͂P�j���v�Z����
		auto otherColliderLineDirection = (selfPosColOtherPolyResult.hitLineFirstVert - selfPosColOtherPolyResult.hitLineSecondVert).normalized();
		
		// �g���g�̍��W����ł��߂�����̏Փ˔���̕Ӂh����O���ɐ����ɐL�т��x�N�g���i�����͂P�j���v�Z����
		auto otherColliderLineVerticalLineDirection = tktkMath::Vector2::perpendicular(otherColliderLineDirection);
		
		// �g���g�̍��W����ł��߂�����̏Փ˔���̕ӂɕ��s�Ŏ��g�̍��W��ʂ���h�Ɓg���g�̍��W����ł��߂�����̏Փ˔���̕ӂ���O���ɐ����ɐL�т����h�ŏՓ˔�����s��
		auto lineCrossCheckResult = tktkCollision::CollisionSupport2D::lineCrossCheck(
			selfPosColOtherPolyResult.selfExtrudePos,
			selfPosColOtherPolyResult.selfExtrudePos + otherColliderLineVerticalLineDirection,
			selfPos,
			selfPos + otherColliderLineDirection
		);
		
		// �g�|���S���̕ӂ��琂���ɉ��΂������h�Ɓg�|���S���̕ӂɕ��s�ŉ~�̒��S��ʂ���h�̌�_�Ɓg�|���S���̕ӂ��琂���ɉ��΂������̊J�n�_�h�̊Ԃ̃x�N�g��
		auto otherColliderLineToCircleCenterPassVec = lineCrossCheckResult.crossPos - selfPosColOtherPolyResult.selfExtrudePos;
		
		// ��̃x�N�g�����~�̔��a�����Z����ΏՓ˂��Ă���
		result.isHit = (otherColliderLineToCircleCenterPassVec.length() < selfRadius);
		
		// �Փ˂��Ă�����
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