#ifndef POST_EFFECT_SHADER_FILE_PATHS_H_
#define POST_EFFECT_SHADER_FILE_PATHS_H_

#include <string>

namespace tktk
{
	// ポストエフェクトで使用するデフォルトのシェーダーファイルパス
	struct PostEffectShaderFilePaths
	{
		std::string postEffectVSFilePath;

		std::string monochromePSFilePath;
	};
}
#endif // !POST_EFFECT_SHADER_FILE_PATHS_H_
