#ifndef RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_
#define RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	// 特定のメッセージを取得したら自身のGameObjectを削除する
	class ReceiveMessageToSelfDestroyer
		: public ComponentBase
	{
	public:

		ReceiveMessageToSelfDestroyer(unsigned int destroyMessegeType);

	public:

		// <PolymorphismFunc>
		void handleMessage(unsigned int messageId, const tktk::MessageAttachment& value);

	private:

		// 自身を削除するメッセージの種類
		unsigned int m_destroyMessegeType;
	};
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_