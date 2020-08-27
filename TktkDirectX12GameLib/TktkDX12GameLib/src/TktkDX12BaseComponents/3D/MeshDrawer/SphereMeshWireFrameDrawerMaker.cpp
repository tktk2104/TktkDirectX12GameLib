#include "TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshWireFrameDrawerMaker.h"

namespace tktk
{
	SphereMeshWireFrameDrawerMaker SphereMeshWireFrameDrawerMaker::m_self;

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = SphereMeshWireFrameDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SphereMeshWireFrameDrawer> SphereMeshWireFrameDrawerMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<SphereMeshWireFrameDrawer>(
			m_drawPriority,
			m_radius,
			m_localPosition,
			m_albedoColor,
			m_cameraHandle,
			m_shadowMapCameraHandle,
			m_lightHandle,
			m_useRtvDescriptorHeapHandle
			);
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::radius(float value)
	{
		// 値を設定して自身の参照を返す
		m_radius = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::localPosition(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_localPosition = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::albedoColor(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_albedoColor = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::useRtvDescriptorHeapHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::cameraHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::shadowMapCameraHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_shadowMapCameraHandle = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::lightHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_lightHandle = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::cameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::shadowMapCameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::lightIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_lightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}