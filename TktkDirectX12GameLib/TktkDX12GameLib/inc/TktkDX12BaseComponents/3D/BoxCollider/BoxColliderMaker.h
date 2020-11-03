#ifndef BOX_COLLIDER_MAKER_H_
#define BOX_COLLIDER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BoxCollider.h"

namespace tktk
{
	// BoxCollider�̃C���X�^���X���쐬����N���X
	class BoxColliderMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BoxColliderMaker() = default;
		BoxColliderMaker(const BoxColliderMaker& other) = default;
		BoxColliderMaker& operator = (const BoxColliderMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static BoxColliderMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		static BoxColliderMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BoxCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		template <class CollisionGroupType, is_idType<CollisionGroupType> = nullptr>
		BoxColliderMaker& collisionGroupType(CollisionGroupType value) { return collisionGroupTypeImpl(static_cast<int>(value)); }

		// �����蔻��̑傫����ݒ�
		BoxColliderMaker& boxSize(const tktkMath::Vector3& value);

		// �����蔻��̃��[�J�����W��ݒ�
		BoxColliderMaker& localPosition(const tktkMath::Vector3& value);

		// �Փˑ���������o���������s�����H
		BoxColliderMaker& isExtrude(bool value);

		// �����o����₷����ݒ�i�����j
		BoxColliderMaker& extrudedRate(float value);

	private: /* ������ */

		BoxColliderMaker& collisionGroupTypeImpl(int value);

	private:

		// ���g�̃|�C���^
		static BoxColliderMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr		m_user					{ };
		StateTypeHierarchy		m_targetState			{  };
		int					m_collisionGroupType	{ 0 };
		tktkMath::Vector3	m_boxSize				{ tktkMath::Vector3_v::one };
		tktkMath::Vector3	m_localPosition			{ tktkMath::Vector3_v::zero };
		bool				m_isExtrude				{ false };
		float				m_extrudedRate			{ 0.0f };
	};
}
#endif // !BOX_COLLIDER_MAKER_H_