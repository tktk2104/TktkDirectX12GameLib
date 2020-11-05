#ifndef BILLBOARD_CLIPPING_DRAWER_MAKER_H_
#define BILLBOARD_CLIPPING_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BillboardClippingDrawer.h"

namespace tktk
{
	// 「BillboardClippingDrawer」を作るヘルパークラス
	class BillboardClippingDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		BillboardClippingDrawerMaker() = default;
		BillboardClippingDrawerMaker(const BillboardClippingDrawerMaker& other) = default;
		BillboardClippingDrawerMaker& operator = (const BillboardClippingDrawerMaker& other) = default;

	public:

		// 作成開始
		static BillboardClippingDrawerMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		static BillboardClippingDrawerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<BillboardClippingDrawer> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		BillboardClippingDrawerMaker& drawPriority(float value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		// ※初期パラメータはバックバッファー
		BillboardClippingDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// 使用するビルボードマテリアルハンドルを設定する
		BillboardClippingDrawerMaker& billboardMaterialHandle(size_t value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		BillboardClippingDrawerMaker& cameraHandle(size_t value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		BillboardClippingDrawerMaker& cameraId(ResourceIdCarrier value);

		// 使用するビルボードマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される
		BillboardClippingDrawerMaker& billboardMaterialId(ResourceIdCarrier value);

		// ビルボードの中心位置の割合を設定する
		BillboardClippingDrawerMaker& centerRate(const tktkMath::Vector2 & value);

		// ビルボードのブレンドレートを設定する
		BillboardClippingDrawerMaker& blendRate(const tktkMath::Color& value);

		// 切り取る範囲のテクスチャ座標での左上座標を設定する（テクセル）
		BillboardClippingDrawerMaker& clippingLeftTopPos(const tktkMath::Vector2& value);

		// 切り取る範囲の大きさを設定する（テクセル）
		BillboardClippingDrawerMaker& clippingSize(const tktkMath::Vector2& value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BillboardClippingDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr			m_user						{  };
		StateTypeHierarchy		m_targetState				{  };
		float					m_drawPriority				{ 0.0f };
		size_t					m_useRtvDescriptorHeapHandle{  };
		size_t					m_cameraHandle				{ 0U };
		size_t					m_billboardMaterialHandle	{ 0U };
		tktkMath::Vector2		m_centerRate				{ 0.5f, 0.5f };
		tktkMath::Color			m_blendRate					{ tktkMath::Color_v::white };
		BillboardClippingParam	m_clippingParam				{  };
	};
}
#endif // !BILLBOARD_CLIPPING_DRAWER_MAKER_H_