#include "TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshWireFrameDrawer.h"

#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Structs/BasicMonoColorMeshCbuffer.h"

namespace tktk
{
	SphereMeshWireFrameDrawer::SphereMeshWireFrameDrawer(float drawPriority, float radius, const tktkMath::Color& albedoColor, unsigned int cameraId, unsigned int shadowMapCameraId, unsigned int lightId, unsigned int useRtvDescriptorHeapHandle)
		: ComponentBase(drawPriority)
		, m_radius(radius)
		, m_albedoColor(albedoColor)
		, m_cameraId(cameraId)
		, m_shadowMapCameraId(shadowMapCameraId)
		, m_lightId(lightId)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
	{
	}

	void SphereMeshWireFrameDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}
	}

	void SphereMeshWireFrameDrawer::draw() const
	{
		// ボーン情報の定数バッファを単位行列で初期化
		DX12GameManager::resetBoneMatrixCbuffer();

		// 単色塗りつぶし色の定数バッファを更新する
		BasicMonoColorMeshCbuffer tempCbufferData{};
		tempCbufferData.albedoColor = m_albedoColor;
		DX12GameManager::updateMaterialAppendParam(DX12GameManager::getSystemId(SystemBasicMeshMaterialType::SphereWireFrame), DX12GameManager::getSystemHandle(SystemCBufferType::BasicMonoColorMeshCbuffer), tempCbufferData);

		// メッシュ描画に必要な値
		MeshDrawFuncBaseArgs baseArgs{};
		{
			// Transform3Dからワールド行列を取得し、半径の値でスケーリングする
			baseArgs.transformBufferData.worldMatrix			= tktkMath::Matrix4::createScale({ m_radius * 2 }) * m_transform->calculateWorldMatrix();

			// 使用するカメラのビュー行列
			baseArgs.transformBufferData.viewMatrix				= DX12GameManager::getViewMatrix(m_cameraId);

			// 使用するカメラのプロジェクション行列
			baseArgs.transformBufferData.projectionMatrix		= DX12GameManager::getProjectionMatrix(m_cameraId);

			// 使用するビューポートハンドル
			baseArgs.viewportHandle								= DX12GameManager::getSystemHandle(SystemViewportType::Basic);

			// 使用するシザー矩形ハンドル
			baseArgs.scissorRectHandle							= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);

			// 使用するレンダーターゲットディスクリプタヒープハンドル
			baseArgs.rtvDescriptorHeapHandle					= m_useRtvDescriptorHeapHandle;

			// 使用する深度ステンシルディスクリプタヒープハンドル
			baseArgs.dsvDescriptorHeapHandle					= DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::Basic);

			// 使用するライト番号
			baseArgs.lightId									= m_lightId;

			// シャドウマップを使用する為に必要なシャドウマップカメラ行列
			baseArgs.shadowMapBufferData.shadowMapViewProjMat	= DX12GameManager::getViewMatrix(m_shadowMapCameraId) * DX12GameManager::getProjectionMatrix(m_shadowMapCameraId);
		}

		// メッシュを描画する
		DX12GameManager::drawBasicMesh(DX12GameManager::getSystemId(SystemBasicMeshType::SphereWireFrame), baseArgs);
	}

	const tktkMath::Color& SphereMeshWireFrameDrawer::getAlbedoColor() const
	{
		return m_albedoColor;
	}
}