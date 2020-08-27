#ifndef MESH_RESOURCE_NUM_H_
#define MESH_RESOURCE_NUM_H_

#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	// ���b�V���֘A�̃��\�[�X���Ǘ�����R���e�i����邽�߂̕ϐ�
	struct MeshResourceNum
	{
		tktkContainer::ResourceContainerInitParam skeletonNum;
		tktkContainer::ResourceContainerInitParam motionNum;
		tktkContainer::ResourceContainerInitParam basicMeshNum;
		tktkContainer::ResourceContainerInitParam basicMeshMaterialNum;
	};
}
#endif // !MESH_RESOURCE_NUM_H_