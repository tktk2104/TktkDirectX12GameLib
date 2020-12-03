#ifndef ACT_3D_RESULT_SCENE_BACKGROUND_SCRIPT_H_
#define ACT_3D_RESULT_SCENE_BACKGROUND_SCRIPT_H_

#include <TktkDX12GameLib.h>

// ゲームの状況により表示内容を変化させるコンポーネント
class Act3D_ResultSceneBackGroundScript
	: public tktk::ComponentBase
{
public:

	Act3D_ResultSceneBackGroundScript() = default;

public:

	void start();
};
#endif // !ACT_3D_RESULT_SCENE_BACKGROUND_SCRIPT_H_