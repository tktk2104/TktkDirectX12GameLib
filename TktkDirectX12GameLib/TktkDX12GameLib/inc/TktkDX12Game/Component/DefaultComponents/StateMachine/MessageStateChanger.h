#ifndef MESSAGE_STATE_CHANGER_H_
#define MESSAGE_STATE_CHANGER_H_

#include <vector>
#include "../../ComponentBase.h"

namespace tktk
{
	// 特定のメッセージを受け取った時に自身のステートを変更するコンポーネント
	class MessageStateChanger
		: public ComponentBase
	{
	public:

		MessageStateChanger(unsigned int messageType, const std::vector<int>& enableStateArray, const std::vector<int>& disableStateArray);

	public:

		void handleMessage(unsigned int messageId, const tktk::MessageAttachment& value);

	private:

		unsigned int		m_messageType;
		std::vector<int>	m_enableStateArray;
		std::vector<int>	m_disableStateArray;
	};
}
#endif // !MESSAGE_STATE_CHANGER_H_