#ifndef RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_
#define RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
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

		// ステートを指定し、作成を開始する
		static ReceiveMessageToSelfDestroyerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<ReceiveMessageToSelfDestroyer> create();

	public:

		// 自身を殺すメッセージの種類を設定
		template<class MessageType, is_idType<MessageType> = nullptr>
		ReceiveMessageToSelfDestroyerMaker& destroyMessegeType(MessageType value) { return destroyMessegeTypeImpl(static_cast<unsigned int>(value)); }

	private: /* 各種id指定系の関数の実装 */

		ReceiveMessageToSelfDestroyerMaker& destroyMessegeTypeImpl(unsigned int value);

	private:

		// 自身のポインタ
		static ReceiveMessageToSelfDestroyerMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr		m_user				{ };
		StateTypeHierarchy		m_targetState		{ };
		unsigned int		m_destroyMessegeType{ 0 };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class MessageType, is_not_idType<MessageType> = nullptr>
		ReceiveMessageToSelfDestroyerMaker& destroyMessegeType(MessageType value) { static_assert(false, "MessageType Fraud Type"); }
	};
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_