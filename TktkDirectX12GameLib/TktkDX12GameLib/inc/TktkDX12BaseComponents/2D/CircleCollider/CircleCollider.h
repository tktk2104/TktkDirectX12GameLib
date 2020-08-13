#ifndef CIRCLE_COLLIDER_H_
#define CIRCLE_COLLIDER_H_

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
			const tktkMath::Vector2& localPosition	// �����蔻��̃��[�J�����W
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();
		bool isCollide(const ComponentBasePtr& other);

	public:

		// �����蔻��̃N���X���擾
		const tktkCollision::Body2dBase& getBodyBase() const;

		// ���O�̏Փ˔���̌��ʂ��擾
		const tktkCollision::HitInfo2D& getHitInfo2D() const;

	private:

		// �Փ˔��茋��
		tktkCollision::HitInfo2D m_hitInfo;

		// �~�̏Փ˔���N���X
		tktkCollision::BoundingCircle m_boundingCircle;

		// ���g�̂Q�������W�R���|�[�l���g
		ComponentPtr<Transform2D> m_transform2D;
	};
}
#endif // !CIRCLE_COLLIDER_H_