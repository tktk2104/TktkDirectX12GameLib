#include "TktkDX12BaseComponents/2D/InertialMovement2D/InertialMovement2DMaker.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	InertialMovement2DMaker InertialMovement2DMaker::m_self;

	InertialMovement2DMaker & InertialMovement2DMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = InertialMovement2DMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<InertialMovement2D> InertialMovement2DMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<InertialMovement2D>(
			m_decelerationPerSec,
			m_initVelocity
			);
	}

	InertialMovement2DMaker & InertialMovement2DMaker::decelerationPerSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_decelerationPerSec = value;
		return *this;
	}

	InertialMovement2DMaker & InertialMovement2DMaker::initVelocity(const tktkMath::Vector2 & value)
	{
		// 値を設定して自身の参照を返す
		m_initVelocity = value;
		return *this;
	}
}