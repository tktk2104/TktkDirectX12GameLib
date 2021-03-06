#ifndef CAMERA_CBUFFER_H_
#define CAMERA_CBUFFER_H_

/* class member */
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// カメラ情報の定数バッファ
	struct CameraCbuffer
	{
		// ビュー行列
		tktkMath::Matrix4	viewMatrix		{ tktkMath::Matrix4_v::identity };

		// プロジェクション行列
		tktkMath::Matrix4	projectionMatrix{ tktkMath::Matrix4_v::identity };
	};
}
#endif // !CAMERA_CBUFFER_H_