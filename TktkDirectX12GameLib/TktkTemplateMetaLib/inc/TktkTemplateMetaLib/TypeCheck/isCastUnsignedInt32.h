#ifndef IS_CAST_UNSIGNED_INT_32_H_
#define IS_CAST_UNSIGNED_INT_32_H_

#include <type_traits>

namespace
{
	// �e���v���[�g�����̌^���S�r�b�g�����t���������ǂ������ʂ���i���̌^��int�ȗ񋓌^���܂ށj
	template <class CheckType, std::enable_if_t<std::is_enum_v<CheckType>>* = nullptr>
	constexpr bool IsUnsignedInt32_f() { return std::is_same_v<std::underlying_type_t<CheckType>, unsigned int>; }

	// �e���v���[�g�����̌^���S�r�b�g�����t���������ǂ������ʂ���i���̌^��int�ȗ񋓌^���܂ށj
	template <class CheckType, std::enable_if_t<!std::is_enum_v<CheckType>>* = nullptr>
	constexpr bool IsUnsignedInt32_f() { return std::is_same_v<CheckType, unsigned int>; };

	template <class CheckType>
	constexpr bool IsUnsignedInt32_v = IsSignedInt32_f<CheckType>();
}

// �uCheckType�v���S�r�b�g�������������^��������R���p�C���\�Ȍ^
template <class CheckType>
using IsUnsignedInt32 = std::enable_if_t<IsUnsignedInt32_v<CheckType>>*;

// �uCheckType�v���S�r�b�g�������������^�ł͂Ȃ�������R���p�C���\�Ȍ^
template <class CheckType>
using IsNotUnsignedInt32 = std::enable_if_t<!IsUnsignedInt32_v<CheckType>>*;

#endif // !IS_CAST_UNSIGNED_INT_32_H_