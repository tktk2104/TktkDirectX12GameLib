#include "TktkCollision/2D/CollisionSupport2D.h"

#include <TktkMath/MathHelper.h>
#include "TktkCollision/2D/BoundingCircle.h"
#include "TktkCollision/2D/BoundingPolygon2D.h"

namespace
{
	// �|���S���Ɠ_�̓����蔻��
	bool polygonCollisionWithPoint(const std::vector<tktkMath::Vector2>& selfVertexs, const tktkMath::Vector2& otherPoint)
	{
		for (size_t i = 0; i < selfVertexs.size(); i++)
		{
			// ���ݎQ�Ƃ��Ă���ӂ��\�����钸�_�B
			const auto& firstVert = selfVertexs.at(i);
			const auto& secondVert = selfVertexs.at((i + 1) % selfVertexs.size());

			// �񎟌��|���S���̕ӂ̒����A������\���x�N�g�����v�Z����
			tktkMath::Vector2 line = secondVert - firstVert;

			// �񎟌��|���S���̕ӂ̈�ڂ̒��_����_�̍��W�ւ̃x�N�g�����v�Z����
			tktkMath::Vector2 firstVertToPoint = otherPoint - firstVert;

			// ��̂Q�̃x�N�g���̊O�ς��v�Z����
			float cross = tktkMath::Vector2::cross(firstVertToPoint, line);

			// ���߂��O�ς����̐��Ȃ�Փ˂��Ă��Ȃ�
			if (cross > 0.0f) return false;
		}
		return true;
	}
}

namespace tktkCollision
{
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

	CollisionSupport2D::LinePolygonHitInfo CollisionSupport2D::lineCollisionWithPolygon(const tktkMath::Vector2& firstPos, const tktkMath::Vector2& secondPos, const std::vector<tktkMath::Vector2>& otherVertexs)
	{
		// ���茋��
		LinePolygonHitInfo result{};

		// �����̐������|���S�����Ɋ��S�ɓ��荞��ł�����
		if (polygonCollisionWithPoint(otherVertexs, firstPos) && polygonCollisionWithPoint(otherVertexs, secondPos))
		{
			result.isHit = true;
			return result;
		}

		// �����_�Q���̃��������m�ۂ���
		result.crossPosArray.reserve(2U);

		// ����̃|���S���̒��_�����񂷂�
		for (size_t i = 0U; i < otherVertexs.size(); i++)
		{
			// �ӂ��\�����钸�_���
			const auto& firstVert	= otherVertexs.at(i);
			const auto& secondVert	= otherVertexs.at((i + 1U) % otherVertexs.size());

			// �g�����̐����h�Ɓg����̏Փ˔���̕Ӂh�̌���������s��
			auto lineCrossResult = tktkCollision::CollisionSupport2D::lineCrossCheck(firstPos, secondPos, firstVert, secondVert);

			// �������������Ă�����
			if (lineCrossResult.isHit)
			{
				// �Փ˃t���O�𗧂Ă�
				result.isHit = true;

				// �����_��ǉ�����
				result.crossPosArray.push_back(lineCrossResult.crossPos);
			}
		}
		return result;
	}

	HitInfo2D CollisionSupport2D::circleCollisionWithCircle(const tktkMath::Vector2& selfCenterPos, float selfRadius, const tktkMath::Vector2& otherCenterPos, float otherRadius)
	{
		// �Փ˔��茋��
		auto result = HitInfo2D();
		
		// ���ꂼ��̒��S���W�̋������v�Z����
		float posDist = tktkMath::Vector2::distance(selfCenterPos, otherCenterPos);

		// �Փ˔��茋��
		result.isHit = (posDist < selfRadius + otherRadius);
		
		// ���g�������o���������v�Z����
		result.selfExtrudeVec = (selfCenterPos - otherCenterPos).normalized() * ((selfRadius + otherRadius) - posDist);

		return result;
	}

