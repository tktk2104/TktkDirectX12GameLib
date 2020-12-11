#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawFuncRunnerInitParam.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BillboardDrawFuncRunnerInitParam BillboardDrawFuncRunnerInitParam::m_self;

	BillboardDrawFuncRunnerInitParam& BillboardDrawFuncRunnerInitParam::create()
	{
		m_self = BillboardDrawFuncRunnerInitParam();

		m_self.m_rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget);
		m_self.m_cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		return m_self;
	}

	BillboardDrawFuncRunnerInitParam& BillboardDrawFuncRunnerInitParam::drawPriority(float value)
	{
		m_self.m_drawPriority = value;
		return m_self;
	}

	BillboardDrawFuncRunnerInitParam& BillboardDrawFuncRunnerInitParam::useRtvDescriptorHeapHandle(size_t value)
	{
		m_self.m_rtvDescriptorHeapHandle = value;
		return m_self;
	}

	BillboardDrawFuncRunnerInitParam& BillboardDrawFuncRunnerInitParam::cameraHandle(size_t value)
	{
		m_self.m_cameraHandle = value;
		return m_self;
	}

	BillboardDrawFuncRunnerInitParam& BillboardDrawFuncRunnerInitParam::cameraId(ResourceIdCarrier value)
	{
		m_self.m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return m_self;
	}
}