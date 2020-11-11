#include"TktkDX12BaseComponents/3D/ColliderWireFrameDrawer3D/ColliderWireFrameDrawer3DMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	ColliderWireFrameDrawer3DMaker ColliderWireFrameDrawer3DMaker::m_self;

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = ColliderWireFrameDrawer3DMaker();

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

	ComponentPtr<ColliderWireFrameDrawer3D> ColliderWireFrameDrawer3DMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<ColliderWireFrameDrawer3D>(
			m_drawPriority,
			m_lineColor,
			m_useResourceHandles
			);
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::cameraId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::useRtvDescriptorHeapHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.rtvDescriptorHeapHandle = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::cameraHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.cameraHandle = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::shadowMapCameraHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.shadowMapCameraHandle = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::shadowMapCameraId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::lightHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.lightHandle = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::lightId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.lightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::lineColor(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_lineColor = value;
		return *this;
	}
}