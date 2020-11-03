#ifndef IS_CAST_SIGNED_INT_32_H_
#define IS_CAST_SIGNED_INT_32_H_

#include <type_traits>

namespace
{
	// テンプレート引数の型が４ビット符号付き整数かどうか判別する（基底の型がintな列挙型も含む）
	template <class CheckType, std::enable_if_t<std::is_enum_v<CheckType>>* = nullptr>
	constexpr bool IsSignedInt32_f() { return std::is_same_v<std::underlying_type_t<CheckType>, int>; }

	// テンプレート引数の型が４ビット符号付き整数かどうか判別する（基底の型がintな列挙型も含む）
	template <class CheckType, std::enable_if_t<!std::is_enum_v<CheckType>>* = nullptr>
	constexpr bool IsSignedInt32_f() { return std::is_same_v<CheckType, int>; };

	template <class CheckType>
	constexpr bool IsSignedInt32_v = IsSignedInt32_f<CheckType>();
}

// 「CheckType」が４ビット符号付き整数型だったらコンパイル可能な型
template <class CheckType>
using IsSignedInt32 = std::enable_if_t<IsSignedInt32_v<CheckType>>*;//

// 「CheckType」が４ビット符号付き整数型ではなかったらコンパイル可能な型
template <class CheckType>
using IsNotSignedInt32 = std::enable_if_t<!IsSignedInt32_v<CheckType>>*;//!IsSignedInt32_v<CheckType>()

#endif // !IS_CAST_SIGNED_INT_32_H_