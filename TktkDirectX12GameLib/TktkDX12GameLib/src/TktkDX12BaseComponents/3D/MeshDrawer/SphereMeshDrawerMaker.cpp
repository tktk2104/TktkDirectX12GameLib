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

		// 使用するレンダーターゲットのディスクリプタヒープIDのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapId = DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SphereMeshDrawer> SphereMeshDrawerMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<SphereMeshDrawer>(
			m_drawPriority,
			m_radius,
			m_albedoColor,
			m_cameraId,
			m_shadowMapCameraId,
			m_lightId,
			m_useRtvDescriptorHeapId
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

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::albedoColor(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_albedoColor = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::useRtvDescriptorHeapIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapId = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::cameraIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraId = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::shadowMapCameraIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_shadowMapCameraId = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::lightIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_lightId = value;
		return *this;
	}
}