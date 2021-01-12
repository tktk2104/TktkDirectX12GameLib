#ifndef TEMP_SPRITE_MATERIAL_INSTANCE_DATA_H_
#define TEMP_SPRITE_MATERIAL_INSTANCE_DATA_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix3.h>

namespace tktk
{
	struct TempSpriteMaterialInstanceData
	{
		// ワールド行列
		tktkMath::Matrix3	worldMatrix			{ tktkMath::Matrix3_v::identity };

		// 使用するテクスチャピクセル数
		tktkMath::Vector2	texturePixelCount	{ tktkMath::Vector2_v::zero };

		// テクスチャピクセルのオフセット値
		tktkMath::Vector2	texturePixelOffset	{ tktkMath::Vector2_v::zero };

		// テクスチャUVに乗算する値
		tktkMath::Vector2	textureUvMulRate	{ tktkMath::Vector2_v::one };

		// スプライトの中心点（割合）
		tktkMath::Vector2	textureCenterRate	{ tktkMath::Vector2_v::zero };

		// ブレンドレート
		tktkMath::Color		blendRate			{ tktkMath::Color_v::white };
	};
}
#endif // !TEMP_SPRITE_MATERIAL_INSTANCE_DATA_H_