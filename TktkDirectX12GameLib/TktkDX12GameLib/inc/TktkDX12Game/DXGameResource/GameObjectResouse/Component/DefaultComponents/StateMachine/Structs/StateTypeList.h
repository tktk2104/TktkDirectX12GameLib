#ifndef STATE_TYPE_LIST_H_
#define STATE_TYPE_LIST_H_

#include <unordered_set>
#include "StateTypeCarrier.h"

namespace tktk
{
	// ステートの一覧を扱う構造体
	struct StateTypeList
	{
	public:

		StateTypeList() = default;

		StateTypeList(std::initializer_list<StateTypeCarrier> targetState) : list(targetState) {}

	public:

		std::unordered_set<StateTypeCarrier> list{};
	};
}
#endif // !STATE_TYPE_LIST_H_