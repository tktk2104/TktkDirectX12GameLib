#ifndef DX_GAME_RESOURCE_INIT_PARAM_H_
#define DX_GAME_RESOURCE_INIT_PARAM_H_

#include "Draw3DParameters/Structs/Draw3DParametersInitParam.h"
#include "DXGameShaderResouse/Structs/DXGameShaderResouseInitParam.h"
#include "DrawFuncRunnerManager/Structs/DrawFuncRunnerManagerInitParam.h"
#include "OtherResouse/Structs/OtherResouseInitParam.h"

namespace tktk
{
	struct DXGameResourceInitParam
	{
		Draw3DParametersInitParam		draw3DParam;
		DXGameShaderResouseInitParam	dxGameShaderResParam;
		DrawFuncRunnerManagerInitParam	drawFuncRunnerMgrParam;
		OtherResouseInitParam			otherResParam;
	};
}
#endif // !DX_GAME_RESOURCE_INIT_PARAM_H_