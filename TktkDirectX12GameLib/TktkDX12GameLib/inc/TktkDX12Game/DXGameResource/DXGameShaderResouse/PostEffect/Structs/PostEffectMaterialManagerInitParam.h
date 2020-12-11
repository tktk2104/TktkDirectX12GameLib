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
		std::string									drawGameAreaVSFilePath;
		std::string									drawGameAreaPSFilePath;

		std::string									postEffectVSFilePath;
		std::string									notPostEffectPSFilePath;
		std::string									monochromePSFilePath;

		std::string									negativePSFilePath;
		std::string									averagingBlurPSFilePath;
		std::string									embossPSFilePath;
		std::string									sharpnessPSFilePath;

		tktkContainer::ResourceContainerInitParam	containerParam;
	};
}
#endif // !POST_EFFECT_MATERIAL_MANAGER_INIT_PARAM_H_