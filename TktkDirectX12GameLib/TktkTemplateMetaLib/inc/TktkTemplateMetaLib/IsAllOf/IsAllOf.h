#ifndef IS_ALL_OF_H_
#define IS_ALL_OF_H_

template <template <class JudgeType> class JugeFunc, class... JudgeTypes>
class is_all_of
{
public:

	template <class Head, class... Body>
	struct is_all_of_check
	{
		static constexpr unsigned int value = JugeFunc<Head>::value;// +is_all_of_check<Body...>::value;
	};

	template <class Head>
	struct is_all_of_check<Head>
	{
		static constexpr unsigned int value = JugeFunc<Head>::value;
	};

public:

	static constexpr bool value = (is_all_of_check<JudgeTypes...>::value == sizeof...(JudgeTypes));
};

template <template <class JudgeType> class JugeFunc, class... JudgeTypes>
constexpr bool is_all_of_v = is_all_of<JugeFunc, JudgeTypes...>::value;

#endif // !IS_ALL_OF_H_