	HitInfo2D CollisionSupport2D::polygonCollisionWithPolygon(const std::vector<tktkMath::Vector2>& selfVertexs, const std::vector<tktkMath::Vector2>& otherVertexs)
	{
		HitInfo2D result{};

		// ���g�̃|���S���̒��S���W���v�Z����
		auto selfPolyCenterPos = tktkMath::Vector2_v::zero;
		for (const auto& selfVert : selfVertexs) selfPolyCenterPos += selfVert;
		selfPolyCenterPos /= selfVertexs.size();

		// ����̃|���S���̒��S���W���v�Z����
		auto otherPolyCenterPos = tktkMath::Vector2_v::zero;
		for (const auto& otherVert : otherVertexs) otherPolyCenterPos += otherVert;
		otherPolyCenterPos /= otherVertexs.size();

		// ���g�̃|���S���̒��S���W������̃|���S�����ɂ�������
		if (polygonCollisionWithPoint(otherVertexs, selfPolyCenterPos))
		{
			// �Փ˂��Ă���
			result.isHit = true;
		}
		else
		{
			// ����̃|���S���̒��S���W�����g�̃|���S�����ɂ�������
			if (polygonCollisionWithPoint(selfVertexs, otherPolyCenterPos))
			{
				// �Փ˂��Ă���
				result.isHit = true;
			}
			else
			{
				// �������Ă���ӂ����݂��邩�H
				bool findInclusionLine = false;

				// ����̃|���S�����\�����钸�_�����񂷂�
				for (size_t vertIndex = 0; vertIndex < otherVertexs.size(); vertIndex++)
				{
					// ����̃|���S���̕ӂƎ��g�̃|���S���ŏՓ˔�����s��
					auto lineCollisionPolygonResult = lineCollisionWithPolygon(otherVertexs.at(vertIndex), otherVertexs.at((vertIndex + 1U) % otherVertexs.size()), selfVertexs);

					// �g����̃|���S���̕ӂƎ��g�̃|���S���h���������Ă��邩�H
					if (lineCollisionPolygonResult.isHit) findInclusionLine = true;
				}

				// �������Ă���ӂ����݂�����Փ˂��Ă���
				if (findInclusionLine) result.isHit = true;
			}
		}

		// �Փ˂��Ă�����
		if (result.isHit)
		{
			// ����̃|���S���̕ӂ��g���ċ��߂������o������
			result.selfExtrudeVec = tktkMath::Vector2_v::positiveInfinity;

			// �����ꂩ�̃|���S���̒��S����ł��������_�܂ł̋���
			float maxCenterToVertDist = 0.0f;

			// ����̃|���S���̒��_�����񂷂�
			for (const auto& node : otherVertexs)
			{
				// �|���S���̒��S�_�ƒ��_�̋������v�Z����
				float dist = tktkMath::Vector2::distance(otherPolyCenterPos, node);

				// �����̒������X�V���Ă�����l���X�V����
				if (dist > maxCenterToVertDist) maxCenterToVertDist = dist;
			}

			// ���g�̃|���S���̒��_�����񂷂�
			for (const auto& node : selfVertexs)
			{
				// �|���S���̒��S�_�ƒ��_�̋������v�Z����
				float dist = tktkMath::Vector2::distance(selfPolyCenterPos, node);

				// �����̒������X�V���Ă�����l���X�V����
				if (dist > maxCenterToVertDist) maxCenterToVertDist = dist;
			}

			// ���g�̃|���S���̒��_�����񂷂�
			for (size_t i = 0; i < selfVertexs.size(); i++)
			{
				const auto& firstVert = selfVertexs.at(i);
				const auto& secondVert = selfVertexs.at((i + 1U) % selfVertexs.size());

				// ���g�̃|���S���̕ӂ��\�����钸�_������̃|���S�����ɓ����Ă��邩�H
				bool firstVertInOtherPoly	= polygonCollisionWithPoint(otherVertexs, firstVert);
				bool secondVertInOtherPoly	= polygonCollisionWithPoint(otherVertexs, secondVert);

				// �Q�̒��_�������������̃|���S�����ɓ����ċ��Ȃ������玟�̗v�f��
				if (!(firstVertInOtherPoly || secondVertInOtherPoly)) continue;
			
				// ���g�̃|���S���̕ӂ̃x�N�g��
				auto selfPolyLineVec = secondVert - firstVert;
			
				// ���g�̃|���S���̕ӂ̋t�@�����v�Z����
				auto selfLineInverseNormal = tktkMath::Vector2::perpendicular(selfPolyLineVec.normalized());

				// �����̊J�n�_�̃I�t�Z�b�g�i�߂荞�ݎ��̕␳�j
				auto collideLineStartOffset = -selfLineInverseNormal * 8.0f;

				// �����̏I�_�Ɍ������x�N�g�����v�Z����
				auto collideLineVec = selfLineInverseNormal * maxCenterToVertDist * 2.0f;
			
				// �Q���_���ꂼ��̉����o�����̓��ő�̕���������ϐ�
				auto maxExtrudeVec = tktkMath::Vector2_v::zero;

				// �����o�������X�V�������H
				bool updatedExtrudeVec = false;
			
				// �P�ڂ̒��_������̃|���S�����ɓ����Ă�����
				if (firstVertInOtherPoly)
				{
					// ���g�̂P�ڂ̒��_����ӂ̖@�������֐L�т������Ƒ���̃|���S���ŏՓ˔��������
					auto firstVertNormalLineColResult = lineCollisionWithPolygon(firstVert + collideLineStartOffset, firstVert + collideLineVec, otherVertexs);

					// �����_�̐��ɂ���ĕ���
					if (firstVertNormalLineColResult.crossPosArray.size() == 1U)
					{
						// �����o�������X�V����
						maxExtrudeVec = firstVertNormalLineColResult.crossPosArray.at(0U) - firstVert;

						updatedExtrudeVec = true;
					}
					else if (firstVertNormalLineColResult.crossPosArray.size() > 1U)
					{
						for (const auto& crossPos : firstVertNormalLineColResult.crossPosArray)
						{
							auto tempExtrudeVec = crossPos - firstVert;

							// �����o�����̍ő�l���X�V���Ă�����l���X�V����
							if (tempExtrudeVec.length() > maxExtrudeVec.length()) maxExtrudeVec = tempExtrudeVec;
						}
						updatedExtrudeVec = true;
					}
				}

				// �Q�ڂ̒��_������̃|���S�����ɓ����Ă�����
				if (secondVertInOtherPoly)
				{
					// ���g�̂Q�ڂ̒��_����ӂ̖@�������֐L�т������Ƒ���̃|���S���ŏՓ˔��������
					auto secondVertNormalLineColResult = lineCollisionWithPolygon(secondVert + collideLineStartOffset, secondVert + collideLineVec, otherVertexs);

					// �����_�̐��ɂ���ĕ���
					if (secondVertNormalLineColResult.crossPosArray.size() == 1U)
					{
						auto tempExtrudeVec = secondVertNormalLineColResult.crossPosArray.at(0U) - secondVert;

						// �����o�����̍ő�l���X�V���Ă�����l���X�V����
						if (tempExtrudeVec.length() > maxExtrudeVec.length()) maxExtrudeVec = tempExtrudeVec;

						updatedExtrudeVec = true;
					}
					else if (secondVertNormalLineColResult.crossPosArray.size() > 1U)
					{
						for (const auto& crossPos : secondVertNormalLineColResult.crossPosArray)
						{
							auto tempExtrudeVec = crossPos - secondVert;

							// �����o�����̍ő�l���X�V���Ă�����l���X�V����
							if (tempExtrudeVec.length() > maxExtrudeVec.length()) maxExtrudeVec = tempExtrudeVec;
						}
						updatedExtrudeVec = true;
					}
				}
			
				// �ӂ��Ƃ̍ő剟���o�������̒��ōŏ��̉����o��������T��
				if (updatedExtrudeVec && maxExtrudeVec.length() < result.selfExtrudeVec.length()) result.selfExtrudeVec = maxExtrudeVec;
			}

			// ����̃|���S���̒��_�����񂷂�
			for (size_t i = 0; i < otherVertexs.size(); i++)
			{
				const auto& firstVert = otherVertexs.at(i);
				const auto& secondVert = otherVertexs.at((i + 1U) % otherVertexs.size());
			
				// ����̃|���S���̕ӂ��\�����钸�_�����g�̃|���S�����ɓ����Ă��邩�H
				bool firstVertInOtherPoly	= polygonCollisionWithPoint(selfVertexs, firstVert);
				bool secondVertInOtherPoly	= polygonCollisionWithPoint(selfVertexs, secondVert);

				// �Q�̒��_������������g�̃|���S�����ɓ����ċ��Ȃ������玟�̗v�f��
				if (!(firstVertInOtherPoly || secondVertInOtherPoly)) continue;

				// ����̃|���S���̕ӂ̃x�N�g��
				auto otherPolyLineVec = secondVert - firstVert;
			
				// ����̃|���S���̕ӂ̋t�@�����v�Z����
				auto otherLineInverseNormal = tktkMath::Vector2::perpendicular(otherPolyLineVec.normalized());
			
				// �����̊J�n�_�̃I�t�Z�b�g�i�߂荞�ݎ��̕␳�j
				auto collideLineStartOffset = -otherLineInverseNormal * 8.0f;

				// �����̏I�_�Ɍ������x�N�g�����v�Z����
				auto lineEndPosVec = otherLineInverseNormal * maxCenterToVertDist * 2.0f;
			
				// �Q���_���ꂼ��̉����o�����̓��ő�̕���������ϐ�
				auto maxExtrudeVec = tktkMath::Vector2_v::zero;
			
				// �����o�������X�V�������H
				bool updatedExtrudeVec = false;

				// �P�ڂ̒��_������̃|���S�����ɓ����Ă�����
				if (firstVertInOtherPoly)
				{
					// ����̂P�ڂ̒��_����ӂ̖@�������֐L�т������Ǝ��g�̃|���S���ŏՓ˔��������
					auto firstVertNormalLineColResult = lineCollisionWithPolygon(firstVert + collideLineStartOffset, firstVert + lineEndPosVec, selfVertexs);

					// �����_�̐��ɂ���ĕ���
					if (firstVertNormalLineColResult.crossPosArray.size() == 1U)
					{
						// �����o�������X�V����
						maxExtrudeVec = firstVertNormalLineColResult.crossPosArray.at(0U) - firstVert;

						updatedExtrudeVec = true;
					}
					else if (firstVertNormalLineColResult.crossPosArray.size() > 1U)
					{
						for (const auto& crossPos : firstVertNormalLineColResult.crossPosArray)
						{
							auto tempExtrudeVec = crossPos - firstVert;

							// �����o�����̍ő�l���X�V���Ă�����l���X�V����
							if (tempExtrudeVec.length() > maxExtrudeVec.length()) maxExtrudeVec = tempExtrudeVec;
						}

						updatedExtrudeVec = true;
					}
				}

				// �Q�ڂ̒��_������̃|���S�����ɓ����Ă�����
				if (secondVertInOtherPoly)
				{
					// ����̂Q�ڂ̒��_����ӂ̖@�������֐L�т������Ǝ��g�̃|���S���ŏՓ˔��������
					auto secondVertNormalLineColResult = lineCollisionWithPolygon(secondVert + collideLineStartOffset, secondVert + lineEndPosVec, selfVertexs);

					// �����_�̐��ɂ���ĕ���
					if (secondVertNormalLineColResult.crossPosArray.size() == 1U)
					{
						auto tempExtrudeVec = secondVertNormalLineColResult.crossPosArray.at(0U) - secondVert;

						// �����o�����̍ő�l���X�V���Ă�����l���X�V����
						if (tempExtrudeVec.length() > maxExtrudeVec.length()) maxExtrudeVec = tempExtrudeVec;

						updatedExtrudeVec = true;
					}
					else if (secondVertNormalLineColResult.crossPosArray.size() > 1U)
					{
						for (const auto& crossPos : secondVertNormalLineColResult.crossPosArray)
						{
							auto tempExtrudeVec = crossPos - secondVert;

							// �����o�����̍ő�l���X�V���Ă�����l���X�V����
							if (tempExtrudeVec.length() > maxExtrudeVec.length()) maxExtrudeVec = tempExtrudeVec;
						}

						updatedExtrudeVec = true;
					}
				}
				
				// �ӂ��Ƃ̍ő剟���o�������̒��ōŏ��̉����o��������T��
				if (updatedExtrudeVec && maxExtrudeVec.length() < result.selfExtrudeVec.length()) result.selfExtrudeVec = maxExtrudeVec * -1.0f;
			}

			// �����o�������擾�ł��Ȃ���Ή����o���Ȃ����ʂ�Ԃ�
			if (result.selfExtrudeVec == tktkMath::Vector2_v::positiveInfinity) result.selfExtrudeVec = tktkMath::Vector2_v::zero;
		}

		return result;
	}

