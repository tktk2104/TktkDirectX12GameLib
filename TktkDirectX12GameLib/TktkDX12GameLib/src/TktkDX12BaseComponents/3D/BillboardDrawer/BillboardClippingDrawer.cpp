#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardClippingDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardCbufferData.h"

namespace tktk
{
	BillboardClippingDrawer::BillboardClippingDrawer(float drawPriority, size_t billboardMaterialHandle, size_t useRtvDescriptorHeapHandle, size_t cameraHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate, const BillboardClippingParam& clippingParam)
		: ComponentBase(drawPriority)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
		, m_cameraHandle(cameraHandle)
		, m_billboardMaterialHandle(billboardMaterialHandle)
		, m_centerRate(centerRate)
		, m_blendRate(blendRate)
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

		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadTransformCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Billboard), BillboardCbufferData()));
	}

	void BillboardClippingDrawer::onDestroy()
	{
		// アップロード用用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
	}

	void BillboardClippingDrawer::draw() const
	{
		BillboardCbufferUpdateFuncArgs bufferDataUpdater{};
		bufferDataUpdater.billboardPosition	= m_transform->getWorldPosition();
		bufferDataUpdater.billboardAngle	= m_transform->calculateWorldEulerAngles().z;
		auto selfScale = m_transform->getWorldScaleRate();
		bufferDataUpdater.billboardScale	= { selfScale.x, selfScale.y };
		bufferDataUpdater.textureCenterRate	= m_centerRate;
		bufferDataUpdater.viewMatrix		= DX12GameManager::getViewMatrix(m_cameraHandle);
		bufferDataUpdater.projectionMatrix	= DX12GameManager::getProjectionMatrix(m_cameraHandle);
		bufferDataUpdater.blendRate			= m_blendRate;

		// 定数バッファの更新
		DX12GameManager::updateBillboardCbufferUseClippingParam(m_billboardMaterialHandle, m_createUploadTransformCbufferHandle, bufferDataUpdater, m_clippingParam);

		BillboardDrawFuncBaseArgs drawFuncArgs{};
		drawFuncArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		drawFuncArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapHandle	= m_useRtvDescriptorHeapHandle;
		drawFuncArgs.dsvDescriptorHeapHandle	= DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::Basic);

		DX12GameManager::drawBillboard(m_billboardMaterialHandle, drawFuncArgs);
	}

	void BillboardClippingDrawer::setBillboardMaterialHandle(size_t handle)
	{
		m_billboardMaterialHandle = handle;
	}

	void BillboardClippingDrawer::setBillboardMaterialId(ResourceIdCarrier id)
	{
		m_billboardMaterialHandle = DX12GameManager::getBillboardMaterialHandle(id);
	}

	void BillboardClippingDrawer::setCenterRate(const tktkMath::Vector2& centerRate)
	{
		m_centerRate = centerRate;
	}

	void BillboardClippingDrawer::setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos)
	{
		m_clippingParam.leftTopPos = leftTopPos;
	}

	void BillboardClippingDrawer::setClippingSize(const tktkMath::Vector2& size)
	{
		m_clippingParam.size = size;
	}
}