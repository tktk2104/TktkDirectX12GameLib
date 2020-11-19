#ifndef ACT_3D_GRASS_BLOCK_H_
#define ACT_3D_GRASS_BLOCK_H_

#include <TktkDX12GameLib.h>

struct Act3D_GrassBlock
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position);
};
#endif // !ACT_3D_GRASS_BLOCK_H_