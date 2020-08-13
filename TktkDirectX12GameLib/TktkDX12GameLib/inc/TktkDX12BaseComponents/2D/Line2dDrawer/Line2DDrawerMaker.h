#ifndef LINE_2D_DRAWER_MAKER_H_
#define LINE_2D_DRAWER_MAKER_H_
#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "Line2DDrawer.h"

namespace tktk
{
	// 「Line2DDrawerMaker」を作るヘルパークラス
	class Line2DDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		Line2DDrawerMaker() = default;
		Line2DDrawerMaker(const Line2DDrawerMaker & other) = default;
		Line2DDrawerMaker& operator = (const Line2DDrawerMaker & other) = default;

	public:

		// インスタンス作成開始
		static Line2DDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<Line2DDrawer> create();
	

	public: /* パラメータ設定関数 */

		// 描画優先度を設定する
		Line2DDrawerMaker& drawPriority(float value);

		// 使用する線のマテリアルIDを設定する
		template<class IdType, is_idType<IdType> = nullptr>
		Line2DDrawerMaker& useLine2DMaterialId(IdType value);

		// 線分を構成する頂点座標の配列を設定する
		Line2DDrawerMaker& lineVertexArray(const std::vector<tktkMath::Vector2>& value);

		// 線の色を設定する
		Line2DDrawerMaker& lineColor(const tktkMath::Color& value);

		// 描画先画像に描画結果をどれぐらいの比率でブレンドするかを設定する
		Line2DDrawerMaker& blendRate(const tktkMath::Color& value);

		// 使用するレンダーターゲットのディスクリプタヒープIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, is_idType<IdType> = nullptr>
		Line2DDrawerMaker& useRtvDescriptorHeapId(IdType value);
	
	private: /* 各種id指定系の関数の実装 */

		Line2DDrawerMaker& useLine2DMaterialIdImpl(unsigned int value);
		Line2DDrawerMaker& useRtvDescriptorHeapIdImpl(unsigned int value);

	private:

		// 自身のポインタ
		static Line2DDrawerMaker m_self;
	
	private:

		// 作成用変数達
		GameObjectPtr					m_user{ };
		float							m_drawPriority{ 0.0f };
		unsigned int					m_useLine2DMaterialId{  };
		unsigned int					m_useRtvDescriptorHeapId{  }; // ※初期パラメータはバックバッファー
		std::vector<tktkMath::Vector2>	m_lineVertexArray{ };
		tktkMath::Color					m_lineColor{ tktkMath::colorWhite };
		tktkMath::Color					m_blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& useLine2DMaterialId(IdType value) { static_assert(false, "Line2DMaterialId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		Line2DDrawerMaker& useRtvDescriptorHeapId(IdType value) { static_assert(false, "RtvDescriptorHeapId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 使用する線のマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline Line2DDrawerMaker& Line2DDrawerMaker::useLine2DMaterialId(IdType value)
	{
		return useLine2DMaterialIdImpl(static_cast<unsigned int>(value));
	}

	// 使用するレンダーターゲットのディスクリプタヒープIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline Line2DDrawerMaker& Line2DDrawerMaker::useRtvDescriptorHeapId(IdType value)
	{
		return useRtvDescriptorHeapIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !LINE_2D_DRAWER_MAKER_H_