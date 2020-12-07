#include "TktkDX12BaseComponents/3D/Camera/BasicCameraControllerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

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
		m_self.m_initCameraAspect = DX12GameManager::getDrawGameAreaSize().x / DX12GameManager::getDrawGameAreaSize().y;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BasicCameraController> BasicCameraControllerMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<BasicCameraController>(
			m_initCameraHandle,
			m_initCameraFov,
			m_initCameraAspect,
			m_initCameraNear,
			m_initCameraFar
			);
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraHandle = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraHandle = DX12GameManager::getCameraHandle(value);
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
}