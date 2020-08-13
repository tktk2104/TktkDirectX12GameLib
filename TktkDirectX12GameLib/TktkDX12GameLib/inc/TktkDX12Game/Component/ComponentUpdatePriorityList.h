#ifndef COMPONENT_UPDATE_PRIORITY_LIST_H_
#define COMPONENT_UPDATE_PRIORITY_LIST_H_

#include <unordered_map>
#include "../ClassTypeChecker/ClassTypeChecker.h"

namespace tktk
{
	// コンポーネントの型ごとの更新優先度を管理するクラス
	class ComponentUpdatePriorityList
	{
	public:

		// テンプレート引数の型のコンポーネントの更新優先度を設定する
		template <class ComponentType>
		void addPriority(float priority);

		// テンプレート引数の型のコンポーネントの更新優先度を取得する
		// 登録されていない型の場合、「m_basePriority」が返る
		template <class ComponentType>
		float getPriority() const;

		// 引数のクラスIDの型のコンポーネントの更新優先度を取得する
		// 登録されていない型の場合、デフォルト値の「0.0f」が返る
		float getPriority(unsigned int typeId) const;

	private:

		static constexpr float m_basePriority{ 0.0f };

		std::unordered_map<unsigned int, float> m_updatePriorityMap;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// テンプレート引数の型のコンポーネントの更新優先度を設定する
	template<class ComponentType>
	inline void ComponentUpdatePriorityList::addPriority(float priority)
	{
		if (m_updatePriorityMap.count(ClassTypeChecker::getClassId<ComponentType>()) == 0U)
		{
			m_updatePriorityMap.emplace(ClassTypeChecker::getClassId<ComponentType>(), priority);
		}
	}

	// テンプレート引数の型のコンポーネントの更新優先度を取得する
	// 登録されていない型の場合、デフォルト値の「0.0f」が返る
	template<class ComponentType>
	inline float ComponentUpdatePriorityList::getPriority() const
	{
		return getPriority(ClassTypeChecker::getClassId<ComponentType>());
	}
}
#endif // !COMPONENT_UPDATE_PRIORITY_LIST_H_