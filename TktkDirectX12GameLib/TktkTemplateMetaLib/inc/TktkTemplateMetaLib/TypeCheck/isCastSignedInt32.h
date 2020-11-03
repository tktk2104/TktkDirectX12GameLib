#ifndef IS_CAST_SIGNED_INT_32_H_
#define IS_CAST_SIGNED_INT_32_H_

#include <type_traits>

namespace
{
	// �e���v���[�g�����̌^���S�r�b�g�����t���������ǂ������ʂ���i���̌^��int�ȗ񋓌^���܂ށj
	template <class CheckType, std::enable_if_t<std::is_enum_v<CheckType>>* = nullptr>
	constexpr bool IsSignedInt32_f() { return std::is_same_v<std::underlying_type_t<CheckType>, int>; }

	// �e���v���[�g�����̌^���S�r�b�g�����t���������ǂ������ʂ���i���̌^��int�ȗ񋓌^���܂ށj
	template <class CheckType, std::enable_if_t<!std::is_enum_v<CheckType>>* = nullptr>
	constexpr bool IsSignedInt32_f() { return std::is_same_v<CheckType, int>; };

	template <class CheckType>
	constexpr bool IsSignedInt32_v = IsSignedInt32_f<CheckType>();
}

// �uCheckType�v���S�r�b�g�����t�������^��������R���p�C���\�Ȍ^
template <class CheckType>
using IsSignedInt32 = std::enable_if_t<IsSignedInt32_v<CheckType>>*;//

// �uCheckType�v���S�r�b�g�����t�������^�ł͂Ȃ�������R���p�C���\�Ȍ^
template <class CheckType>
using IsNotSignedInt32 = std::enable_if_t<!IsSignedInt32_v<CheckType>>*;//!IsSignedInt32_v<CheckType>()

#endif // !IS_CAST_SIGNED_INT_32_H_