#ifndef BILLBOARD_DRAWER_MAKER_H_
#define BILLBOARD_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
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

		// ステートを指定し、作成を開始する
		static BillboardDrawerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<BillboardDrawer> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		BillboardDrawerMaker& drawPriority(float value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		// ※初期パラメータはバックバッファー
		BillboardDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// 使用するビルボードマテリアルハンドルを設定する
		BillboardDrawerMaker& billboardMaterialHandle(unsigned int value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		BillboardDrawerMaker& cameraHandle(unsigned int value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		template<class IdType, is_idType<IdType> = nullptr>
		BillboardDrawerMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

		// 使用するビルボードマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		template<class IdType, is_idType<IdType> = nullptr>
		BillboardDrawerMaker& billboardMaterialId(IdType value) { return billboardMaterialIdImpl(static_cast<int>(value)); }

		// ビルボードの中心位置の割合を設定する
		BillboardDrawerMaker& centerRate(const tktkMath::Vector2 & value);

		// ビルボードのブレンドレートを設定する
		BillboardDrawerMaker& blendRate(const tktkMath::Color& value);

	private: /* 各種id指定系の関数の実装 */

		BillboardDrawerMaker& billboardMaterialIdImpl(int value);
		BillboardDrawerMaker& cameraIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BillboardDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user						{  };
		StateTypeHierarchy		m_targetState				{  };
		float				m_drawPriority				{ 0.0f };
		unsigned int		m_useRtvDescriptorHeapHandle{  };
		unsigned int		m_cameraHandle				{ 0U };
		unsigned int		m_billboardMaterialHandle	{ 0U };
		tktkMath::Vector2	m_centerRate				{ 0.5f, 0.5f };
		tktkMath::Color		m_blendRate					{ tktkMath::Color_v::white };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BillboardDrawerMaker& billboardMaterialId(IdType value) { static_assert(false, "BillboardMaterialId Fraud Type"); }
	};
}
#endif // !BILLBOARD_DRAWER_MAKER_H_