#include "TktkDX12BaseComponents/2D/Transform2D/Transform2DMaker.h"

namespace tktk
{
	Transform2DMaker Transform2DMaker::m_self;

	Transform2DMaker& Transform2DMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = Transform2DMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<Transform2D> Transform2DMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<Transform2D>(
			m_initPosition,
			m_initScaleRate,
			m_initRotationDeg,
			m_traceType
			);
	}

	Transform2DMaker& Transform2DMaker::initPosition(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_initPosition = value;
		return *this;
	}

	Transform2DMaker& Transform2DMaker::initScaleRate(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_initScaleRate = value;
		return *this;
	}

	Transform2DMaker& Transform2DMaker::initRotationDeg(float value)
	{
		// 値を設定して自身の参照を返す
		m_initRotationDeg = value;
		return *this;
	}

	Transform2DMaker& Transform2DMaker::traceType(TraceParentType value)
	{
		// 値を設定して自身の参照を返す
		m_traceType = value;
		return *this;
	}
}