#ifndef TO_INT_FUNC_H_
#define TO_INT_FUNC_H_

template<class T>
constexpr unsigned int toInt(T value)
{
	return static_cast<unsigned int>(value);
}
#endif // !TO_INT_FUNC_H_