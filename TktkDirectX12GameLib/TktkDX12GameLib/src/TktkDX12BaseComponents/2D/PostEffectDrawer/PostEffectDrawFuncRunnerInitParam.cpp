#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawFuncRunnerInitParam.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	PostEffectDrawFuncRunnerInitParam PostEffectDrawFuncRunnerInitParam::m_self;

	PostEffectDrawFuncRunnerInitParam& PostEffectDrawFuncRunnerInitParam::create()
	{
		m_self = PostEffectDrawFuncRunnerInitParam();

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はゲーム描画エリア
		m_self.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		return m_self;
	}
}