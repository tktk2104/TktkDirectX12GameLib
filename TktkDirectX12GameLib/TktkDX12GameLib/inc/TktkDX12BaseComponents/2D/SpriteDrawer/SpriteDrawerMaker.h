#ifndef SPRITE_DRAWER_MAKER_H_
#define SPRITE_DRAWER_MAKER_H_

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
		SpriteDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// 使用するスプライトマテリアルハンドルを設定する
		SpriteDrawerMaker& spriteMaterialHandle(size_t value);

		// 使用するスプライトマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		SpriteDrawerMaker& spriteMaterialId(ResourceIdCarrier value);

		// スプライトの中心位置の割合を設定する
		SpriteDrawerMaker& centerRate(const tktkMath::Vector2& value);

		// ブレンドレートを設定する
		SpriteDrawerMaker& blendRate(const tktkMath::Color& value);

		// 切り取る範囲の左上座標を設定する（テクスチャサイズを（1, 1）とした時の割合）
		SpriteDrawerMaker& clippingLeftTopPosRate(const tktkMath::Vector2& value);

		// 切り取る範囲の大きさを設定する（テクスチャサイズを（1, 1）とした時の割合）
		SpriteDrawerMaker& clippingSizeRate(const tktkMath::Vector2& value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SpriteDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user						{  };
		float				m_drawPriority				{ 0.0f };
		size_t				m_useRtvDescriptorHeapHandle{  };
		size_t				m_spriteMaterialHandle		{ 0U };
		tktkMath::Vector2	m_centerRate				{ 0.5f, 0.5f };
		tktkMath::Color		m_blendRate					{ tktkMath::Color_v::white };
		tktkMath::Vector2	m_leftTopPosRate			{ tktkMath::Vector2_v::zero };
		tktkMath::Vector2	m_sizeRate					{ tktkMath::Vector2_v::one };
	};
}
#endif // !SPRITE_DRAWER_MAKER_H_