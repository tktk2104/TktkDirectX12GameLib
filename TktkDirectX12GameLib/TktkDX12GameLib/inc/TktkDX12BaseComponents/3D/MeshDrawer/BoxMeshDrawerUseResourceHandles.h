#ifndef BOX_MESH_DRAWER_USE_RESOURCE_HANDLES_H_
#define BOX_MESH_DRAWER_USE_RESOURCE_HANDLES_H_

namespace tktk
{
	struct BoxMeshDrawerUseResourceHandles
	{
		unsigned int rtvDescriptorHeapHandle;
		unsigned int cameraHandle;
		unsigned int shadowMapCameraHandle;
		unsigned int lightHandle;
	};
}
#endif // !BOX_MESH_DRAWER_USE_RESOURCE_HANDLES_H_