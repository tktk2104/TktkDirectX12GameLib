#include "TktkDX12BaseComponents/2D/InertialRotatement2D/InertialRotatement2DMaker.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

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
		// コンポーネントを作成する
		return m_user->createComponent<InertialRotatement2D>(
			m_decelerationPerSec,
			m_initVelocity
			);
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