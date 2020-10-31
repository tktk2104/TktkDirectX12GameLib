#ifndef INERTIAL_ROTATEMENT_2D_MAKER_H_
#define INERTIAL_ROTATEMENT_2D_MAKER_H_

#include "InertialRotatement2D.h"

namespace tktk
{
	// InertialRotatement2D�̃C���X�^���X���쐬����N���X
	class InertialRotatement2DMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		InertialRotatement2DMaker() = default;
		InertialRotatement2DMaker(const InertialRotatement2DMaker& other) = default;
		InertialRotatement2DMaker& operator = (const InertialRotatement2DMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static InertialRotatement2DMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static InertialRotatement2DMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<InertialRotatement2D> create();

		// ���x���P�b�Ԃłǂꂾ�����������邩��ݒ�
		InertialRotatement2DMaker& decelerationPerSec(float value);

		// �������x��ݒ�
		InertialRotatement2DMaker& initVelocity(float value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		// ���g�̃|�C���^
		static InertialRotatement2DMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user					{ };
		std::vector<int>	m_targetState			{  };
		float				m_decelerationPerSec	{ 30.0f };
		float				m_initVelocity			{ 0.0f };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline InertialRotatement2DMaker& InertialRotatement2DMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !INERTIAL_ROTATEMENT_2D_MAKER_H_