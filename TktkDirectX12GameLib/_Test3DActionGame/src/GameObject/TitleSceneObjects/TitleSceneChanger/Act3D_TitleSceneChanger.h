#ifndef ACT_3D_TITLE_SCENE_CHANGER_H_
#define ACT_3D_TITLE_SCENE_CHANGER_H_

#include <TktkDX12GameLib.h>

// タイトルシーンから遷移させる処理を行うオブジェクト
struct Act3D_TitleSceneChanger
{
	static tktk::GameObjectPtr create();
};
#endif // !ACT_3D_TITLE_SCENE_CHANGER_H_