#ifndef COLLISION_SUPPORT_3D_H_
#define COLLISION_SUPPORT_3D_H_

#include <array>
#include <vector>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "HitInfo3D.h"

namespace tktkCollision
{
	class BoundingSphere;
	class BoundingMesh;

	class CollisionSupport3D
	{
	public:

		struct LinePolygonHitInfo
		{
			// ƒ|ƒŠƒSƒ“‚Æü•ª‚ªgÕ“Ëh‚µ‚½‚©‚Ç‚¤‚©H
			bool				isHit				{ false };

			// ƒ|ƒŠƒSƒ“‚Ìg‰„’·–Êã‚Éhü•ª‚ªgÕ“Ëh‚µ‚½‚©‚Ç‚¤‚©H
			bool				isExtensionPolyHit	{ false };

			// ƒ|ƒŠƒSƒ“‚Ìg•Óã‚Éhü•ª‚ªgÕ“Ëh‚µ‚½‚©‚Ç‚¤‚©H
			bool				isPolyEdgeHit		{ false };

			// ƒ|ƒŠƒSƒ“‚Ìg‰„’·–Êã‚Éhü•ª‚ªgŒğ·h‚µ‚½‚©‚Ç‚¤‚©H
			bool				isExtensionPolyCross{ false };

			// ü‚Æƒ|ƒŠƒSƒ“‚ÌÕ“Ë“_
			tktkMath::Vector3	hitPos				{ tktkMath::Vector3_v::zero };
		};

		// gƒ|ƒŠƒSƒ“h‚ğg‚Á‚Ägüh‚ÌÕ“Ë”»’è‚ğs‚¤
		// ¦Õ“Ë”»’èŒ‹‰Ê‚ÌŒ`®‚ª‘¼‚Æˆá‚¤
		static LinePolygonHitInfo lineCollisionWithPolygon(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const std::vector<tktkMath::Vector3>& otherPolygon);

	public:

		// gƒƒbƒVƒ…h‚ğg‚Á‚Äg“_h‚ÌÕ“Ë”»’è‚ğs‚¤
		// ¦Õ“Ë”»’èŒ‹‰Ê‚ÌŒ`®‚ª‘¼‚Æˆá‚¤
		static bool pointCollisionWithMesh(const tktkMath::Vector3& point, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh);

	public:

		// ü‚Æƒ|ƒŠƒSƒ“‚ÌÕ“Ëî•ñ
		struct LinePolyHitData
		{
			// ü‚Æƒ|ƒŠƒSƒ“‚ªŒğ·‚µ‚Ä‚¢‚é‚©H
			bool								isCross			{ false };

			// ü‚Æƒ|ƒŠƒSƒ“‚Ì•Ó‚ªÕ“Ë‚µ‚Ä‚¢‚é‚©H
			bool								isPolyEdgeHit	{ false };

			// ü‚Æƒ|ƒŠƒSƒ“‚ÌÕ“Ë“_
			tktkMath::Vector3					hitPos			{ tktkMath::Vector3_v::zero };

			// Œğ·‚µ‚½ƒ|ƒŠƒSƒ“‚Ì’¸“_
			std::vector<tktkMath::Vector3>		polyVert		{};
		};

		struct LineMeshHitInfo
		{
			// Õ“Ë‚µ‚½‚©‚Ç‚¤‚©H
			bool								isHit{ false };

			// ü‚ÆƒƒbƒVƒ…‚ÌŒğ·“_iŠî–{‚P‚Â‚¾‚ªAü‚ªŠÑ’Ê‚µ‚Ä‚¢‚½‚è‚·‚é‚Æ•¡”‚ÌŒ‹‰Ê‚Æ‚È‚éj
			std::vector<LinePolyHitData>		linePolyCrossDataArray;
		};

		// gƒƒbƒVƒ…h‚ğg‚Á‚Ägüh‚ÌÕ“Ë”»’è‚ğs‚¤
		// ¦Õ“Ë”»’èŒ‹‰Ê‚ÌŒ`®‚ª‘¼‚Æˆá‚¤
		static LineMeshHitInfo lineCollisionWithMesh(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh);

	public:

		// gƒƒbƒVƒ…h‚ğg‚Á‚Ägƒ|ƒŠƒSƒ“h‚ÌÕ“Ë”»’è‚ğs‚¤
		static HitInfo3D polygonCollisionWithMesh(const std::vector<tktkMath::Vector3>& polygon, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh);

	public:

		// g‹…‘Ìh‚ğg‚Á‚Äg‹…‘Ìh‚ÌÕ“Ë”»’è‚ğs‚¤
		static HitInfo3D sphereCollisionWithSphere(const tktkMath::Vector3& selfCenterPos, float selfRadius, const tktkMath::Vector3& otherCenterPos, float otherRadius);

		// gƒƒbƒVƒ…h‚ğg‚Á‚ÄgƒƒbƒVƒ…h‚ÌÕ“Ë”»’è‚ğs‚¤
		static HitInfo3D meshCollisionWithMesh(const std::vector<std::vector<tktkMath::Vector3>>& selfMesh, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh);

		// gƒƒbƒVƒ…h‚ğg‚Á‚Äg‹…‘Ìh‚ÌÕ“Ë”»’è‚ğs‚¤
		static HitInfo3D sphereCollisionWithMesh(const tktkMath::Vector3& selfCenterPos, float selfRadius, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh);

		// g‹…‘Ìh‚ğg‚Á‚ÄgƒƒbƒVƒ…h‚ÌÕ“Ë”»’è‚ğs‚¤
		static HitInfo3D meshCollisionWithSphere(const std::vector<std::vector<tktkMath::Vector3>>& selfMesh, const tktkMath::Vector3& otherCenterPos, float otherRadius);
	};
}
#endif // !COLLISION_SUPPORT_3D_H_