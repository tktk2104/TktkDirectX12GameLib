#ifndef GRAPHICS_PIPELINE_RESOURCE_NUM_H_
#define GRAPHICS_PIPELINE_RESOURCE_NUM_H_

#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	struct GraphicsPipeLineResourceNum
	{
		tktkContainer::ResourceContainerInitParam pipeLineStateContainerInitParam;	// パイプラインステートを管理するコンテナを初期化する時の値
		tktkContainer::ResourceContainerInitParam rootSignatureContainerInitParam;	// ルートシグネチャを管理するコンテナを初期化する時の値
	};
}
#endif // !GRAPHICS_PIPELINE_RESOURCE_NUM_H_