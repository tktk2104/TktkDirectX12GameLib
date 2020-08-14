#ifndef SCISSOR_RECT_INIT_PARAM_H_
#define SCISSOR_RECT_INIT_PARAM_H_

#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// シザー矩形を作る時に必要な変数
	struct ScissorRectInitParam
	{
		tktkMath::Vector2	m_topLeft;
		tktkMath::Vector2	m_botRight;
	};
}
#endif // !SCISSOR_RECT_INIT_PARAM_H_