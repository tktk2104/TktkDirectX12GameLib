#ifndef ACT_3D_DEFAULT_CAMERA_H_
#define ACT_3D_DEFAULT_CAMERA_H_

#include <TktkDX12GameLib.h>

struct Act3D_DefaultCamera
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position, const tktkMath::Quaternion& rotation);
};
#endif // !ACT_3D_DEFAULT_CAMERA_H_