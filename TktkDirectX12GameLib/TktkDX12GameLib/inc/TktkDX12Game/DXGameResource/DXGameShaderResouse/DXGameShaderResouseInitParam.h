#ifndef DX_GAME_SHADER_RESOUSE_INIT_PARAM_H_
#define DX_GAME_SHADER_RESOUSE_INIT_PARAM_H_

#include "PostEffect/PostEffectMaterialManagerInitParam.h"
#include "Line2D/Line2DMaterialManagerInitParam.h"
#include "Sprite/SpriteMaterialManagerInitParam.h"
#include "Billboard/BillboardMaterialManagerInitParam.h"
#include "MeshResouse/Structs/MeshResourceInitParam.h"

namespace tktk
{
	struct DXGameShaderResouseInitParam
	{
		PostEffectMaterialManagerInitParam	postEffectMatMgrParam;
		Line2DMaterialManagerInitParam		line2DMatMgrParam;
		SpriteMaterialManagerInitParam		spriteMatMgrParam;
		BillboardMaterialManagerInitParam	billboardMatMgrParam;
		MeshResourceInitParam				meshResParam;
	};
}
#endif // !DX_GAME_SHADER_RESOUSE_INIT_PARAM_H_