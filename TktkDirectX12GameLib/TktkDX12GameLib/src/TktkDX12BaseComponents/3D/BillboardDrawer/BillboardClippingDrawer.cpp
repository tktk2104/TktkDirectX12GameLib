#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardClippingDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12Game/DXGameResource/Billboard/BillboardTransformCbufferData.h"

namespace tktk
{
	BillboardClippingDrawer::BillboardClippingDrawer(float drawPriority, unsigned int billboardMaterialHandle, unsigned int useRtvDescriptorHeapHandle, unsigned int cameraHandle, const tktkMath::Vector2& centerRate, const BillboardClippingParam& clippingParam)
		: ComponentBase(drawPriority)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
		, m_cameraHandle(cameraHandle)
		, m_billboardMaterialHandle(billboardMaterialHandle)
		, m_billboardCenterRate(centerRate)
		, m_clippingParam(clippingParam)
	{
	}

	void BillboardClippingDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BillboardClippingDrawer not found Transform3D");
		}

		// コピー用バッファを作り、そのハンドルを取得する
		m_createCopyTransformCbufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::BillboardTransform), BillboardTransformCbufferData());
	}

	void BillboardClippingDrawer::onDestroy()
	{
		// コピー用バッファを削除する
		DX12GameManager::eraseCopyBuffer(m_createCopyTransformCbufferHandle);
	}

	void BillboardClippingDrawer::draw() const
	{
		BillboardTransformCbufferUpdateFuncArgs transformBufferDataUpdater{};
		transformBufferDataUpdater.billboardPosition	= m_transform->getWorldPosition();
		transformBufferDataUpdater.billboardAngle		= m_transform->calculateWorldEulerAngles().z;
		auto selfScale = m_transform->getWorldScaleRate();
		transformBufferDataUpdater.billboardScale		= { selfScale.x, selfScale.y };
		transformBufferDataUpdater.textureCenterRate	= m_billboardCenterRate;
		transformBufferDataUpdater.viewMatrix			= DX12GameManager::getViewMatrix(m_cameraHandle);
		transformBufferDataUpdater.projectionMatrix		= DX12GameManager::getProjectionMatrix(m_cameraHandle);

		// 座標変換用の定数バッファの更新
		DX12GameManager::updateBillboardTransformCbufferUseClippingParam(m_billboardMaterialHandle, m_createCopyTransformCbufferHandle, transformBufferDataUpdater, m_clippingParam);

		BillboardDrawFuncBaseArgs drawFuncArgs{};
		drawFuncArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		drawFuncArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapHandle	= m_useRtvDescriptorHeapHandle;

		DX12GameManager::drawBillboard(m_billboardMaterialHandle, drawFuncArgs);
	}

	void BillboardClippingDrawer::setBillboardMaterialHandle(unsigned int handle)
	{
		m_billboardMaterialHandle = handle;
	}

	void BillboardClippingDrawer::setCenterRate(const tktkMath::Vector2& centerRate)
	{
		m_billboardCenterRate = centerRate;
	}

	void BillboardClippingDrawer::setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos)
	{
		m_clippingParam.leftTopPos = leftTopPos;
	}

	void BillboardClippingDrawer::setClippingSize(const tktkMath::Vector2& size)
	{
		m_clippingParam.size = size;
	}

	void BillboardClippingDrawer::setBillboardMaterialIdImpl(int id)
	{
		m_billboardMaterialHandle = DX12GameManager::getBillboardMaterialHandle(id);
	}
}