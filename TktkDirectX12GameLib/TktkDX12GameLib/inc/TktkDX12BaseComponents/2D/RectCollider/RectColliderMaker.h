#ifndef RECT_COLLIDER_MAKER_H_
#define RECT_COLLIDER_MAKER_H_

#include "RectCollider.h"

namespace tktk
{
	// RectCollider�̃C���X�^���X���쐬����N���X
	class RectColliderMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		RectColliderMaker() = default;
		RectColliderMaker(const RectColliderMaker& other) = default;
		RectColliderMaker& operator = (const RectColliderMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static RectColliderMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static RectColliderMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<RectCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		template <class CollisionGroupType, is_idType<CollisionGroupType> = nullptr>
		RectColliderMaker& collisionGroupType(CollisionGroupType value) { return collisionGroupTypeImpl(static_cast<int>(value)); }

		// �����蔻��̑傫����ݒ�
		RectColliderMaker& rectSize(const tktkMath::Vector2& value);

		// �����蔻��̃��[�J�����W��ݒ�
		RectColliderMaker& localPosition(const tktkMath::Vector2& value);

		// �Փˑ���������o���������s�����H
		RectColliderMaker& isExtrude(bool value);

		// �����o����₷����ݒ�i�����j
		RectColliderMaker& extrudedRate(float value);

	private: /* ������ */

		RectColliderMaker& collisionGroupTypeImpl(int value);

	private:

		// ���g�̃|�C���^
		static RectColliderMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr		m_user				{ };
		std::vector<int>	m_targetState		{  };
		int					m_collisionGroupType{ 0 };
		tktkMath::Vector2	m_rectSize			{ tktkMath::Vector2_v::one };
		tktkMath::Vector2	m_localPosition		{ tktkMath::Vector2_v::zero };
		bool				m_isExtrude			{ false };
		float				m_extrudedRate		{ 0.0f };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline RectColliderMaker& RectColliderMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !RECT_COLLIDER_MAKER_H_