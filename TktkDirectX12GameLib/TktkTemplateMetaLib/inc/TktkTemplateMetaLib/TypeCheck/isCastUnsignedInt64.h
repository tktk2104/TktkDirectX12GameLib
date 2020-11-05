#ifndef IS_CAST_UNSIGNED_INT_64_H_
#define IS_CAST_UNSIGNED_INT_64_H_

#include <type_traits>

namespace
{
	// �e���v���[�g�����̌^���W�o�C�g�����t���������ǂ������ʂ���i���̌^��int�ȗ񋓌^���܂ށj
	template <class CheckType, std::enable_if_t<std::is_enum_v<CheckType>>* = nullptr>
	constexpr bool IsUnsignedInt64_f() { return std::is_same_v<std::underlying_type_t<CheckType>, unsigned long long>; }

	// �e���v���[�g�����̌^���W�o�C�g�����t���������ǂ������ʂ���i���̌^��int�ȗ񋓌^���܂ށj
	template <class CheckType, std::enable_if_t<!std::is_enum_v<CheckType>>* = nullptr>
	constexpr bool IsUnsignedInt64_f() { return std::is_same_v<CheckType, unsigned long long>; };

	template <class CheckType>
	constexpr bool IsUnsignedInt64_v = IsSignedInt64_f<CheckType>();
}

// �uCheckType�v���W�o�C�g�������������^��������R���p�C���\�Ȍ^
template <class CheckType>
using IsUnsignedInt64 = std::enable_if_t<IsUnsignedInt64_v<CheckType>>*;

// �uCheckType�v���W�o�C�g�������������^�ł͂Ȃ�������R���p�C���\�Ȍ^
template <class CheckType>
using IsNotUnsignedInt64 = std::enable_if_t<!IsUnsignedInt64_v<CheckType>>*;

#endif // !IS_CAST_UNSIGNED_INT_64_H_