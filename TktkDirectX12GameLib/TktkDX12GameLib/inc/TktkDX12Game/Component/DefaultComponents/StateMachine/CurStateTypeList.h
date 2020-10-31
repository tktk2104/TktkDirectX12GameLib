#ifndef CUR_STATE_TYPE_LIST_H_
#define CUR_STATE_TYPE_LIST_H_

#include <forward_list>
#include "../../ComponentBase.h"

namespace tktk
{
	// 自身のステートを管理するコンポーネント
	class CurStateTypeList
		: public ComponentBase
	{
	public:

		CurStateTypeList() = default;

	public:

		// ステートを有効にする
		void stateEnable(int stateType);

		// ステートを無効にする
		void stateDisable(int stateType);

		// 全てのステートを無効にする
		void clearState();

		// 引数のステートを持っているか？
		bool contain(int stateType) const;

	private:

		// 現在のステートのリスト
		std::forward_list<int> m_stateTypeList;
	};
}
#endif // !CUR_STATE_TYPE_LIST_H_