#ifndef BOX_COLLIDER_H_
#define BOX_COLLIDER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* class member */
#include <TktkCollision/3D/BoundingMesh.h>

namespace tktk
{
	/* class member */
	class Transform3D;
	class InertialMovement3D;

	// OBB�̓����蔻��̃R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform3D�z
	class BoxCollider
		: public ComponentBase
	{
	public:

		BoxCollider(
			CollisionGroupTypeCarrier collisionGroupType,	// �����蔻��̃O���[�v�ԍ�
			const tktkMath::Vector3& boxSize,				// �����蔻��̑傫��
			const tktkMath::Vector3& localPosition,			// �����蔻��̃��[�J�����W
			bool isExtrude,									// �Փˑ���������o���������s�����H
			float extrudedRate								// �����o����₷���i�����j
		);

	public:

		// <PolymorphismFunc>
		void start();
		bool isCollide(const ComponentBasePtr& other);
		void afterCollide();

	public:

		// �����蔻��̃N���X���擾
		const tktkCollision::BoundingMesh& getBoundingMesh() const;

		// �Փˑ���������o���������s�����H
		bool isExtrud() const;

		// �����o����₷�����擾
		float getExtrudedRate() const;

		// ���W�Ǘ��R���|�[�l���g���擾
		const ComponentPtr<Transform3D>& getTransform() const;

		// TODO : �R���������`��R���|�[�l���g������Ă��̊֐���s�v�ɂ���
		const std::vector<tktkMath::Vector3>& getTempVerts() const;

	private:

		// ���g�̉����o������
		void extrusion();

	private:

		struct HitInfo
		{
			GameObjectPtr				otherObject;

			bool						isExtrude;

			float						otherExtrudedRate;

			tktkCollision::HitInfo3D	hitInfo;
		};

	private:

		// TODO : �R���������`��R���|�[�l���g������Ă��̕ϐ���s�v�ɂ���
		std::vector<tktkMath::Vector3> m_tempVerts;

		// AABB�̏Փ˔���N���X
		tktkCollision::BoundingMesh			m_boundingMesh;

		// �Փˑ���������o���������s�����H
		bool								m_isExtrude;

		// �����o����₷���i�����j
		float								m_extrudedRate;

		// �Փˑ���ƏՓˌ��ʂ�ێ����郊�X�g
		std::forward_list<HitInfo>			m_hitInfo3dPairList;

		// ���g�̂R�������W�R���|�[�l���g
		ComponentPtr<Transform3D>			m_transform3D;

		// ���g�̂R���������ړ��R���|�[�l���g
		ComponentPtr<InertialMovement3D>	m_inertialMovement3D;
	};
}
#endif // !BOX_COLLIDER_H_