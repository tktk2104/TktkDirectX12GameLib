#include "TktkCollision/3D/CollisionSupport3D.h"

#include "TktkMath/MathHelper.h"
#include "TktkCollision/2D/CollisionSupport2D.h"
#include "TktkCollision/3D/BoundingSphere.h"
#include "TktkCollision/3D/BoundingMesh.h"

namespace tktkCollision
{
	CollisionSupport3D::LinePolygonHitInfo CollisionSupport3D::lineCollisionWithPolygon(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const std::vector<tktkMath::Vector3>& otherPolygon)
	{
		// ����̃|���S���̒��_���R��菭�Ȃ��ꍇ�A����s��
		if (otherPolygon.size() < 3U) return LinePolygonHitInfo();

		// ��꒸�_�����񒸓_�ւ̃x�N�g�����v�Z����
		auto firstVertexToSecond = otherPolygon.at(1U) - otherPolygon.at(0U);

		// ��꒸�_�����O���_�ւ̃x�N�g�����v�Z����
		auto firstVertexToThird = otherPolygon.at(2U) - otherPolygon.at(0U);

		// �|���S���̖@�������v�Z����
		tktkMath::Vector3 normal = tktkMath::Vector3::cross(firstVertexToSecond, firstVertexToThird).normalized();

		// ��꒸�_��������̊J�n�_�ւ̃x�N�g�����v�Z����
		auto firstVertexToFirstPos = firstPos - otherPolygon.at(0U);

		// ��꒸�_��������̏I���_�ւ̃x�N�g�����v�Z����
		auto firstVertexToSecondPos = secondPos - otherPolygon.at(0U);

		// �g��꒸�_��������̊J�n�_�ւ̃x�N�g���h�Ɓg�|���S���̖@���h�̓���
		float firstVertToFirstPosNormalDot = tktkMath::Vector3::dot(firstVertexToFirstPos, normal);

		// �g��꒸�_��������̏I���_�ւ̃x�N�g���h�Ɓg�|���S���̖@���h�̓���
		float firstVertToSecondPosNormalDot = tktkMath::Vector3::dot(firstVertexToSecondPos, normal);

		// �������|���S���̉����ʏ�ɐڐG���Ă��Ȃ���Ώ������I����
		if (firstVertToFirstPosNormalDot * firstVertToSecondPosNormalDot > 0.0f) return LinePolygonHitInfo();

		LinePolygonHitInfo result;

		// �g�|���S���̉�������Ɂh�Փ˂��Ă���t���O�𗧂Ă�
		result.isExtensionPolyHit = true;

		// �������g�����h�����S�Ɂg�|���S���̉����ʁh��ɑ��݂��Ă�����
		if (firstVertToFirstPosNormalDot == 0.0f && firstVertToSecondPosNormalDot == 0.0f)
		{
			// �����ƃ|���S���̌����_�́g�����̒��S�_�h
			result.hitPos = firstPos + (secondPos - firstPos) / 2;
		}
		// �������g�����̊J�n�_�h�݂̂��g�|���S���̉����ʁh��ɑ��݂��Ă�����
		else if (firstVertToFirstPosNormalDot == 0.0f)
		{
			// �����ƃ|���S���̌����_�́g�����̊J�n�_�h
			result.hitPos = firstPos;
		}
		// �������g�����̏I���_�h�݂̂��g�|���S���̉����ʁh��ɑ��݂��Ă�����
		else if (firstVertToSecondPosNormalDot == 0.0f)
		{
			// �����ƃ|���S���̌����_�́g�����̏I���_�h
			result.hitPos = secondPos;
		}
		// �������g�����h���g�|���S���̉����ʁh�ƌ������Ă�����
		else
		{
			// �g�����h�Ɓg�|���S���̉����ʁh���������Ă���t���O�𗧂Ă�
			result.isExtensionPolyCross = true;

			// �v�Z�Ŏg�p����g������h���v�Z���� 
			auto internalDivisionRatio = (normal * firstVertToFirstPosNormalDot).length() / ((normal * firstVertToFirstPosNormalDot).length() + (normal * firstVertToSecondPosNormalDot).length());

			// ��꒸�_��������̌����_�ւ̃x�N�g�����v�Z����
			auto firstVertexToCrossPos = (1 - internalDivisionRatio) * firstVertexToFirstPos + internalDivisionRatio * firstVertexToSecondPos;

			// �����̌����_���v�Z����
			result.hitPos = otherPolygon.at(0U) + firstVertexToCrossPos;
		}

		for (size_t i = 0U; i < otherPolygon.size(); i++)
		{
			// �|���S���̕ӂ��\�����钸�_�Q��
			const auto& curVertPos = otherPolygon.at(i);
			const auto& nextVertPos = otherPolygon.at((i + 1U) % otherPolygon.size());

			// ���݂̒��_���玟�̒��_�ւ̃x�N�g�����v�Z����
			auto curVertexToNext = nextVertPos - curVertPos;

			// ���݂̒��_��������̌����_�ւ̃x�N�g�����v�Z����
			auto curVertexToCrossPos = result.hitPos - curVertPos;

			// �g���̒��_��������̌����_�ւ̃x�N�g���h���[���x�N�g�����A��̂Q�̃x�N�g�����^�t�̕�����������|���S���̕ӏ�ɐ������Փ˂��Ă���
			if (curVertexToCrossPos.length() < tktkMath::MathHelper::kEpsilon ||
				(curVertexToNext.normalized() - curVertexToCrossPos.normalized()).length() < tktkMath::MathHelper::kEpsilon)
			{
				result.isPolyEdgeHit = true;
			}

			// ��Q�̃x�N�g���̊O�ς����߂�
			auto testNormal = tktkMath::Vector3::cross(curVertexToNext, curVertexToCrossPos).normalized();

			// �O�ς��[���x�N�g���������ꍇ�A�����̌����_�̓|���S���̕ӏ�ɑ��݂���
			if (testNormal == tktkMath::Vector3_v::zero) continue;

			// �O�ς��|���S���̖@���ƈ�v�����ꍇ�A�����̌����_�̓|���S���̒��ɑ��݂���
			if (tktkMath::Vector3::distance(normal, testNormal) < tktkMath::MathHelper::kEpsilon) continue;

			// �������|���S���ɐڐG���Ă��Ȃ���Ώ������I����
			return result;

			//if (!(tktkMath::Vector3::distance(normal, testNormal) < tktkMath::MathHelper::kEpsilon)) return result; //testNormal.length() < tktkMath::MathHelper::kEpsilon || 
		}
		// �g���S�Ɂh�Փ˂��Ă���t���O�𗧂Ă�
		result.isHit = true;
		return result;
	}

