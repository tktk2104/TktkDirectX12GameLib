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

		// �����̃��[���h�s��ō��W�ϊ�����
		void transform(const tktkMath::Matrix4& worldMatrix);

		// ���̂Ƃ̏Փ˔��菈��
		template <class OtherBody3DType, is_BoundingSphere<OtherBody3DType> = nullptr>
		HitInfo3D isCollide(const OtherBody3DType& otherBody) const;

		// ���b�V���Ƃ̏Փ˔��菈��
		template <class OtherBody3DType, is_BoundingMesh<OtherBody3DType> = nullptr>
		HitInfo3D isCollide(const OtherBody3DType& otherBody) const;

	public:

		// ���a���擾
		float getBaseRadius() const;

		// ���S���W���擾
		const tktkMath::Vector3& getBaseCenterPosition() const;

		// ���[���h��Ԃō��W�ϊ���̔��a���擾
		float getTransformedRadius() const;

		// ���[���h��Ԃō��W�ϊ���̒��S���W���擾
		const tktkMath::Vector3& getTransformedCenterPosition() const;

	public:

		// ���̃N���X�����̂̏Փ˔���ł��鎖�̏ؖ�
		static constexpr Body3DType ShapeType{ Body3DType::Sphere };

	private:

		// ���̂̔��a
		float				m_baseRadius;

		// ���̂̒��S���W
		tktkMath::Vector3	m_baseCenterPosition;

		// ���̂̔��a
		float				m_transformedRadius;

		// ���̂̒��S���W
		tktkMath::Vector3	m_transformedCenterPosition;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�̓e���v���[�g�֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// ���̂Ƃ̏Փ˔��菈��
	template<class OtherBody3DType, is_BoundingSphere<OtherBody3DType>>
	inline HitInfo3D BoundingSphere::isCollide(const OtherBody3DType& otherBody) const
	{
		return CollisionSupport3D::sphereCollisionWithSphere(m_transformedCenterPosition, m_transformedRadius, otherBody.m_transformedCenterPosition, otherBody.m_transformedRadius);
	}
	
	// ���b�V���Ƃ̏Փ˔��菈��
	template<class OtherBody3DType, is_BoundingMesh<OtherBody3DType>>
	inline HitInfo3D BoundingSphere::isCollide(const OtherBody3DType& otherBody) const
	{
		return CollisionSupport3D::sphereCollisionWithMesh(m_transformedCenterPosition, m_transformedRadius, otherBody.getTransformedPolygonVertex());
	}
}
#endif // !BOUNDING_SPHERE_H_