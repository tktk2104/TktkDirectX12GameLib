#ifndef POST_EFFECT_MATERIAL_DATA_H_
#define POST_EFFECT_MATERIAL_DATA_H_

#include <vector>
#include "PostEffectMaterialInitParam.h"
#include "PostEffectMaterialDrawFuncArgs.h"

namespace tktk
{
	// �|�X�g�G�t�F�N�g�}�e���A�����Ǘ�����N���X
	class PostEffectMaterialData
	{
	public:

		PostEffectMaterialData(const PostEffectMaterialInitParam& initParam);
		~PostEffectMaterialData() = default;

	public:

		// �|�X�g�G�t�F�N�g��`�悷��
		void drawPostEffect(const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		unsigned int m_usePipeLineStateHandle;
		unsigned int m_useDescriptorHeapHandle;
		std::vector<unsigned int> m_autoClearRtvDescriptorHeapHandleArray;
	};
}
#endif // !POST_EFFECT_MATERIAL_DATA_H_