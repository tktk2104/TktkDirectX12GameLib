#include "TktkDX12BaseComponents/3D/Camera/OrthographicCameraControllerMaker.h"

namespace tktk
{
	OrthographicCameraControllerMaker OrthographicCameraControllerMaker::m_self;

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = OrthographicCameraControllerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するカメラハンドルのデフォルト値はデフォルト通常カメラ
		m_self.m_initCameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// 自身の参照を返す
		return m_self;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = OrthographicCameraControllerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 使用するカメラハンドルのデフォルト値はデフォルト通常カメラ
		m_self.m_initCameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<OrthographicCameraController> OrthographicCameraControllerMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			return m_user->createComponent<OrthographicCameraController>(
				m_initCameraHandle,
				m_initCameraWidth,
				m_initCameraHeight,
				m_initCameraNear,
				m_initCameraFar
				);
		}
		
		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<OrthographicCameraController>(
			m_initCameraHandle,
			m_initCameraWidth,
			m_initCameraHeight,
			m_initCameraNear,
			m_initCameraFar
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraHandle = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraWidth(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraWidth = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraHeight(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraHeight = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraNear(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraNear = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraFar(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraFar = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}
}