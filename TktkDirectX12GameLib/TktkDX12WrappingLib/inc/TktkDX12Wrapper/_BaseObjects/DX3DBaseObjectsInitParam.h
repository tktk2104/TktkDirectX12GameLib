#ifndef DX3D_BASE_OBJECTS_INIT_PARAM_H_
#define DX3D_BASE_OBJECTS_INIT_PARAM_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../Includer/WindowsHeaderIncluder.h"
#include "../Resource/DX3DResourceNum.h"

namespace tktk
{
	// �uDX3DBaseObjects�v����鎞�ɕK�v�ȕϐ�
	struct DX3DBaseObjectsInitParam
	{
		DX3DResourceNum		resourceNum;
		HWND				hwnd;
		tktkMath::Vector2	windowSize;
		tktkMath::Color		backGroundColor;
		bool				craeteDebugLayer;
	};
}
#endif // !DX3D_BASE_OBJECTS_INIT_PARAM_H_