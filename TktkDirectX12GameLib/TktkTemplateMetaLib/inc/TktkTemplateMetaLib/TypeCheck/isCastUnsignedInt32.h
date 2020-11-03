#ifndef IS_CAST_UNSIGNED_INT_32_H_
#define IS_CAST_UNSIGNED_INT_32_H_

#include <type_traits>

namespace
{
	// テンプレート引数の型が４ビット符号付き整数かどうか判別する（基底の型がintな列挙型も含む）
	template <class CheckType, std::enable_if_t<std::is_enum_v<CheckType>>* = nullptr>
	constexpr bool IsUnsignedInt32_f() { return std::is_same_v<std::underlying_type_t<CheckType>, unsigned int>; }

	// テンプレート引数の型が４ビット符号付き整数かどうか判別する（基底の型がintな列挙型も含む）
	template <class CheckType, std::enable_if_t<!std::is_enum_v<CheckType>>* = nullptr>
	constexpr bool IsUnsignedInt32_f() { return std::is_same_v<CheckType, unsigned int>; };

	template <class CheckType>
	constexpr bool IsUnsignedInt32_v = IsSignedInt32_f<CheckType>();
}

// 「CheckType」が４ビット符号無し整数型だったらコンパイル可能な型
template <class CheckType>
using IsUnsignedInt32 = std::enable_if_t<IsUnsignedInt32_v<CheckType>>*;

// 「CheckType」が４ビット符号無し整数型ではなかったらコンパイル可能な型
template <class CheckType>
using IsNotUnsignedInt32 = std::enable_if_t<!IsUnsignedInt32_v<CheckType>>*;

#endif // !IS_CAST_UNSIGNED_INT_32_H_