#ifndef LINE_2D_DATA_H_
#define LINE_2D_DATA_H_

#include "Line2DMaterialInitParam.h"
#include "Line2DMaterialDrawFuncArgs.h"

namespace tktk
{
	// ライン２Dの情報を管理するクラス
	class Line2DMaterialData
	{
	public:

		explicit Line2DMaterialData(const Line2DMaterialDataInitParam& initParam);
		~Line2DMaterialData() = default;

	public:

		// ２Ｄラインを描画する
		void drawLine(const Line2DMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		// ２Ｄラインの定数バッファを更新する
		void updateLine2DCbuffer(const Line2DMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		unsigned int m_createdVertexBufferId;
	};
}

#endif // !LINE_2D_DATA_H_