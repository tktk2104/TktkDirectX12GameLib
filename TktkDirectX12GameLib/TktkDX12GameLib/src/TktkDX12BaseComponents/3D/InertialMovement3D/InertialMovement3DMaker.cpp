#include "TktkDX12BaseComponents/3D/InertialMovement3D/InertialMovement3DMaker.h"

namespace tktk
{
	InertialMovement3DMaker InertialMovement3DMaker::m_self;

	InertialMovement3DMaker & InertialMovement3DMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = InertialMovement3DMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<InertialMovement3D> InertialMovement3DMaker::craete()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<InertialMovement3D>(
			m_decelerationPerSec,
			m_initVelocity
			);
	}

	InertialMovement3DMaker & InertialMovement3DMaker::decelerationPerSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_decelerationPerSec = value;
		return *this;
	}

	InertialMovement3DMaker & InertialMovement3DMaker::initVelocity(const tktkMath::Vector3 & value)
	{
		// 値を設定して自身の参照を返す
		m_initVelocity = value;
		return *this;
	}
}