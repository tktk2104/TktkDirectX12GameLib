#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

#include "Body3DTypeChecker.h"
#include "CollisionSupport3D.h"

namespace tktkCollision
{
	// ����
	// �����A���̃X�P�[���l�͖��������
	class BoundingSphere
	{
	public:

		BoundingSphere(float radius, const tktkMath::Vector3& centerPosition);

	public:

		// ���̂Ƃ̏Փ˔��菈��
		template <class OtherBody3DType, is_BoundingSphere<OtherBody3DType> = nullptr>
		HitInfo3D isCollide(const OtherBody3DType& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix) const;

		// ���b�V���Ƃ̏Փ˔��菈��
		template <class OtherBody3DType, is_BoundingMesh<OtherBody3DType> = nullptr>
		HitInfo3D isCollide(const OtherBody3DType& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix) const;

	public:

		// ���a���擾
		float getRadius() const;

		// ���S���W���擾
		const tktkMath::Vector3& getCenterPosition() const;

	public:

		// ���̃N���X�����̂̏Փ˔���ł��鎖�̏ؖ�
		static constexpr Body3DType ShapeType{ Body3DType::Sphere };

	private:

		// ���̂̔��a
		float				m_radius;

		// ���̂̒��S���W
		tktkMath::Vector3	m_centerPosition;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�̓e���v���[�g�֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// ���̂Ƃ̏Փ˔��菈��
	template<class OtherBody3DType, is_BoundingSphere<OtherBody3DType>>
	inline HitInfo3D BoundingSphere::isCollide(const OtherBody3DType& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix) const
	{
		return CollisionSupport3D::sphereCollisionWithSphere(*this, otherBody, selfWorldMatrix, otherWorldMatrix);
	}
	
	// ���b�V���Ƃ̏Փ˔��菈��
	template<class OtherBody3DType, is_BoundingMesh<OtherBody3DType>>
	inline HitInfo3D BoundingSphere::isCollide(const OtherBody3DType& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix) const
	{
		return CollisionSupport3D::sphereCollisionWithMesh(*this, otherBody, selfWorldMatrix, otherWorldMatrix);
	}
}
#endif // !BOUNDING_SPHERE_H_