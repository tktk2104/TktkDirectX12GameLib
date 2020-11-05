#ifndef BOX_MESH_DRAWER_USE_RESOURCE_HANDLES_H_
#define BOX_MESH_DRAWER_USE_RESOURCE_HANDLES_H_

namespace tktk
{
	struct BoxMeshDrawerUseResourceHandles
	{
		size_t rtvDescriptorHeapHandle;
		size_t cameraHandle;
		size_t shadowMapCameraHandle;
		size_t lightHandle;
	};
}
#endif // !BOX_MESH_DRAWER_USE_RESOURCE_HANDLES_H_