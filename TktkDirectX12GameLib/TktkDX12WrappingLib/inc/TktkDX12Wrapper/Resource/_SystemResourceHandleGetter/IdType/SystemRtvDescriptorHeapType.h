#ifndef SYSTEM_RTV_DESCRIPTOR_HEAP_TYPE_H_
#define SYSTEM_RTV_DESCRIPTOR_HEAP_TYPE_H_

namespace tktk
{
	// システムで使用しているレンダーターゲット用のディスクリプタヒープの数
	constexpr unsigned int SystemRtvDescriptorHeapNum = 1U;

	// システムで使用しているレンダーターゲット用のディスクリプタヒープの種類
	enum class SystemRtvDescriptorHeapType
	{
		BackBuffer = 0U
	};
}
#endif // !SYSTEM_RTV_DESCRIPTOR_HEAP_TYPE_H_