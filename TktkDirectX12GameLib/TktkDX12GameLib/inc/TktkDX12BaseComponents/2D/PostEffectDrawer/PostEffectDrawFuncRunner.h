#ifndef POST_EFFECT_DRAW_FUNC_RUNNER_H_
#define POST_EFFECT_DRAW_FUNC_RUNNER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	struct PostEffectDrawFuncRunnerInitParam;

	// ポストエフェクト描画コンポーネント
	class PostEffectDrawFuncRunner
		: public ComponentBase
	{
	public:

		PostEffectDrawFuncRunner(size_t postEffectMaterialHandle, const PostEffectDrawFuncRunnerInitParam& initParam);

	public:

		void draw() const;

	public:

		size_t getPostEffectMaterialHandle() const;

	private:

		size_t	m_useRtvDescriptorHeapHandle;
		size_t	m_postEffectMaterialHandle;
	};
}
#endif // !POST_EFFECT_DRAW_FUNC_RUNNER_H_
