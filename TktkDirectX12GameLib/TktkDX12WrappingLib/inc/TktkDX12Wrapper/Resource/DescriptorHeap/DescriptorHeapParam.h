#ifndef DESCRIPTOR_HEAP_PARAM_H_
#define DESCRIPTOR_HEAP_PARAM_H_

namespace tktk
{
	enum class DescriptorHeapType
	{
		basic,
		rtv,
		dsv
	};

	struct DescriptorHeapParam
	{
		DescriptorHeapType	type;
		size_t				handle;
	};
}
#endif // !DESCRIPTOR_HEAP_PARAM_H_