	bool CollisionSupport3D::pointCollisionWithMesh(const tktkMath::Vector3& point, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh)
	{
		// ����̃|���S�������񂷂�
		for (const auto& otherPoly : otherMesh)
		{
			// ����̃|���S���̒��_���R��菭�Ȃ��ꍇ�A����s�Ȃ̂Ŏ��̃|���S���̔����
			if (otherPoly.size() < 3U) continue;

			// ��꒸�_�����񒸓_�ւ̃x�N�g�����v�Z����
			auto firstVertexToSecond = otherPoly.at(1U) - otherPoly.at(0U);

			// ��꒸�_�����O���_�ւ̃x�N�g�����v�Z����
			auto firstVertexToThird = otherPoly.at(2U) - otherPoly.at(0U);

			// �|���S���̖@�������v�Z����
			tktkMath::Vector3 normal = tktkMath::Vector3::cross(firstVertexToSecond, firstVertexToThird).normalized();

			// ��꒸�_����_�ւ̃x�N�g�����v�Z����
			auto firstVertexToPoint = point - otherPoly.at(0U);

			// �g��꒸�_����_�ւ̃x�N�g���h�Ɓg�|���S���̖@���h�̓���
			float firstVertToPointNormalDot = tktkMath::Vector3::dot(firstVertexToPoint, normal);

			if (firstVertToPointNormalDot > 0.0f) return false;
		}
		return true;
	}

