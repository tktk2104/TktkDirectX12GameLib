#include "TktkDX12BaseComponents/3D/MeshDrawer/BasicMeshDrawerMaker.h"

namespace tktk
{
	BasicMeshDrawerMaker BasicMeshDrawerMaker::m_self;

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BasicMeshDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BasicMeshDrawer> BasicMeshDrawerMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<BasicMeshDrawer>(
			m_drawPriority,
			m_meshHandle,
			m_skeletonHandle,
			m_cameraHandle,
			m_shadowMapCameraHandle,
			m_lightHandle,
			m_useRtvDescriptorHeapHandle
			);
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::useRtvDescriptorHeapHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::meshHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_meshHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::skeletonHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_skeletonHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::cameraHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::shadowMapCameraHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_shadowMapCameraHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::lightHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_lightHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::meshIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_meshHandle = DX12GameManager::getBasicMeshHandle(value);
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::skeletonIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_skeletonHandle = DX12GameManager::getSkeletonHandle(value);
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::cameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::shadowMapCameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::lightIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_lightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}