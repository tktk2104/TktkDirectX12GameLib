#ifndef SYSTEM_BASIC_DESCRIPTOR_HEAP_TYPE_H_
#define SYSTEM_BASIC_DESCRIPTOR_HEAP_TYPE_H_

namespace tktk
{
	// システムで使用している通常のディスクリプタヒープの種類
	enum class SystemBasicDescriptorHeapType
	{
		Line2D,
		Sphere,
		Box,
		SimpleMeshShadowMap,
		SkinningMeshShadowMap
	};
}
#endif // !SYSTEM_BASIC_DESCRIPTOR_HEAP_TYPE_H_