#ifndef DX_GAME_RESOURCE_INIT_PARAM_H_
#define DX_GAME_RESOURCE_INIT_PARAM_H_

#include "Draw3DParameters/Draw3DParametersInitParam.h"
#include "DXGameShaderResouse/DXGameShaderResouseInitParam.h"
#include "OtherResouse/OtherResouseInitParam.h"

namespace tktk
{
	struct DXGameResourceInitParam
	{
		Draw3DParametersInitParam		draw3DParam;
		DXGameShaderResouseInitParam	dxGameShaderResParam;
		OtherResouseInitParam			otherResParam;
	};
}
#endif // !DX_GAME_RESOURCE_INIT_PARAM_H_