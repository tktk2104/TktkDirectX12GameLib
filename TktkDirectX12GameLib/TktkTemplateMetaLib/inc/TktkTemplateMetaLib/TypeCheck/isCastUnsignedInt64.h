#ifndef IS_CAST_UNSIGNED_INT_64_H_
#define IS_CAST_UNSIGNED_INT_64_H_

#include <type_traits>

namespace
{
	// テンプレート引数の型が８バイト符号付き整数かどうか判別する（基底の型がintな列挙型も含む）
	template <class CheckType, std::enable_if_t<std::is_enum_v<CheckType>>* = nullptr>
	constexpr bool IsUnsignedInt64_f() { return std::is_same_v<std::underlying_type_t<CheckType>, unsigned long long>; }

	// テンプレート引数の型が８バイト符号付き整数かどうか判別する（基底の型がintな列挙型も含む）
	template <class CheckType, std::enable_if_t<!std::is_enum_v<CheckType>>* = nullptr>
	constexpr bool IsUnsignedInt64_f() { return std::is_same_v<CheckType, unsigned long long>; };

	template <class CheckType>
	constexpr bool IsUnsignedInt64_v = IsSignedInt64_f<CheckType>();
}

// 「CheckType」が８バイト符号無し整数型だったらコンパイル可能な型
template <class CheckType>
using IsUnsignedInt64 = std::enable_if_t<IsUnsignedInt64_v<CheckType>>*;

// 「CheckType」が８バイト符号無し整数型ではなかったらコンパイル可能な型
template <class CheckType>
using IsNotUnsignedInt64 = std::enable_if_t<!IsUnsignedInt64_v<CheckType>>*;

#endif // !IS_CAST_UNSIGNED_INT_64_H_