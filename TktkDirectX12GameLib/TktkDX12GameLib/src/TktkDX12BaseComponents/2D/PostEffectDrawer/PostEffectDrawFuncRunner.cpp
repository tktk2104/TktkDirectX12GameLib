#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawFuncRunner.h"

#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawFuncRunnerInitParam.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	PostEffectDrawFuncRunner::PostEffectDrawFuncRunner(size_t postEffectMaterialHandle, const PostEffectDrawFuncRunnerInitParam& initParam)
		: ComponentBase(initParam.drawPriority)
		, m_useRtvDescriptorHeapHandle(initParam.rtvDescriptorHeapHandle)
		, m_postEffectMaterialHandle(postEffectMaterialHandle)
	{
	}

	void PostEffectDrawFuncRunner::draw() const
	{
		// �|�X�g�G�t�F�N�g�̕`��ɕK�v�Ȓl���\���̂ɂ܂Ƃ߂�
		PostEffectMaterialDrawFuncArgs drawFuncArgs{};
		drawFuncArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		drawFuncArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapHandle	= m_useRtvDescriptorHeapHandle;

		// �|�X�g�G�t�F�N�g�̕`����s��
		DX12GameManager::drawPostEffect(m_postEffectMaterialHandle, drawFuncArgs);
	}

	size_t PostEffectDrawFuncRunner::getPostEffectMaterialHandle() const
	{
		return m_postEffectMaterialHandle;
	}
}