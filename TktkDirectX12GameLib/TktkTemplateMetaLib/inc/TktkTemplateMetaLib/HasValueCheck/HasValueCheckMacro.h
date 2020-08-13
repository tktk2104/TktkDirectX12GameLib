#ifndef HAS_VALUE_CHECK_MACRO_H_
#define HAS_VALUE_CHECK_MACRO_H_

#include <type_traits>

#define HAS_VALUE_CHECK(valueName)																										\
																																		\
/* 「has_## valueName ##_checker」のための構造体 */																						\
struct has_## valueName ##_chcker_impl																									\
{																																		\
	/* 「JudgePtrType->valueName」が成立するなら「std::true_type」型を返す関数となる */													\
	template <class JudgePtrType, class ValueType>																						\
	static auto check(JudgePtrType*)																									\
		->decltype(std::declval<JudgePtrType&>()->## valueName ##,																		\
			std::bool_constant<std::is_same_v<decltype(std::declval<JudgePtrType&>()->## valueName ##), ValueType>>());					\
																																		\
	/* 「JudgePtrType->valueName」が成立しないなら「std::false_type」型を返す関数となる */												\
	template <class JudgePtrType, class ValueType>																						\
	static auto check(...)																												\
		->std::false_type;																												\
};																																		\
																																		\
/* 「JudgePtrType->valueName」が成立するなら「std::true_type」、しないなら「std::false_type」の型になる */								\
template<class JudgePtrType, class ValueType>																							\
using has_## valueName ##_chcker = decltype(has_## valueName ##_chcker_impl::check<JudgePtrType, ValueType>(nullptr));					\
																																		\
/* 「has_## valueName ##_checker」の判定で使用する変数の型を指定 */																		\
template<class ValueType>																												\
struct valueName ##_setter																												\
{																																		\
	/* 「JudgePtrType->valueName = ValueType」が成立するならその値に第二引数の値を代入する */											\
	template <class JudgePtrType, std::enable_if_t<has_## valueName ##_chcker<JudgePtrType, ValueType>::value>* = nullptr>				\
	static void chackAndSet(JudgePtrType runClass, ValueType&& value)																	\
	{																																	\
		runClass->## valueName ## = std::move(value);																					\
	}																																	\
	/* 「JudgePtrType->valueName = ValueType」が成立しないなら何もしない */																\
	template <class JudgePtrType, std::enable_if_t<!has_## valueName ##_chcker<JudgePtrType, ValueType>::value>* = nullptr>				\
	static void chackAndSet(JudgePtrType runClass, ValueType&& value) {}																\
};																																		\
																																		\
/* 「has_## valueName ##_checker」の判定で使用する変数の型と代入する配列の要素数を指定 */												\
template<class ValueType, int ArraySize>																								\
struct valueName ##_array_setter																										\
{																																		\
	/* 「JudgePtrType->valueName = ValueType[ArraySize]」が成立するならその値に第二引数の値を代入（配列をコピー）する */				\
	template <class JudgePtrType, std::enable_if_t<has_## valueName ##_chcker<JudgePtrType, ValueType[ArraySize]>::value>* = nullptr>	\
	static void chackAndSet(JudgePtrType runClass, const ValueType* arrayTop)															\
	{																																	\
		memcpy(&(runClass->## valueName ##), arrayTop, sizeof(ValueType) * ArraySize);													\
	}																																	\
	/* 「JudgePtrType->valueName = ValueType[ArraySize]」が成立しないなら何もしない */													\
	template <class JudgePtrType, std::enable_if_t<!has_## valueName ##_chcker<JudgePtrType, ValueType[ArraySize]>::value>* = nullptr>	\
	static void chackAndSet(JudgePtrType runClass, const ValueType* arrayTop) {}														\
};

#endif // !HAS_VALUE_CHECK_MACRO_H_