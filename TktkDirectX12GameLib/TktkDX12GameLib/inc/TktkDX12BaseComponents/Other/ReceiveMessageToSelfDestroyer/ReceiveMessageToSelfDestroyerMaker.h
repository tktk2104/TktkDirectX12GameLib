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
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static ReceiveMessageToSelfDestroyerMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

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
		std::vector<int>	m_targetState		{ };
		unsigned int		m_destroyMessegeType{ 0 };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class MessageType, is_not_idType<MessageType> = nullptr>
		ReceiveMessageToSelfDestroyerMaker& destroyMessegeType(MessageType value) { static_assert(false, "MessageType Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline ReceiveMessageToSelfDestroyerMaker& ReceiveMessageToSelfDestroyerMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
	{
		// 作成開始処理を行う
		auto& result = makeStart(user);

		// 初期化子リストを配列に変換
		auto targetStateArray = std::vector<StateIdType>(targetState);

		// 対象のステートの階層数分のメモリを確保
		result.m_targetState.reserve(targetStateArray.size());

		// 対象のステートの階層を設定する
		for (const auto& node : targetStateArray) result.m_targetState.push_back(static_cast<int>(node));

		// 自身の参照を返す
		return result;
	}
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_