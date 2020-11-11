#include "TktkDX12BaseComponents/3D/MeshDrawer/BasicMeshDrawerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	BasicMeshDrawerMaker BasicMeshDrawerMaker::m_self;

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BasicMeshDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するカメラハンドルのデフォルト値はデフォルト通常カメラ
		m_self.m_useResourceHandles.cameraHandle			= DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// 使用するシャドウマップカメラハンドルのデフォルト値はデフォルトシャドウマップカメラ
		m_self.m_useResourceHandles.shadowMapCameraHandle	= DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		// 使用するライトハンドルのデフォルト値はデフォルトライト
		m_self.m_useResourceHandles.lightHandle				= DX12GameManager::getSystemHandle(SystemLightType::DefaultLight);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useResourceHandles.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BasicMeshDrawer> BasicMeshDrawerMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<BasicMeshDrawer>(m_drawPriority, m_baseScale, m_baseRotation, m_useResourceHandles);
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::baseScale(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_baseScale = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::baseRotation(const tktkMath::Quaternion& value)
	{
		// 値を設定して自身の参照を返す
		m_baseRotation = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::useRtvDescriptorHeapHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.rtvDescriptorHeapHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::meshHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.meshHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::meshId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.meshHandle = DX12GameManager::getBasicMeshHandle(value);
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::skeletonHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.skeletonHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::skeletonId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.skeletonHandle = DX12GameManager::getSkeletonHandle(value);
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::cameraHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.cameraHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::cameraId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::shadowMapCameraHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.shadowMapCameraHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::shadowMapCameraId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::lightHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.lightHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::lightId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.lightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}