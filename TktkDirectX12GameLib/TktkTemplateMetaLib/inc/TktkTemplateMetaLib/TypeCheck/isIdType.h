#ifndef IS_ID_TYPE_H_
#define IS_ID_TYPE_H_

#include <type_traits>

// テンプレート引数の型がidを表す上で適切かを判定する定数
template <class T>
constexpr bool is_idType_v = (std::is_enum_v<T> || std::is_integral_v<T>);

// 「CheckType」がidを表す型だったらコンパイル可能な型
template <class CheckType>
using is_idType = std::enable_if_t<is_idType_v<CheckType>>*;

// 「CheckType」がidを表す型では無かったらコンパイル可能な型
template <class CheckType>
using is_not_idType = std::enable_if_t<!is_idType_v<CheckType>>*;

#endif // !IS_ID_TYPE_H_