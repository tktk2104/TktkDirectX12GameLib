#ifndef MOTION_CHANGER_MAKER_H_
#define MOTION_CHANGER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
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

	public:

		// �쐬����
		ComponentPtr<MotionChanger> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// ���[�V���������[�v�����邩��ݒ肷��
		MotionChangerMaker& isLoop(bool value);

		// ���[�V�����̍Đ����x�{����ݒ肷��
		MotionChangerMaker& motionSpeedRate(float value);

		// �g�p���郂�[�V�����n���h����ݒ肷��
		MotionChangerMaker& initMotionHandle(size_t value);

		// �g�p���郂�[�V����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		MotionChangerMaker& initMotionId(ResourceIdCarrier value);

		// �����A�j���[�V�����t���[����ݒ肷��
		MotionChangerMaker& initFrame(float value);

		// ���b�Ԃ����ă��[�V�����̑J�ڂ��s�����H
		MotionChangerMaker& lerpTimeSec(float value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static MotionChangerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user				{  };
		bool				m_isLoop			{ true };
		float				m_motionSpeedRate	{ 1.0f };
		size_t				m_initMotionHandle	{ 0U };
		float				m_initFrame			{ 0.0f };
		float				m_lerpTimeSec		{ 1.0f };
	};
}
#endif // !MOTION_CHANGER_MAKER_H_