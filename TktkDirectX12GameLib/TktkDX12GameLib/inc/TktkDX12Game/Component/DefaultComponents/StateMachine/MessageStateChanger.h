#ifndef MESSAGE_STATE_CHANGER_H_
#define MESSAGE_STATE_CHANGER_H_

#include "../../ComponentBase.h"
#include "StateTypeList.h"
#include "../../../EventMessage/MessageTypeCarrier.h"

namespace tktk
{
	// ����̃��b�Z�[�W���󂯎�������Ɏ��g�̃X�e�[�g��ύX����R���|�[�l���g
	class MessageStateChanger
		: public ComponentBase
	{
	public:

		MessageStateChanger(MessageTypeCarrier type, const StateTypeList& enableStateArray, const StateTypeList& disableStateArray);

	public:

		void handleMessage(MessageTypeCarrier type, const tktk::MessageAttachment& value);

	private:

		MessageTypeCarrier	m_messageType;
		StateTypeList			m_enableStateArray;
		StateTypeList			m_disableStateArray;
	};
}
#endif // !MESSAGE_STATE_CHANGER_H_