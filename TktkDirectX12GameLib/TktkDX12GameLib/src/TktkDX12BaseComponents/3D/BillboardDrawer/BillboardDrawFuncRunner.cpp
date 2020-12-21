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
		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadCameraCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Camera), CameraCBufferData()));
	}

	void BillboardDrawFuncRunner::onDestroy()
	{
		// アップロード用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadCameraCbufferHandle);
	}

	void BillboardDrawFuncRunner::update()
	{
		DX12GameManager::clearBillboardInstanceParam(m_billboardHandle);
	}

	void BillboardDrawFuncRunner::draw() const
	{
		// カメラ情報定数バッファの更新
		updateCameraCbuffer();

		// 指定したビルボードをインスタンス描画する時に使用する値をｚソートして頂点バッファに書き込む
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
		// カメラ情報定数バッファ形式
		CameraCBufferData transformBufferData{};

		// 使用するカメラのビュー行列
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_cameraHandle);

		// 使用するカメラのプロジェクション行列
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_cameraHandle);

		// 定数バッファのアップロード用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateUploadBuffer(m_createUploadCameraCbufferHandle, transformBufferData);

		// 座標変換用の定数バッファにアップロードバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createUploadCameraCbufferHandle);
	}
}