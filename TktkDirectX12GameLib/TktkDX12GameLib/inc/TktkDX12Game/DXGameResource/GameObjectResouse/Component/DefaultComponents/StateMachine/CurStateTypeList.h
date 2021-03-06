#ifndef CUR_STATE_TYPE_LIST_H_
#define CUR_STATE_TYPE_LIST_H_

/* std::unordered_set */
#include <unordered_set>

/* baseClass */
#include "../../ComponentBase.h"

/* class member */
#include "Structs/StateTypeCarrier.h"

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
		void stateEnable(StateTypeCarrier stateType);

		// ステートを無効にする
		void stateDisable(StateTypeCarrier stateType);

		// 全てのステートを無効にする
		void clearState();

		// 引数のステートを持っているか？
		bool contain(StateTypeCarrier stateType) const;

	private:

		// 現在のステートのリスト
		std::unordered_set<StateTypeCarrier> m_stateTypeList;
	};
}
#endif // !CUR_STATE_TYPE_LIST_H_