#ifndef BUFFER_RESOURCE_INIT_PARAM_H_
#define BUFFER_RESOURCE_INIT_PARAM_H_

#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	// それぞれのバッファーリソースの数を設定するための構造体
	struct BufferResourceNum
	{
		tktkContainer::ResourceContainerInitParam copyBufferContainerInitParam;		// コピーバッファを管理するコンテナを初期化する時の値
		tktkContainer::ResourceContainerInitParam vertexBufferContainerInitParam;	// 頂点バッファを管理するコンテナを初期化する時の値
		tktkContainer::ResourceContainerInitParam indexBufferContainerInitParam;	// インデックスバッファを管理するコンテナを初期化する時の値
		tktkContainer::ResourceContainerInitParam cbufferContainerInitParam;		// 定数バッファを管理するコンテナを初期化する時の値
		tktkContainer::ResourceContainerInitParam textureBufferStaticNodeNum;		// テクスチャバッファを管理するコンテナを初期化する時の値
		tktkContainer::ResourceContainerInitParam dsbufferStaticNodeNum;			// 深度ステンシルバッファを管理するコンテナを初期化する時の値
		tktkContainer::ResourceContainerInitParam rtbufferStaticNodeNum;			// レンダーターゲットバッファを管理するコンテナを初期化する時の値
	};
}
#endif // !BUFFER_RESOURCE_INIT_PARAM_H_