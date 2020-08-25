#ifndef SYSTEM_BASIC_DESCRIPTOR_HEAP_TYPE_H_
#define SYSTEM_BASIC_DESCRIPTOR_HEAP_TYPE_H_

namespace tktk
{
	// システムで使用している通常のディスクリプタヒープの数
	constexpr unsigned int SystemBasicDescriptorHeapNum = 3U;

	// システムで使用している通常のディスクリプタヒープの種類
	enum class SystemBasicDescriptorHeapType
	{
		Line2D				= 0U,
		Sphere,
		BasicMeshShadowMap
	};
}
#endif // !SYSTEM_BASIC_DESCRIPTOR_HEAP_TYPE_H_