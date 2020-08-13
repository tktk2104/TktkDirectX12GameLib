#ifndef DSV_DESCRIPTOR_HEAP_INIT_PARAM_H_
#define DSV_DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <vector>

namespace tktk
{
	enum class DsvDescriptorType
	{
		normal,
	};

	struct DsvDescriptorParam
	{
		DsvDescriptorType	type;
		unsigned int		id;
	};

	struct DsvDescriptorHeapInitParam
	{
		bool							shaderVisible{ true };
		std::vector<DsvDescriptorParam>	descriptorParamArray{ };
	};
}
#endif // !DSV_DESCRIPTOR_HEAP_INIT_PARAM_H_