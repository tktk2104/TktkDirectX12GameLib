#ifndef MESH_RESOURCE_NUM_H_
#define MESH_RESOURCE_NUM_H_

#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	// メッシュ関連のリソースを管理するコンテナを作るための変数
	struct MeshResourceNum
	{
		tktkContainer::ResourceContainerInitParam skeletonNum;
		tktkContainer::ResourceContainerInitParam motionNum;
		tktkContainer::ResourceContainerInitParam basicMeshNum;
		tktkContainer::ResourceContainerInitParam basicMeshMaterialNum;
	};
}
#endif // !MESH_RESOURCE_NUM_H_