#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BasicMeshShadowMapWriter.h"

namespace tktk
{
	BasicMeshShadowMapWriter::BasicMeshShadowMapWriter(float drawPriority, unsigned int meshId, unsigned int skeletonId, unsigned int cameraId)
		: ComponentBase(drawPriority)
		, m_meshId(meshId)
		, m_skeletonId(skeletonId)
		, m_cameraId(cameraId)
	{
	}

	void BasicMeshShadowMapWriter::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshShadowMapWriter not found Transform3D");
		}
	}

	void BasicMeshShadowMapWriter::draw() const
	{
		// ボーン行列の定数バッファを更新する
		DX12GameManager::updateBoneMatrixCbuffer(m_skeletonId);

		// 深度マップ書き出しに必要な値
		MeshTransformCbuffer transformBufferData{};
		{
			// Transform3Dからワールド行列を取得
			transformBufferData.worldMatrix = m_transform->calculateWorldMatrix();

			// 使用するカメラのビュー行列
			transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_cameraId);

			// 使用するカメラのプロジェクション行列
			transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_cameraId);
		}

		// シャドウマップを描画する
		DX12GameManager::writeBasicMeshShadowMap(m_meshId, transformBufferData);
	}
}