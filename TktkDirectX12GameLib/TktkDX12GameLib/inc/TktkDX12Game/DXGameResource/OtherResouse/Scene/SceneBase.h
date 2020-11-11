#ifndef SCENE_BASE_H_
#define SCENE_BASE_H_

namespace tktk
{
	// シーンを共通のポインタで管理するためのインターフェース
	class SceneBase
	{
	public:
		virtual ~SceneBase() = default;
	};
}
#endif // !SCENE_BASE_H_