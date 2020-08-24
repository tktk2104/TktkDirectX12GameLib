#include "TktkCollision/3D/Body3dBase/CollisionSupport3D.h"

#include "TktkCollision/3D/BoundingSphere.h"
#include "TktkCollision/3D/AxisAlignedBoundingBox.h"

namespace tktkCollision
{
	bool CollisionSupport3D::collideSphereToSphere(const Body3dBase& self, const Body3dBase& other, HitInfo3D* hitinfo)
	{
		const BoundingSphere& selfSphere = dynamic_cast<const BoundingSphere&>(self);
		const BoundingSphere& otherSphere = dynamic_cast<const BoundingSphere&>(other);

		tktkMath::Vector3 selfCenterPos = selfSphere.calculatePose().calculateTranslation();
		tktkMath::Vector3 otherCenterPos = otherSphere.calculatePose().calculateTranslation();

		float selfRadius = selfSphere.calculateRadius();
		float otherRadius = otherSphere.calculateRadius();

		tktkMath::Vector3 selfToOtherDirection = tktkMath::Vector3::normalize(selfCenterPos - otherCenterPos);
		tktkMath::Vector3 otherToSelfDirection = tktkMath::Vector3::normalize(otherCenterPos - selfCenterPos);

		hitinfo->selfPointClosestToOther = selfCenterPos + (selfToOtherDirection * otherRadius);
		hitinfo->otherPointClosestToSelf = otherCenterPos + (otherToSelfDirection * selfRadius);

		hitinfo->isHit = (tktkMath::Vector3::distance(selfCenterPos, otherCenterPos) < selfRadius + otherRadius);

		return hitinfo->isHit;
	}

	bool CollisionSupport3D::collideAabbToAabb(const Body3dBase& self, const Body3dBase& other, HitInfo3D* hitinfo)
	{
		const AxisAlignedBoundingBox& selfAABB = dynamic_cast<const AxisAlignedBoundingBox&>(self);
		const AxisAlignedBoundingBox& otherAABB = dynamic_cast<const AxisAlignedBoundingBox&>(other);

		tktkMath::Vector3 seltCenterPos = selfAABB.calculatePose().calculateTranslation();
		tktkMath::Vector3 otherCenterPos = otherAABB.calculatePose().calculateTranslation();

		tktkMath::Vector3 selfMin = selfAABB.calculateCornerPoint(AxisAlignedBoundingBox::CornerType::Min);
		tktkMath::Vector3 selfMax = selfAABB.calculateCornerPoint(AxisAlignedBoundingBox::CornerType::Max);

		tktkMath::Vector3 otherMin = otherAABB.calculateCornerPoint(AxisAlignedBoundingBox::CornerType::Min);
		tktkMath::Vector3 otherMax = otherAABB.calculateCornerPoint(AxisAlignedBoundingBox::CornerType::Max);

		hitinfo->selfPointClosestToOther = tktkMath::Vector3::clamp(
			seltCenterPos, otherMin, otherMax
		);

		hitinfo->otherPointClosestToSelf = tktkMath::Vector3::clamp(
			otherCenterPos, selfMin, selfMax
		);

		bool selfMinPosXCheck = selfMin.x < otherMax.x;
		bool selfMinPosYCheck = selfMin.y < otherMax.y;
		bool selfMinPosZCheck = selfMin.z < otherMax.z;

		bool selfMaxPosXCheck = selfMax.x > otherMin.x;
		bool selfMaxPosYCheck = selfMax.y > otherMin.y;
		bool selfMaxPosZCheck = selfMax.z > otherMin.z;

		// bool‚Ìà–¾•Ï”‚ðŽg‚í‚¸‚É”»’è‚µ‚½•û‚ª”äŠr‚Ìˆ—‚ªŒ¸‚éiŒë·‚Ì”ÍˆÍ“àj
		hitinfo->isHit = (
			selfMinPosXCheck &&
			selfMinPosYCheck &&
			selfMinPosZCheck &&
			selfMaxPosXCheck &&
			selfMaxPosYCheck &&
			selfMaxPosZCheck
			);

		return hitinfo->isHit;
	}

	bool CollisionSupport3D::collideSphereToAabb(const Body3dBase& self, const Body3dBase& other, HitInfo3D* hitinfo)
	{
		const BoundingSphere& selfSphere = dynamic_cast<const BoundingSphere&>(self);
		const AxisAlignedBoundingBox& otherAABB = dynamic_cast<const AxisAlignedBoundingBox&>(other);

		tktkMath::Vector3 selfCenterPos = selfSphere.calculatePose().calculateTranslation();
		tktkMath::Vector3 otherCenterPos = otherAABB.calculatePose().calculateTranslation();

		tktkMath::Vector3 otherMin = otherAABB.calculateCornerPoint(AxisAlignedBoundingBox::CornerType::Min);
		tktkMath::Vector3 otherMax = otherAABB.calculateCornerPoint(AxisAlignedBoundingBox::CornerType::Max);

		hitinfo->selfPointClosestToOther = tktkMath::Vector3::clamp(
			selfCenterPos, otherMin, otherMax
		);

		float selfRadius = selfSphere.calculateRadius();

		tktkMath::Vector3 otherToSelfDirection = tktkMath::Vector3::normalize(otherCenterPos - selfCenterPos);

		hitinfo->otherPointClosestToSelf = otherCenterPos + (otherToSelfDirection * selfRadius);

		hitinfo->isHit = (tktkMath::Vector3::distance(selfCenterPos, hitinfo->selfPointClosestToOther) < selfRadius);

		return hitinfo->isHit;
	}

	bool CollisionSupport3D::collideAabbToSphere(const Body3dBase& self, const Body3dBase& other, HitInfo3D* hitinfo)
	{
		bool result = collideSphereToAabb(other, self, hitinfo);

		auto tempSelfPoint = hitinfo->selfPointClosestToOther;
		hitinfo->selfPointClosestToOther = hitinfo->otherPointClosestToSelf;
		hitinfo->otherPointClosestToSelf = tempSelfPoint;

		return result;
	}
}