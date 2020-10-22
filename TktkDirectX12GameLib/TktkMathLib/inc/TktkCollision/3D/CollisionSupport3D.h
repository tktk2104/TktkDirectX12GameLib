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
			// �Փ˂������ǂ����H
			bool				isHit{ false };

			// ���ƃ|���S���̌����_
			tktkMath::Vector3	crossPos{ tktkMath::Vector3_v::zero };
		};

		// �g�|���S���h���g���āg���h�̏Փ˔�����s��
		// ���Փ˔��茋�ʂ̌`�������ƈႤ
		static LinePolygonHitInfo lineCollisionWithPolygon(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const std::array<tktkMath::Vector3, 3U>& otherVertexs);

	public:

		struct LineMeshHitInfo
		{
			// �Փ˂������ǂ����H
			bool								isHit{ false };

			// ���ƃ|���S���̌����_
			tktkMath::Vector3					crossPos{ tktkMath::Vector3_v::zero };

			// �����o���Ɏg�p�����|���S�����\�����钸�_���W
			std::array<tktkMath::Vector3, 3U>	otherVertexs{ tktkMath::Vector3_v::zero, tktkMath::Vector3_v::zero, tktkMath::Vector3_v::zero };
		};

		// �g���b�V���h���g���āg���h�̏Փ˔�����s��
		// ���Փ˔��茋�ʂ̌`�������ƈႤ
		static LineMeshHitInfo lineCollisionWithMesh(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const BoundingMesh& otherBody, const tktkMath::Matrix4& otherWorldMatrix);

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