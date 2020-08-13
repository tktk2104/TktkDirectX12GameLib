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

		// 使用するレンダーターゲットのディスクリプタヒープIDのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapId = DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SphereMeshWireFrameDrawer> SphereMeshWireFrameDrawerMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<SphereMeshWireFrameDrawer>(
			m_drawPriority,
			m_radius,
			m_albedoColor,
			m_cameraId,
			m_shadowMapCameraId,
			m_lightId,
			m_useRtvDescriptorHeapId
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

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::albedoColor(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_albedoColor = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::useRtvDescriptorHeapIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapId = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::cameraIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraId = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::shadowMapCameraIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_shadowMapCameraId = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::lightIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_lightId = value;
		return *this;
	}
}