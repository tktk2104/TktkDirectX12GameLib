#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

namespace tktk
{
	PostEffectDrawer::PostEffectDrawer(float drawPriority, size_t postEffectMaterialHandle, size_t useRtvDescriptorHeapHandle)
		: ComponentBase(drawPriority)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
		, m_postEffectMaterialHandle(postEffectMaterialHandle)
	{
	}

	void PostEffectDrawer::draw() const
	{
		// ポストエフェクトの描画に必要な値を構造体にまとめる
		PostEffectMaterialDrawFuncArgs drawFuncArgs{};
		drawFuncArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		drawFuncArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapHandle	= m_useRtvDescriptorHeapHandle;

		// ポストエフェクトの描画を行う
		DX12GameManager::drawPostEffect(m_postEffectMaterialHandle, drawFuncArgs);
	}
}