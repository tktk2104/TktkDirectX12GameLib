#ifndef RTV_DESCRIPTOR_HEAP_INIT_PARAM_H_
#define RTV_DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <vector>

namespace tktk
{
	// このディスクリプタヒープで扱うバッファーの種類
	enum class RtvDescriptorType
	{
		normal,
		backBuffer
	};

	// 個々のディスクリプタの情報
	struct RtvDescriptorParam
	{
		RtvDescriptorType	type;
		size_t				handle;
	};

	// レンダーターゲットビュー用のディスクリプタヒープを作る時に必要な変数
	struct RtvDescriptorHeapInitParam
	{
		bool							shaderVisible{ true };
		std::vector<RtvDescriptorParam>	descriptorParamArray{ };
	};
}
#endif // !RTV_DESCRIPTOR_HEAP_INIT_PARAM_H_