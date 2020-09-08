#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12Game/DXGameResource/Billboard/BillboardCbufferData.h"

namespace tktk
{
	BillboardDrawer::BillboardDrawer(float drawPriority, unsigned int billboardMaterialHandle, unsigned int useRtvDescriptorHeapHandle, unsigned int cameraHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate)
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

		// �R�s�[�p�o�b�t�@�����A���̃n���h�����擾����
		m_createCopyTransformCbufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Billboard), BillboardCbufferData());
	}

	void BillboardDrawer::onDestroy()
	{
		// �R�s�[�p�o�b�t�@���폜����
		DX12GameManager::eraseCopyBuffer(m_createCopyTransformCbufferHandle);
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

		// �萔�o�b�t�@�̍X�V
		DX12GameManager::updateBillboardCbuffer(m_billboardMaterialHandle, m_createCopyTransformCbufferHandle, bufferDataUpdater);

		BillboardDrawFuncBaseArgs drawFuncArgs{};
		drawFuncArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		drawFuncArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapHandle	= m_useRtvDescriptorHeapHandle;
		drawFuncArgs.dsvDescriptorHeapHandle	= DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::Basic);

		DX12GameManager::drawBillboard(m_billboardMaterialHandle, drawFuncArgs);
	}

	void BillboardDrawer::setBillboardMaterialHandle(unsigned int handle)
	{
		m_billboardMaterialHandle = handle;
	}

	void BillboardDrawer::setCenterRate(const tktkMath::Vector2& centerRate)
	{
		m_centerRate = centerRate;
	}

	void BillboardDrawer::setBillboardMaterialIdImpl(int id)
	{
		m_billboardMaterialHandle = DX12GameManager::getBillboardMaterialHandle(id);
	}
}