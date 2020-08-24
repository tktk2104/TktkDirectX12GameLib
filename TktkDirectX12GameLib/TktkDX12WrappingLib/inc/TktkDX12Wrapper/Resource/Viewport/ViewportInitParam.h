#ifndef VIEWPORT_INIT_PARAM_H_
#define VIEWPORT_INIT_PARAM_H_

#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// ビューポートを作る時に必要な変数
	struct ViewportInitParam
	{
		tktkMath::Vector2	windowSize;
		tktkMath::Vector2	topLeft;
		float				maxDepth;
		float				minDepth;
	};
}
#endif // !VIEWPORT_INIT_PARAM_H_