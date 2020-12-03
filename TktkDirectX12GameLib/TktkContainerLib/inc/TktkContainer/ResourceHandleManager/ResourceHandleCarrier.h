#ifndef RESOURCE_HANDLE_CARRIER_H_
#define RESOURCE_HANDLE_CARRIER_H_

#ifdef _M_AMD64 /* x64ビルドなら */
#include <TktkTemplateMetaLib/TypeCheck/isCastUnsignedInt64.h>

template <class T>
using IsResourceHandleType		= IsUnsignedInt64<T>;
template <class T>
using IsNotResourceHandleType	= IsNotUnsignedInt64<T>;

#else /* x86ビルドなら */
#include <TktkTemplateMetaLib/TypeCheck/isCastUnsignedInt32.h>

template <class T>
using IsResourceHandleType		= IsUnsignedInt32<T>;
template <class T>
using IsNotResourceHandleType	= IsNotUnsignedInt32<T>;
#endif

namespace tktkContainer
{
	// リソースハンドルを保持する構造体
	struct ResourceHandleCarrier
	{
	public:

		ResourceHandleCarrier() = default;

		// 暗黙変換を許すためにわざと「explicit」を外している
		template <class ConstructType, IsResourceHandleType<ConstructType> = nullptr>
		ResourceHandleCarrier(ConstructType tag) : value(static_cast<size_t>(tag)) {}

		// 不正な型を扱おうとした
		template <class ConstructType, IsNotResourceHandleType<ConstructType> = nullptr>
		ResourceHandleCarrier(ConstructType tag) { static_assert(false, "ConstructType Fraud Type"); }

	public:

		// 引数のメッセージの種類と自身のメッセージの種類が等しいか識別する
		template <class ConstructType, IsResourceHandleType<ConstructType> = nullptr>
		bool isSame(ConstructType other) { return value == static_cast<size_t>(other); }

		// 不正な型を比較した
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