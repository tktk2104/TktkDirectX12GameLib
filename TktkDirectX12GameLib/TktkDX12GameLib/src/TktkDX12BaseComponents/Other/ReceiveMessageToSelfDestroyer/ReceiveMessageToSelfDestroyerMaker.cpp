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
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.empty())
		{
			return m_user->createComponent<ReceiveMessageToSelfDestroyer>(m_destroyMessegeType);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<ReceiveMessageToSelfDestroyer>(m_destroyMessegeType);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	ReceiveMessageToSelfDestroyerMaker& ReceiveMessageToSelfDestroyerMaker::destroyMessegeTypeImpl(unsigned int value)
	{
		m_destroyMessegeType = value;
		return *this;
	}
}