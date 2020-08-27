#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BasicMeshShadowMapWriter.h"

namespace tktk
{
	BasicMeshShadowMapWriter::BasicMeshShadowMapWriter(float drawPriority, unsigned int meshHandle, unsigned int skeletonHandle, unsigned int cameraHandle)
		: ComponentBase(drawPriority)
		, m_meshHandle(meshHandle)
		, m_skeletonHandle(skeletonHandle)
		, m_cameraHandle(cameraHandle)
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
		DX12GameManager::updateBoneMatrixCbuffer(m_skeletonHandle);

		// 深度マップ書き出しに必要な値
		MeshTransformCbuffer transformBufferData{};
		{
			// Transform3Dからワールド行列を取得
			transformBufferData.worldMatrix			= m_transform->calculateWorldMatrix();

			// 使用するカメラのビュー行列
			transformBufferData.viewMatrix			= DX12GameManager::getViewMatrix(m_cameraHandle);

			// 使用するカメラのプロジェクション行列
			transformBufferData.projectionMatrix	= DX12GameManager::getProjectionMatrix(m_cameraHandle);
		}

		// シャドウマップを描画する
		DX12GameManager::writeBasicMeshShadowMap(m_meshHandle, transformBufferData);
	}
}