#ifndef STATE_TYPE_HIERARCHY_H_
#define STATE_TYPE_HIERARCHY_H_

#include <vector>
#include "StateTypeCarrier.h"

namespace tktk
{
	// ステートの階層を扱う構造体
	struct StateTypeHierarchy
	{
	public:

		StateTypeHierarchy() = default;

		explicit StateTypeHierarchy(std::initializer_list<StateTypeCarrier> targetState) : hierarchy(targetState) {}

	public:

		std::vector<StateTypeCarrier> hierarchy{};
	};
}
#endif // !STATE_TYPE_HIERARCHY_H_