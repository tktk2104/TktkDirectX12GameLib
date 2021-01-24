#ifndef SPRITE_ANIMATOR_MAKER_H_
#define SPRITE_ANIMATOR_MAKER_H_

#include "SpriteAnimator.h"

namespace tktk
{
	// �uSpriteAnimator�v�����w���p�[�N���X
	class SpriteAnimatorMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		SpriteAnimatorMaker() = default;
		SpriteAnimatorMaker(const SpriteAnimatorMaker& other) = default;
		SpriteAnimatorMaker& operator = (const SpriteAnimatorMaker& other) = default;

	public:

		// �쐬�J�n
		static SpriteAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SpriteAnimator> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �A�j���[�V�����Ώۂ̃X�v���C�g�`��R���|�[�l���g�����O�ɐݒ肷��i���ݒ肵�Ȃ������ꍇ�A�����ŋ��ʂ�GameObject���������Ă���X�v���C�g�`��R���|�[�l���g���ΏۂɂȂ�j
		SpriteAnimatorMaker& targetDrawer(const ComponentPtr<SpriteDrawer>& value);

		// �A�j���[�V���������[�v���邩��ݒ肷��
		SpriteAnimatorMaker& isLoop(bool value);

		// �A�j���[�V�����̏����t���[����ݒ肷��
		SpriteAnimatorMaker& initFrame(float value);

		// �A�j���[�V�����̍Đ����x������ݒ肷��
		SpriteAnimatorMaker& animSpeedRate(float value);

		// �A�j���[�V�����P�t���[��������ɂ����鎞�Ԃ�ݒ肷��
		SpriteAnimatorMaker& animFramePerSec(float value);

		// �A�j���[�V�����̑��t���[������ݒ肷��
		SpriteAnimatorMaker& totalAnimFrameSize(unsigned int value);


	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static SpriteAnimatorMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr				m_user					{  };
		ComponentPtr<SpriteDrawer>	m_targetDrawer			{ ComponentPtr<SpriteDrawer>() };
		bool						m_isLoop				{ true };
		float						m_initFrame				{ 0.0f };
		float						m_animSpeedRate			{ 1.0f };
		float						m_animFramePerSec		{ 0.1f };
		unsigned int				m_totalAnimFrameSize	{ 1U };
	};
}
#endif // !SPRITE_ANIMATOR_MAKER_H_