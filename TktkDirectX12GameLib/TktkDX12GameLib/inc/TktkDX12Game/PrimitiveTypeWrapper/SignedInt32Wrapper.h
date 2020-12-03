#ifndef SIGNED_INT_32_WRAPPER_H_
#define SIGNED_INT_32_WRAPPER_H_

#include <TktkTemplateMetaLib/TypeCheck/isCastSignedInt32.h>

namespace tktk
{
	// �S�o�C�g�����t��������ێ�����\����
	struct SignedInt32Wrapper
	{
	public:

		SignedInt32Wrapper() = default;

		// �Öٕϊ����������߂ɂ킴�Ɓuexplicit�v���O���Ă���
		template <class ConstructType, IsSignedInt32<ConstructType> = nullptr>
		SignedInt32Wrapper(ConstructType tag) : value(static_cast<int>(tag)) {}

		// �s���Ȍ^���������Ƃ���
		template <class ConstructType, IsNotSignedInt32<ConstructType> = nullptr>
		SignedInt32Wrapper(ConstructType tag) { static_assert(false, "ConstructType Fraud Type"); }

	public:

		// �����̃��b�Z�[�W�̎�ނƎ��g�̃��b�Z�[�W�̎�ނ������������ʂ���
		template <class ConstructType, IsSignedInt32<ConstructType> = nullptr>
		bool isSame(ConstructType other) { return value == static_cast<int>(other); }

		// �s���Ȍ^���r����
		template <class ConstructType, IsNotSignedInt32<ConstructType> = nullptr>
		bool isSame(ConstructType other) { static_assert(false, "ConstructType Fraud Type"); }

	public:

		bool operator==(const SignedInt32Wrapper& other) const { return value == other.value; }
		bool operator!=(const SignedInt32Wrapper& other) const { return value != other.value; }

	public:

		int value{};
	};
}

// �uSignedInt32Wrapper�v���n�b�V���ɑΉ�������
template<>
struct std::hash<tktk::SignedInt32Wrapper>
{
	size_t operator()(const tktk::SignedInt32Wrapper& data) const { return std::hash<int>()(data.value); }
};
#endif // !SIGNED_INT_32_WRAPPER_H_