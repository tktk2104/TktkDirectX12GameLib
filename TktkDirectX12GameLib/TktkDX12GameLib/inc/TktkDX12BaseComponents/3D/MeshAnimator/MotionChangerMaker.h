#ifndef MOTION_CHANGER_MAKER_H_
#define MOTION_CHANGER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "MotionChanger.h"

namespace tktk
{
	// �uMotionChanger�v�����w���p�[�N���X
	class MotionChangerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		MotionChangerMaker() = default;
		MotionChangerMaker(const MotionChangerMaker& other) = default;
		MotionChangerMaker& operator = (const MotionChangerMaker& other) = default;

	public:

		// �쐬�J�n
		static MotionChangerMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		static MotionChangerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<MotionChanger> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// ���[�V���������[�v�����邩��ݒ肷��
		MotionChangerMaker& isLoop(bool value);

		// �g�p���郂�[�V�����n���h����ݒ肷��
		MotionChangerMaker& initMotionHandle(unsigned int value);

		// �g�p���郂�[�V����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		template<class IdType, is_idType<IdType> = nullptr>
		MotionChangerMaker& initMotionId(IdType value);

		// ���b�Ԃ����ă��[�V�����̑J�ڂ��s�����H
		MotionChangerMaker& lerpTimeSec(float value);

	private: /* �e��id�w��n�̊֐��̎��� */

		MotionChangerMaker& initMotionIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static MotionChangerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr	m_user				{  };
		StateTypeHierarchy	m_targetState		{  };
		unsigned int	m_isLoop			{ true };
		unsigned int	m_initMotionHandle	{ 0U };
		float			m_lerpTimeSec		{ 1.0f };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MotionChangerMaker& initMotionId(IdType value) { static_assert(false, "MotionId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �g�p���鏉�����[�V����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
	template<class IdType, is_idType<IdType>>
	inline MotionChangerMaker& MotionChangerMaker::initMotionId(IdType value)
	{
		return initMotionIdImpl(static_cast<int>(value));
	}
}
#endif // !MOTION_CHANGER_MAKER_H_