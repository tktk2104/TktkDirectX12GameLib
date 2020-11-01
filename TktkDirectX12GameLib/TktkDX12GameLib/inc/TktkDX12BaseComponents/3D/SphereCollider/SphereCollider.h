#ifndef SPHERE_COLLIDER_H_
#define SPHERE_COLLIDER_H_

#include <TktkMath/Structs/Vector3.h>
#include <TktkCollision/3D/BoundingSphere.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// ���̂̓����蔻��̃R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform3D�z
	class SphereCollider
		: public ComponentBase
	{
	public:

		SphereCollider(
			int collisionGroupType,					// �����蔻��̃O���[�v�ԍ�
			float radius,							// �����蔻��̔��a
			const tktkMath::Vector3& localPosition,	// �����蔻��̃��[�J�����W
			bool isExtrude,							// �Փˑ���������o���������s�����H
			float extrudedRate						// �����o����₷���i�����j
		);

	public:

		// <PolymorphismFunc>
		void start();
		bool isCollide(const ComponentBasePtr& other);
		void afterCollide();

	public:

		// �����蔻��̃N���X���擾
		const tktkCollision::BoundingSphere& getBoundingSphere() const;

		// �Փˑ���������o���������s�����H
		bool isExtrud() const;

		// �����o����₷�����擾
		float getExtrudedRate() const;

		// ���W�Ǘ��R���|�[�l���g���擾
		const ComponentPtr<Transform3D>& getTransform() const;

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

		// ���̂̏Փ˔���N���X
		tktkCollision::BoundingSphere m_boundingSphere;

		// �Փˑ���������o���������s�����H
		bool						m_isExtrude;

		// �����o����₷���i�����j
		float						m_extrudedRate;

		// �Փˑ���ƏՓˌ��ʂ�ێ����郊�X�g
		std::forward_list<HitInfo>	m_hitInfo3dPairList;

		// ���g�̂R�������W�R���|�[�l���g
		ComponentPtr<Transform3D> m_transform3D;
	};
}
#endif // !SPHERE_COLLIDER_H_