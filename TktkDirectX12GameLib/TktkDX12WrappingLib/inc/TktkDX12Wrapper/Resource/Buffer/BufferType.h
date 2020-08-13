#ifndef BUFFER_TYPE_H_
#define BUFFER_TYPE_H_

namespace tktk
{
	// バッファーの種類
	enum class BufferType
	{
		vertex,			// 頂点バッファ
		index,			// インデックスバッファ
		constant,		// 定数バッファ
		texture,		// テクスチャバッファ
		renderTarget,	// 深度ステンシルバッファ
		depthStencil	// レンダーターゲットバッファ
	};
}
#endif // !BUFFER_TYPE_H_