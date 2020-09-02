#ifndef SPHERE_MESH_DRAWER_USE_RESOURCE_HANDLES_H_
#define SPHERE_MESH_DRAWER_USE_RESOURCE_HANDLES_H_

namespace tktk
{
	struct SphereMeshDrawerUseResourceHandles
	{
		unsigned int rtvDescriptorHeapHandle;
		unsigned int cameraHandle;
		unsigned int shadowMapCameraHandle;
		unsigned int lightHandle;
	};
}
#endif // !SPHERE_MESH_DRAWER_USE_RESOURCE_HANDLES_H_