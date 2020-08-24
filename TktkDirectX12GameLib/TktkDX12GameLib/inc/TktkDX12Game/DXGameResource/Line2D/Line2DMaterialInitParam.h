#ifndef LINE_2D_DATA_INIT_PARAM_H_
#define LINE_2D_DATA_INIT_PARAM_H_

#include <vector>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// ２Ｄラインを作る時に必要な変数
	struct Line2DMaterialDataInitParam
	{
		unsigned int					createVertexBufferId;
	};
}
#endif // !LINE_2D_DATA_INIT_PARAM_H_