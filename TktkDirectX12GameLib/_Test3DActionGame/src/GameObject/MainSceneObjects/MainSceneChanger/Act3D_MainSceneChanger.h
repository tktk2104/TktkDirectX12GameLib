#ifndef ACT_3D_MAIN_SCENE_CHANGER_H_
#define ACT_3D_MAIN_SCENE_CHANGER_H_

#include <TktkDX12GameLib.h>

// メインシーンから遷移させる処理を行うオブジェクト
struct Act3D_MainSceneChanger
{
	static tktk::GameObjectPtr create();
};
#endif // !ACT_3D_MAIN_SCENE_CHANGER_H_