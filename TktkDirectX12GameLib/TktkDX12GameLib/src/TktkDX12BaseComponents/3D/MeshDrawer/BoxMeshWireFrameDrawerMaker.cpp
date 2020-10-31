#include "TktkDX12BaseComponents/3D/MeshDrawer/BoxMeshWireFrameDrawerMaker.h"

namespace tktk
{
	BoxMeshWireFrameDrawerMaker BoxMeshWireFrameDrawerMaker::m_self;

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BoxMeshWireFrameDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するカメラハンドルのデフォルト値はデフォルト通常カメラ
		m_self.m_useResourceHandles.cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// 使用するシャドウマップカメラハンドルのデフォルト値はデフォルトシャドウマップカメラ
		m_self.m_useResourceHandles.shadowMapCameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		// 使用するライトハンドルのデフォルト値はデフォルトライト
		m_self.m_useResourceHandles.lightHandle = DX12GameManager::getSystemHandle(SystemLightType::DefaultLight);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useResourceHandles.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BoxMeshWireFrameDrawer> BoxMeshWireFrameDrawerMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<BoxMeshWireFrameDrawer>(
				m_drawPriority,
				m_boxSize,
				m_localPosition,
				m_albedoColor,
				m_useResourceHandles
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<BoxMeshWireFrameDrawer>(
			m_drawPriority,
			m_boxSize,
			m_localPosition,
			m_albedoColor,
			m_useResourceHandles
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::boxSize(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_boxSize = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::localPosition(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_localPosition = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::albedoColor(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_albedoColor = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::useRtvDescriptorHeapHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.rtvDescriptorHeapHandle = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::cameraHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.cameraHandle = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::shadowMapCameraHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.shadowMapCameraHandle = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::lightHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.lightHandle = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::cameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::shadowMapCameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::lightIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_useResourceHandles.lightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}