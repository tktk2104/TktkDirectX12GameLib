#ifndef SPRITE_MATERIAL_INSTANCE_DATA_H_
#define SPRITE_MATERIAL_INSTANCE_DATA_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
//#include <TktkMath/Structs/Matrix3.h>

namespace tktk
{
	struct SpriteMaterialInstanceData
	{
		// ワールド行列（hslsの仕様上、float4x3）
		float				worldMatrix[12]		{};

		// テクスチャUVのオフセット値
		tktkMath::Vector2	textureUvOffset		{ tktkMath::Vector2_v::zero };

		// テクスチャUVに乗算する値
		tktkMath::Vector2	textureUvMulRate	{ tktkMath::Vector2_v::zero };

		// テクスチャのサイズ（ピクセル）
		tktkMath::Vector2	textureSize			{ tktkMath::Vector2_v::one };

		// スプライトの中心点（割合）
		tktkMath::Vector2	textureCenterRate	{ tktkMath::Vector2_v::zero };

		// ブレンドレート
		tktkMath::Color		blendRate			{ tktkMath::Color_v::white };
	};
}
#endif // !SPRITE_MATERIAL_INSTANCE_DATA_H_