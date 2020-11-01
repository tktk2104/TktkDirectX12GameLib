#ifndef CIRCLE_COLLIDER_MAKER_H_
#define CIRCLE_COLLIDER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "CircleCollider.h"

namespace tktk
{
	// CircleCollider�̃C���X�^���X���쐬����N���X
	class CircleColliderMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		CircleColliderMaker() = default;
		CircleColliderMaker(const CircleColliderMaker& other) = default;
		CircleColliderMaker& operator = (const CircleColliderMaker& other) = default;

	public:

		// �쐬�J�n
		static CircleColliderMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static CircleColliderMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<CircleCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		template <class CollisionGroupType, is_idType<CollisionGroupType> = nullptr>
		CircleColliderMaker& collisionGroupType(CollisionGroupType value) { return collisionGroupTypeImpl(static_cast<int>(value)); }

		// �����蔻��̔��a��ݒ�
		CircleColliderMaker& radius(float value);

		// �����蔻��̃��[�J�����W��ݒ�
		CircleColliderMaker& localPosition(const tktkMath::Vector2& value);

		// �Փˑ���������o���������s�����H
		CircleColliderMaker& isExtrude(bool value);

		// �����o����₷����ݒ�i�����j
		CircleColliderMaker& extrudedRate(float value);

	private: /* ������ */

		CircleColliderMaker& collisionGroupTypeImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		// ���g�̃|�C���^
		static CircleColliderMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user					{ };
		std::vector<int>	m_targetState			{  };
		int					m_collisionGroupType	{ 0 };
		float				m_radius				{ 1.0f };
		tktkMath::Vector2	m_localPosition			{ tktkMath::Vector2_v::zero };
		bool				m_isExtrude				{ false };
		float				m_extrudedRate			{ 0.0f };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline CircleColliderMaker& CircleColliderMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !CIRCLE_COLLIDER_MAKER_H_