#ifndef BILLBOARD_CLIPPING_PARAM_H_
#define BILLBOARD_CLIPPING_PARAM_H_

/* class member */
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// �r���{�[�h��ؔ����`�悷��ۂɕK�v�ȕϐ�
	struct BillboardClippingParam
	{
		tktkMath::Vector2 leftTopPos;
		tktkMath::Vector2 size;
	};
}
#endif // !BILLBOARD_CLIPPING_PARAM_H_