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
		// ※初期パラメータはバックバッファー
		SpriteDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// 使用するスプライトマテリアルハンドルを設定する
		SpriteDrawerMaker& spriteMaterialHandle(unsigned int value);

		// 使用するスプライトマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		template<class IdType, is_idType<IdType> = nullptr>
		SpriteDrawerMaker& spriteMaterialId(IdType value) { return spriteMaterialIdImpl(static_cast<int>(value)); }

		// スプライトの中心位置の割合を設定する
		SpriteDrawerMaker& centerRate(const tktkMath::Vector2& value);

	private: /* 各種id指定系の関数の実装 */

		SpriteDrawerMaker& spriteMaterialIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SpriteDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user						{  };
		float				m_drawPriority				{ 0.0f };
		unsigned int		m_useRtvDescriptorHeapHandle{  };
		unsigned int		m_spriteMaterialHandle		{ 0U };
		tktkMath::Vector2	m_centerRate				{ 0.5f, 0.5f };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, is_not_idType<IdType> = nullptr>
		SpriteDrawerMaker& spriteMaterialId(IdType value) { static_assert(false, "SpriteMaterialId Fraud Type"); }
	};
}
#endif // !SPRITE_DRAWER_MAKER_H_