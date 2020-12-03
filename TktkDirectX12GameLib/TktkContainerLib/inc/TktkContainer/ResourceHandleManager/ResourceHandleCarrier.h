#ifndef RESOURCE_HANDLE_CARRIER_H_
#define RESOURCE_HANDLE_CARRIER_H_

#ifdef _M_AMD64 /* x64�r���h�Ȃ� */
#include <TktkTemplateMetaLib/TypeCheck/isCastUnsignedInt64.h>

template <class T>
using IsResourceHandleType		= IsUnsignedInt64<T>;
template <class T>
using IsNotResourceHandleType	= IsNotUnsignedInt64<T>;

#else /* x86�r���h�Ȃ� */
#include <TktkTemplateMetaLib/TypeCheck/isCastUnsignedInt32.h>

template <class T>
using IsResourceHandleType		= IsUnsignedInt32<T>;
template <class T>
using IsNotResourceHandleType	= IsNotUnsignedInt32<T>;
#endif

namespace tktkContainer
{
	// ���\�[�X�n���h����ێ�����\����
	struct ResourceHandleCarrier
	{
	public:

		ResourceHandleCarrier() = default;

		// �Öٕϊ����������߂ɂ킴�Ɓuexplicit�v���O���Ă���
		template <class ConstructType, IsResourceHandleType<ConstructType> = nullptr>
		ResourceHandleCarrier(ConstructType tag) : value(static_cast<size_t>(tag)) {}

		// �s���Ȍ^���������Ƃ���
		template <class ConstructType, IsNotResourceHandleType<ConstructType> = nullptr>
		ResourceHandleCarrier(ConstructType tag) { static_assert(false, "ConstructType Fraud Type"); }

	public:

		// �����̃��b�Z�[�W�̎�ނƎ��g�̃��b�Z�[�W�̎�ނ������������ʂ���
		template <class ConstructType, IsResourceHandleType<ConstructType> = nullptr>
		bool isSame(ConstructType other) { return value == static_cast<size_t>(other); }

		// �s���Ȍ^���r����
		template <class ConstructType, IsNotResourceHandleType<ConstructType> = nullptr>
		bool isSame(ConstructType other) { static_assert(false, "ConstructType Fraud Type"); }

	public:

		bool operator==(const ResourceHandleCarrier& other) const { return value == other.value; }
		bool operator!=(const ResourceHandleCarrier& other) const { return value != other.value; }

	public:

		size_t value{};
	};
}
#endif // !RESOURCE_HANDLE_CARRIER_H_