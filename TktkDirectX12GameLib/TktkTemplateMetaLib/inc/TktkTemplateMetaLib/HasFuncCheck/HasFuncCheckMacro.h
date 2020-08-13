#ifndef HAS_FUNC_CHECK_MACRO_H_
#define HAS_FUNC_CHECK_MACRO_H_

#include <type_traits>

#define HAS_FUNC_CHECK(funcName)																														\
																																						\
/* 「has_## funcName ##_checker」のための構造体 */																										\
struct has_## funcName ##_checker_impl																													\
{																																						\
	/* 「ReturnType = JudgePtrType->## funcName ##(ArgsType...)」が成立するなら「std::true_type」型を返す関数となる */									\
	template <class JudgePtrType, class ReturnType, class... ArgsType>																					\
	static auto check(JudgePtrType*)																													\
		->decltype(std::declval<JudgePtrType&>()->## funcName ##(std::declval<ArgsType>()...),															\
			std::bool_constant<std::is_same_v<decltype(std::declval<JudgePtrType&>()->## funcName ##(std::declval<ArgsType>()...)), ReturnType>>());	\
																																						\
	/* 「ReturnType = JudgePtrType->## funcName ##(ArgsType...)」が成立しないなら「std::false_type」型を返す関数となる	*/								\
	template <class JudgePtrType, class ReturnType, class... ArgsType>																					\
	static auto check(...)																																\
		->std::false_type;																																\
};																																						\
																																						\
/* 「ReturnType = JudgePtrType->## funcName ##(ArgsType...)」が成立するなら「std::true_type」、しないなら「std::false_type」の型になる */				\
template <class JudgePtrType, class ReturnType, class... ArgsType>																						\
using has_## funcName ##_checker = decltype(has_## funcName ##_checker_impl::check<JudgePtrType, ReturnType, ArgsType...>(nullptr));					\
																																						\
																																						\
/* 「has_## funcName ##_checker」の判定で使用する関数の引数、戻り値を指定 */																			\
template<class ReturnType, class... ArgsType>																											\
struct funcName ##_runner																																\
{																																						\
	/* 「ReturnType = JudgePtrType->## funcName ##(ArgsType...)」が成立するなら関数を実行してその戻り値を返す */										\
	template <class JudgePtrType, std::enable_if_t<has_## funcName ##_checker<JudgePtrType, ReturnType, ArgsType...>::value>* = nullptr>				\
	static ReturnType checkAndRun(JudgePtrType runClass, ReturnType&& defaultReturnValue, ArgsType... params)											\
	{																																					\
		return std::forward<ReturnType>(runClass->## funcName ##(params...));																			\
	}																																					\
																																						\
	/* 「ReturnType = JudgePtrType->## funcName ##(ArgsType...)」が成立しないなら関数を実行せずに「defaultReturnValue」を返す */						\
	template <class JudgePtrType, std::enable_if_t<!has_## funcName ##_checker<JudgePtrType, ReturnType, ArgsType...>::value>* = nullptr>				\
	static ReturnType checkAndRun(JudgePtrType runClass, ReturnType&& defaultReturnValue, ArgsType... params)											\
	{																																					\
		return std::forward<ReturnType>(defaultReturnValue);																							\
	}																																					\
																																						\
};																																						\
/* 「has_## funcName ##_checker」の判定で使用する関数の戻り値が無い（void）の場合 */																	\
template <class... ArgsType>																															\
struct funcName ##_runner<void, ArgsType...>																											\
{																																						\
	/* 「JudgePtrType->## funcName ##(ArgsType...)」が成立するなら関数を実行する */																		\
	template <class JudgePtrType, std::enable_if_t<has_## funcName ##_checker<JudgePtrType, void, ArgsType...>::value>* = nullptr>						\
	static void checkAndRun(JudgePtrType runClass, ArgsType... params)																					\
	{																																					\
		runClass->## funcName ##(params...);																											\
	}																																					\
																																						\
	/* 「JudgePtrType->## funcName ##(ArgsType...)」が成立しないなら何もしない */																		\
	template <class JudgePtrType, std::enable_if_t<!has_## funcName ##_checker<JudgePtrType, void, ArgsType...>::value>* = nullptr>						\
	static void checkAndRun(JudgePtrType runClass, ArgsType... params) {}																				\
};

#endif // !HAS_FUNC_CHECK_MACRO_H_