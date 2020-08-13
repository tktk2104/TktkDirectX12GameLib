#ifndef COMPONENT_BASE_PTR_H_
#define COMPONENT_BASE_PTR_H_

#include <memory>
#include "../ClassTypeChecker/ClassTypeChecker.h"
#include "ComponentPtr.h"

namespace tktk
{
	class ComponentBase;

	// コンポーネントの型情報を隠蔽したポインタクラス
	class ComponentBasePtr
	{
	public:

		ComponentBasePtr() = default;

		template <class ComponentType>
		ComponentBasePtr(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		// ポインタを取得
		std::shared_ptr<ComponentBase> operator ->() const;

		// 引数のポインタと自身が同じポインタを指しているか判定する
		bool isSame(const ComponentBasePtr& other) const;

		// 引数のポインタと自身が同じポインタを指しているか判定する
		template <class ComponentType>
		bool isSame(const ComponentPtr<ComponentType>& other) const;

		// テンプレート引数の型に自身のポインタがキャストできるか判定する
		template <class ComponentType>
		bool canCast() const;

		// テンプレート引数の型にキャストした「ComponentPtr」を取得する
		// キャストできなかったら空の「ComponentPtr」を返す
		template <class ComponentType>
		ComponentPtr<ComponentType> castPtr() const;

		// アクティブフラグを変更する
		void setActive(bool isActive) const;

		// 死亡フラグを取得する
		bool isDead() const;

	private:

		unsigned int					m_componentTypeId{ 0U };
		std::weak_ptr<ComponentBase>	m_componentPtr{ };
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class ComponentType>
	inline ComponentBasePtr::ComponentBasePtr(const std::weak_ptr<ComponentType>& componentPtr)
		: m_componentTypeId(ClassTypeChecker::getClassId<ComponentType>())
		, m_componentPtr(componentPtr)
	{
	}

	// 引数のポインタと自身が同じポインタを指しているか判定する
	template<class ComponentType>
	inline bool ComponentBasePtr::isSame(const ComponentPtr<ComponentType>& other) const
	{
		return other.isSame(castPtr<ComponentType>());
	}

	// テンプレート引数の型に自身のポインタがキャストできるか判定する
	template<class ComponentType>
	inline bool ComponentBasePtr::canCast() const
	{
		return (ClassTypeChecker::getClassId<ComponentType>() == m_componentTypeId);
	}

	// テンプレート引数の型にキャストした「ComponentPtr」を取得する
	// キャストできなかったら空の「ComponentPtr」を返す
	template<class ComponentType>
	inline ComponentPtr<ComponentType> ComponentBasePtr::castPtr() const
	{
		if (canCast<ComponentType>())
		{
			return ComponentPtr<ComponentType>(std::dynamic_pointer_cast<ComponentType>(m_componentPtr.lock()));
		}
		return ComponentPtr<ComponentType>();
	}
}
#endif // !COMPONENT_BASE_PTR_H_