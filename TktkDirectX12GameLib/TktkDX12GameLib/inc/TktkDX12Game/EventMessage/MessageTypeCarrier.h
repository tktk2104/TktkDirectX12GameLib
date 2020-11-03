#ifndef MESSAGE_TYPE_CARRIER_H_
#define MESSAGE_TYPE_CARRIER_H_

#include <TktkTemplateMetaLib/TypeCheck/isCastSignedInt32.h>

namespace tktk
{
	// メッセージの種類を保持する構造体
	struct MessageTypeCarrier
	{
	public:

		MessageTypeCarrier() = default;

		// 暗黙変換を許すためにわざと「explicit」を外している
		template <class MessageType, IsSignedInt32<MessageType> = nullptr>
		MessageTypeCarrier(MessageType tag) : type(static_cast<int>(tag)) {}

		// 不正な型をMessageTypeとして扱おうとした
		template <class MessageType, IsNotSignedInt32<MessageType> = nullptr>
		MessageTypeCarrier(MessageType tag) { static_assert(false, "MessageType Fraud Type"); }

	public:

		// 引数のメッセージの種類と自身のメッセージの種類が等しいか識別する
		template <class MessageType, IsSignedInt32<MessageType> = nullptr>
		bool isSame(MessageType other) { return type == static_cast<int>(other); }

		// 不正な型を比較した
		template <class MessageType, IsNotSignedInt32<MessageType> = nullptr>
		bool isSame(MessageType other) { static_assert(false, "MessageType Fraud Type"); }

	public:

		bool operator==(const MessageTypeCarrier& other) const { return type == other.type; }
		bool operator!=(const MessageTypeCarrier& other) const { return type != other.type; }

	public:

		int type{};
	};
}

// 「MessageTypeCarrier」をハッシュに対応させる
template<>
struct std::hash<tktk::MessageTypeCarrier>
{
	size_t operator()(const tktk::MessageTypeCarrier& data) const { return std::hash<int>()(data.type); }
};
#endif // !MESSAGE_TYPE_CARRIER_H_