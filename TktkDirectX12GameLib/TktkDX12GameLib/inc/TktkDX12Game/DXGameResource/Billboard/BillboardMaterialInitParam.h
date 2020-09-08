#ifndef BILLBOARD_MATERIAL_INIT_PARAM_H_
#define BILLBOARD_MATERIAL_INIT_PARAM_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkDX12Wrapper/Resource/Buffer/BufferType.h>

namespace tktk
{
	struct BillboardMaterialInitParam
	{
		// 描画するバッファーの種類
		BufferType			srvBufferType;

		// 描画するバッファーのID
		unsigned int		useBufferHandle;

		// テクスチャUVのオフセット
		tktkMath::Vector2	textureUvOffset{ 0.0f, 0.0f };

		// テクスチャUVに乗算する値
		tktkMath::Vector2	textureUvMulRate{ 1.0f, 1.0f };
	};
}
#endif // !BILLBOARD_MATERIAL_INIT_PARAM_H_
