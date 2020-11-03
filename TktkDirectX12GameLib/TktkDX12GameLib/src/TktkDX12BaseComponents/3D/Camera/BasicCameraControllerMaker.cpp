#include "TktkDX12BaseComponents/3D/Camera/BasicCameraControllerMaker.h"

namespace tktk
{
	BasicCameraControllerMaker BasicCameraControllerMaker::m_self;

	BasicCameraControllerMaker& BasicCameraControllerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BasicCameraControllerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するカメラハンドルのデフォルト値はデフォルト通常カメラ
		m_self.m_initCameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// カメラアスペクト比のデフォルト値はゲームスクリーンの比率
		m_self.m_initCameraAspect = DX12GameManager::getWindowSize().x / DX12GameManager::getWindowSize().y;

		// 自身の参照を返す
		return m_self;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BasicCameraControllerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 使用するカメラハンドルのデフォルト値はデフォルト通常カメラ
		m_self.m_initCameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// カメラアスペクト比のデフォルト値はゲームスクリーンの比率
		m_self.m_initCameraAspect = DX12GameManager::getWindowSize().x / DX12GameManager::getWindowSize().y;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BasicCameraController> BasicCameraControllerMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			return m_user->createComponent<BasicCameraController>(
				m_initCameraHandle,
				m_initCameraFov,
				m_initCameraAspect,
				m_initCameraNear,
				m_initCameraFar
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<BasicCameraController>(
			m_initCameraHandle,
			m_initCameraFov,
			m_initCameraAspect,
			m_initCameraNear,
			m_initCameraFar
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraHandle = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraFov(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraFov = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraAspect(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraAspect = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraNear(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraNear = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraFar(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraFar = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}
}