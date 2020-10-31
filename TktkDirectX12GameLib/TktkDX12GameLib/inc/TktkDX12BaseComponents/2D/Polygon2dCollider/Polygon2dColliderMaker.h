#ifndef POLYGON_2D_COLLIDER_MAKER_H_
#define POLYGON_2D_COLLIDER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "Polygon2dCollider.h"

namespace tktk
{
	// RectCollider�̃C���X�^���X���쐬����N���X
	class Polygon2dColliderMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		Polygon2dColliderMaker() = default;
		Polygon2dColliderMaker(const Polygon2dColliderMaker& other) = default;
		Polygon2dColliderMaker& operator = (const Polygon2dColliderMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static Polygon2dColliderMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static Polygon2dColliderMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<Polygon2dCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		template <class CollisionGroupType, is_idType<CollisionGroupType> = nullptr>
		Polygon2dColliderMaker& collisionGroupType(CollisionGroupType value) { return collisionGroupTypeImpl(static_cast<int>(value)); }

		// �����蔻��̑傫����ݒ�
		Polygon2dColliderMaker& vertexs(const std::vector<tktkMath::Vector2>& value);

		// �����o����₷����ݒ�i�����j
		Polygon2dColliderMaker& extrudedRate(float value);

	private: /* ������ */

		Polygon2dColliderMaker& collisionGroupTypeImpl(int value);

	private:

		// ���g�̃|�C���^
		static Polygon2dColliderMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr					m_user					{ };
		std::vector<int>				m_targetState			{  };
		int								m_collisionGroupType	{ 0 };
		std::vector<tktkMath::Vector2>	m_vertexs				{};
		float							m_extrudedRate			{ 0.0f };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline Polygon2dColliderMaker& Polygon2dColliderMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !POLYGON_2D_COLLIDER_MAKER_H_