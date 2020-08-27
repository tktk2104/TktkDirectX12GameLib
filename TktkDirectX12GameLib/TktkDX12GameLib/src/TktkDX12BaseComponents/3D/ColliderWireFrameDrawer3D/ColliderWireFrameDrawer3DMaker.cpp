#include"TktkDX12BaseComponents/3D/ColliderWireFrameDrawer3D/ColliderWireFrameDrawer3DMaker.h"

namespace tktk
{
	ColliderWireFrameDrawer3DMaker ColliderWireFrameDrawer3DMaker::m_self;

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = ColliderWireFrameDrawer3DMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<ColliderWireFrameDrawer3D> ColliderWireFrameDrawer3DMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<ColliderWireFrameDrawer3D>(
			m_drawPriority,
			m_cameraHandle,
			m_shadowMapCameraHandle,
			m_lightHandle,
			m_useRtvDescriptorHeapHandle,
			m_lineColor
			);
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::useRtvDescriptorHeapHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::cameraHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::shadowMapCameraHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_shadowMapCameraHandle = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::lightHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_lightHandle = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::lineColor(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_lineColor = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::cameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::shadowMapCameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::lightIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_lightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}