#include "TktkDX12BaseComponents/3D/ShadowMapWriter/WriteMeshShadowMapFuncRunner.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/CameraCbuffer.h"

namespace tktk
{
	WriteMeshShadowMapFuncRunner::WriteMeshShadowMapFuncRunner(size_t meshHandle, bool useBone, size_t skeletonHandle)
		: ComponentBase(-1000.0f)
		, m_meshHandle(meshHandle)
		, m_useBone(useBone)
		, m_skeletonHandle(skeletonHandle)
	{
	}

	void WriteMeshShadowMapFuncRunner::start()
	{
		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadCameraCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Camera), CameraCbuffer()));
		
		// もしスケルトンが設定されていたらアップロード用バッファを作る
		if (m_skeletonHandle != 0U) m_createUploadBoneMatrixCbufferHandle = DX12GameManager::createSkeletonUploadBufferHandle(m_skeletonHandle);
	}

	void WriteMeshShadowMapFuncRunner::onDestroy()
	{
		// アップロード用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadCameraCbufferHandle);

		DX12GameManager::eraseUploadBuffer(m_createUploadBoneMatrixCbufferHandle);
	}

	void WriteMeshShadowMapFuncRunner::draw() const
	{
		// カメラ情報定数バッファの更新
		updateCameraCbuffer();

		// もしスケルトンが未設定だったら
		if (m_skeletonHandle == 0U)
		{
			// ボーン情報の定数バッファを単位行列で初期化
			DX12GameManager::resetBoneMatrixCbuffer();
		}
		// そうでなければ
		else
		{
			// ボーン行列の定数バッファを更新する
			DX12GameManager::updateBoneMatrixCbuffer(m_skeletonHandle, m_createUploadBoneMatrixCbufferHandle);
		}

		if (m_useBone)
		{
			// スキニングメッシュシャドウマップを描画する
			DX12GameManager::writeMeshShadowMapUseBone(m_meshHandle);
		}
		else
		{
			// シャドウマップを描画する
			DX12GameManager::writeMeshShadowMap(m_meshHandle);
		}
	}

	void WriteMeshShadowMapFuncRunner::updateCameraCbuffer() const
	{
		// カメラ情報定数バッファ形式
		CameraCbuffer transformBufferData{};

		// 使用するカメラのビュー行列
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera));

		// 使用するカメラのプロジェクション行列
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera));

		// 定数バッファのアップロード用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateUploadBuffer(m_createUploadCameraCbufferHandle, transformBufferData);

		// 座標変換用の定数バッファにアップロードバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createUploadCameraCbufferHandle);
	}
}