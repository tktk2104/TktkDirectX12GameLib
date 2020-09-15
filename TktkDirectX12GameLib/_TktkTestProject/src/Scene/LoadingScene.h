#ifndef LOADING_SCENE_H_
#define LOADING_SCENE_H_

#include <TktkDX12Game/DXGameResource/Scene/SceneBase.h>

class LoadingScene
	: public tktk::SceneBase
{
public:

	void start();

	void end();
};
#endif // !LOADING_SCENE_H_