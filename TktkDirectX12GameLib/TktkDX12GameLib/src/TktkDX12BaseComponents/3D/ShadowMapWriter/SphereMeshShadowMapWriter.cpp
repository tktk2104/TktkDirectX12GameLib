#include "TktkDX12BaseComponents/3D/ShadowMapWriter/SphereMeshShadowMapWriter.h"

namespace tktk
{
	SphereMeshShadowMapWriter::SphereMeshShadowMapWriter(float drawPriority, float radius, const tktkMath::Vector3& localPosition, size_t cameraHandle)
		: ComponentBase(drawPriority)
		, m_radius(radius)
		, m_localPosition(localPosition)
		, m_cameraHandle(cameraHandle)
	{
	}

	void SphereMeshShadowMapWriter::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SphereMeshShadowMapWriter not found Transform3D");
		}

		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadTransformCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform), MeshTransformCbuffer()));
	}

	void SphereMeshShadowMapWriter::onDestroy()
	{
		// アップロード用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
	}

	void SphereMeshShadowMapWriter::draw() const
	{
		// ボーン情報の定数バッファを単位行列で初期化
		DX12GameManager::resetBoneMatrixCbuffer();

		// 座標変換用の定数バッファの更新を行う
		updateTransformCbuffer();

		// シャドウマップを描画する
		DX12GameManager::writeBasicMeshShadowMap(DX12GameManager::getSystemHandle(SystemBasicMeshType::Sphere));
	}

	void SphereMeshShadowMapWriter::updateTransformCbuffer() const
	{
		// メッシュの座標変換用定数バッファ形式
		MeshTransformCbuffer transformBufferData{};

		// Transform3Dからワールド行列を取得
		transformBufferData.worldMatrix = m_transform->calculateWorldMatrix();

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