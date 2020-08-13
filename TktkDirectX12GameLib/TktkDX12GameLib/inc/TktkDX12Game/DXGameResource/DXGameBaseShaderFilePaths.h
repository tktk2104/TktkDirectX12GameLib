#ifndef DX_GAME_BASE_SHADER_FILE_PATHS_H_
#define DX_GAME_BASE_SHADER_FILE_PATHS_H_

#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "PostEffect/PostEffectShaderFilePaths.h"

namespace tktk
{
	// ゲームで使用する表面的なリソースで使用するシェーダーのファイルパス
	struct DXGameBaseShaderFilePaths
	{
		// スプライトシェーダーのファイルパス
		tktk::ShaderFilePaths		spriteShaderFilePaths{};

		// 2Dラインシェーダーのファイルパス
		tktk::ShaderFilePaths		line2DShaderFilePaths{};

		// 通常メッシュシェーダーのファイルパス
		tktk::ShaderFilePaths		basicMeshShaderFilePaths{};

		// 単色塗りつぶしメッシュシェーダーのファイルパス
		std::string					monoColorShaderPsFilePath;

		// シャドウマップシェーダーのファイルパス
		std::string					writeShadowMapVsFilePath{};

		// ポストエフェクトシェーダーのファイルパス
		PostEffectShaderFilePaths	postEffectShaderFilePaths{};
	};
}
#endif // !DX_GAME_BASE_SHADER_FILE_PATHS_H_