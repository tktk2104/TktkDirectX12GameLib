#ifndef LINE_2D_DATA_H_
#define LINE_2D_DATA_H_

#include "Line2DMaterialInitParam.h"
#include "Line2DMaterialDrawFuncArgs.h"

namespace tktk
{
	// ƒ‰ƒCƒ“‚QD‚Ìî•ñ‚ğŠÇ—‚·‚éƒNƒ‰ƒX
	class Line2DMaterialData
	{
	public:

		explicit Line2DMaterialData(const Line2DMaterialDataInitParam& initParam);
		~Line2DMaterialData() = default;

	public:

		void drawLine(const Line2DMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		void updateLine2DCbuffer(const Line2DMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		unsigned int m_createdVertexBufferId;
	};
}

#endif // !LINE_2D_DATA_H_