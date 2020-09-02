#ifndef BASIC_MESH_DRAWER_USE_RESOURCE_H_
#define BASIC_MESH_DRAWER_USE_RESOURCE_H_

namespace tktk
{
	struct BasicMeshDrawerUseResourceHandles
	{
		unsigned int rtvDescriptorHeapHandle;
		unsigned int meshHandle;
		unsigned int skeletonHandle;
		unsigned int cameraHandle;
		unsigned int shadowMapCameraHandle;
		unsigned int lightHandle;
	};
}
#endif // !BASIC_MESH_DRAWER_USE_RESOURCE_H_