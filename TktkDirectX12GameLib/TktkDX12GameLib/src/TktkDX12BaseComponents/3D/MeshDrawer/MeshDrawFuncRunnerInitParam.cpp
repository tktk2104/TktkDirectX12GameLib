#include "TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawFuncRunnerInitParam.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	MeshDrawFuncRunnerInitParam MeshDrawFuncRunnerInitParam::m_self;

	MeshDrawFuncRunnerInitParam& MeshDrawFuncRunnerInitParam::create()
	{
		m_self = MeshDrawFuncRunnerInitParam();

		m_self.m_rtvDescriptorHeapHandle	= DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget);
		m_self.m_lightHandle				= DX12GameManager::getSystemHandle(SystemLightType::DefaultLight);
		m_self.m_cameraHandle				= DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);
		m_self.m_shadowMapCameraHandle		= DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		return m_self;
	}

	MeshDrawFuncRunnerInitParam& MeshDrawFuncRunnerInitParam::writeShadowMap(bool value)
	{
		m_self.m_writeShadowMap = value;
		return m_self;
	}

	MeshDrawFuncRunnerInitParam& MeshDrawFuncRunnerInitParam::drawPriority(float value)
	{
		m_self.m_drawPriority = value;
		return m_self;
	}

	MeshDrawFuncRunnerInitParam& MeshDrawFuncRunnerInitParam::useBone(bool value)
	{
		m_self.m_useBone = value;
		return m_self;
	}

	MeshDrawFuncRunnerInitParam& MeshDrawFuncRunnerInitParam::useRtvDescriptorHeapHandle(size_t value)
	{
		m_self.m_rtvDescriptorHeapHandle = value;
		return m_self;
	}

	MeshDrawFuncRunnerInitParam& MeshDrawFuncRunnerInitParam::lightHandle(size_t value)
	{
		m_self.m_lightHandle = value;
		return m_self;
	}

	MeshDrawFuncRunnerInitParam& MeshDrawFuncRunnerInitParam::lightId(ResourceIdCarrier value)
	{
		m_self.m_lightHandle = DX12GameManager::getLightHandle(value);
		return m_self;
	}

	MeshDrawFuncRunnerInitParam& MeshDrawFuncRunnerInitParam::cameraHandle(size_t value)
	{
		m_self.m_cameraHandle = value;
		return m_self;
	}

	MeshDrawFuncRunnerInitParam& MeshDrawFuncRunnerInitParam::cameraId(ResourceIdCarrier value)
	{
		m_self.m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return m_self;
	}

	MeshDrawFuncRunnerInitParam& MeshDrawFuncRunnerInitParam::shadowMapCameraHandle(size_t value)
	{
		m_self.m_shadowMapCameraHandle = value;
		return m_self;
	}

	MeshDrawFuncRunnerInitParam& MeshDrawFuncRunnerInitParam::shadowMapCameraId(ResourceIdCarrier value)
	{
		m_self.m_shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
		return m_self;
	}
}