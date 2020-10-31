#include "TktkDX12BaseComponents/3D/MeshDrawer/BasicMeshDrawer.h"

namespace tktk
{
	BasicMeshDrawer::BasicMeshDrawer(float drawPriority, const tktkMath::Vector3& baseScale, const tktkMath::Quaternion& baseRotation, const BasicMeshDrawerUseResourceHandles& useResourceHandles)
		: ComponentBase(drawPriority)
		, m_baseScale(baseScale)
		, m_baseRotation(baseRotation)
		, m_useResourceHandles(useResourceHandles)
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

		// コピー用バッファを作り、そのハンドルを取得する
		m_createCopyTransformCbufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform), MeshTransformCbuffer());
		m_createCopyShadowMapCbufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshShadowMap), MeshShadowMapCBuffer());
		m_createCopyBoneMatrixCbufferHandle = DX12GameManager::createSkeletonCopyBufferHandle(m_useResourceHandles.skeletonHandle);
	}

	void BasicMeshDrawer::onDestroy()
	{
		// コピー用バッファを削除する
		DX12GameManager::eraseCopyBuffer(m_createCopyTransformCbufferHandle);
		DX12GameManager::eraseCopyBuffer(m_createCopyShadowMapCbufferHandle);
		DX12GameManager::eraseCopyBuffer(m_createCopyBoneMatrixCbufferHandle);
	}

	void BasicMeshDrawer::draw() const
	{
		if (!m_animator.expired())
		{
			m_animator->transformSkeleton(m_useResourceHandles.skeletonHandle);
		}

		// ボーン行列の定数バッファを更新する
		DX12GameManager::updateBoneMatrixCbuffer(m_useResourceHandles.skeletonHandle, m_createCopyBoneMatrixCbufferHandle);

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
		DX12GameManager::drawBasicMesh(m_useResourceHandles.meshHandle, baseArgs);
	}

	void BasicMeshDrawer::updateTransformCbuffer() const
	{
		// メッシュの座標変換用定数バッファ形式
		MeshTransformCbuffer transformBufferData{};

		// Transform3Dからワールド行列を取得
		transformBufferData.worldMatrix = tktkMath::Matrix4::createTRS(
			m_transform->getWorldPosition(),
			m_baseRotation * m_transform->getWorldRotation(),
			tktkMath::Vector3::scale(m_baseScale, m_transform->getWorldScaleRate())
		);

		// 使用するカメラのビュー行列
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_useResourceHandles.cameraHandle);

		// 使用するカメラのプロジェクション行列
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_useResourceHandles.cameraHandle);

		// 定数バッファのコピー用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateCopyBuffer(m_createCopyTransformCbufferHandle, transformBufferData);

		// 座標変換用の定数バッファにコピーバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createCopyTransformCbufferHandle);
	}

	void BasicMeshDrawer::updateShadowMapCbuffer() const
	{
		// メッシュのシャドウマップ描画用定数バッファ形式
		MeshShadowMapCBuffer shadowMapBufferData{};

		// シャドウマップを使用する為に必要なシャドウマップカメラ行列
		shadowMapBufferData.shadowMapViewProjMat = DX12GameManager::getViewMatrix(m_useResourceHandles.shadowMapCameraHandle) * DX12GameManager::getProjectionMatrix(m_useResourceHandles.shadowMapCameraHandle);

		// 定数バッファのコピー用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateCopyBuffer(m_createCopyShadowMapCbufferHandle, shadowMapBufferData);

		// シャドウマップ使用用の定数バッファにコピーバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createCopyShadowMapCbufferHandle);
	}
}