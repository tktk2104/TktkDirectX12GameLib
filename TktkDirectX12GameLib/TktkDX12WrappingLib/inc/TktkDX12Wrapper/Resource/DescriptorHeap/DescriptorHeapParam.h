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
		DescriptorHeapType	m_type;
		unsigned int		m_id;
	};
}
#endif // !DESCRIPTOR_HEAP_PARAM_H_