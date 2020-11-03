#ifndef GAME_OBJECT_TAG_CARRIER_H_
#define GAME_OBJECT_TAG_CARRIER_H_

#include <TktkTemplateMetaLib/TypeCheck/isCastSignedInt32.h>

namespace tktk
{
	// ゲームオブジェクトタグを保持する構造体
	struct GameObjectTagCarrier
	{
	public:

		GameObjectTagCarrier() = default;

		// 暗黙変換を許すためにわざと「explicit」を外している
		template <class TagType, IsSignedInt32<TagType> = nullptr>
		GameObjectTagCarrier(TagType tag) : tag(static_cast<int>(tag)) {}

		// 不正な型をGameObjectTagとして扱おうとした
		template <class TagType, IsNotSignedInt32<TagType> = nullptr>
		GameObjectTagCarrier(TagType tag) { static_assert(false, "GameObjectTag Fraud Type"); }

	public:

		// 引数のタグと自身のタグが等しいか識別する
		template <class TagType, IsSignedInt32<TagType> = nullptr>
		bool isSame(TagType other) { return tag == static_cast<int>(other); }

		// 不正な型を比較した
		template <class TagType, IsNotSignedInt32<TagType> = nullptr>
		bool isSame(TagType other) { static_assert(false, "GameObjectTag Fraud Type"); }

	public:

		bool operator==(const GameObjectTagCarrier& other) const { return tag == other.tag; }
		bool operator!=(const GameObjectTagCarrier& other) const { return tag != other.tag; }

	public:

		int tag{};
	};
}

// 「GameObjectTagCarrier」をハッシュに対応させる
template<>
struct std::hash<tktk::GameObjectTagCarrier>
{
	size_t operator()(const tktk::GameObjectTagCarrier& data) const { return std::hash<int>()(data.tag); }
};
#endif // !GAME_OBJECT_TAG_CARRIER_H_