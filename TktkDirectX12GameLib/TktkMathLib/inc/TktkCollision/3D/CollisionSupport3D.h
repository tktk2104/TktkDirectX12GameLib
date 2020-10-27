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
			// �|���S���Ɛ������g�Փˁh�������ǂ����H
			bool				isHit				{ false };

			// �|���S���́g�����ʏ�Ɂh�������g�Փˁh�������ǂ����H
			bool				isExtensionPolyHit	{ false };

			// �|���S���́g�ӏ�Ɂh�������g�Փˁh�������ǂ����H
			bool				isPolyEdgeHit		{ false };

			// �|���S���́g�����ʏ�Ɂh�������g�����h�������ǂ����H
			bool				isExtensionPolyCross{ false };

			// ���ƃ|���S���̏Փ˓_
			tktkMath::Vector3	hitPos				{ tktkMath::Vector3_v::zero };
		};

		// �g�|���S���h���g���āg���h�̏Փ˔�����s��
		// ���Փ˔��茋�ʂ̌`�������ƈႤ
		static LinePolygonHitInfo lineCollisionWithPolygon(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const std::vector<tktkMath::Vector3>& otherPolygon);

	public:

		// �g���b�V���h���g���āg�_�h�̏Փ˔�����s��
		// ���Փ˔��茋�ʂ̌`�������ƈႤ
		static bool pointCollisionWithMesh(const tktkMath::Vector3& point, const BoundingMesh& otherBody, const tktkMath::Matrix4& otherWorldMatrix);

	public:

		// ���ƃ|���S���̏Փˏ��
		struct LinePolyHitData
		{
			// ���ƃ|���S�����������Ă��邩�H
			bool								isCross			{ false };

			// ���ƃ|���S���̕ӂ��Փ˂��Ă��邩�H
			bool								isPolyEdgeHit	{ false };

			// ���ƃ|���S���̏Փ˓_
			tktkMath::Vector3					hitPos			{ tktkMath::Vector3_v::zero };

			// ���������|���S���̒��_
			std::vector<tktkMath::Vector3>		polyVert		{};
		};

		struct LineMeshHitInfo
		{
			// �Փ˂������ǂ����H
			bool								isHit{ false };

			// ���ƃ��b�V���̌����_�i��{�P�����A�����ђʂ��Ă����肷��ƕ����̌��ʂƂȂ�j
			std::vector<LinePolyHitData>		linePolyCrossDataArray;
		};

		// �g���b�V���h���g���āg���h�̏Փ˔�����s��
		// ���Փ˔��茋�ʂ̌`�������ƈႤ
		static LineMeshHitInfo lineCollisionWithMesh(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const BoundingMesh& otherBody, const tktkMath::Matrix4& otherWorldMatrix);

	public:

		// �g���b�V���h���g���āg�|���S���h�̏Փ˔�����s��
		static HitInfo3D polygonCollisionWithMesh(const std::vector<tktkMath::Vector3>& polygon, const BoundingMesh& otherBody, const tktkMath::Matrix4& otherWorldMatrix);

	public:

		// �g���́h���g���āg���́h�̏Փ˔�����s��
		static HitInfo3D sphereCollisionWithSphere(const BoundingSphere& selfBody, const BoundingSphere& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix);

		// �g���b�V���h���g���āg���b�V���h�̏Փ˔�����s��
		static HitInfo3D meshCollisionWithMesh(const BoundingMesh& selfBody, const BoundingMesh& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix);

		// �g���b�V���h���g���āg���́h�̏Փ˔�����s��
		static HitInfo3D sphereCollisionWithMesh(const BoundingSphere& selfBody, const BoundingMesh& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix);

		// �g���́h���g���āg���b�V���h�̏Փ˔�����s��
		static HitInfo3D meshCollisionWithSphere(const BoundingMesh& selfBody, const BoundingSphere& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix);
	};
}
#endif // !COLLISION_SUPPORT_3D_H_