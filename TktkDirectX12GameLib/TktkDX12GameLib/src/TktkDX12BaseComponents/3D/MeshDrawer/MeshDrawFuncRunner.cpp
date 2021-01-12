#include "TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawFuncRunner.h"

#include "TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawFuncRunnerInitParam.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/CameraCBufferData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshShadowMapCBufferData.h"

namespace tktk
{
	MeshDrawFuncRunner::MeshDrawFuncRunner(size_t meshHandle, const MeshDrawFuncRunnerInitParam& initParam)
		: ComponentBase(initParam.m_drawPriority)
		, m_useBone(initParam.m_useBone)
		, m_meshHandle(meshHandle)
		, m_rtvDescriptorHeapHandle(initParam.m_rtvDescriptorHeapHandle)
		, m_lightHandle(initParam.m_lightHandle)
		, m_cameraHandle(initParam.m_cameraHandle)
		, m_shadowMapCameraHandle(initParam.m_shadowMapCameraHandle)
	{
	}

	void MeshDrawFuncRunner::start()
	{
		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadCameraCbufferHandle		= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Camera), CameraCBufferData()));
		m_createUploadShadowMapCbufferHandle	= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::ShadowMap), MeshShadowMapCBufferData()));
	}

	void MeshDrawFuncRunner::onDestroy()
	{
		// アップロード用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadCameraCbufferHandle);
		DX12GameManager::eraseUploadBuffer(m_createUploadShadowMapCbufferHandle);
	}

	void MeshDrawFuncRunner::update()
	{
		DX12GameManager::clearMeshInstanceParam(m_meshHandle);
	}

	void MeshDrawFuncRunner::draw() const
	{
		// カメラ情報定数バッファの更新
		updateCameraCbuffer();

		// シャドウマップ用の定数バッファの更新を行う
		updateShadowMapCbuffer();

		// メッシュ描画に必要な値
		MeshDrawFuncBaseArgs baseArgs{};

		// 使用するビューポートハンドル
		baseArgs.viewportHandle = DX12GameManager::getSystemHandle(SystemViewportType::Basic);

		// 使用するシザー矩形ハンドル
		baseArgs.scissorRectHandle = DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);

		// 使用するレンダーターゲットディスクリプタヒープハンドル
		baseArgs.rtvDescriptorHeapHandle = m_rtvDescriptorHeapHandle;

		// 使用する深度ステンシルディスクリプタヒープハンドル
		baseArgs.dsvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::Basic);

		// 使用するライト番号
		baseArgs.lightHandle = m_lightHandle;

		if (m_useBone)
		{
			// スキニングメッシュを描画する
			DX12GameManager::drawMeshUseBone(m_meshHandle, baseArgs);
		}
		else
		{
			// メッシュを描画する
			DX12GameManager::drawMesh(m_meshHandle, baseArgs);
		}
	}

	void MeshDrawFuncRunner::updateCameraCbuffer() const
	{
		// カメラ情報定数バッファ形式
		CameraCBufferData transformBufferData{};

		// 使用するカメラのビュー行列
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_cameraHandle);

		// 使用するカメラのプロジェクション行列
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_cameraHandle);

		// 定数バッファのアップロード用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateUploadBuffer(m_createUploadCameraCbufferHandle, CopySourceDataCarrier(transformBufferData, 0U));

		// 座標変換用の定数バッファにアップロードバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createUploadCameraCbufferHandle);
	}

	void MeshDrawFuncRunner::updateShadowMapCbuffer() const
	{
		// メッシュのシャドウマップ描画用定数バッファ形式
		MeshShadowMapCBufferData shadowMapBufferData{};

		// シャドウマップを使用する為に必要なシャドウマップカメラ行列
		shadowMapBufferData.shadowMapViewProjMat = DX12GameManager::getViewMatrix(m_shadowMapCameraHandle) * DX12GameManager::getProjectionMatrix(m_shadowMapCameraHandle);

		// 定数バッファのアップロード用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateUploadBuffer(m_createUploadShadowMapCbufferHandle, CopySourceDataCarrier(shadowMapBufferData, 0U));

		// シャドウマップ使用用の定数バッファにアップロード用バッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createUploadShadowMapCbufferHandle);
	}
}