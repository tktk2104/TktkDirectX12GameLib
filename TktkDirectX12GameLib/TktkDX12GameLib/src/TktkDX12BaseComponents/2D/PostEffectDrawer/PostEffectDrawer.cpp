#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

namespace tktk
{
	PostEffectDrawer::PostEffectDrawer(float drawPriority, unsigned int postEffectMaterialId, unsigned int useRtvDescriptorHeapId)
		: ComponentBase(drawPriority)
		, m_useRtvDescriptorHeapId(useRtvDescriptorHeapId)
		, m_postEffectMaterialId(postEffectMaterialId)
	{
	}

	void PostEffectDrawer::draw() const
	{
		// ポストエフェクトの描画に必要な値を構造体にまとめる
		PostEffectMaterialDrawFuncArgs drawFuncArgs{};
		drawFuncArgs.viewportId		= DX12GameManager::getSystemId(SystemViewportType::Basic);
		drawFuncArgs.scissorRectId	= DX12GameManager::getSystemId(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapId = m_useRtvDescriptorHeapId;

		// ポストエフェクトの描画を行う
		DX12GameManager::drawPostEffect(m_postEffectMaterialId, drawFuncArgs);

		// TODO : レンダーターゲットのクリア処理は仮
		DX12GameManager::setRtv(0U, 0U, 1U);
		DX12GameManager::clearRtv(0U, 0U, tktkMath::Color_v::red);
		DX12GameManager::unSetRtv(0U, 0U, 1U);
	}
}