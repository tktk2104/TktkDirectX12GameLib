#ifndef SPRITE_MATERIAL_INIT_PARAM_H_
#define SPRITE_MATERIAL_INIT_PARAM_H_

/* class member */
#include <TktkDX12Wrapper/Resource/Buffer/BufferType.h>

namespace tktk
{
	// スプライトマテリアルを作るときに必要な情報
	struct SpriteMaterialInitParam
	{
		// 描画するバッファーの種類
		BufferType			srvBufferType;

		// 描画するバッファーのID
		size_t				useBufferHandle;

		// 描画できる最大インスタンス数
		size_t				maxInstanceCount;
	};
}
#endif // !SPRITE_MATERIAL_INIT_PARAM_H_