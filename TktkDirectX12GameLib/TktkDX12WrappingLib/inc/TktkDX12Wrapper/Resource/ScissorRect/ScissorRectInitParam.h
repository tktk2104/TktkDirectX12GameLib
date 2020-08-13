#ifndef SCISSOR_RECT_INIT_PARAM_H_
#define SCISSOR_RECT_INIT_PARAM_H_

#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	struct ScissorRectInitParam
	{
		tktkMath::Vector2	m_topLeft;
		tktkMath::Vector2	m_botRight;
	};
}
#endif // !SCISSOR_RECT_INIT_PARAM_H_