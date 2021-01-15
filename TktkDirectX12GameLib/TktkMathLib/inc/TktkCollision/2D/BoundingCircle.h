#ifndef BOUNDING_CIRCLE_H_
#define BOUNDING_CIRCLE_H_

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix3.h>
#include "Body2DTypeChecker.h"
#include "CollisionSupport2D.h"

namespace tktkCollision
{
	// �~�̏Փ˔���̃N���X
	// �����̃X�P�[���l�͖��������
	class BoundingCircle
	{
	public:

		BoundingCircle(float radius, const tktkMath::Vector2& centerPosition);

	public:

		// �����̃��[���h�s��ō��W�ϊ�����
		void transform(const tktkMath::Matrix3& worldMatrix);

		// �~�Ƃ̏Փ˔��菈��
		template <class OtherBody2DType, is_BoundingCircle<OtherBody2DType>		= nullptr>
		HitInfo2D isCollide(const OtherBody2DType& otherBody) const;

		// �񎟌��|���S���Ƃ̏Փ˔��菈��
		template <class OtherBody2DType, is_BoundingPolygon2d<OtherBody2DType>	= nullptr>
		HitInfo2D isCollide(const OtherBody2DType& otherBody) const;

	public:

		// ���a���擾
		float getRadius() const;

		// ���S���W���擾
		const tktkMath::Vector2& getCenterPosition() const;

		// ���[���h��Ԃō��W�ϊ���̔��a���擾
		float getTransformedRadius() const;

		// ���[���h��Ԃō��W�ϊ���̒��S���W���擾
		const tktkMath::Vector2& getTransformedCenterPosition() const;

	public:

		// ���̃N���X���~�̏Փ˔���ł��鎖�̏ؖ�
		static constexpr Body2DType ShapeType{ Body2DType::Circle };

	private:

		// �~�̔��a
		float				m_baseRadius;

		// �~�̒��S���W
		tktkMath::Vector2	m_baseCenterPosition;

		// �~�̔��a
		float				m_transformedRadius;

		// �~�̒��S���W
		tktkMath::Vector2	m_transformedCenterPosition;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�̓e���v���[�g�֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �~�Ƃ̏Փ˔��菈��
	template<class OtherBody2DType, is_BoundingCircle<OtherBody2DType>>
	inline HitInfo2D BoundingCircle::isCollide(const OtherBody2DType& otherBody) const
	{
		return CollisionSupport2D::circleCollisionWithCircle(m_transformedCenterPosition, m_transformedRadius, otherBody.m_transformedCenterPosition, otherBody.m_transformedRadius);
	}

	// �񎟌��|���S���Ƃ̏Փ˔��菈��
	template<class OtherBody2DType, is_BoundingPolygon2d<OtherBody2DType>>
	inline HitInfo2D BoundingCircle::isCollide(const OtherBody2DType& otherBody) const
	{
		return CollisionSupport2D::circleCollisionWithPolygon(m_transformedCenterPosition, m_transformedRadius, otherBody.getTransformedVertexs());
	}
}
#endif // !BOUNDING_CIRCLE_H_