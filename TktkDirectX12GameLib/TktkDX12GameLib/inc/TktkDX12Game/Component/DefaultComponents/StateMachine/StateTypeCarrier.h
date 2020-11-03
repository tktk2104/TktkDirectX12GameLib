#ifndef STATE_TYPE_CARRIER_H_
#define STATE_TYPE_CARRIER_H_

#include <TktkTemplateMetaLib/TypeCheck/isCastSignedInt32.h>

namespace tktk
{
	// ステートの種類を保持する構造体
	struct StateTypeCarrier
	{
	public:

		StateTypeCarrier() = default;

		// 暗黙変換を許すためにわざと「explicit」を外している
		template <class StateType, IsSignedInt32<StateType> = nullptr>
		StateTypeCarrier(StateType tag) : type(static_cast<int>(tag)) {}

		// 不正な型をStateTypeとして扱おうとした
		template <class StateType, IsNotSignedInt32<StateType> = nullptr>
		StateTypeCarrier(StateType tag) { static_assert(false, "StateType Fraud Type"); }

	public:

		// 引数のステートの種類と自身のステートの種類が等しいか識別する
		template <class StateType, IsSignedInt32<StateType> = nullptr>
		bool isSame(StateType other) { return type == static_cast<int>(other); }

		// 不正な型を比較した
		template <class StateType, IsNotSignedInt32<StateType> = nullptr>
		bool isSame(StateType other) { static_assert(false, "StateType Fraud Type"); }

	public:

		bool operator==(const StateTypeCarrier& other) const { return type == other.type; }
		bool operator!=(const StateTypeCarrier& other) const { return type != other.type; }

	public:

		int type{};
	};
}

// 「StateTypeCarrier」をハッシュに対応させる
template<>
struct std::hash<tktk::StateTypeCarrier>
{
	size_t operator()(const tktk::StateTypeCarrier& data) const { return std::hash<int>()(data.type); }
};
#endif // !STATE_TYPE_CARRIER_H_
