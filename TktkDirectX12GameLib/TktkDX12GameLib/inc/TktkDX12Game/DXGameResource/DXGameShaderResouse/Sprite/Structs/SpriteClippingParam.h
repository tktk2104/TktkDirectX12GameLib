#ifndef SPRITE_CLIPPING_PARAM_H_
#define SPRITE_CLIPPING_PARAM_H_

/* class member */
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// スプライトの切抜き描画をする時に必要な変数
	struct SpriteClippingParam
	{
		tktkMath::Vector2 leftTopPos;
		tktkMath::Vector2 size;
	};
}
#endif // !SPRITE_CLIPPING_PARAM_H_