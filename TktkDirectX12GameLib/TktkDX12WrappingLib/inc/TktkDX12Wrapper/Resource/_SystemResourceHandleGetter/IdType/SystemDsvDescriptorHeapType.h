#ifndef SYSTEM_DSV_DESCRIPTOR_HEAP_TYPE_H_
#define SYSTEM_DSV_DESCRIPTOR_HEAP_TYPE_H_

namespace tktk
{
	// システムで使用している深度ステンシル用のディスクリプタヒープの種類
	enum class SystemDsvDescriptorHeapType
	{
		Basic,
		ShadowMap
	};
}
#endif // !SYSTEM_DSV_DESCRIPTOR_HEAP_TYPE_H_