	HitInfo2D CollisionSupport2D::circleCollisionWithPolygon(const tktkMath::Vector2& selfCenterPos, float selfRadius, const std::vector<tktkMath::Vector2>& otherVertexs)
	{
		float minDist = std::numeric_limits<float>::max();

		HitInfo2D result{};

		// ����̃|���S�����\�����钸�_�����񂷂�
		for (size_t vertIndex = 0; vertIndex < otherVertexs.size(); vertIndex++)
		{
			// �|���S���̕ӂ̃x�N�g�����v�Z����
			auto firstVertexToSecond = otherVertexs.at((vertIndex + 1U) % otherVertexs.size()) - otherVertexs.at(vertIndex);

			// �|���S���̕ӂ̖@�����v�Z����
			auto normal = -tktkMath::Vector2::perpendicular(firstVertexToSecond).normalized();

			// �|���S���̕ӂ̖@���̋t�����ɔ��a�������ړ��������W
			auto circleMostFarSurface = (selfCenterPos - normal * selfRadius);

			// �ӂ̊J�n�_������W�ւ̃x�N�g�����v�Z����
			auto firstVertexToPoint = circleMostFarSurface - otherVertexs.at(vertIndex);

			// �g�ӂ̊J�n�_������W�ւ̃x�N�g���h�Ɓg�|���S���̕ӂ̖@���h�̓���
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