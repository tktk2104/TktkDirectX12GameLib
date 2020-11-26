#ifndef SPRITE_CLIPPING_DRAWER_MAKER_H_
#define SPRITE_CLIPPING_DRAWER_MAKER_H_

#include "SpriteClippingDrawer.h"

namespace tktk
{
	// 「SpriteClippingDrawer」を作るヘルパークラス
	class SpriteClippingDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		SpriteClippingDrawerMaker() = default;
		SpriteClippingDrawerMaker(const SpriteClippingDrawerMaker& other) = default;
		SpriteClippingDrawerMaker& operator = (const SpriteClippingDrawerMaker& other) = default;

	public:

		// 作成開始
		static SpriteClippingDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<SpriteClippingDrawer> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		SpriteClippingDrawerMaker& drawPriority(float value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		// ※初期パラメータはバックバッファー
		SpriteClippingDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// 使用するスプライトマテリアルハンドルを設定する
		SpriteClippingDrawerMaker& spriteMaterialHandle(size_t value);

		// 使用するスプライトマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		SpriteClippingDrawerMaker& spriteMaterialId(ResourceIdCarrier value);

		// スプライトの中心位置の割合を設定する
		SpriteClippingDrawerMaker& centerRate(const tktkMath::Vector2& value);

		// ブレンドレートを設定する
		SpriteClippingDrawerMaker& blendRate(const tktkMath::Color& value);

		// 切り取る範囲のテクスチャ座標での左上座標を設定する（テクセル）
		SpriteClippingDrawerMaker& clippingLeftTopPos(const tktkMath::Vector2& value);

		// 切り取る範囲の大きさを設定する（テクセル）
		SpriteClippingDrawerMaker& clippingSize(const tktkMath::Vector2& value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SpriteClippingDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user						{  };
		float				m_drawPriority				{ 0.0f };
		size_t				m_useRtvDescriptorHeapHandle{  };
		size_t				m_spriteMaterialHandle		{ 0U };
		tktkMath::Vector2	m_centerRate				{ 0.5f, 0.5f };
		tktkMath::Color		m_blendRate					{ tktkMath::Color_v::white };
		SpriteClippingParam	m_clippingParam				{  };
	};
}
#endif // !SPRITE_CLIPPING_DRAWER_MAKER_H_
