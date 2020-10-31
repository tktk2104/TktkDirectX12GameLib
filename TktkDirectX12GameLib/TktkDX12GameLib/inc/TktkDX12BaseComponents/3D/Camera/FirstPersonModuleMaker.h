#ifndef FIRST_PERSON_MODULE_MAKER_H_
#define FIRST_PERSON_MODULE_MAKER_H_

#include "FirstPersonModule.h"

namespace tktk
{
	// �uFirstPersonModule�v�����w���p�[�N���X
	class FirstPersonModuleMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		FirstPersonModuleMaker() = default;
		FirstPersonModuleMaker(const FirstPersonModuleMaker& other) = default;
		FirstPersonModuleMaker& operator = (const FirstPersonModuleMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static FirstPersonModuleMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static FirstPersonModuleMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<FirstPersonModule> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �������b��]�p�x��ݒ肷��
		FirstPersonModuleMaker& rotateDegSpeedPerSec(float value);

		// �������b�ړ�������ݒ肷��
		FirstPersonModuleMaker& moveSpeedPerSec(float value);

		// ��ɃJ�����̕����Ɉړ����邩��ݒ肷��i�ړ��L�[��y���̍��W��ω������邩�H�j
		FirstPersonModuleMaker& alwaysMoveForward(bool value);

		// �X�y�[�X�ƃV�t�g��y���̍��W��ω������邩��ݒ肷��
		FirstPersonModuleMaker& enableUpDownKey(bool value);

	private:

		// ���g�̃|�C���^
		static FirstPersonModuleMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr		m_user					{ };
		std::vector<int>	m_targetState			{  };
		float				m_rotateDegSpeedPerSec	{ 100.0f };
		float				m_moveSpeedPerSec		{ 100.0f };
		bool				m_alwaysMoveForward		{ false };
		bool				m_enableUpDownKey		{ false };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline FirstPersonModuleMaker& FirstPersonModuleMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !FIRST_PERSON_MODULE_MAKER_H_