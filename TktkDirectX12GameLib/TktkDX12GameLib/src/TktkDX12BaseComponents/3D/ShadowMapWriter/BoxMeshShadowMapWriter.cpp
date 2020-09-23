#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BoxMeshShadowMapWriter.h"

namespace tktk
{
	BoxMeshShadowMapWriter::BoxMeshShadowMapWriter(float drawPriority, const tktkMath::Vector3& boxSize, const tktkMath::Vector3& localPosition, unsigned int cameraHandle)
		: ComponentBase(drawPriority)
		, m_boxSize(boxSize)
		, m_localPosition(localPosition)
		, m_cameraHandle(cameraHandle)
	{
	}

	void BoxMeshShadowMapWriter::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BoxMeshShadowMapWriter not found Transform3D");
		}

		// コピー用バッファを作り、そのハンドルを取得する
		m_createCopyTransformCbufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform), MeshTransformCbuffer());
	}

	void BoxMeshShadowMapWriter::onDestroy()
	{
		// コピー用バッファを削除する
		DX12GameManager::eraseCopyBuffer(m_createCopyTransformCbufferHandle);
	}

	void BoxMeshShadowMapWriter::draw() const
	{
		// ボーン情報の定数バッファを単位行列で初期化
		DX12GameManager::resetBoneMatrixCbuffer();

		// 座標変換用の定数バッファの更新を行う
		updateTransformCbuffer();

		// シャドウマップを描画する
		DX12GameManager::writeBasicMeshShadowMap(DX12GameManager::getSystemHandle(SystemBasicMeshType::Box));
	}

	void BoxMeshShadowMapWriter::updateTransformCbuffer() const
	{
		// メッシュの座標変換用定数バッファ形式
		MeshTransformCbuffer transformBufferData{};

		// Transform3Dからワールド行列を取得
		transformBufferData.worldMatrix = m_transform->calculateWorldMatrix();

		// 使用するカメラのビュー行列
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_cameraHandle);

		// 使用するカメラのプロジェクション行列
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_cameraHandle);

		// 定数バッファのコピー用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateCopyBuffer(m_createCopyTransformCbufferHandle, transformBufferData);

		// 座標変換用の定数バッファにコピーバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createCopyTransformCbufferHandle);
	}
}