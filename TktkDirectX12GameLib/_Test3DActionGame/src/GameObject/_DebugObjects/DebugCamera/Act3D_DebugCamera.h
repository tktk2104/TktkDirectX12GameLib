#ifndef ACT_3D_DEBUG_CAMERA_H_
#define ACT_3D_DEBUG_CAMERA_H_

#include <TktkDX12GameLib.h>

struct Act3D_DebugCamera
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position);
};
#endif // !ACT_3D_DEBUG_CAMERA_H_