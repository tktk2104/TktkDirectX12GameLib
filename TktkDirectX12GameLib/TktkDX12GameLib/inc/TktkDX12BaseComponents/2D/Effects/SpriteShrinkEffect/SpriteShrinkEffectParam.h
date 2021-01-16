#ifndef SPRITE_SHRINK_EFFECT_PARAM_H_
#define SPRITE_SHRINK_EFFECT_PARAM_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	struct SpriteShrinkEffectParam
	{
		//************************************************************
		/* ������� */

		// ���k�_���W
		tktkMath::Vector2 shrinkTargetPos				{ tktkMath::Vector2_v::zero };
		// ���k�_���W�̂Ԃ�
		tktkMath::Vector2 shrinkTargetPosRandomRange	{ tktkMath::Vector2_v::zero };

		// �ŏ��̐������ԁi�b�j
		float	firstGenerateTimeSec					{ 0.0f };

		// �����p�x�i�b�j
		float	generateIntervalTimeSec					{ 0.1f };
		// �����p�x�̂Ԃ�
		float	generateIntervalTimeRandomRange			{ 0.0f};

		// �P�x�ɉ��������邩�H
		int		generateNumPerOnce						{ 3 };
		// �P�x�ɐ���������̂Ԃ�
		int		generateNumPerOnceRandomRange			{ 0 };

		// �ő剽�������邩�H
		int		totalGenerateNum						{ -1 };

		// �A�N�e�B�u�t���O�ύX���ɏ�Ԃ����Z�b�g���邩�H
		bool	changeAvtiveToReset						{ false };

		//************************************************************
		/* �p�[�e�B�N����� */

		// �g�p����X�v���C�g�̃n���h��
		size_t	useSpriteHandle						{ 0U };

		// �X�v���C�g�̃X�P�[��
		tktkMath::Vector2 spriteScale				{ tktkMath::Vector2_v::one };
		// �X�v���C�g�̃X�P�[���̂Ԃ�
		tktkMath::Vector2 spriteScaleRandomRange	{ tktkMath::Vector2_v::zero };

		// �X�v���C�g�̃u�����h���[�g
		tktkMath::Color spriteBlendRate				{ tktkMath::Color_v::white };

		// �q�v�f�Ƃ��Ĉ������H
		bool	setChild							{ false };

		// �������ԁi�b�j
		float	lifeTimeSec							{ 0.5f };
		// �������Ԃ̂Ԃ�
		float	lifeTimeSecRandomRange				{ 0.0f };

		// �ړ����x�i���b�j
		float	moveSpeedPerSec						{ 256.0f };
		// �ړ����x�̂Ԃ�
		float	moveSpeedPerSecRandomRange			{ 0.0f };

		//************************************************************
		/* �p�[�e�B�N���A�j���[�V������� */

		// �A�j���[�V�������g�p���邩�H
		bool				useAnimation{ false };

		// �A�j���[�V���������[�v���邩�H
		bool				isLoop{ false };

		// �A�j���[�V�����̏����t���[��
		float				initFrame{ 0.0f };

		// �A�j���[�V�����̍Đ����x����
		float				animSpeedRate{ 1.0f };

		// �A�j���[�V�����P�t���[��������ɂ����鎞�ԁi�b�j
		float				animFramePerSec{ 0.1f };

		// �A�j���[�V�����̑��t���[����
		unsigned int		totalAnimFrameSize{ 1U };
	};
}
#endif // !SPRITE_SHRINK_EFFECT_PARAM_H_