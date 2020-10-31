#ifndef TRANSFORM_2D_MAKER_H_
#define TRANSFORM_2D_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "Transform2D.h"

namespace tktk
{
	// �uTransform2D�v�����w���p�[�N���X
	class Transform2DMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		Transform2DMaker() = default;
		Transform2DMaker(const Transform2DMaker& other) = default;
		Transform2DMaker& operator = (const Transform2DMaker& other) = default;

	public:

		// �쐬�J�n
		static Transform2DMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static Transform2DMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<Transform2D> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �������W��ݒ肷��
		Transform2DMaker& initPosition(const tktkMath::Vector2& value);

		// �����X�P�[����ݒ肷��
		Transform2DMaker& initScaleRate(const tktkMath::Vector2& value);

		// ������]��ݒ肷��
		Transform2DMaker& initRotationDeg(float value);

		// �e��Transform2D�Ƃ̊֌W���̎�ނ�ݒ肷��
		Transform2DMaker& traceType(TraceParentType value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static Transform2DMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user				{  };
		std::vector<int>	m_targetState		{  };
		tktkMath::Vector2	m_initPosition		{ tktkMath::Vector2_v::zero };
		tktkMath::Vector2	m_initScaleRate		{ tktkMath::Vector2_v::one };
		float				m_initRotationDeg	{ 0.0f };
		TraceParentType		m_traceType			{ TraceParentType::trace_All };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline Transform2DMaker& Transform2DMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !TRANSFORM_2D_MAKER_H_