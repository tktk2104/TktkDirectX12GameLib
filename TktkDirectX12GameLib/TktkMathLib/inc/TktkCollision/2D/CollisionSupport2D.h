#ifndef COLLISION_SUPPORT_2D_H_
#define COLLISION_SUPPORT_2D_H_

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix3.h>
#include "HitInfo2D.h"

namespace tktkCollision
{
	class BoundingCircle;
	class BoundingPolygon2D;

	class CollisionSupport2D
	{
	public:

		// �|���S���ƃ|���S���̓����蔻��
		static bool collidePolygonToPolygon(const BoundingPolygon2D& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// �~�ƃ|���S���̓����蔻��
		static bool collideCircleToPolygon(const BoundingCircle& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// �|���S���Ɠ_�̓����蔻��
		static bool collidePolygonToPoint(const BoundingPolygon2D& selfBody, const tktkMath::Vector2& otherPoint, const tktkMath::Matrix3& selfWorldMatrix);
	
	public:

		struct LineCrossCheckResult
		{
			// �������������Ă��邩�H
			bool isHit{ false };

			// ��̐��̌����_
			tktkMath::Vector2 crossPos{ tktkMath::Vector2_v::zero };
		};

		// �Q�̐������������Ă��邩�ƁA�Q�̐��̌����_���v�Z����
		// ��������͐����A�����_����͒����Ƃ��Čv�Z���Ă���
		static LineCrossCheckResult lineCrossCheck(
			const tktkMath::Vector2& firstLinePosOne,
			const tktkMath::Vector2& firstLinePosTwo,
			const tktkMath::Vector2& secondLinePosOne,
			const tktkMath::Vector2& secondLinePosTwo
		);

	public:

		struct LinePolygonHitInfo
		{
			// �Փ˂������ǂ����H
			bool				isHit				{ false };

			// �Փˎ��g���h���g���̏I�����W����ɊJ�n���W�����ɉ����o���h���̐��̏I�����W
			tktkMath::Vector2	selfExtrudePos		{ tktkMath::Vector2_v::zero };

			// �����o���Ɏg�p�����|���S���̕ӂ��\������P�ڂ̒��_���W
			tktkMath::Vector2	hitLineFirstVert	{ tktkMath::Vector2_v::zero };

			// �����o���Ɏg�p�����|���S���̕ӂ��\������Q�ڂ̒��_���W
			tktkMath::Vector2	hitLineSecondVert	{ tktkMath::Vector2_v::zero };
		};

		// �g�|���S���h���g���āg���h�̏Փ˔�����s��
		// ���Փ˔��茋�ʂ̌`�������ƈႤ
		static LinePolygonHitInfo lineCollisionWithPolygon(const tktkMath::Vector2& firstPos, const tktkMath::Vector2& secondPos, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& otherWorldMatrix);


	public:

		// �g�~�h���g���āg�~�h�̏Փ˔�����s��
		static HitInfo2D circleCollisionWithCircle(const BoundingCircle& selfBody,		const BoundingCircle& otherBody,	const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// �g�|���S���h���g���āg�|���S���h�̏Փ˔�����s��
		static HitInfo2D polygonCollisionWithPolygon(const BoundingPolygon2D& selfBody,	const BoundingPolygon2D& otherBody,	const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// �g�|���S���h���g���āg�~�h�̏Փ˔�����s��
		static HitInfo2D circleCollisionWithPolygon(const BoundingCircle& selfBody,		const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// �g�~�h���g���āg�|���S���h�̏Փ˔�����s��
		static HitInfo2D polygonCollisionWithCircle(const BoundingPolygon2D& selfBody,	const BoundingCircle& otherBody,	const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);
	};
}
#endif // !COLLISION_SUPPORT_2D_H_