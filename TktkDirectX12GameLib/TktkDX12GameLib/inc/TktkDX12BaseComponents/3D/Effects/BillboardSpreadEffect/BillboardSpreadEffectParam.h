#ifndef BILLBOARD_SPREAD_EFFECT_PARAM_H_
#define BILLBOARD_SPREAD_EFFECT_PARAM_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	struct BillboardSpreadEffectParam
	{
		//************************************************************
		/* ������� */

		// �������[�J�����W
		tktkMath::Vector3 generateLocalPos				{ tktkMath::Vector3_v::zero };
		// �������[�J�����W�̂Ԃ�
		tktkMath::Vector3 generateLocalPosRandomRange	{ tktkMath::Vector3_v::zero };

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

		// �g�p����r���{�[�h�̃n���h��
		size_t	useBillboardHandle						{ 0U };

		// �r���{�[�h�̃X�P�[��
		tktkMath::Vector2 billboardScale				{ 0.1f, 0.1f };
		// �r���{�[�h�̃X�P�[���̂Ԃ�
		tktkMath::Vector2 billboardScaleRandomRange		{ tktkMath::Vector2_v::zero };

		// �r���{�[�h�̃u�����h���[�g
		tktkMath::Color billboardBlendRate				{ tktkMath::Color_v::white };

		// �q�v�f�Ƃ��Ĉ������H
		bool	setChild								{ false };

		// �������ԁi�b�j
		float	lifeTimeSec								{ 0.5f };
		// �������Ԃ̂Ԃ�
		float	lifeTimeSecRandomRange					{ 0.0f };

		// �ړ����x�i���b�j
		float	moveSpeedPerSec							{ 10.0f };
		// �ړ����x�̂Ԃ�
		float	moveSpeedPerSecRandomRange				{ 0.0f };
	};
}
#endif // !BILLBOARD_SPREAD_EFFECT_PARAM_H_