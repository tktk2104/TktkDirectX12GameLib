#ifndef SPRITE_DRAWER_MAKER_H_
#define SPRITE_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "SpriteDrawer.h"

namespace tktk
{
	// 「SpriteDrawer」を作るヘルパークラス
	class SpriteDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		SpriteDrawerMaker() = default;
		SpriteDrawerMaker(const SpriteDrawerMaker& other) = default;
		SpriteDrawerMaker& operator = (const SpriteDrawerMaker& other) = default;

	public:

		// 作成開始
		static SpriteDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<SpriteDrawer> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		SpriteDrawerMaker& drawPriority(float value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		SpriteDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// 使用するスプライトマテリアルハンドルを設定する
		SpriteDrawerMaker& spriteMaterialHandle(unsigned int value);

		// 使用するスプライトマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		template<class IdType, is_idType<IdType> = nullptr>
		SpriteDrawerMaker& spriteMaterialId(IdType value);

	private: /* 各種id指定系の関数の実装 */

		SpriteDrawerMaker& spriteMaterialIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SpriteDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr	m_user						{  };
		float			m_drawPriority				{ 0.0f };
		unsigned int	m_useRtvDescriptorHeapHandle{  }; // ※初期パラメータはバックバッファー
		unsigned int	m_spriteMaterialHandle		{ 0U };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteDrawerMaker& spriteMaterialId(IdType value) { static_assert(false, "PostEffectMaterialId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 使用するスプライトマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline SpriteDrawerMaker& SpriteDrawerMaker::spriteMaterialId(IdType value)
	{
		return spriteMaterialIdImpl(static_cast<int>(value));
	}
}
#endif // !SPRITE_DRAWER_MAKER_H_