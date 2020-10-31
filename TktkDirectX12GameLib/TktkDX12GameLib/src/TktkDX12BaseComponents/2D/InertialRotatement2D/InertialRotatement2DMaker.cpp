#include "TktkDX12BaseComponents/2D/InertialRotatement2D/InertialRotatement2DMaker.h"

namespace tktk
{
	InertialRotatement2DMaker InertialRotatement2DMaker::m_self;

	InertialRotatement2DMaker & InertialRotatement2DMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = InertialRotatement2DMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<InertialRotatement2D> InertialRotatement2DMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<InertialRotatement2D>(
				m_decelerationPerSec,
				m_initVelocity
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<InertialRotatement2D>(
			m_decelerationPerSec,
			m_initVelocity
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	InertialRotatement2DMaker & InertialRotatement2DMaker::decelerationPerSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_decelerationPerSec = value;
		return *this;
	}

	InertialRotatement2DMaker & InertialRotatement2DMaker::initVelocity(float value)
	{
		// 値を設定して自身の参照を返す
		m_initVelocity = value;
		return *this;
	}
}