	CollisionSupport3D::LineMeshHitInfo CollisionSupport3D::lineCollisionWithMesh(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh)
	{
		LineMeshHitInfo result;

		// ����̃|���S�������񂷂�
		for (const auto& otherPoly : otherMesh)
		{
			// ����̃|���S���̒��_���R��菭�Ȃ��ꍇ�A����s�Ȃ̂Ŏ��̃|���S���̔����
			if (otherPoly.size() < 3U) continue;

			// �|���S���Ɛ����ŏՓ˔�����s��
			auto polygonHitInfo = lineCollisionWithPolygon(firstPos, secondPos, otherPoly);

			// �|���S���Ɛ������Փ˂��Ă���ΏՓˌ��ʂ�Ԃ�
			if (polygonHitInfo.isHit)
			{
				result.isHit = true;
				result.linePolyCrossDataArray.push_back({ polygonHitInfo.isExtensionPolyCross, polygonHitInfo.isPolyEdgeHit, polygonHitInfo.hitPos, otherPoly });
			}
		}
		return result;
	}

	HitInfo3D CollisionSupport3D::polygonCollisionWithMesh(const std::vector<tktkMath::Vector3>& polygon, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh)
	{
		// ���g�̃|���S���̒��_���R��菭�Ȃ��ꍇ�A����s��
		if (polygon.size() < 3U) return HitInfo3D();

		// ���g�̃|���S���̖@�����v�Z����
		tktkMath::Vector3 polygonNormal = tktkMath::Vector3::cross(polygon.at(1U) - polygon.at(0U), polygon.at(2U) - polygon.at(0)).normalized();

		HitInfo3D result{};

		// ���g�̃|���S������ł���������̒��_�܂ł̋���
		float mostFarOtherVertLen = 0.0f;

		// ���g�̃|���S������ł������g�����o���Ɏg�p�ł���h����̒��_�܂ł̋���
		float mostFarCollideUseOtherVertLen = -1.0f;

		// ����̃|���S�������񂷂�
		for (const auto& otherPoly : otherMesh)
		{
			// ����̃|���S�����\�����钸�_�����񂷂�
			for (const auto& otherVert : otherPoly)
			{
				// ����̒��_���J�n�_�Ƃ��鎩�g�̃|���S���̔��]�@���x�N�g���̒���
				auto otherVertToExtensionPolyCrossVecLen = tktkMath::Vector3::dot(polygon.at(0U) - otherVert, polygonNormal);

				// �g����̒��_���J�n�_�Ƃ��鎩�g�̃|���S���̔��]�@���x�N�g���̒����h�̐�Βl
				float absOtherVertToExtensionPolyCrossVecLen = std::abs(otherVertToExtensionPolyCrossVecLen);

				// �g���g�̃|���S������ł���������̒��_�܂ł̋����h�̉������X�V���Ă�����A��l���X�V����
				if (absOtherVertToExtensionPolyCrossVecLen > mostFarOtherVertLen) mostFarOtherVertLen = absOtherVertToExtensionPolyCrossVecLen;

				// �@���x�N�g���̒������O��菬�����i���g�̃|���S���ƏՓ˂��Ă��Ȃ��j�ꍇ�͎��̒��_��
				if (otherVertToExtensionPolyCrossVecLen < 0.0f) continue;

				// �g����̒��_���J�n�_�Ƃ��鎩�g�̃|���S���̔��]�@���x�N�g���h�Ɓg���g�̃|���S���̖ʁh�̌����_
				auto crossPos = otherVert + (polygonNormal * otherVertToExtensionPolyCrossVecLen);

				// �g���g�̃|���S���h�Ɂg����̒��_���J�n�_�Ƃ��鎩�g�̃|���S���̔��]�@���x�N�g���h���Փ˂��Ă��邩�H
				bool isHitPolygon = true;

				// ���g�̃|���S�������񂷂�
				for (size_t i = 0U; i < polygon.size(); i++)
				{
					// ���g�̃|���S���̕ӂ��\�����钸�_�Q��
					const auto& curVertPos	= polygon.at(i);
					const auto& nextVertPos = polygon.at((i + 1U) % polygon.size());

					// ���݂̒��_���玟�̒��_�ւ̃x�N�g�����v�Z����
					auto curVertexToNext = nextVertPos - curVertPos;

					// ���݂̒��_��������̌����_�ւ̃x�N�g�����v�Z����
					auto curVertexToCrossPos = crossPos - curVertPos;

					if (curVertexToCrossPos.y < tktkMath::MathHelper::kEpsilon) curVertexToCrossPos.y = 0.0f;

					// ��Q�̃x�N�g���̊O�ς����߂�
					auto testNormal = tktkMath::Vector3::cross(curVertexToNext.normalized(), curVertexToCrossPos.normalized()).normalized();

					// �O�ς��[���x�N�g���������ꍇ�A�����̌����_�͎��g�̃|���S���̕ӏ�ɑ��݂���
					if (testNormal == tktkMath::Vector3_v::zero) continue;

					// �O�ς����g�̃|���S���̖@���ƈ�v�����ꍇ�A�����̌����_�̓|���S���̒��ɑ��݂���
					if (tktkMath::Vector3::distance(polygonNormal, testNormal) < tktkMath::MathHelper::kEpsilon) continue;

					// �������|���S���ɐڐG���Ă��Ȃ�
					isHitPolygon = false;
				}

				// �g���g�̃|���S���h�Ɂg����̒��_���J�n�_�Ƃ��鎩�g�̃|���S���̔��]�@���x�N�g���h���Փ˂��Ă��Ȃ��ꍇ�͎��̒��_��
				if (!isHitPolygon) continue;

				// �����A�g����̒��_���J�n�_�Ƃ��鎩�g�̃|���S���̔��]�@���x�N�g���̒����h�̐�Βl�̑傫�����X�V���Ă�����
				if (otherVertToExtensionPolyCrossVecLen > mostFarCollideUseOtherVertLen)
				{
					// �Փ˃t���O�𗧂Ă�
					result.isHit = true;

					// ��l���X�V
					mostFarCollideUseOtherVertLen = otherVertToExtensionPolyCrossVecLen;

					// ���g�̉����o���������X�V
					result.selfExtrudeVec = polygonNormal * otherVertToExtensionPolyCrossVecLen;
				}
			}
		}

		// ���g�̃|���S�����\�����钸�_�����񂷂�
		for (const auto& selfVert : polygon)
		{
			// �g���g�̃|���S���̒��_���玩�g�̃|���S���̔��]�@�������ɉ��т������h�Ɓg����̃��b�V���h�ŏՓ˔�����s��
			auto lineCrossResult = lineCollisionWithMesh(selfVert, selfVert - (polygonNormal * mostFarOtherVertLen), otherMesh);

			// �g���g�̃|���S���̒��_���玩�g�̃|���S���̔��]�@�������ɉ��т������h�Ɓg����̃��b�V���h���Փ˂��Ă��Ȃ������玟�̒��_��
			if (!lineCrossResult.isHit) continue;

			// �g���g�̃|���S���̒��_���玩�g�̃|���S���̖@�������ɉ��т������h�Ɓg����̃��b�V���h�̏Փ˓_�����񂷂�
			for (const auto& linePolyCrossData : lineCrossResult.linePolyCrossDataArray)
			{
				// �g���g�̃|���S���̒��_���玩�g�̃|���S���̖@�������ɉ��т������Ƒ���̃��b�V���̏Փ˓_�h����g���g�̃|���S���̒��_�h�ւ̃x�N�g��
				auto hitPosToSelfVert = selfVert - linePolyCrossData.hitPos;

				// �����A�g����̒��_���J�n�_�Ƃ��鎩�g�̃|���S���̔��]�@���x�N�g���̒����h�̐�Βl�̑傫�����X�V���Ă�����
				if (hitPosToSelfVert.length() > mostFarCollideUseOtherVertLen)
				{
					// �Փ˃t���O�𗧂Ă�
					result.isHit = true;

					// ��l���X�V
					mostFarCollideUseOtherVertLen = hitPosToSelfVert.length();

					// ���g�̉����o���������X�V
					result.selfExtrudeVec = hitPosToSelfVert;
				}
			}
		}

		return result;
	}

