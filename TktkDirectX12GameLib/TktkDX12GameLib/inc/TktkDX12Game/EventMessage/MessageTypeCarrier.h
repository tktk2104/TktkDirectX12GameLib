#ifndef MESSAGE_TYPE_CARRIER_H_
#define MESSAGE_TYPE_CARRIER_H_

#include <TktkTemplateMetaLib/TypeCheck/isCastSignedInt32.h>

namespace tktk
{
	// ���b�Z�[�W�̎�ނ�ێ�����\����
	struct MessageTypeCarrier
	{
	public:

		MessageTypeCarrier() = default;

		// �Öٕϊ����������߂ɂ킴�Ɓuexplicit�v���O���Ă���
		template <class MessageType, IsSignedInt32<MessageType> = nullptr>
		MessageTypeCarrier(MessageType tag) : type(static_cast<int>(tag)) {}

		// �s���Ȍ^��MessageType�Ƃ��Ĉ������Ƃ���
		template <class MessageType, IsNotSignedInt32<MessageType> = nullptr>
		MessageTypeCarrier(MessageType tag) { static_assert(false, "MessageType Fraud Type"); }

	public:

		// �����̃��b�Z�[�W�̎�ނƎ��g�̃��b�Z�[�W�̎�ނ������������ʂ���
		template <class MessageType, IsSignedInt32<MessageType> = nullptr>
		bool isSame(MessageType other) { return type == static_cast<int>(other); }

		// �s���Ȍ^���r����
		template <class MessageType, IsNotSignedInt32<MessageType> = nullptr>
		bool isSame(MessageType other) { static_assert(false, "MessageType Fraud Type"); }

	public:

		bool operator==(const MessageTypeCarrier& other) const { return type == other.type; }
		bool operator!=(const MessageTypeCarrier& other) const { return type != other.type; }

	public:

		int type{};
	};
}

// �uMessageTypeCarrier�v���n�b�V���ɑΉ�������
template<>
struct std::hash<tktk::MessageTypeCarrier>
{
	size_t operator()(const tktk::MessageTypeCarrier& data) const { return std::hash<int>()(data.type); }
};
#endif // !MESSAGE_TYPE_CARRIER_H_