#ifndef RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_
#define RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_

#include "ReceiveMessageToSelfDestroyer.h"

namespace tktk
{
	class ReceiveMessageToSelfDestroyerMaker
	{
	private: /* プライベートコンストラクタ達 */

		ReceiveMessageToSelfDestroyerMaker() = default;
		ReceiveMessageToSelfDestroyerMaker(const ReceiveMessageToSelfDestroyerMaker& other) = default;
		ReceiveMessageToSelfDestroyerMaker& operator = (const ReceiveMessageToSelfDestroyerMaker& other) = default;

	public:

		// インスタンス作成開始
		static ReceiveMessageToSelfDestroyerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<ReceiveMessageToSelfDestroyer> create();

	public:

		// 自身を殺すメッセージの種類を設定
		ReceiveMessageToSelfDestroyerMaker& destroyMessegeType(MessageTypeCarrier value);

	private:

		// 自身のポインタ
		static ReceiveMessageToSelfDestroyerMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr		m_user				{ };
		MessageTypeCarrier	m_destroyMessegeType{ 0 };
	};
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_