	HitInfo3D CollisionSupport3D::sphereCollisionWithSphere(const tktkMath::Vector3& selfCenterPos, float selfRadius, const tktkMath::Vector3& otherCenterPos, float otherRadius)
	{
		auto result = HitInfo3D();

		// ���ꂼ��̒��S���W�̋������v�Z����
		float posDist = tktkMath::Vector3::distance(selfCenterPos, otherCenterPos);

		// �Փ˔��茋��
		result.isHit = (posDist < selfRadius + otherRadius);

		// ���g�������o���������v�Z����
		result.selfExtrudeVec = (selfCenterPos - otherCenterPos).normalized() * ((selfRadius + otherRadius) - posDist);

		return result;
	}

	HitInfo3D CollisionSupport3D::meshCollisionWithMesh(const std::vector<std::vector<tktkMath::Vector3>>& selfMesh, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh)
	{
		//**************************************************
		// �Փˑ���̃|���S�����ɐڐG���Ă���ӂ����邩�ǂ����̃t���O

		HitInfo3D result{};
		result.selfExtrudeVec = { std::numeric_limits<float>::max() / 2.0f };

		// ����̃|���S�������񂷂�
		for (const auto& otherPoly : otherMesh)
		{
			// ����̃|���S���̒��_���R��菭�Ȃ��ꍇ�A����s�Ȃ̂Ŏ��̃|���S���̔����
			if (otherPoly.size() < 3U) continue;

			// ����̃|���S���̒��S���W���v�Z����
			auto otherPolyCenterPos = tktkMath::Vector3_v::zero;
			for (const auto& otherVert : otherPoly) otherPolyCenterPos += otherVert;
			otherPolyCenterPos /= otherPoly.size();

			// ����̃|���S���̒��S���W�����g�̃��b�V�����ɂ��邩���肷��
			bool findInclusionLine = pointCollisionWithMesh(otherPolyCenterPos, selfMesh);

			// ����̃|���S�����\�����钸�_�����񂷂�
			for (size_t vertIndex = 0; vertIndex < otherPoly.size(); vertIndex++)
			{
				// ���g�̃|���S���̕ӂƑ���̃��b�V���ŏՓ˔�����s��
				auto lineCollisionMeshResult = lineCollisionWithMesh(otherPoly.at(vertIndex), otherPoly.at((vertIndex + 1U) % otherPoly.size()), selfMesh);

				// �����g���g�̃|���S���̕ӂƑ���̃��b�V���h���Փ˂��Ă�����
				if (lineCollisionMeshResult.isHit) findInclusionLine = true;
			}

			if (!findInclusionLine) continue;

			result.isHit = true;

			auto polyHitResult = polygonCollisionWithMesh(otherPoly, selfMesh);

			if (!polyHitResult.isHit) continue;

			// �����o�������̋����̒Z�����X�V���Ă�����
			if (polyHitResult.selfExtrudeVec.length() < result.selfExtrudeVec.length())
			{
				// �����o���������X�V����
				result.selfExtrudeVec = polyHitResult.selfExtrudeVec;
			}
		}

		// ���g�̃|���S�������񂷂�
		for (const auto& selfPoly : selfMesh)
		{
			// ���g�̃|���S���̒��_���R��菭�Ȃ��ꍇ�A����s�Ȃ̂Ŏ��̃|���S���̔����
			if (selfPoly.size() < 3U) continue;

			// ���g�̃|���S���̒��S���W���v�Z����
			auto selfPolyCenterPos = tktkMath::Vector3_v::zero;
			for (const auto& selfVert : selfPoly) selfPolyCenterPos += selfVert;
			selfPolyCenterPos /= selfPoly.size();

			// ���g�̃|���S���̒��S���W������̃��b�V�����ɂ��邩���肷��
			bool findInclusionLine = pointCollisionWithMesh(selfPolyCenterPos, otherMesh);

			// ���g�̃|���S�����\�����钸�_�����񂷂�
			for (size_t vertIndex = 0; vertIndex < selfPoly.size(); vertIndex++)
			{
				// ���g�̃|���S���̕ӂƑ���̃��b�V���ŏՓ˔�����s��
				auto lineCollisionMeshResult = lineCollisionWithMesh(selfPoly.at(vertIndex), selfPoly.at((vertIndex + 1U) % selfPoly.size()), otherMesh);

				// �����g���g�̃|���S���̕ӂƑ���̃��b�V���h���Փ˂��Ă�����
				if (lineCollisionMeshResult.isHit) findInclusionLine = true;
			}

			if (!findInclusionLine) continue;

			result.isHit = true;

			auto polyHitResult = polygonCollisionWithMesh(selfPoly, otherMesh);

			if (!polyHitResult.isHit) continue;

			// �����o�������̋����̒Z�����X�V���Ă�����
			if (polyHitResult.selfExtrudeVec.length() < result.selfExtrudeVec.length())
			{
				// �����o���������X�V����
				result.selfExtrudeVec = -polyHitResult.selfExtrudeVec;
			}
		}

		if (result.selfExtrudeVec == tktkMath::Vector3{ std::numeric_limits<float>::max() / 2.0f }) result.selfExtrudeVec = tktkMath::Vector3_v::zero;

		return result;
	}

