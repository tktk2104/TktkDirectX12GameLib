#ifndef BILLBOARD_MATERIAL_CBUFFER_DATA_H_
#define BILLBOARD_MATERIAL_CBUFFER_DATA_H_

#include <TktkMath/Structs/Color.h>

namespace tktk
{
	struct BillboardMaterialCbufferData
	{
		// ブレンドレート
		tktkMath::Color		blendRate{ tktkMath::Color_v::white };
	};
}
#endif // !BILLBOARD_MATERIAL_CBUFFER_DATA_H_
