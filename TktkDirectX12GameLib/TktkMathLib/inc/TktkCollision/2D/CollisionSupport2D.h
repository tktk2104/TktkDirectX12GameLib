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

		// ƒ|ƒŠƒSƒ“‚Æƒ|ƒŠƒSƒ“‚Ì“–‚½‚è”»’è
		static bool collidePolygonToPolygon(const BoundingPolygon2D& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// ‰~‚Æƒ|ƒŠƒSƒ“‚Ì“–‚½‚è”»’è
		static bool collideCircleToPolygon(const BoundingCircle& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// ƒ|ƒŠƒSƒ“‚Æ“_‚Ì“–‚½‚è”»’è
		static bool collidePolygonToPoint(const BoundingPolygon2D& selfBody, const tktkMath::Vector2& otherPoint, const tktkMath::Matrix3& selfWorldMatrix);
	
	public:

		struct LineCrossCheckResult
		{
			// ü•ª‚ªŒğ·‚µ‚Ä‚¢‚é‚©H
			bool isHit{ false };

			// “ñ‚Â‚Ìü‚ÌŒğ·“_
			tktkMath::Vector2 crossPos{ tktkMath::Vector2_v::zero };
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
			bool				isHit				{ false };

			// Õ“Ëgüh‚ğgü‚ÌI—¹À•W‚ğŠî€‚ÉŠJnÀ•W•ûŒü‚É‰Ÿ‚µo‚·h‚Ìü‚ÌI—¹À•W
			tktkMath::Vector2	selfExtrudePos		{ tktkMath::Vector2_v::zero };

			// ‰Ÿ‚µo‚µ‚Ég—p‚µ‚½ƒ|ƒŠƒSƒ“‚Ì•Ó‚ğ\¬‚·‚é‚P‚Â–Ú‚Ì’¸“_À•W
			tktkMath::Vector2	hitLineFirstVert	{ tktkMath::Vector2_v::zero };

			// ‰Ÿ‚µo‚µ‚Ég—p‚µ‚½ƒ|ƒŠƒSƒ“‚Ì•Ó‚ğ\¬‚·‚é‚Q‚Â–Ú‚Ì’¸“_À•W
			tktkMath::Vector2	hitLineSecondVert	{ tktkMath::Vector2_v::zero };
		};

		// gƒ|ƒŠƒSƒ“h‚ğg‚Á‚Ägüh‚ÌÕ“Ë”»’è‚ğs‚¤
		// ¦Õ“Ë”»’èŒ‹‰Ê‚ÌŒ`®‚ª‘¼‚Æˆá‚¤
		static LinePolygonHitInfo lineCollisionWithPolygon(const tktkMath::Vector2& firstPos, const tktkMath::Vector2& secondPos, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& otherWorldMatrix);


	public:

		// g‰~h‚ğg‚Á‚Äg‰~h‚ÌÕ“Ë”»’è‚ğs‚¤
		static HitInfo2D circleCollisionWithCircle(const BoundingCircle& selfBody,		const BoundingCircle& otherBody,	const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// gƒ|ƒŠƒSƒ“h‚ğg‚Á‚Ägƒ|ƒŠƒSƒ“h‚ÌÕ“Ë”»’è‚ğs‚¤
		static HitInfo2D polygonCollisionWithPolygon(const BoundingPolygon2D& selfBody,	const BoundingPolygon2D& otherBody,	const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// gƒ|ƒŠƒSƒ“h‚ğg‚Á‚Äg‰~h‚ÌÕ“Ë”»’è‚ğs‚¤
		static HitInfo2D circleCollisionWithPolygon(const BoundingCircle& selfBody,		const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// g‰~h‚ğg‚Á‚Ägƒ|ƒŠƒSƒ“h‚ÌÕ“Ë”»’è‚ğs‚¤
		static HitInfo2D polygonCollisionWithCircle(const BoundingPolygon2D& selfBody,	const BoundingCircle& otherBody,	const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);
	};
}
#endif // !COLLISION_SUPPORT_2D_H_