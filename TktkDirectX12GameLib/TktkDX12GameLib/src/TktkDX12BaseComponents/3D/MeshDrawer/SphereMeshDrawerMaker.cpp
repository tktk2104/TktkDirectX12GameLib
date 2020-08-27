#include "TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshDrawerMaker.h"

namespace tktk
{
	SphereMeshDrawerMaker SphereMeshDrawerMaker::m_self;

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = SphereMeshDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SphereMeshDrawer> SphereMeshDrawerMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<SphereMeshDrawer>(
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

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::radius(float value)
	{
		// 値を設定して自身の参照を返す
		m_radius = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::localPosition(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_localPosition = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::albedoColor(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_albedoColor = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::useRtvDescriptorHeapHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::cameraHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::shadowMapCameraHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_shadowMapCameraHandle = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::lightHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_lightHandle = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::cameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::shadowMapCameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::lightIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_lightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}