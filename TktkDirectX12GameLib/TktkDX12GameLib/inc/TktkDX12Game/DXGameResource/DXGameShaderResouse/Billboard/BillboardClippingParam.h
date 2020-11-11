#ifndef BILLBOARD_CLIPPING_PARAM_H_
#define BILLBOARD_CLIPPING_PARAM_H_

/* class member */
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// ビルボードを切抜き描画する際に必要な変数
	struct BillboardClippingParam
	{
		tktkMath::Vector2 leftTopPos;
		tktkMath::Vector2 size;
	};
}
#endif // !BILLBOARD_CLIPPING_PARAM_H_