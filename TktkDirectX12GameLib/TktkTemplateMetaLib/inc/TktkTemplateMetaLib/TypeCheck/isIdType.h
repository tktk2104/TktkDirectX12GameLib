#ifndef IS_ID_TYPE_H_
#define IS_ID_TYPE_H_

#include <type_traits>

// �e���v���[�g�����̌^��id��\����œK�؂��𔻒肷��萔
template <class T>
constexpr bool is_idType_v = (std::is_enum_v<T> || std::is_integral_v<T>);

// �uCheckType�v��id��\���^��������R���p�C���\�Ȍ^
template <class CheckType>
using is_idType = std::enable_if_t<is_idType_v<CheckType>>*;

// �uCheckType�v��id��\���^�ł͖���������R���p�C���\�Ȍ^
template <class CheckType>
using is_not_idType = std::enable_if_t<!is_idType_v<CheckType>>*;

#endif // !IS_ID_TYPE_H_