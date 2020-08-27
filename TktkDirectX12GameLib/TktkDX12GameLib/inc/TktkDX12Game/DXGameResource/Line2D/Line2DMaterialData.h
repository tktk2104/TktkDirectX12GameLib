#ifndef LINE_2D_DATA_H_
#define LINE_2D_DATA_H_

#include "Line2DMaterialDrawFuncArgs.h"

namespace tktk
{
	// ライン２Dの情報を管理するクラス
	class Line2DMaterialData
	{
	public:

		Line2DMaterialData() = default;
		~Line2DMaterialData();

		// ムーブコンストラクタ
		Line2DMaterialData(Line2DMaterialData&& other) noexcept;

	public:

		// ２Ｄラインを描画する
		// ※前フレームで作った頂点バッファを削除し、内部でライン描画用の頂点バッファを作り、そのリソースハンドルを保持する処理の為、非const関数
		void drawLine(const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	private:

		// ２Ｄラインの定数バッファを更新する
		void updateLine2DCbuffer(const Line2DMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		unsigned int m_createdVertexBufferHandle{ 0U };
	};
}

#endif // !LINE_2D_DATA_H_