#ifndef LINE_2D_DATA_H_
#define LINE_2D_DATA_H_

#include "Line2DMaterialDrawFuncArgs.h"

namespace tktk
{
	// ライン２Dの情報を管理するクラス
	class Line2DMaterialData
	{
	public:

		Line2DMaterialData();
		~Line2DMaterialData();

		// ムーブコンストラクタ
		Line2DMaterialData(Line2DMaterialData&& other) noexcept;

	public:

		// ２Ｄラインを描画する
		// ※前フレームで作った頂点バッファを削除し、内部でライン描画用の頂点バッファを作り、そのリソースハンドルを保持する処理の為、非const関数
		void drawLine(const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	private:

		// 定数バッファのコピー用バッファを更新する
		void updateCopyCbuffer(const Line2DMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		size_t m_createUploadCbufferHandle{ 0U };
		size_t m_createdVertexBufferHandle{ 0U };
	};
}

#endif // !LINE_2D_DATA_H_