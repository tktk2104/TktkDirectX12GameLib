#ifndef SPHERE_MESH_DRAWER_USE_RESOURCE_HANDLES_H_
#define SPHERE_MESH_DRAWER_USE_RESOURCE_HANDLES_H_

namespace tktk
{
	struct SphereMeshDrawerUseResourceHandles
	{
		size_t rtvDescriptorHeapHandle;
		size_t cameraHandle;
		size_t shadowMapCameraHandle;
		size_t lightHandle;
	};
}
#endif // !SPHERE_MESH_DRAWER_USE_RESOURCE_HANDLES_H_