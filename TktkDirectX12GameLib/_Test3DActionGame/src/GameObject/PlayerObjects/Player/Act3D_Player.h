#ifndef ACT_3D_PLAYER_H_
#define ACT_3D_PLAYER_H_

#include <TktkDX12GameLib.h>

// �v���C���[�I�u�W�F�N�g
struct Act3D_Player
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation);
};
#endif // !ACT_3D_PLAYER_H_