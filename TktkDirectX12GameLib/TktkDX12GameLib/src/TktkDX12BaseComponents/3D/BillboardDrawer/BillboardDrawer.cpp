#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawer.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardCbufferData.h"

namespace tktk
{
	BillboardDrawer::BillboardDrawer(float drawPriority, size_t billboardMaterialHandle, size_t useRtvDescriptorHeapHandle, size_t cameraHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate)
		: ComponentBase(drawPriority)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
		, m_cameraHandle(cameraHandle)
		, m_billboardMaterialHandle(billboardMaterialHandle)
		, m_centerRate(centerRate)
		, m_blendRate(blendRate)
	{
	}

	void BillboardDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BillboardDrawer not found Transform3D");
		}

		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadTransformCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Billboard), BillboardCbufferData()));
	}

	void BillboardDrawer::onDestroy()
	{
		// アップロード用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
	}

	void BillboardDrawer::draw() const
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
		DX12GameManager::updateBillboardCbuffer(m_billboardMaterialHandle, m_createUploadTransformCbufferHandle, bufferDataUpdater);

		BillboardDrawFuncBaseArgs drawFuncArgs{};
		drawFuncArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		drawFuncArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapHandle	= m_useRtvDescriptorHeapHandle;
		drawFuncArgs.dsvDescriptorHeapHandle	= DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::Basic);

		DX12GameManager::drawBillboard(m_billboardMaterialHandle, drawFuncArgs);
	}

	void BillboardDrawer::setBillboardMaterialHandle(size_t handle)
	{
		m_billboardMaterialHandle = handle;
	}

	void BillboardDrawer::setBillboardMaterialId(ResourceIdCarrier id)
	{
		m_billboardMaterialHandle = DX12GameManager::getBillboardMaterialHandle(id);
	}

	void BillboardDrawer::setCenterRate(const tktkMath::Vector2& centerRate)
	{
		m_centerRate = centerRate;
	}
}