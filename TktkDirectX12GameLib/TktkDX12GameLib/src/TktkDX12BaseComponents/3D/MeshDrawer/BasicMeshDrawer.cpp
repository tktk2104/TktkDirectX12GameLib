#include "TktkDX12BaseComponents/3D/MeshDrawer/BasicMeshDrawer.h"

namespace tktk
{
	BasicMeshDrawer::BasicMeshDrawer(float drawPriority, unsigned int meshHandle, unsigned int skeletonHandle, unsigned int cameraHandle, unsigned int shadowMapCameraHandle, unsigned int lightHandle, unsigned int useRtvDescriptorHeapHandle)
		: ComponentBase(drawPriority)
		, m_meshHandle(meshHandle)
		, m_skeletonHandle(skeletonHandle)
		, m_cameraHandle(cameraHandle)
		, m_shadowMapCameraHandle(shadowMapCameraHandle)
		, m_lightHandle(lightHandle)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
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
			m_animator->transformSkeleton(m_skeletonHandle);
		}

		// ボーン行列の定数バッファを更新する
		DX12GameManager::updateBoneMatrixCbuffer(m_skeletonHandle);

		// メッシュ描画に必要な値
		MeshDrawFuncBaseArgs baseArgs{};
		{
			// Transform3Dからワールド行列を取得
			baseArgs.transformBufferData.worldMatrix				= m_transform->calculateWorldMatrix();

			// 使用するカメラのビュー行列
			baseArgs.transformBufferData.viewMatrix					= DX12GameManager::getViewMatrix(m_cameraHandle);

			// 使用するカメラのプロジェクション行列
			baseArgs.transformBufferData.projectionMatrix			= DX12GameManager::getProjectionMatrix(m_cameraHandle);

			// 使用するビューポートハンドル
			baseArgs.viewportHandle									= DX12GameManager::getSystemHandle(SystemViewportType::Basic);

			// 使用するシザー矩形ハンドル
			baseArgs.scissorRectHandle								= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);

			// 使用するレンダーターゲットディスクリプタヒープハンドル
			baseArgs.rtvDescriptorHeapHandle						= m_useRtvDescriptorHeapHandle;

			// 使用する深度ステンシルディスクリプタヒープハンドル
			baseArgs.dsvDescriptorHeapHandle						= DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::Basic);

			// 使用するライト番号
			baseArgs.lightId										= m_lightHandle;

			// シャドウマップを使用する為に必要なシャドウマップカメラ行列
			baseArgs.shadowMapBufferData.shadowMapViewProjMat		= DX12GameManager::getViewMatrix(m_shadowMapCameraHandle) * DX12GameManager::getProjectionMatrix(m_shadowMapCameraHandle);
		}

		// メッシュを描画する
		DX12GameManager::drawBasicMesh(m_meshHandle, baseArgs);
	}
}