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
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static BoxColliderMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

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
		std::vector<int>	m_targetState			{  };
		int					m_collisionGroupType	{ 0 };
		tktkMath::Vector3	m_boxSize				{ tktkMath::Vector3_v::one };
		tktkMath::Vector3	m_localPosition			{ tktkMath::Vector3_v::zero };
		float				m_extrudedRate			{ 0.0f };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline BoxColliderMaker& BoxColliderMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
	{
		// �쐬�J�n�������s��
		auto& result = makeStart(user);

		// �������q���X�g��z��ɕϊ�
		auto targetStateArray = std::vector<StateIdType>(targetState);

		// �Ώۂ̃X�e�[�g�̊K�w�����̃��������m��
		result.m_targetState.reserve(targetStateArray.size());

		// �Ώۂ̃X�e�[�g�̊K�w��ݒ肷��
		for (const auto& node : targetStateArray) result.m_targetState.push_back(static_cast<int>(node));

		// ���g�̎Q�Ƃ�Ԃ�
		return result;
	}
}
#endif // !BOX_COLLIDER_MAKER_H_