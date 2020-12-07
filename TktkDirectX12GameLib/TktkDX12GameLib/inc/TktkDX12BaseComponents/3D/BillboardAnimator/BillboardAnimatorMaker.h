#ifndef BILLBOARD_ANIMATOR_MAKER_H_
#define BILLBOARD_ANIMATOR_MAKER_H_

#include "BillboardAnimator.h"

namespace tktk
{
	// �uBillboardAnimator�v�����w���p�[�N���X
	class BillboardAnimatorMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BillboardAnimatorMaker() = default;
		BillboardAnimatorMaker(const BillboardAnimatorMaker& other) = default;
		BillboardAnimatorMaker& operator = (const BillboardAnimatorMaker& other) = default;

	public:

		// �쐬�J�n
		static BillboardAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BillboardAnimator> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �A�j���[�V���������[�v���邩��ݒ肷��
		BillboardAnimatorMaker& isLoop(bool value);

		// �A�j���[�V�����̏����t���[����ݒ肷��
		BillboardAnimatorMaker& initFrame(float value);

		// �A�j���[�V�����̍Đ����x������ݒ肷��
		BillboardAnimatorMaker& animSpeedRate(float value);

		// �A�j���[�V�����P�t���[��������ɂ����鎞�Ԃ�ݒ肷��
		BillboardAnimatorMaker& animFramePerSec(float value);

		// �A�j���[�V�����̑��t���[������ݒ肷��
		BillboardAnimatorMaker& totalAnimFrameSize(unsigned int value);


	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BillboardAnimatorMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user				{  };
		bool				m_isLoop			{ true };
		float				m_initFrame			{ 0.0f };
		float				m_animSpeedRate		{ 1.0f };
		float				m_animFramePerSec	{ 0.1f };
		unsigned int		m_totalAnimFrameSize{ 1U };
	};
}
#endif // !BILLBOARD_ANIMATOR_MAKER_H_