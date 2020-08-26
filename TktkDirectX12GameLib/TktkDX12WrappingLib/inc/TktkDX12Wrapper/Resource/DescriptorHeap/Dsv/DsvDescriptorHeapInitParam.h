#ifndef DSV_DESCRIPTOR_HEAP_INIT_PARAM_H_
#define DSV_DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <vector>

namespace tktk
{
	// このディスクリプタヒープで扱うバッファーの種類
	enum class DsvDescriptorType
	{
		normal,
	};

	// 個々のディスクリプタの情報
	struct DsvDescriptorParam
	{
		DsvDescriptorType	type;
		unsigned int		handle;
	};

	// 深度ステンシルビュー用のディスクリプタヒープを作る時に必要な変数
	struct DsvDescriptorHeapInitParam
	{
		bool							shaderVisible{ true };
		std::vector<DsvDescriptorParam>	descriptorParamArray{ };
	};
}
#endif // !DSV_DESCRIPTOR_HEAP_INIT_PARAM_H_