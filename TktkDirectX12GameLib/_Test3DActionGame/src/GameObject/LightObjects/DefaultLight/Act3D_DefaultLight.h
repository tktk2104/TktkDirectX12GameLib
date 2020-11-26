#ifndef ACT_3D_DEFAULT_LIGHT_H_
#define ACT_3D_DEFAULT_LIGHT_H_

#include <TktkDX12GameLib.h>

struct Act3D_DefaultLight
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position);
};
#endif // !ACT_3D_DEFAULT_LIGHT_H_