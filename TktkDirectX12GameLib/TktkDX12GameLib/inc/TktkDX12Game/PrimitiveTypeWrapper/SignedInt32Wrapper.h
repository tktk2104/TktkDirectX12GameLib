#ifndef SIGNED_INT_32_WRAPPER_H_
#define SIGNED_INT_32_WRAPPER_H_

#include <TktkTemplateMetaLib/TypeCheck/isCastSignedInt32.h>

namespace tktk
{
	// ４バイト符号付き整数を保持する構造体
	struct SignedInt32Wrapper
	{
	public:

		SignedInt32Wrapper() = default;

		// 暗黙変換を許すためにわざと「explicit」を外している
		template <class ConstructType, IsSignedInt32<ConstructType> = nullptr>
		SignedInt32Wrapper(ConstructType tag) : value(static_cast<int>(tag)) {}

		// 不正な型を扱おうとした
		template <class ConstructType, IsNotSignedInt32<ConstructType> = nullptr>
		SignedInt32Wrapper(ConstructType tag) { static_assert(false, "ConstructType Fraud Type"); }

	public:

		// 引数のメッセージの種類と自身のメッセージの種類が等しいか識別する
		template <class ConstructType, IsSignedInt32<ConstructType> = nullptr>
		bool isSame(ConstructType other) { return value == static_cast<int>(other); }

		// 不正な型を比較した
		template <class ConstructType, IsNotSignedInt32<ConstructType> = nullptr>
		bool isSame(ConstructType other) { static_assert(false, "ConstructType Fraud Type"); }

	public:

		bool operator==(const SignedInt32Wrapper& other) const { return value == other.value; }
		bool operator!=(const SignedInt32Wrapper& other) const { return value != other.value; }

	public:

		int value{};
	};
}

// 「SignedInt32Wrapper」をハッシュに対応させる
template<>
struct std::hash<tktk::SignedInt32Wrapper>
{
	size_t operator()(const tktk::SignedInt32Wrapper& data) const { return std::hash<int>()(data.value); }
};
#endif // !SIGNED_INT_32_WRAPPER_H_