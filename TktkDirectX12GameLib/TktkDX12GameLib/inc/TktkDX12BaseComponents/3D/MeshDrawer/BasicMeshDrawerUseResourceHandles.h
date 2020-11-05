#ifndef BASIC_MESH_DRAWER_USE_RESOURCE_H_
#define BASIC_MESH_DRAWER_USE_RESOURCE_H_

namespace tktk
{
	struct BasicMeshDrawerUseResourceHandles
	{
		size_t rtvDescriptorHeapHandle;
		size_t meshHandle;
		size_t skeletonHandle;
		size_t cameraHandle;
		size_t shadowMapCameraHandle;
		size_t lightHandle;
	};
}
#endif // !BASIC_MESH_DRAWER_USE_RESOURCE_H_