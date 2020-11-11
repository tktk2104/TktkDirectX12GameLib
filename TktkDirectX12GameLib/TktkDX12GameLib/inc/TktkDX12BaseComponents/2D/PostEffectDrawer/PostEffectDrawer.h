#ifndef POST_EFFECT_DRAWER_H_
#define POST_EFFECT_DRAWER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	// ポストエフェクト描画コンポーネント
	class PostEffectDrawer
		: public ComponentBase
	{
	public:

		PostEffectDrawer(float drawPriority, size_t postEffectMaterialHandle, size_t useRtvDescriptorHeapHandle);

	public:

		void draw() const;

	private:

		size_t	m_useRtvDescriptorHeapHandle;
		size_t	m_postEffectMaterialHandle;
	};
}
#endif // !POST_EFFECT_DRAWER_H_