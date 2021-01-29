#ifndef SHT_2D_BASE_BACK_GROUND_SPAWN_STOPPER_SCRIPT_H_
#define SHT_2D_BASE_BACK_GROUND_SPAWN_STOPPER_SCRIPT_H_

#include <TktkDX12GameLib.h>

// 基地の背景生成停止コンポーネント
class Sht2D_BaseBackGroundSpawnStopperScript
	: public tktk::ComponentBase
{
public:

	Sht2D_BaseBackGroundSpawnStopperScript() = default;

public:

	void start();
};
#endif // !SHT_2D_BASE_BACK_GROUND_SPAWN_STOPPER_SCRIPT_H_