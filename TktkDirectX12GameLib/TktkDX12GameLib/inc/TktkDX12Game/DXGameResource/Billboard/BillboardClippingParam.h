#ifndef BILLBOARD_CLIPPING_PARAM_H_
#define BILLBOARD_CLIPPING_PARAM_H_

#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	struct BillboardClippingParam
	{
		tktkMath::Vector2 leftTopPos;
		tktkMath::Vector2 size;
	};
}
#endif // !BILLBOARD_CLIPPING_PARAM_H_