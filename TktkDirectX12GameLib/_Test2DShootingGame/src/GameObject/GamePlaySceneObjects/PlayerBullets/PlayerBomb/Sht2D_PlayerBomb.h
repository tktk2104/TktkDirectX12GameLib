#ifndef SHT_2D_PLAYER_BOMB_H_
#define SHT_2D_PLAYER_BOMB_H_

#include <TktkDX12GameLib.h>

// �v���C���[�{���I�u�W�F�N�g
struct Sht2D_PlayerBomb
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& position, float rotate, float moveSpeedPerSec, float activeTimeSec);
};
#endif // !SHT_2D_PLAYER_BOMB_H_