	HitInfo3D CollisionSupport3D::sphereCollisionWithMesh(const tktkMath::Vector3& selfCenterPos, float selfRadius, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh)
	{
		float minDist = std::numeric_limits<float>::max();

		auto result = HitInfo3D();
		
		// ����̃|���S�������񂷂�
		for (const auto& otherPoly : otherMesh)
		{
			// ����̃|���S���̒��_���R��菭�Ȃ��ꍇ�A����s�Ȃ̂Ŏ��̃|���S���̔����
			if (otherPoly.size() < 3U) continue;

			// ��꒸�_�����񒸓_�ւ̃x�N�g�����v�Z����
			auto firstVertexToSecond = otherPoly.at(1U) - otherPoly.at(0U);

			// ��꒸�_�����O���_�ւ̃x�N�g�����v�Z����
			auto firstVertexToThird = otherPoly.at(2U) - otherPoly.at(0U);

			// �|���S���̖@�������v�Z����
			tktkMath::Vector3 normal = tktkMath::Vector3::cross(firstVertexToSecond, firstVertexToThird).normalized();

			// �|���S���̋t�����ɔ��a�������ړ�����z�\
			auto sphereMostFarSurface = (selfCenterPos + normal * selfRadius);

			// ��꒸�_����_�ւ̃x�N�g�����v�Z����
			auto firstVertexToPoint = sphereMostFarSurface - otherPoly.at(0U);

			// �g��꒸�_����_�ւ̃x�N�g���h�Ɓg�|���S���̖@���h�̓���
			float firstVertToPointNormalDot = tktkMath::Vector3::dot(firstVertexToPoint, normal);

			if (firstVertToPointNormalDot > 0.0f) return HitInfo3D();

			if (-firstVertToPointNormalDot < minDist)
			{
				minDist = -firstVertToPointNormalDot;
				result.selfExtrudeVec = -firstVertToPointNormalDot * normal;
			}
		}
		result.isHit = true;
		return result;
	}

	HitInfo3D CollisionSupport3D::meshCollisionWithSphere(const std::vector<std::vector<tktkMath::Vector3>>& selfMesh, const tktkMath::Vector3& otherCenterPos, float otherRadius)
	{
		auto result = sphereCollisionWithMesh(otherCenterPos, otherRadius, selfMesh);
		result.selfExtrudeVec *= -1.0f;
		return result;
	}
}