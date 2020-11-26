#ifndef BILLBOARD_MATERIAL_INIT_PARAM_H_
#define BILLBOARD_MATERIAL_INIT_PARAM_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkDX12Wrapper/Resource/Buffer/BufferType.h>

namespace tktk
{
	// ビルボードマテリアルの作成に必要な変数
	struct BillboardMaterialInitParam
	{
		// 描画するバッファーの種類
		BufferType			srvBufferType;

		// 描画するバッファーのID
		size_t				useBufferHandle;

		// 描画できる最大インスタンス数
		size_t				maxInstanceCount;

		// 加算ブレンドを行うか？
		bool				isEffect;
	};
}
#endif // !BILLBOARD_MATERIAL_INIT_PARAM_H_
