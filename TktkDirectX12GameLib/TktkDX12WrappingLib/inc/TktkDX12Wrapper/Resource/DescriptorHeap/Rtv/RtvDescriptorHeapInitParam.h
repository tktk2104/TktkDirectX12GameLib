#ifndef RTV_DESCRIPTOR_HEAP_INIT_PARAM_H_
#define RTV_DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <vector>

namespace tktk
{
	enum class RtvDescriptorType
	{
		normal,
		backBuffer
	};

	struct RtvDescriptorParam
	{
		RtvDescriptorType	type;
		unsigned int		id;
	};

	struct RtvDescriptorHeapInitParam
	{
		bool							shaderVisible{ true };
		std::vector<RtvDescriptorParam>	descriptorParamArray{ };
	};
}
#endif // !RTV_DESCRIPTOR_HEAP_INIT_PARAM_H_