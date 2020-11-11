#ifndef BONE_MATRIX_CBUFFER_DATA_H_
#define BONE_MATRIX_CBUFFER_DATA_H_

/* class member */
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// ボーン情報の定数バッファ
	struct BoneMatrixCbufferData
	{
		// ボーン行列の配列
		tktkMath::Matrix4 boneMatrix[128U]{ };
	};
}
#endif // !BONE_MATRIX_CBUFFER_DATA_H_