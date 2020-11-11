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

		// 描画優先度を設定する
		BillboardDrawerMaker& drawPriority(float value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		// ※初期パラメータはバックバッファー
		BillboardDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// 使用するビルボードマテリアルハンドルを設定する
		BillboardDrawerMaker& billboardMaterialHandle(size_t value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		BillboardDrawerMaker& cameraHandle(size_t value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		BillboardDrawerMaker& cameraId(ResourceIdCarrier value);

		// 使用するビルボードマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		BillboardDrawerMaker& billboardMaterialId(ResourceIdCarrier value);

		// ビルボードの中心位置の割合を設定する
		BillboardDrawerMaker& centerRate(const tktkMath::Vector2 & value);

		// ビルボードのブレンドレートを設定する
		BillboardDrawerMaker& blendRate(const tktkMath::Color& value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BillboardDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user						{  };
		float				m_drawPriority				{ 0.0f };
		size_t				m_useRtvDescriptorHeapHandle{  };
		size_t				m_cameraHandle				{ 0U };
		size_t				m_billboardMaterialHandle	{ 0U };
		tktkMath::Vector2	m_centerRate				{ 0.5f, 0.5f };
		tktkMath::Color		m_blendRate					{ tktkMath::Color_v::white };
	};
}
#endif // !BILLBOARD_DRAWER_MAKER_H_