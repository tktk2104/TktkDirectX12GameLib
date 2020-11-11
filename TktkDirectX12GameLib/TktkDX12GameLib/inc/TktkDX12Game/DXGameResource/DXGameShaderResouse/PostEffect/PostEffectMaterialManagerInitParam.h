#ifndef POST_EFFECT_MATERIAL_MANAGER_INIT_PARAM_H_
#define POST_EFFECT_MATERIAL_MANAGER_INIT_PARAM_H_

/* class member */
#include <string>
#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	// ポストエフェクトマテリアル管理クラスの初期化に必要な変数
	struct PostEffectMaterialManagerInitParam
	{
		std::string									postEffectVSFilePath;
		std::string									monochromePSFilePath;
		tktkContainer::ResourceContainerInitParam	containerParam;
	};
}
#endif // !POST_EFFECT_MATERIAL_MANAGER_INIT_PARAM_H_