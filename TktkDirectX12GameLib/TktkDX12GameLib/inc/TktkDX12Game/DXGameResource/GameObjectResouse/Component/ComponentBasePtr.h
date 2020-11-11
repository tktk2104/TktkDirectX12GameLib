#ifndef COMPONENT_BASE_PTR_H_
#define COMPONENT_BASE_PTR_H_

/* std::weak_ptr */
#include <memory>

/* std::type_index */
#include <typeindex>

/* funcUseType */
#include "ComponentPtr.h"

namespace tktk
{
	/* class member */
	class ComponentBase;

	// コンポーネントの型情報を隠蔽したポインタクラス
	class ComponentBasePtr
	{
	public:

		ComponentBasePtr() = default;

		ComponentBasePtr(std::type_index componentType, const std::weak_ptr<ComponentBase>& componentPtr);

		template <class ComponentType>
		ComponentBasePtr(const std::weak_ptr<ComponentType>& componentPtr)
			: m_componentType(typeid(ComponentType))
			, m_componentPtr(componentPtr) {}

		template <class ComponentType>
		ComponentBasePtr(const ComponentPtr<ComponentType>& componentPtr)
			: m_componentType(typeid(ComponentType))
			, m_componentPtr(componentPtr.m_componentPtr) {}

	public:

		// ポインタを取得
		std::shared_ptr<ComponentBase> operator ->() const;

		// 引数のポインタと自身が同じポインタを指しているか判定する
		bool isSame(const ComponentBasePtr& other) const;

		// 引数のポインタと自身が同じポインタを指しているか判定する
		template <class ComponentType>
		bool isSame(const ComponentPtr<ComponentType>& other) const { return other.isSame(castPtr<ComponentType>()); }

		// テンプレート引数の型に自身のポインタがキャストできるか判定する
		template <class ComponentType>
		bool canCast() const { return canCast(typeid(ComponentType)); }

		// 引数の型に自身のポインタがキャストできるか判定する
		bool canCast(std::type_index type) const;

		// テンプレート引数の型にキャストした「ComponentPtr」を取得する
		// キャストできなかったら空の「ComponentPtr」を返す
		template <class ComponentType>
		ComponentPtr<ComponentType> castPtr() const
		{
			if (canCast<ComponentType>())
			{
				return ComponentPtr<ComponentType>(std::dynamic_pointer_cast<ComponentType>(m_componentPtr.lock()));
			}
			return ComponentPtr<ComponentType>();
		}

		// アクティブフラグを変更する
		void setActive(bool isActive) const;

		// 死亡フラグを取得する
		bool isDead() const;

	private:

		std::type_index					m_componentType	{ typeid(void) };
		std::weak_ptr<ComponentBase>	m_componentPtr	{ };
	};
}
#endif // !COMPONENT_BASE_PTR_H_