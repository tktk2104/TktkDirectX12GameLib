#ifndef BONE_MATRIX_CBUFFER_DATA_H_
#define BONE_MATRIX_CBUFFER_DATA_H_

/* class member */
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// �{�[�����̒萔�o�b�t�@
	struct BoneMatrixCbufferData
	{
		// �{�[���s��̔z��
		tktkMath::Matrix4 boneMatrix[128U]{ };
	};
}
#endif // !BONE_MATRIX_CBUFFER_DATA_H_