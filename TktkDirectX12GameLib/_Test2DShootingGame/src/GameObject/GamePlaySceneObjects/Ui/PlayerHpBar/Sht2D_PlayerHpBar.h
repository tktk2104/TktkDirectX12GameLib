#ifndef SHT_2D_PLAYER_HP_BAR_H_
#define SHT_2D_PLAYER_HP_BAR_H_

#include <TktkDX12GameLib.h>

// �v���C���[��Hp��\������Ui
struct Sht2D_PlayerHpBar
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& pos);
};
#endif // !SHT_2D_PLAYER_HP_BAR_H_