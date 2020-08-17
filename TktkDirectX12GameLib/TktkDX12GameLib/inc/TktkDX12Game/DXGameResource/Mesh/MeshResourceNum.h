#ifndef MESH_RESOURCE_NUM_H_
#define MESH_RESOURCE_NUM_H_

namespace tktk
{
	// メッシュ関連のリソースの数
	struct MeshResourceNum
	{
		unsigned int skeletonNum;
		unsigned int motionNum;
		unsigned int basicMeshNum;
		unsigned int basicMeshMaterialNum;
	};
}
#endif // !MESH_RESOURCE_NUM_H_