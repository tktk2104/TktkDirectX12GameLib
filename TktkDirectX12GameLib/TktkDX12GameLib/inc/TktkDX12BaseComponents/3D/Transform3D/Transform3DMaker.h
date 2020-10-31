#ifndef TRANSFORM_3D_MAKER_H_
#define TRANSFORM_3D_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "Transform3D.h"

namespace tktk
{
	// �uTransform3D�v�����w���p�[�N���X
	class Transform3DMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		Transform3DMaker() = default;
		Transform3DMaker(const Transform3DMaker& other) = default;
		Transform3DMaker& operator = (const Transform3DMaker& other) = default;

	public:

		// �쐬�J�n
		static Transform3DMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static Transform3DMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<Transform3D> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �������W��ݒ肷��
		Transform3DMaker& initPosition(const tktkMath::Vector3& value);

		// �����X�P�[����ݒ肷��
		Transform3DMaker& initScaleRate(const tktkMath::Vector3& value);

		// ������]��ݒ肷��
		Transform3DMaker& initRotation(const tktkMath::Quaternion& value);

		// ������]��ݒ肷��i�I�C���[�p�j
		Transform3DMaker& initRotation(const tktkMath::Vector3& value);

		// �s�񂩂珉���p�����[�^��ݒ肷��i���W�ϊ����̂݁j
		Transform3DMaker& setInitTransformFromMatrix(const tktkMath::Matrix4& value);

		// �e��Transform3D�Ƃ̊֌W���̎�ނ�ݒ肷��
		Transform3DMaker& traceType(TraceParentType value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static Transform3DMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr			m_user			{  };
		std::vector<int>		m_targetState	{  };
		tktkMath::Vector3		m_initPosition	{ tktkMath::Vector3_v::zero };
		tktkMath::Vector3		m_initScaleRate	{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion	m_initRotation	{ tktkMath::Quaternion_v::identity };
		TraceParentType			m_traceType		{ TraceParentType::trace_All };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline Transform3DMaker& Transform3DMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !TRANSFORM_3D_MAKER_H_