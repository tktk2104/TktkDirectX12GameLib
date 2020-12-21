#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawFuncRunner.h"

#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawFuncRunnerInitParam.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/CameraCBufferData.h"

namespace tktk
{
	BillboardDrawFuncRunner::BillboardDrawFuncRunner(size_t billboardHandle, const BillboardDrawFuncRunnerInitParam& initParam)
		: ComponentBase(initParam.m_drawPriority)
		, m_billboardHandle(billboardHandle)
		, m_rtvDescriptorHeapHandle(initParam.m_rtvDescriptorHeapHandle)
		, m_cameraHandle(initParam.m_cameraHandle)
	{
	}

	void BillboardDrawFuncRunner::start()
	{
		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadCameraCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Camera), CameraCBufferData()));
	}

	void BillboardDrawFuncRunner::onDestroy()
	{
		// �A�b�v���[�h�p�o�b�t�@���폜����
		DX12GameManager::eraseUploadBuffer(m_createUploadCameraCbufferHandle);
	}

	void BillboardDrawFuncRunner::update()
	{
		DX12GameManager::clearBillboardInstanceParam(m_billboardHandle);
	}

	void BillboardDrawFuncRunner::draw() const
	{
		// �J�������萔�o�b�t�@�̍X�V
		updateCameraCbuffer();

		// �w�肵���r���{�[�h���C���X�^���X�`�悷�鎞�Ɏg�p����l�����\�[�g���Ē��_�o�b�t�@�ɏ�������
		DX12GameManager::updateBillboardInstanceParam(m_billboardHandle, DX12GameManager::getViewMatrix(m_cameraHandle) * DX12GameManager::getProjectionMatrix(m_cameraHandle));

		BillboardDrawFuncBaseArgs baseArgs{};
		baseArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		baseArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		baseArgs.rtvDescriptorHeapHandle	= m_rtvDescriptorHeapHandle;
		baseArgs.dsvDescriptorHeapHandle	= DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::Basic);
	
		DX12GameManager::drawBillboard(m_billboardHandle, baseArgs);
	}

	void BillboardDrawFuncRunner::updateCameraCbuffer() const
	{
		// �J�������萔�o�b�t�@�`��
		CameraCBufferData transformBufferData{};

		// �g�p����J�����̃r���[�s��
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_cameraHandle);

		// �g�p����J�����̃v���W�F�N�V�����s��
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_cameraHandle);

		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateUploadBuffer(m_createUploadCameraCbufferHandle, transformBufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�ɃA�b�v���[�h�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createUploadCameraCbufferHandle);
	}
}