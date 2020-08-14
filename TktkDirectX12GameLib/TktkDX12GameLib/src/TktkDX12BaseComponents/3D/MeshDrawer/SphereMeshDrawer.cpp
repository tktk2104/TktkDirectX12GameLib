#include "TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshDrawer.h"

#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/BasicMonoColorMeshCbuffer.h"

namespace tktk
{
	SphereMeshDrawer::SphereMeshDrawer(float drawPriority, float radius, const tktkMath::Color& albedoColor, unsigned int cameraId, unsigned int shadowMapCameraId, unsigned int lightId, unsigned int useRtvDescriptorHeapId)
		: ComponentBase(drawPriority)
		, m_radius(radius)
		, m_albedoColor(albedoColor)
		, m_cameraId(cameraId)
		, m_shadowMapCameraId(shadowMapCameraId)
		, m_lightId(lightId)
		, m_useRtvDescriptorHeapId(useRtvDescriptorHeapId)
	{
	}

	void SphereMeshDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}
	}

	void SphereMeshDrawer::draw() const
	{
		// ボーン情報の定数バッファを単位行列で初期化
		DX12GameManager::resetBoneMatrixCbuffer();

		// 単色塗りつぶし色の定数バッファを更新する
		BasicMonoColorMeshCbuffer tempCbufferData{};
		tempCbufferData.albedoColor = m_albedoColor;
		DX12GameManager::updateMaterialAppendParam(DX12GameManager::getSystemId(SystemBasicMeshMaterialType::Sphere), DX12GameManager::getSystemId(SystemCBufferType::BasicMonoColorMeshCbuffer), tempCbufferData);

		// メッシュ描画に必要な値
		MeshDrawFuncBaseArgs baseArgs{};
		{
			// Transform3Dからワールド行列を取得し、半径の値でスケーリングする
			baseArgs.transformBufferData.worldMatrix = tktkMath::Matrix4::createScale({ m_radius * 2 }) * m_transform->calculateWorldMatrix();

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
		DX12GameManager::drawBasicMesh(DX12GameManager::getSystemId(SystemBasicMeshType::Sphere), baseArgs);
	}

	const tktkMath::Color& SphereMeshDrawer::getAlbedoColor() const
	{
		return m_albedoColor;
	}

	void SphereMeshDrawer::setAlbedoColor(const tktkMath::Color& color)
	{
		m_albedoColor = color;
	}
}