#ifndef BILLBOARD_TRANSFORM_CBUFFER_UPDATE_FUNC_ARGS_H_
#define BILLBOARD_TRANSFORM_CBUFFER_UPDATE_FUNC_ARGS_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Matrix4.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	// �r���{�[�h�̒萔�o�b�t�@���X�V���鎞�ɕK�v�ȕϐ�
	struct BillboardCbufferUpdateFuncArgs
	{
		// �r���r�[�h�̍��W
		tktkMath::Vector3	billboardPosition	{ tktkMath::Vector3_v::zero };

		// �r���{�[�h�̉�]�p�x
		float				billboardAngle		{ 0.0f };

		// �r���{�[�h�̃X�P�[��
		tktkMath::Vector2	billboardScale		{ tktkMath::Vector2_v::one };

		// �X�v���C�g�̒��S�_�i�����j
		tktkMath::Vector2	textureCenterRate	{ tktkMath::Vector2_v::zero };

		// �r���[�s��
		tktkMath::Matrix4	viewMatrix			{ tktkMath::Matrix4_v::identity };

		// �v���W�F�N�V�����s��
		tktkMath::Matrix4	projectionMatrix	{ tktkMath::Matrix4_v::identity };

		// �u�����h���[�g
		tktkMath::Color		blendRate			{ tktkMath::Color_v::white };
	};
}
#endif // !BILLBOARD_TRANSFORM_CBUFFER_UPDATE_FUNC_ARGS_H_
