#ifndef MESSAGE_ATTACHMENT_H_
#define MESSAGE_ATTACHMENT_H_

#include <memory>
#include <utility>

namespace tktk
{
	// メッセージを送るときに渡す値を格納するクラス
	class MessageAttachment
	{
	public:

		MessageAttachment() = default;

		// 意図的に「explicit」を外している
		template<class T>
		MessageAttachment(T&& value);

		// コンストラクタで渡した値のポインタを取得する
		// ※テンプレート引数が正しくない型だった場合、期限切れのポインタが返される
		template<class T>
		std::weak_ptr<T> getValuePtr() const;

	private:

		// ポインタを所持する構造体のインターフェース
		struct PtrCarrierInterface
		{
			virtual ~PtrCarrierInterface() = default;
		};

		// ポインタを所持する構造体
		template<class T>
		struct PtrCarrier : public PtrCarrierInterface
		{
			PtrCarrier(const T& value);

			std::shared_ptr<T> m_ptr;
		};

	private:

		// ポインタを所持する構造体のポインタ（型情報は隠蔽する）
		std::shared_ptr<PtrCarrierInterface> m_ptrCarrier { nullptr };
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class T>
	inline MessageAttachment::MessageAttachment(T&& value)
	{
		m_ptrCarrier = std::make_shared<PtrCarrier<T>>(std::forward<T>(value));
	}

	// コンストラクタで渡した値のポインタを取得する
	// ※テンプレート引数が正しくない型だった場合、期限切れのポインタが返される
	template<class T>
	inline std::weak_ptr<T> MessageAttachment::getValuePtr() const
	{
		auto tempPtr = std::dynamic_pointer_cast<PtrCarrier<T>>(m_ptrCarrier);
		if (tempPtr == nullptr) return std::weak_ptr<T>();
		return tempPtr->m_ptr;
	}

	template<class T>
	inline MessageAttachment::PtrCarrier<T>::PtrCarrier(const T& value)
	{
		m_ptr = std::make_shared<T>(value);
	}
}
#endif // !MESSAGE_ATTACHMENT_H_