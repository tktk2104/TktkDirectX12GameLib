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

		// ステートを指定し、作成を開始する
		static SpriteDrawerMaker& makeStart(const StateTypeHierarchy&& targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<SpriteDrawer> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		SpriteDrawerMaker& drawPriority(float value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		// ※初期パラメータはバックバッファー
		SpriteDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// 使用するスプライトマテリアルハンドルを設定する
		SpriteDrawerMaker& spriteMaterialHandle(size_t value);

		// 使用するスプライトマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		SpriteDrawerMaker& spriteMaterialId(ResourceIdCarrier value);

		// スプライトの中心位置の割合を設定する
		SpriteDrawerMaker& centerRate(const tktkMath::Vector2& value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SpriteDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user						{  };
		StateTypeHierarchy	m_targetState				{  };
		float				m_drawPriority				{ 0.0f };
		size_t				m_useRtvDescriptorHeapHandle{  };
		size_t				m_spriteMaterialHandle		{ 0U };
		tktkMath::Vector2	m_centerRate				{ 0.5f, 0.5f };
	};
}
#endif // !SPRITE_DRAWER_MAKER_H_