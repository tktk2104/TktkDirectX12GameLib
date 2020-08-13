#include "TktkDX12BaseComponents/3D/MeshDrawer/BasicMeshDrawer.h"

namespace tktk
{
	BasicMeshDrawer::BasicMeshDrawer(float drawPriority, unsigned int meshId, unsigned int skeletonId, unsigned int cameraId, unsigned int shadowMapCameraId, unsigned int lightId, unsigned int useRtvDescriptorHeapId)
		: ComponentBase(drawPriority)
		, m_meshId(meshId)
		, m_skeletonId(skeletonId)
		, m_cameraId(cameraId)
		, m_shadowMapCameraId(shadowMapCameraId)
		, m_lightId(lightId)
		, m_useRtvDescriptorHeapId(useRtvDescriptorHeapId)
	{
	}

	void BasicMeshDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}

		m_animator = getComponent<MeshAnimator>();
	}

	void BasicMeshDrawer::draw() const
	{
		if (!m_animator.expired())
		{
			m_animator->transformSkeleton(m_skeletonId);
		}

		// ボーン行列の定数バッファを更新する
		DX12GameManager::updateBoneMatrixCbuffer(m_skeletonId);

		// メッシュ描画に必要な値
		MeshDrawFuncBaseArgs baseArgs{};
		{
			// Transform3Dからワールド行列を取得
			baseArgs.transformBufferData.worldMatrix = m_transform->calculateWorldMatrix();

			// 使用するカメラのビュー行列
			baseArgs.transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_cameraId);

			// 使用するカメラのプロジェクション行列
			baseArgs.transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_cameraId);

			// 使用するビューポート番号
			baseArgs.viewportId = DX12GameManager::getSystemId(SystemViewportType::Basic);

			// 使用するシザー矩形番号
			baseArgs.scissorRectId = DX12GameManager::getSystemId(SystemScissorRectType::Basic);

			// 使用するレンダーターゲットディスクリプタヒープ番号
			baseArgs.rtvDescriptorHeapId = m_useRtvDescriptorHeapId;

			// 使用する深度ステンシルディスクリプタヒープ番号
			baseArgs.dsvDescriptorHeapId = DX12GameManager::getSystemId(SystemDsvDescriptorHeapType::Basic);

			// 使用するライト番号
			baseArgs.lightId = m_lightId;

			// シャドウマップを使用する為に必要なシャドウマップカメラ行列
			baseArgs.shadowMapBufferData.shadowMapViewProjMat = DX12GameManager::getViewMatrix(m_shadowMapCameraId) * DX12GameManager::getProjectionMatrix(m_shadowMapCameraId);
		}

		// メッシュを描画する
		DX12GameManager::drawBasicMesh(m_meshId, baseArgs);
	}
}