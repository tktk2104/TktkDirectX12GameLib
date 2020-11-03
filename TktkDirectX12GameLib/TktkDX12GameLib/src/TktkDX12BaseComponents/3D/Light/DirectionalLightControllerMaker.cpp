#include "TktkDX12BaseComponents/3D/Light/DirectionalLightControllerMaker.h"

namespace tktk
{
	DirectionalLightControllerMaker DirectionalLightControllerMaker::m_self;

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = DirectionalLightControllerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するライトハンドルのデフォルト値はデフォルトライト
		m_self.m_initLightHandle = DX12GameManager::getSystemHandle(SystemLightType::DefaultLight);

		// 自身の参照を返す
		return m_self;
	}

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = DirectionalLightControllerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 使用するライトハンドルのデフォルト値はデフォルトライト
		m_self.m_initLightHandle = DX12GameManager::getSystemHandle(SystemLightType::DefaultLight);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<DirectionalLightController> DirectionalLightControllerMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			return  m_user->createComponent<DirectionalLightController>(
				m_initLightHandle,
				m_initAmbient,
				m_initDiffuse,
				m_initSpeqular
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<DirectionalLightController>(
			m_initLightHandle,
			m_initAmbient,
			m_initDiffuse,
			m_initSpeqular
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::initLightHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_initLightHandle = value;
		return *this;
	}

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::initAmbient(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_initAmbient = value;
		return *this;
	}

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::initDiffuse(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_initDiffuse = value;
		return *this;
	}

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::initSpeqular(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_initSpeqular = value;
		return *this;
	}

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::initLightIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_initLightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}