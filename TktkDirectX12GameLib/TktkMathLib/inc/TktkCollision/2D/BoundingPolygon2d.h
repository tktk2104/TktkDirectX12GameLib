#ifndef BOUNDING_POLYGON_2D_H_
#define BOUNDING_POLYGON_2D_H_

#include <vector>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix3.h>
#include "Body2DTypeChecker.h"
#include "CollisionSupport2D.h"

namespace tktkCollision
{
	class BoundingPolygon2D
	{
	public:

		explicit BoundingPolygon2D(const std::vector<tktkMath::Vector2>& vertexs);

	public:

		// �����̃��[���h�s��ō��W�ϊ�����
		void transform(const tktkMath::Matrix3& worldMatrix);

		// �~�Ƃ̏Փ˔��菈��
		template <class OtherBody2DType, is_BoundingCircle<OtherBody2DType>		= nullptr>
		HitInfo2D isCollide(const OtherBody2DType& otherBody) const;

		// �񎟌��|���S���Ƃ̏Փ˔��菈��
		template <class OtherBody2DType, is_BoundingPolygon2d<OtherBody2DType> = nullptr>
		HitInfo2D isCollide(const OtherBody2DType& otherBody) const;

	public:

		const std::vector<tktkMath::Vector2>& getVertexs() const;

		const std::vector<tktkMath::Vector2>& getTransformedVertexs() const;

	public:

		// ���̃N���X���񎟌��|���S���̏Փ˔���ł��鎖�̏ؖ�
		static constexpr Body2DType ShapeType{ Body2DType::Polygon };

	private:

		// �|���S�����\�����钸�_
		std::vector<tktkMath::Vector2> m_baseVertexs;

		// ���[���h��Ԃō��W�ϊ���̃|���S�����\�����钸�_
		std::vector<tktkMath::Vector2> m_transformedVertexs;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�̓e���v���[�g�֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �~�Ƃ̏Փ˔��菈��
	template<class OtherBody2DType, is_BoundingCircle<OtherBody2DType>>
	inline HitInfo2D BoundingPolygon2D::isCollide(const OtherBody2DType& otherBody) const
	{
		return CollisionSupport2D::polygonCollisionWithCircle(m_transformedVertexs, otherBody.getTransformedCenterPosition(), otherBody.getTransformedRadius());
	}

	// �񎟌��|���S���Ƃ̏Փ˔��菈��
	template<class OtherBody2DType, is_BoundingPolygon2d<OtherBody2DType>>
	inline HitInfo2D BoundingPolygon2D::isCollide(const OtherBody2DType& otherBody) const
	{
		return CollisionSupport2D::polygonCollisionWithPolygon(m_transformedVertexs, otherBody.m_transformedVertexs);
	}
}
#endif // !BOUNDING_POLYGON_2D_H_