#ifndef SPHERE_COLLIDER_MAKER_H_
#define SPHERE_COLLIDER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "SphereCollider.h"

namespace tktk
{
	// SphereCollider�̃C���X�^���X���쐬����N���X
	class SphereColliderMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		SphereColliderMaker() = default;
		SphereColliderMaker(const SphereColliderMaker& other) = default;
		SphereColliderMaker& operator = (const SphereColliderMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static SphereColliderMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		static SphereColliderMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SphereCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		SphereColliderMaker& collisionGroupType(CollisionGroupTypeCarrier value);

		// �����蔻��̔��a��ݒ�
		SphereColliderMaker& radius(float value);

		// �����蔻��̃��[�J�����W��ݒ�
		SphereColliderMaker& localPosition(const tktkMath::Vector3& value);

		// �Փˑ���������o���������s�����H
		SphereColliderMaker& isExtrude(bool value);

		// �����o����₷����ݒ�i�����j
		SphereColliderMaker& extrudedRate(float value);

	private:

		// ���g�̃|�C���^
		static SphereColliderMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr				m_user				{ };
		StateTypeHierarchy			m_targetState		{  };
		CollisionGroupTypeCarrier	m_collisionGroupType{ 0 };
		float						m_radius			{ 1.0f };
		tktkMath::Vector3			m_localPosition		{ tktkMath::Vector3_v::zero };
		bool						m_isExtrude			{ false };
		float						m_extrudedRate		{ 0.0f };
	};
}
#endif // !SPHERE_COLLIDER_MAKER_H_