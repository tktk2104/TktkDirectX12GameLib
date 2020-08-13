#ifndef SPRITE_MATERIAL_INIT_PARAM_H_
#define SPRITE_MATERIAL_INIT_PARAM_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkDX12Wrapper/Resource/Buffer/BufferType.h>

namespace tktk
{
	// スプライトマテリアルを作るときに必要な情報
	struct SpriteMaterialInitParam
	{
		// 作るディスクリプタヒープのID
		unsigned int		createDescriptorHeapId;

		// 描画するバッファーの種類
		BufferType			srvBufferType;

		// 描画するバッファーのID
		unsigned int		useBufferId;

		// ブレンド値
		tktkMath::Color		blendRate		{ 1.0f, 1.0f, 1.0f, 1.0f };

		// テクスチャUVのオフセット
		tktkMath::Vector2	textureUvOffset	{ 0.0f, 0.0f };

		// テクスチャUVに乗算する値
		tktkMath::Vector2	textureUvMulRate{ 1.0f, 1.0f };

		// スプライトの中心点（割合）
		tktkMath::Vector2	spriteCenterRate{ 0.5f, 0.5f };
	};
}
#endif // !SPRITE_MATERIAL_INIT_PARAM_H_