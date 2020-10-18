#ifndef CIRCLE_COLLIDER_H_
#define CIRCLE_COLLIDER_H_

#include <forward_list>
#include <TktkMath/Structs/Vector2.h>
#include <TktkCollision/2D/BoundingCircle.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform2D/Transform2D.h"

namespace tktk
{
	// �^�~�̓����蔻��̃R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class CircleCollider
		: public ComponentBase
	{
	public:

		CircleCollider(
			int collisionGroupType,					// �����蔻��̃O���[�v�ԍ�
			float radius,							// �����蔻��̔��a
			const tktkMath::Vector2& localPosition,	// �����蔻��̃��[�J�����W
			float extrudedRate						// �����o����₷���i�����j
		);

	public:

		// <PolymorphismFunc>
		void start();
		bool isCollide(const ComponentBasePtr& other);
		void afterCollide();

	public:

		// �����蔻��̃N���X���擾
		const tktkCollision::BoundingCircle& getBoundingCircle() const;

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

			float						otherExtrudedRate;

			tktkCollision::HitInfo2D	hitInfo;
		};
	private:

		// �~�̏Փ˔���N���X
		tktkCollision::BoundingCircle	m_boundingCircle;

		// �����o����₷���i�����j
		float							m_extrudedRate;

		// �Փˑ���ƏՓˌ��ʂ�ێ����郊�X�g
		std::forward_list<HitInfo>		m_hitInfo2dPairList;

		// ���g�̂Q�������W�R���|�[�l���g
		ComponentPtr<Transform2D>		m_transform2D;
	};
}
#endif // !CIRCLE_COLLIDER_H_