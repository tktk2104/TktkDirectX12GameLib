#ifndef BILLBOARD_TRANSFORM_CBUFFER_UPDATE_FUNC_ARGS_H_
#define BILLBOARD_TRANSFORM_CBUFFER_UPDATE_FUNC_ARGS_H_

#include <TktkMath/Structs/Matrix4.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	struct BillboardTransformCbufferUpdateFuncArgs
	{
		// ビルビードの座標
		tktkMath::Vector3	billboardPosition	{ tktkMath::Vector3_v::zero };

		// ビルボードの回転角度
		float				billboardAngle		{ 0.0f };

		// ビルボードのスケール
		tktkMath::Vector2	billboardScale		{ tktkMath::Vector2_v::one };

		// スプライトの中心点（割合）
		tktkMath::Vector2	textureCenterRate	{ tktkMath::Vector2_v::zero };

		// ビュー行列
		tktkMath::Matrix4	viewMatrix			{ tktkMath::Matrix4_v::identity };

		// プロジェクション行列
		tktkMath::Matrix4	projectionMatrix	{ tktkMath::Matrix4_v::identity };
	};
}
#endif // !BILLBOARD_TRANSFORM_CBUFFER_UPDATE_FUNC_ARGS_H_
