#ifndef BASIC_DESCRIPTOR_HEAP_INIT_PARAM_H_
#define BASIC_DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <vector>
#include "../../Buffer/BufferType.h"

namespace tktk
{
	struct BasicDescriptorParam
	{
		BufferType			type	{};
		unsigned int		id		{};
	};

	enum class BasicDescriptorType
	{
		constantBuffer,
		textureBuffer,
	};

	struct BasicDescriptorTableParam
	{
		BasicDescriptorType					type				{};
		std::vector<BasicDescriptorParam>	descriptorParamArray{};
	};

	// 「CBV_SRV_UAV」のディスクリプタヒープを作るためのデータ
	struct BasicDescriptorHeapInitParam
	{
		bool									shaderVisible				{ true };
		std::vector<BasicDescriptorTableParam>	descriptorTableParamArray	{ };
	};
}
#endif // !BASIC_DESCRIPTOR_HEAP_INIT_PARAM_H_