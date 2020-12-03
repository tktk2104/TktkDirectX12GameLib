#include "TktkDX12BaseComponents/3D/Light/PointLightControllerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	PointLightControllerMaker PointLightControllerMaker::m_self;

	PointLightControllerMaker& PointLightControllerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = PointLightControllerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するライトハンドルのデフォルト値はデフォルトライト
		m_self.m_initLightHandle = DX12GameManager::getSystemHandle(SystemLightType::DefaultLight);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<PointLightController> PointLightControllerMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<PointLightController>(
			m_initLightHandle,
			m_initAmbient,
			m_initDiffuse,
			m_initSpeqular
			);
	}

	PointLightControllerMaker& PointLightControllerMaker::initLightHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_initLightHandle = value;
		return *this;
	}

	PointLightControllerMaker& PointLightControllerMaker::initLightId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_initLightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}

	PointLightControllerMaker& PointLightControllerMaker::initAmbient(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_initAmbient = value;
		return *this;
	}

	PointLightControllerMaker& PointLightControllerMaker::initDiffuse(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_initDiffuse = value;
		return *this;
	}

	PointLightControllerMaker& PointLightControllerMaker::initSpeqular(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_initSpeqular = value;
		return *this;
	}
}