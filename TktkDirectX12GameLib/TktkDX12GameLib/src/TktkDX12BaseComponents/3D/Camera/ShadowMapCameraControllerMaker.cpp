#include "TktkDX12BaseComponents/3D/Camera/ShadowMapCameraControllerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	ShadowMapCameraControllerMaker ShadowMapCameraControllerMaker::m_self;

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = ShadowMapCameraControllerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するカメラハンドルのデフォルト値はデフォルトシャドウマップカメラ
		m_self.m_initCameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<ShadowMapCameraController> ShadowMapCameraControllerMaker::create()
	{
		return m_user->createComponent<ShadowMapCameraController>(
			m_initCameraHandle,
			m_targetTag,
			m_direction,
			m_initCameraWidth,
			m_initCameraHeight,
			m_initCameraNear,
			m_initCameraFar
			);
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::initCameraHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraHandle = value;
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::initCameraId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::targetTag(GameObjectTagCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_targetTag = value;
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::direction(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_direction = value;
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::initCameraWidth(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraWidth = value;
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::initCameraHeight(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraHeight = value;
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::initCameraNear(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraNear = value;
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::initCameraFar(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraFar = value;
		return *this;
	}
}