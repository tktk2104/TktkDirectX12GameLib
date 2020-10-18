#include "TktkDX12BaseComponents/2D/RectCollider/RectColliderMaker.h"

namespace tktk
{
	RectColliderMaker RectColliderMaker::m_self;

	RectColliderMaker & RectColliderMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = RectColliderMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<RectCollider> RectColliderMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<RectCollider>(
			m_collisionGroupType,
			m_rectSize,
			m_localPosition,
			m_extrudedRate
			);
	}

	RectColliderMaker & RectColliderMaker::rectSize(const tktkMath::Vector2 & value)
	{
		// 値を設定して自身の参照を返す
		m_rectSize = value;
		return *this;
	}

	RectColliderMaker & RectColliderMaker::localPosition(const tktkMath::Vector2 & value)
	{
		// 値を設定して自身の参照を返す
		m_localPosition = value;
		return *this;
	}

	RectColliderMaker& RectColliderMaker::extrudedRate(float value)
	{
		// 値を設定して自身の参照を返す
		m_extrudedRate = value;
		return *this;
	}

	RectColliderMaker& RectColliderMaker::collisionGroupTypeImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_collisionGroupType = value;
		return *this;
	}
}