#ifndef BASIC_DESCRIPTOR_HEAP_INIT_PARAM_H_
#define BASIC_DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <vector>
#include "../../Buffer/BufferType.h"

namespace tktk
{
	// 個々のディスクリプタの情報
	struct BasicDescriptorParam
	{
		BufferType			type	{};
		size_t				handle	{};
	};

	// このディスクリプタヒープで扱うバッファーの種類
	enum class BasicDescriptorType
	{
		constantBuffer,
		textureBuffer,
	};

	// ディスクリプタテーブルを作る時に必要な変数
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