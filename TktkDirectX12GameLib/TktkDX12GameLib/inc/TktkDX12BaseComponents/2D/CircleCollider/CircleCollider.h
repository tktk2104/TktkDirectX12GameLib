#ifndef CIRCLE_COLLIDER_H_
#define CIRCLE_COLLIDER_H_

/* std::forward_list */
#include <forward_list>

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>

/* class member */
#include <TktkCollision/2D/BoundingCircle.h>

/* baseClass */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	/* class member */
	class Transform2D;
	class InertialMovement2D;

	// �^�~�̓����蔻��̃R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class CircleCollider
		: public ComponentBase
	{
	public:

		CircleCollider(
			CollisionGroupTypeCarrier collisionGroupType,	// �����蔻��̃O���[�v�ԍ�
			float radius,									// �����蔻��̔��a
			const tktkMath::Vector2& localPosition,			// �����蔻��̃��[�J�����W
			bool isExtrude,									// �Փˑ���������o���������s�����H
			float extrudedRate								// �����o����₷���i�����j
		);

	public:

		// <PolymorphismFunc>
		void start();
		void beforeCollide();
		bool isCollide(const ComponentBasePtr& other);
		void afterCollide();

	public:

		// �����蔻��̃N���X���擾
		const tktkCollision::BoundingCircle& getBoundingCircle() const;

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

		// �~�̏Փ˔���N���X
		tktkCollision::BoundingCircle		m_boundingCircle;

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
#endif // !CIRCLE_COLLIDER_H_