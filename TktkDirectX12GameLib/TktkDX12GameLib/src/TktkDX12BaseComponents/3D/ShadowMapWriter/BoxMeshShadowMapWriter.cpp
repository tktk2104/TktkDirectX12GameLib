#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BoxMeshShadowMapWriter.h"

#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshTransformCbuffer.h"

namespace tktk
{
	BoxMeshShadowMapWriter::BoxMeshShadowMapWriter(float drawPriority, const tktkMath::Vector3& boxSize, const tktkMath::Vector3& localPosition, size_t cameraHandle)
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

		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadTransformCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform), MeshTransformCbuffer()));
	}

	void BoxMeshShadowMapWriter::onDestroy()
	{
		// アップロード用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
	}

	void BoxMeshShadowMapWriter::draw() const
	{
		// ボーン情報の定数バッファを単位行列で初期化
		DX12GameManager::resetBoneMatrixCbuffer();

		// 座標変換用の定数バッファの更新を行う
		updateTransformCbuffer();

		// シャドウマップを描画する
		DX12GameManager::writeMeshShadowMap(DX12GameManager::getSystemHandle(SystemBasicMeshType::Box));
	}

	void BoxMeshShadowMapWriter::updateTransformCbuffer() const
	{
		// メッシュの座標変換用定数バッファ形式
		MeshTransformCbuffer transformBufferData{};

		// Transform3Dからワールド行列を取得
		transformBufferData.worldMatrix = tktkMath::Matrix4::createTRS(
			m_localPosition + m_transform->getWorldPosition(),
			m_transform->getWorldRotation(),
			tktkMath::Vector3::scale(m_boxSize * 0.5f, m_transform->getWorldScaleRate())
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