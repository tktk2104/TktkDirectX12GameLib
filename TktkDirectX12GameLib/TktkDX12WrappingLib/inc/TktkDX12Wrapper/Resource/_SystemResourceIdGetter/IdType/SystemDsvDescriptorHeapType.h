#ifndef SYSTEM_DSV_DESCRIPTOR_HEAP_TYPE_H_
#define SYSTEM_DSV_DESCRIPTOR_HEAP_TYPE_H_

namespace tktk
{
	// システムで使用している深度ステンシル用のディスクリプタヒープの数
	constexpr unsigned int SystemDsvDescriptorHeapNum = 2U;

	// システムで使用している深度ステンシル用のディスクリプタヒープの種類
	enum class SystemDsvDescriptorHeapType
	{
		Basic		= 0U,
		ShadowMap	= 1U
	};
}
#endif // !SYSTEM_DSV_DESCRIPTOR_HEAP_TYPE_H_