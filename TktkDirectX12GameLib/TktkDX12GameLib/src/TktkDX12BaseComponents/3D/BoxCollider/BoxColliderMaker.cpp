#include "TktkDX12BaseComponents/3D/BoxCollider/BoxColliderMaker.h"

namespace tktk
{
	BoxColliderMaker BoxColliderMaker::m_self;

	BoxColliderMaker & BoxColliderMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BoxColliderMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BoxCollider> BoxColliderMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<BoxCollider>(
			m_collisionGroupType,
			m_boxSize,
			m_localPosition
			);
	}

	BoxColliderMaker & BoxColliderMaker::boxSize(const tktkMath::Vector3 & value)
	{
		// 値を設定して自身の参照を返す
		m_boxSize = value;
		return *this;
	}

	BoxColliderMaker & BoxColliderMaker::localPosition(const tktkMath::Vector3 & value)
	{
		// 値を設定して自身の参照を返す
		m_localPosition = value;
		return *this;
	}

	BoxColliderMaker& BoxColliderMaker::collisionGroupTypeImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_collisionGroupType = value;
		return *this;
	}
}