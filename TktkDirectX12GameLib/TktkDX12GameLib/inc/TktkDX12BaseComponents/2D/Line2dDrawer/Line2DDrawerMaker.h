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

		// 線分を構成する頂点座標の配列を設定する
		Line2DDrawerMaker& lineVertexArray(const std::vector<tktkMath::Vector2>& value);

		// 線の色を設定する
		Line2DDrawerMaker& lineColor(const tktkMath::Color& value);

		// 描画先画像に描画結果をどれぐらいの比率でブレンドするかを設定する
		Line2DDrawerMaker& blendRate(const tktkMath::Color& value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		Line2DDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

	private:

		// 自身のポインタ
		static Line2DDrawerMaker m_self;
	
	private:

		// 作成用変数達
		GameObjectPtr					m_user						{ };
		float							m_drawPriority				{ 0.0f };
		unsigned int					m_useRtvDescriptorHeapHandle{  }; // ※初期パラメータはバックバッファー
		std::vector<tktkMath::Vector2>	m_lineVertexArray			{ };
		tktkMath::Color					m_lineColor					{ tktkMath::Color_v::white };
		tktkMath::Color					m_blendRate					{ 1.0f, 1.0f, 1.0f, 1.0f };
	};
}
#endif // !LINE_2D_DRAWER_MAKER_H_