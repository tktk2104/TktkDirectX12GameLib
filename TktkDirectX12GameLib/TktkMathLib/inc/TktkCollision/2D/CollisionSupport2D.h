#ifndef COLLISION_SUPPORT_2D_H_
#define COLLISION_SUPPORT_2D_H_

#include <vector>
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

		struct LineCrossCheckResult
		{
			// �������������Ă��邩�H
			bool isHit					{ false };

			// ��̐��̌����_
			tktkMath::Vector2 crossPos	{ tktkMath::Vector2_v::zero };
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
			bool							isHit			{ false };

			// �|���S���Ɛ����̌����_�̔z��
			std::vector<tktkMath::Vector2>	crossPosArray;
		};

		// �g�|���S���h���g���āg���h�̏Փ˔�����s��
		// ���Փ˔��茋�ʂ̌`�������ƈႤ
		static LinePolygonHitInfo lineCollisionWithPolygon(const tktkMath::Vector2& firstPos, const tktkMath::Vector2& secondPos, const std::vector<tktkMath::Vector2>& otherVertexs);

	public:

		// �g�~�h���g���āg�~�h�̏Փ˔�����s��
		static HitInfo2D circleCollisionWithCircle(const tktkMath::Vector2& selfCenterPos, float selfRadius, const tktkMath::Vector2& otherCenterPos, float otherRadius);

		// �g�|���S���h���g���āg�|���S���h�̏Փ˔�����s��
		static HitInfo2D polygonCollisionWithPolygon(const std::vector<tktkMath::Vector2>& selfVertexs, const std::vector<tktkMath::Vector2>& otherVertexs);

		// �g�|���S���h���g���āg�~�h�̏Փ˔�����s��
		static HitInfo2D circleCollisionWithPolygon(const tktkMath::Vector2& selfCenterPos, float selfRadius, const std::vector<tktkMath::Vector2>& otherVertexs);

		// �g�~�h���g���āg�|���S���h�̏Փ˔�����s��
		static HitInfo2D polygonCollisionWithCircle(const std::vector<tktkMath::Vector2>& selfVertexs, const tktkMath::Vector2& otherCenterPos, float otherRadius);
	};
}
#endif // !COLLISION_SUPPORT_2D_H_