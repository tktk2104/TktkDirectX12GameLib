#ifndef DESCRIPTOR_HEAP_INIT_PARAM_H_
#define DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	struct DescriptorHeapNum
	{
		tktkContainer::ResourceContainerInitParam basicDescriptorHeapContainerInitParam;	// 通常のディスクリプタヒープを管理するコンテナを初期化する時の値
		tktkContainer::ResourceContainerInitParam rtvDescriptorHeapContainerInitParam;		// レンダーターゲットビュー用のディスクリプタヒープを管理するコンテナを初期化する時の値
		tktkContainer::ResourceContainerInitParam dsvDescriptorHeapContainerInitParam;		// 深度ステンシルビュー用のディスクリプタヒープを管理するコンテナを初期化する時の値
	};
}
#endif // !DESCRIPTOR_HEAP_INIT_PARAM_H_