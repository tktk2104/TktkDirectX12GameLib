#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawFuncRunnerInitParam.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	SpriteDrawFuncRunnerInitParam SpriteDrawFuncRunnerInitParam::m_self;

	SpriteDrawFuncRunnerInitParam& SpriteDrawFuncRunnerInitParam::create()
	{
		m_self = SpriteDrawFuncRunnerInitParam();

		m_self.m_rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget);

		return m_self;
	}

	SpriteDrawFuncRunnerInitParam& SpriteDrawFuncRunnerInitParam::drawPriority(float value)
	{
		m_self.m_drawPriority = value;
		return m_self;
	}

	SpriteDrawFuncRunnerInitParam& SpriteDrawFuncRunnerInitParam::useRtvDescriptorHeapHandle(size_t value)
	{
		m_self.m_rtvDescriptorHeapHandle = value;
		return m_self;
	}
}