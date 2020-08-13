#ifndef COMPONENT_PTR_H_
#define COMPONENT_PTR_H_

#include <memory>

namespace tktk
{
	// コンポーネントの型情報を保持したポインタクラス
	template <class ComponentType>
	class ComponentPtr
	{
	public:

		ComponentPtr() = default;

		explicit ComponentPtr(const std::weak_ptr<ComponentType>& weakPtr);

	public:

		// ポインタが期限切れか判定する
		bool expired() const;

		// 引数のポインタと自身が同じポインタを指しているか判定する
		bool isSame(const ComponentPtr<ComponentType>& other) const;

		// ポインタの使用
		std::shared_ptr<ComponentType> operator ->() const;

	private:

		std::weak_ptr<ComponentType> m_componentPtr;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class ComponentType>
	inline ComponentPtr<ComponentType>::ComponentPtr(const std::weak_ptr<ComponentType>& weakPtr)
		: m_componentPtr(weakPtr)
	{
	}

	// ポインタが期限切れか判定する
	template<class ComponentType>
	inline bool ComponentPtr<ComponentType>::expired() const
	{
		return m_componentPtr.expired();
	}

	// 引数のポインタと自身が同じポインタを指しているか判定する
	template<class ComponentType>
	inline bool ComponentPtr<ComponentType>::isSame(const ComponentPtr<ComponentType>& other) const
	{
		return !m_componentPtr.expired() && !other.m_componentPtr.expired() && m_componentPtr.lock() == other.m_componentPtr.lock();
	}

	// ポインタの使用
	template<class ComponentType>
	inline std::shared_ptr<ComponentType> ComponentPtr<ComponentType>::operator->() const
	{
		if (m_componentPtr.expired()) return nullptr;
		return m_componentPtr.lock();
	}
}
#endif // !COMPONENT_PTR_H_