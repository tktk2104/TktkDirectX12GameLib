#ifndef BILLBOARD_DRAWER_MAKER_H_
#define BILLBOARD_DRAWER_MAKER_H_

#include "BillboardDrawer.h"

namespace tktk
{
	// 「BillboardDrawer」を作るヘルパークラス
	class BillboardDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		BillboardDrawerMaker() = default;
		BillboardDrawerMaker(const BillboardDrawerMaker& other) = default;
		BillboardDrawerMaker& operator = (const BillboardDrawerMaker& other) = default;

	public:

		// 作成開始
		static BillboardDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<BillboardDrawer> create();

	public:  /* パラメータ設定関数 */

		// 使用するビルボードマテリアルハンドルを設定する
		BillboardDrawerMaker& billboardMaterialHandle(size_t value);

		// 使用するビルボードマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		BillboardDrawerMaker& billboardMaterialId(ResourceIdCarrier value);

		// ビルボードの中心位置の割合を設定する
		BillboardDrawerMaker& centerRate(const tktkMath::Vector2& value);

		// ビルボードのブレンドレートを設定する
		BillboardDrawerMaker& blendRate(const tktkMath::Color& value);

		// 切り取る範囲のテクスチャ座標での左上座標を設定する（テクセル）
		BillboardDrawerMaker& clippingLeftTopPos(const tktkMath::Vector2& value);

		// ビルボードハンドルを使用し、クリッピングを行わない設定をする
		BillboardDrawerMaker& notClippingUseHandle(size_t billboarddMaterialHandle);

		// ビルボードIdを使用し、クリッピングを行わない設定をする（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		BillboardDrawerMaker& notClippingUseId(ResourceIdCarrier billboarddMaterialId);

		// 切り取る範囲の大きさを設定する（テクセル）
		BillboardDrawerMaker& clippingSize(const tktkMath::Vector2& value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BillboardDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user						{  };
		size_t				m_billboardMaterialHandle	{ 0U };
		tktkMath::Vector2	m_centerRate				{ 0.5f, 0.5f };
		tktkMath::Color		m_blendRate					{ tktkMath::Color_v::white };
		tktkMath::Vector2	m_clippingLeftTopPos		{ 0.0f, 0.0f };
		tktkMath::Vector2	m_clippingSize				{ 64.0f, 64.0f };
	};
}
#endif // !BILLBOARD_DRAWER_MAKER_H_