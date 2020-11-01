#ifndef BOUNDING_MESH_H_
#define BOUNDING_MESH_H_

#include <vector>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "Body3DTypeChecker.h"
#include "CollisionSupport3D.h"

namespace tktkCollision
{
	class BoundingMesh
	{
	public:

		BoundingMesh(const std::vector<std::vector<tktkMath::Vector3>>& mesh, const tktkMath::Vector3& centerPos);

	public:

		// ���̂Ƃ̏Փ˔��菈��
		template <class OtherBody3DType, is_BoundingSphere<OtherBody3DType> = nullptr>
		HitInfo3D isCollide(const OtherBody3DType& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix) const;

		// ���b�V���Ƃ̏Փ˔��菈��
		template <class OtherBody3DType, is_BoundingMesh<OtherBody3DType> = nullptr>
		HitInfo3D isCollide(const OtherBody3DType& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix) const;

	public:

		const std::vector<std::vector<tktkMath::Vector3>>& getVertexs() const;

	public:

		// ���̃N���X�����b�V���̏Փ˔���ł��鎖�̏ؖ�
		static constexpr Body3DType ShapeType{ Body3DType::Mesh };

	private:

		// ���b�V�����\������|���S���ƁA������\�����钸�_
		std::vector<std::vector<tktkMath::Vector3>> m_mesh;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�̓e���v���[�g�֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// ���̂Ƃ̏Փ˔��菈��
	template<class OtherBody3DType, is_BoundingSphere<OtherBody3DType>>
	inline HitInfo3D BoundingMesh::isCollide(const OtherBody3DType& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix) const
	{
		return CollisionSupport3D::meshCollisionWithSphere(*this, otherBody, selfWorldMatrix, otherWorldMatrix);
	}

	// ���b�V���Ƃ̏Փ˔��菈��
	template<class OtherBody3DType, is_BoundingMesh<OtherBody3DType>>
	inline HitInfo3D BoundingMesh::isCollide(const OtherBody3DType& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix) const
	{
		return CollisionSupport3D::meshCollisionWithMesh(*this, otherBody, selfWorldMatrix, otherWorldMatrix);
	}
}
#endif // !BOUNDING_MESH_H_