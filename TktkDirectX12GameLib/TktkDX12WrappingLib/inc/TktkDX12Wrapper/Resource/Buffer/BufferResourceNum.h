#ifndef BUFFER_RESOURCE_INIT_PARAM_H_
#define BUFFER_RESOURCE_INIT_PARAM_H_

namespace tktk
{
	// それぞれのバッファーリソースの数を設定するための構造体
	struct BufferResourceNum
	{
		unsigned int vertexBufferNum;		// 頂点バッファの数
		unsigned int indexBufferNum;		// インデックスバッファの数
		unsigned int constantBufferNum;		// 定数バッファの数
		unsigned int textureBufferNum;		// テクスチャバッファの数
		unsigned int depthStencilBufferNum;	// 深度ステンシルバッファの数
		unsigned int renderTargetBufferNum;	// レンダーターゲットバッファの数
	};
}
#endif // !BUFFER_RESOURCE_INIT_PARAM_H_