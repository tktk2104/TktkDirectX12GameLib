#ifndef COMPONENT_PTR_H_
#define COMPONENT_PTR_H_

/* std::weak_ptr */
#include <memory>

namespace tktk
{
	// コンポーネントの型情報を保持したポインタクラス
	template <class ComponentType>
	class ComponentPtr
	{
		// ComponentBasePtrはフレンドクラス
		friend class ComponentBasePtr;

	public:

		ComponentPtr() = default;

		explicit ComponentPtr(const std::weak_ptr<ComponentType>& weakPtr)
			: m_componentPtr(weakPtr) {}

	public:

		// ポインタが期限切れか判定する
		bool expired() const { return m_componentPtr.expired(); }

		// 引数のポインタと自身が同じポインタを指しているか判定する
		bool isSame(const ComponentPtr<ComponentType>& other) const { return !m_componentPtr.expired() && !other.m_componentPtr.expired() && m_componentPtr.lock() == other.m_componentPtr.lock(); }

		// ポインタの使用
		std::shared_ptr<ComponentType> operator ->() const
		{
			if (m_componentPtr.expired()) return nullptr;
			return m_componentPtr.lock();
		}

	private:

		std::weak_ptr<ComponentType> m_componentPtr;
	};
}
#endif // !COMPONENT_PTR_H_