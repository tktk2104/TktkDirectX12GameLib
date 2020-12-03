#ifndef POLYGON_2D_COLLIDER_H_
#define POLYGON_2D_COLLIDER_H_

/* std::forward_list */
#include <forward_list>

/* std::vector */
#include <vector>

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>

/* class member */
#include <TktkCollision/2D/BoundingPolygon2D.h>

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	/* class member */
	class Transform2D;
	class InertialMovement2D;

	// ���p�`�̓����蔻��̃R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class Polygon2dCollider
		: public ComponentBase
	{
	public:

		Polygon2dCollider(
			CollisionGroupTypeCarrier collisionGroupType,	// �����蔻��̃O���[�v�ԍ�
			const std::vector<tktkMath::Vector2>& vertexs,	// �����蔻����\�����钸�_�̍��W�i���v���j
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
		const tktkCollision::BoundingPolygon2D& getBoundingPolygon2d() const;

		// �Փˑ���������o���������s�����H
		bool isExtrud() const;

		// �����o����₷�����擾
		float getExtrudedRate() const;

		// ���W�Ǘ��R���|�[�l���g���擾
		const ComponentPtr<Transform2D>& getTransform() const;

	private:

		// ���g�̉����o������
		void extrusion();

	private:

		struct HitInfo
		{
			GameObjectPtr				otherObject;

			bool						isExtrude;

			float						otherExtrudedRate;

			tktkCollision::HitInfo2D	hitInfo;
		};

	private:

		// �Q�����|���S���̏Փ˔���N���X
		tktkCollision::BoundingPolygon2D	m_boundingPolygon2d;

		// �Փˑ���������o���������s�����H
		bool								m_isExtrude;

		// �����o����₷���i�����j
		float								m_extrudedRate;

		// �Փˑ���ƏՓˌ��ʂ�ێ����郊�X�g
		std::forward_list<HitInfo>			m_hitInfo2dPairList;

		// ���g�̂Q�������W�R���|�[�l���g
		ComponentPtr<Transform2D>			m_transform2D;

		// ���g�̂Q���������ړ��R���|�[�l���g
		ComponentPtr<InertialMovement2D>	m_inertialMovement2D;
	};
}
#endif // !POLYGON_2D_COLLIDER_H_