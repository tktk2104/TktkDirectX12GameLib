#ifndef LINE_2D_CONSTANT_BUFFER_DATA_H_
#define LINE_2D_CONSTANT_BUFFER_DATA_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// ２Ｄライン描画用の定数バッファ
	struct Line2DConstantBufferData
	{
		// ワールド行列
		float				worldMatrix[12]{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f
		};

		// 線の色
		tktkMath::Color		lineColor;

		// 画面サイズ
		tktkMath::Vector2	screenSize;

		// パディング
		float				pad[2]{ 0.0f, 0.0f };
	};
}
#endif // !LINE_2D_CONSTANT_BUFFER_DATA_H_