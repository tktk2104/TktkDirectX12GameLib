#ifndef COMPONENT_RUN_FUNC_PRIORITY_LIST_H_
#define COMPONENT_RUN_FUNC_PRIORITY_LIST_H_

/* std::unordered_map */
#include <unordered_map>

/* std::type_index */
#include <typeindex>

namespace tktk
{
	// コンポーネントの型ごとの更新優先度を管理するクラス
	class ComponentRunFuncPriorityList
	{
	public:

		// 引数の型のコンポーネントの更新優先度を設定する
		void addPriority(std::type_index type, float priority);

		// 引数の型のコンポーネントの更新優先度を取得する
		// 登録されていない型の場合、「BasePriority」が返る
		float getPriority(std::type_index type) const;

	private:

		static constexpr float BasePriority{ 0.0f };

	private:

		std::unordered_map<std::type_index, float> m_updatePriorityMap;
	};
}
#endif // !COMPONENT_RUN_FUNC_PRIORITY_LIST_H_