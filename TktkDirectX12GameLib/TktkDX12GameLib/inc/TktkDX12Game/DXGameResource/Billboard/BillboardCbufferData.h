#ifndef BILLBOARD_TRANSFORM_CBUFFER_DATA_H_
#define BILLBOARD_TRANSFORM_CBUFFER_DATA_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Matrix4.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	struct BillboardCbufferData
	{
		// ビルビードの座標
		tktkMath::Vector3	billboardPosition	{ tktkMath::Vector3_v::zero };

		// ビルボードの回転角度
		float				billboardAngle		{ 0.0f };

		// ビルボードのスケール
		tktkMath::Vector2	billboardScale		{ tktkMath::Vector2_v::one };

		// テクスチャUVのオフセット値
		tktkMath::Vector2	textureUvOffset		{ tktkMath::Vector2_v::zero };

		// テクスチャUVに乗算する値
		tktkMath::Vector2	textureUvMulRate	{ tktkMath::Vector2_v::zero };

		// テクスチャのサイズ（ピクセル）
		tktkMath::Vector2	textureSize			{ tktkMath::Vector2_v::one };

		// スプライトの中心点（割合）
		tktkMath::Vector2	textureCenterRate	{ tktkMath::Vector2_v::zero };

		// パディング
		float				pad[2]				{  };

		// ビュー行列
		tktkMath::Matrix4	viewMatrix			{ tktkMath::Matrix4_v::identity };

		// プロジェクション行列
		tktkMath::Matrix4	projectionMatrix	{ tktkMath::Matrix4_v::identity };

		// ブレンドレート
		tktkMath::Color		blendRate			{ tktkMath::Color_v::white };
	};
}
#endif // !BILLBOARD_TRANSFORM_CBUFFER_DATA_H_