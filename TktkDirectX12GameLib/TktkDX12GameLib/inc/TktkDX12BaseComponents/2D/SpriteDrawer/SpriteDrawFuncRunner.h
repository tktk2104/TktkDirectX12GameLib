#ifndef SPRITE_DRAW_FUNC_RUNNER_H_
#define SPRITE_DRAW_FUNC_RUNNER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	struct SpriteDrawFuncRunnerInitParam;


	class SpriteDrawFuncRunner
		: public ComponentBase
	{
	public:

		SpriteDrawFuncRunner(size_t spriteHandle, const SpriteDrawFuncRunnerInitParam& initParam);

	public:

		void update();
		void draw() const;

	private:

		// 使用するリソースハンドル
		size_t m_spriteHandle;
		size_t m_rtvDescriptorHeapHandle;
	};
}
#endif // !SPRITE_DRAW_FUNC_RUNNER_H_