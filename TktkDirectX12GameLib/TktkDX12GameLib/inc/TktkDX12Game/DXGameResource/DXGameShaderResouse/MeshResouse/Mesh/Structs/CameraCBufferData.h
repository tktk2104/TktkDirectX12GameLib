#ifndef CAMERA_CBUFFER_DATA_H_
#define CAMERA_CBUFFER_DATA_H_

/* class member */
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// �J�������̒萔�o�b�t�@
	struct CameraCBufferData
	{
		// �r���[�s��
		tktkMath::Matrix4	viewMatrix		{ tktkMath::Matrix4_v::identity };

		// �v���W�F�N�V�����s��
		tktkMath::Matrix4	projectionMatrix{ tktkMath::Matrix4_v::identity };
	};
}
#endif // !CAMERA_CBUFFER_DATA_H_