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

		// 使用するレンダーターゲットのディスクリプタヒープIDのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapId = DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BasicMeshDrawer> BasicMeshDrawerMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<BasicMeshDrawer>(
			m_drawPriority,
			m_meshId,
			m_skeletonId,
			m_cameraId,
			m_shadowMapCameraId,
			m_lightId,
			m_useRtvDescriptorHeapId
			);
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::useRtvDescriptorHeapIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapId = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::meshIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_meshId = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::skeletonIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_skeletonId = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::cameraIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraId = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::shadowMapCameraIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_shadowMapCameraId = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::lightIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_lightId = value;
		return *this;
	}
}