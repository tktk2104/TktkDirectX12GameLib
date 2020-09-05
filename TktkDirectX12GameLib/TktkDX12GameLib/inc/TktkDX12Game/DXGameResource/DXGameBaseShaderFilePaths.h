#ifndef DX_GAME_BASE_SHADER_FILE_PATHS_H_
#define DX_GAME_BASE_SHADER_FILE_PATHS_H_

#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "PostEffect/PostEffectShaderFilePaths.h"
#include "Mesh/MeshResourceShaderFilePaths.h"

namespace tktk
{
	// �Q�[���Ŏg�p����\�ʓI�ȃ��\�[�X�Ŏg�p����V�F�[�_�[�̃t�@�C���p�X
	struct DXGameBaseShaderFilePaths
	{
		// �X�v���C�g�V�F�[�_�[�̃t�@�C���p�X
		ShaderFilePaths				spriteShaderFilePaths		{};

		// 2D���C���V�F�[�_�[�̃t�@�C���p�X
		ShaderFilePaths				line2DShaderFilePaths		{};

		// �r���{�[�h�V�F�[�_�[�̃t�@�C���p�X
		ShaderFilePaths				billboardShaderFilePaths	{};

		// ���b�V���`��Ŏg�p����V�F�[�_�[�̃t�@�C���p�X
		MeshResourceShaderFilePaths	meshResourceShaderFilePaths	{};

		// �|�X�g�G�t�F�N�g�V�F�[�_�[�̃t�@�C���p�X
		PostEffectShaderFilePaths	postEffectShaderFilePaths{};
	};
}
#endif // !DX_GAME_BASE_SHADER_FILE_PATHS_H_