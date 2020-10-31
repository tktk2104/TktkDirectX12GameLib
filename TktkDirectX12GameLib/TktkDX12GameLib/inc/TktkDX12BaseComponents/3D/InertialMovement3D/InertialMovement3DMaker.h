#ifndef INERTIAL_MOVEMENT_3D_MAKER_H_
#define INERTIAL_MOVEMENT_3D_MAKER_H_

#include "InertialMovement3D.h"

namespace tktk
{
	// InertialMovement3D�̃C���X�^���X���쐬����N���X
	class InertialMovement3DMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		InertialMovement3DMaker() = default;
		InertialMovement3DMaker(const InertialMovement3DMaker& other) = default;
		InertialMovement3DMaker& operator = (const InertialMovement3DMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static InertialMovement3DMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static InertialMovement3DMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<InertialMovement3D> craete();

		// ���x���P�b�Ԃłǂꂾ�����������邩��ݒ�
		InertialMovement3DMaker& decelerationPerSec(float value);

		// �������x��ݒ�
		InertialMovement3DMaker& initVelocity(const tktkMath::Vector3& value);

	private:

		// ���g�̃|�C���^
		static InertialMovement3DMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr		m_user				{ };
		std::vector<int>	m_targetState		{  };
		float				m_decelerationPerSec{ 64.0f };
		tktkMath::Vector3	m_initVelocity		{ tktkMath::Vector3_v::zero };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline InertialMovement3DMaker& InertialMovement3DMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !INERTIAL_MOVEMENT_3D_MAKER_H_