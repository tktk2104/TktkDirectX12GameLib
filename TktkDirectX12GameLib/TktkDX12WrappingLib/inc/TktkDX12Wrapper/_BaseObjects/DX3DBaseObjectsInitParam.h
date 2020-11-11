#ifndef DX3D_BASE_OBJECTS_INIT_PARAM_H_
#define DX3D_BASE_OBJECTS_INIT_PARAM_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../Includer/WindowsHeaderIncluder.h"
#include "../Resource/DX3DResourceNum.h"

namespace tktk
{
	// 「DX3DBaseObjects」を作る時に必要な変数
	struct DX3DBaseObjectsInitParam
	{
		DX3DResourceNum		resourceNum;
		HWND				hwnd;
		tktkMath::Vector2	windowSize;
		bool				craeteDebugLayer;
	};
}
#endif // !DX3D_BASE_OBJECTS_INIT_PARAM_H_
