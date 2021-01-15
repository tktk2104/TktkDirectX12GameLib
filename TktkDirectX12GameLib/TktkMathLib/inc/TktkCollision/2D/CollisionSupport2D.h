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
			// ü•ª‚ªŒğ·‚µ‚Ä‚¢‚é‚©H
			bool isHit					{ false };

			// “ñ‚Â‚Ìü‚ÌŒğ·“_
			tktkMath::Vector2 crossPos	{ tktkMath::Vector2_v::zero };
		};

		// ‚Q‚Â‚Ìü•ª‚ªŒğ·‚µ‚Ä‚¢‚é‚©‚ÆA‚Q‚Â‚Ìü‚ÌŒğ·“_‚ğŒvZ‚·‚é
		// Œğ·”»’è‚Íü•ªAŒğ·“_”»’è‚Í’¼ü‚Æ‚µ‚ÄŒvZ‚µ‚Ä‚¢‚é
		static LineCrossCheckResult lineCrossCheck(
			const tktkMath::Vector2& firstLinePosOne,
			const tktkMath::Vector2& firstLinePosTwo,
			const tktkMath::Vector2& secondLinePosOne,
			const tktkMath::Vector2& secondLinePosTwo
		);

	public:

		struct LinePolygonHitInfo
		{
			// Õ“Ë‚µ‚½‚©‚Ç‚¤‚©H
			bool							isHit			{ false };

			// ƒ|ƒŠƒSƒ“‚Æü•ª‚ÌŒğ·“_‚Ì”z—ñ
			std::vector<tktkMath::Vector2>	crossPosArray;
		};

		// gƒ|ƒŠƒSƒ“h‚ğg‚Á‚Ägüh‚ÌÕ“Ë”»’è‚ğs‚¤
		// ¦Õ“Ë”»’èŒ‹‰Ê‚ÌŒ`®‚ª‘¼‚Æˆá‚¤
		static LinePolygonHitInfo lineCollisionWithPolygon(const tktkMath::Vector2& firstPos, const tktkMath::Vector2& secondPos, const std::vector<tktkMath::Vector2>& otherVertexs);

	public:

		// g‰~h‚ğg‚Á‚Äg‰~h‚ÌÕ“Ë”»’è‚ğs‚¤
		static HitInfo2D circleCollisionWithCircle(const tktkMath::Vector2& selfCenterPos, float selfRadius, const tktkMath::Vector2& otherCenterPos, float otherRadius);

		// gƒ|ƒŠƒSƒ“h‚ğg‚Á‚Ägƒ|ƒŠƒSƒ“h‚ÌÕ“Ë”»’è‚ğs‚¤
		static HitInfo2D polygonCollisionWithPolygon(const std::vector<tktkMath::Vector2>& selfVertexs, const std::vector<tktkMath::Vector2>& otherVertexs);

		// gƒ|ƒŠƒSƒ“h‚ğg‚Á‚Äg‰~h‚ÌÕ“Ë”»’è‚ğs‚¤
		static HitInfo2D circleCollisionWithPolygon(const tktkMath::Vector2& selfCenterPos, float selfRadius, const std::vector<tktkMath::Vector2>& otherVertexs);

		// g‰~h‚ğg‚Á‚Ägƒ|ƒŠƒSƒ“h‚ÌÕ“Ë”»’è‚ğs‚¤
		static HitInfo2D polygonCollisionWithCircle(const std::vector<tktkMath::Vector2>& selfVertexs, const tktkMath::Vector2& otherCenterPos, float otherRadius);
	};
}
#endif // !COLLISION_SUPPORT_2D_H_