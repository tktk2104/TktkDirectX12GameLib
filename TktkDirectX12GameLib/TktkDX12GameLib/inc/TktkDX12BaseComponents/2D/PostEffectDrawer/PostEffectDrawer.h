#ifndef POST_EFFECT_DRAWER_H_
#define POST_EFFECT_DRAWER_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	// �|�X�g�G�t�F�N�g�`��R���|�[�l���g
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