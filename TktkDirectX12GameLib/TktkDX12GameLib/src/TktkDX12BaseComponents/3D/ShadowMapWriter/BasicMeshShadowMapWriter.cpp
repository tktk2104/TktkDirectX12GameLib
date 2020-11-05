#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BasicMeshShadowMapWriter.h"

namespace tktk
{
	BasicMeshShadowMapWriter::BasicMeshShadowMapWriter(float drawPriority, const tktkMath::Vector3& baseScale, const tktkMath::Quaternion& baseRotation, size_t meshHandle, size_t skeletonHandle, size_t cameraHandle)
		: ComponentBase(drawPriority)
		, m_meshHandle(meshHandle)
		, m_skeletonHandle(skeletonHandle)
		, m_cameraHandle(cameraHandle)
		, m_baseScale(baseScale)
		, m_baseRotation(baseRotation)
	{
	}

	void BasicMeshShadowMapWriter::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshShadowMapWriter not found Transform3D");
		}

		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadTransformCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform), MeshTransformCbuffer()));
		m_createUploadBoneMatrixCbufferHandle = DX12GameManager::createSkeletonUploadBufferHandle(m_skeletonHandle);
	}

	void BasicMeshShadowMapWriter::onDestroy()
	{
		// アップロード用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
		DX12GameManager::eraseUploadBuffer(m_createUploadBoneMatrixCbufferHandle);
	}

	void BasicMeshShadowMapWriter::draw() const
	{
		// ボーン行列の定数バッファを更新する
		DX12GameManager::updateBoneMatrixCbuffer(m_skeletonHandle, m_createUploadBoneMatrixCbufferHandle);

		// 座標変換用の定数バッファの更新を行う
		updateTransformCbuffer();

		// シャドウマップを描画する
		DX12GameManager::writeBasicMeshShadowMap(m_meshHandle);
	}

	void BasicMeshShadowMapWriter::updateTransformCbuffer() const
	{
		// 深度マップ書き出しに必要な値
		MeshTransformCbuffer transformBufferData{};

		// Transform3Dからワールド行列を取得
		transformBufferData.worldMatrix = tktkMath::Matrix4::createTRS(
			m_transform->getWorldPosition(),
			m_baseRotation * m_transform->getWorldRotation(),
			tktkMath::Vector3::scale(m_baseScale, m_transform->getWorldScaleRate())
		);

		// 使用するカメラのビュー行列
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_cameraHandle);

		// 使用するカメラのプロジェクション行列
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_cameraHandle);

		// 定数バッファのアップロード用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateUploadBuffer(m_createUploadTransformCbufferHandle, transformBufferData);

		// 座標変換用の定数バッファにアップロード用バッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createUploadTransformCbufferHandle);
	}
}