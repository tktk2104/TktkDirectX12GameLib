#include "TktkDX12BaseComponents/Other/ReceiveMessageToSelfDestroyer/ReceiveMessageToSelfDestroyerMaker.h"

namespace tktk
{
	ReceiveMessageToSelfDestroyerMaker ReceiveMessageToSelfDestroyerMaker::m_self;

	ReceiveMessageToSelfDestroyerMaker & ReceiveMessageToSelfDestroyerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = ReceiveMessageToSelfDestroyerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<ReceiveMessageToSelfDestroyer> ReceiveMessageToSelfDestroyerMaker::create()
	{
		return m_user->createComponent<ReceiveMessageToSelfDestroyer>(
			m_destroyMessegeType
			);
	}

	ReceiveMessageToSelfDestroyerMaker & ReceiveMessageToSelfDestroyerMaker::destroyMessegeType(int value)
	{
		m_destroyMessegeType = value;
		return *this;
	}
}