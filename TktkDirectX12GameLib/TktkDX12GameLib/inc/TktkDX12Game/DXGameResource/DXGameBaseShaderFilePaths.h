#ifndef DX_GAME_BASE_SHADER_FILE_PATHS_H_
#define DX_GAME_BASE_SHADER_FILE_PATHS_H_

#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "PostEffect/PostEffectShaderFilePaths.h"
#include "Mesh/MeshResourceShaderFilePaths.h"

namespace tktk
{
	// ゲームで使用する表面的なリソースで使用するシェーダーのファイルパス
	struct DXGameBaseShaderFilePaths
	{
		// スプライトシェーダーのファイルパス
		ShaderFilePaths				spriteShaderFilePaths		{};

		// 2Dラインシェーダーのファイルパス
		ShaderFilePaths				line2DShaderFilePaths		{};

		// ビルボードシェーダーのファイルパス
		ShaderFilePaths				billboardShaderFilePaths	{};

		// メッシュ描画で使用するシェーダーのファイルパス
		MeshResourceShaderFilePaths	meshResourceShaderFilePaths	{};

		// ポストエフェクトシェーダーのファイルパス
		PostEffectShaderFilePaths	postEffectShaderFilePaths{};
	};
}
#endif // !DX_GAME_BASE_SHADER_FILE_PATHS_H_