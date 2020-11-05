#include "TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshWireFrameDrawer.h"

#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Structs/BasicMonoColorMeshCbuffer.h"

namespace tktk
{
	SphereMeshWireFrameDrawer::SphereMeshWireFrameDrawer(float drawPriority, float radius, const tktkMath::Vector3& localPosition, const tktkMath::Color& albedoColor, const SphereMeshDrawerUseResourceHandles& useResourceHandles)
		: ComponentBase(drawPriority)
		, m_radius(radius)
		, m_localPosition(localPosition)
		, m_albedoColor(albedoColor)
		, m_useResourceHandles(useResourceHandles)
	{
	}

	void SphereMeshWireFrameDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}
		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadTransformCbufferHandle		= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform), MeshTransformCbuffer()));
		m_createUploadShadowMapCbufferHandle		= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshShadowMap), MeshShadowMapCBuffer()));
		m_createUploadMonoColorMeshCbufferHandle	= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::BasicMonoColorMeshCbuffer), BasicMonoColorMeshCbuffer()));
	}

	void SphereMeshWireFrameDrawer::onDestroy()
	{
		// アップロード用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
		DX12GameManager::eraseUploadBuffer(m_createUploadShadowMapCbufferHandle);
		DX12GameManager::eraseUploadBuffer(m_createUploadMonoColorMeshCbufferHandle);
	}

	void SphereMeshWireFrameDrawer::draw() const
	{
		// ボーン情報の定数バッファを単位行列で初期化
		DX12GameManager::resetBoneMatrixCbuffer();

		// 単色塗りつぶし色の定数バッファを更新する
		{
			BasicMonoColorMeshCbuffer tempCbufferData{};
			tempCbufferData.albedoColor = m_albedoColor;

			DX12GameManager::updateUploadBuffer(m_createUploadMonoColorMeshCbufferHandle, tempCbufferData);
			DX12GameManager::copyBuffer(m_createUploadMonoColorMeshCbufferHandle);
		}

		// 座標変換用の定数バッファの更新を行う
		updateTransformCbuffer();

		// シャドウマップ用の定数バッファの更新を行う
		updateShadowMapCbuffer();

		// メッシュ描画に必要な値
		MeshDrawFuncBaseArgs baseArgs{};

		// 使用するビューポートハンドル
		baseArgs.viewportHandle = DX12GameManager::getSystemHandle(SystemViewportType::Basic);

		// 使用するシザー矩形ハンドル
		baseArgs.scissorRectHandle = DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);

		// 使用するレンダーターゲットディスクリプタヒープハンドル
		baseArgs.rtvDescriptorHeapHandle = m_useResourceHandles.rtvDescriptorHeapHandle;

		// 使用する深度ステンシルディスクリプタヒープハンドル
		baseArgs.dsvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::Basic);

		// 使用するライト番号
		baseArgs.lightHandle = m_useResourceHandles.lightHandle;

		// メッシュを描画する
		DX12GameManager::drawBasicMesh(DX12GameManager::getSystemHandle(SystemBasicMeshType::SphereWireFrame), baseArgs);
	}

	const tktkMath::Color& SphereMeshWireFrameDrawer::getAlbedoColor() const
	{
		return m_albedoColor;
	}

	void SphereMeshWireFrameDrawer::updateTransformCbuffer() const
	{
		// メッシュの座標変換用定数バッファ形式
		MeshTransformCbuffer transformBufferData{};

		// Transform3Dからワールド行列を取得
		transformBufferData.worldMatrix = tktkMath::Matrix4::createTranslation(m_localPosition) * m_transform->calculateWorldMatrix();

		// 使用するカメラのビュー行列
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_useResourceHandles.cameraHandle);

		// 使用するカメラのプロジェクション行列
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_useResourceHandles.cameraHandle);

		// 定数バッファのアップロード用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateUploadBuffer(m_createUploadTransformCbufferHandle, transformBufferData);

		// 座標変換用の定数バッファにアップロード用バッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createUploadTransformCbufferHandle);
	}

	void SphereMeshWireFrameDrawer::updateShadowMapCbuffer() const
	{
		// メッシュのシャドウマップ描画用定数バッファ形式
		MeshShadowMapCBuffer shadowMapBufferData{};

		// シャドウマップを使用する為に必要なシャドウマップカメラ行列
		shadowMapBufferData.shadowMapViewProjMat = DX12GameManager::getViewMatrix(m_useResourceHandles.shadowMapCameraHandle) * DX12GameManager::getProjectionMatrix(m_useResourceHandles.shadowMapCameraHandle);

		// 定数バッファのアップロード用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateUploadBuffer(m_createUploadShadowMapCbufferHandle, shadowMapBufferData);

		// シャドウマップ使用用の定数バッファにアップロード用バッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createUploadShadowMapCbufferHandle);
	}
}