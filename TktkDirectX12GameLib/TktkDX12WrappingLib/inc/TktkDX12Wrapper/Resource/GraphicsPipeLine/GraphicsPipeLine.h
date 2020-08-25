#ifndef GRAPHICS_PIPE_LINE_H_
#define GRAPHICS_PIPE_LINE_H_

#include <memory>	// std::unique_ptr
#include "../../Includer/D3d12Includer.h"
#include "GraphicsPipeLineInitParamIncluder.h"
#include "GraphicsPipeLineResourceNum.h"

namespace tktk
{
	// �O���錾�B
	class RootSignature;
	class PipeLineState;

	// �O���t�B�b�N�p�C�v���C�����Ǘ�����N���X
	class GraphicsPipeLine
	{
	public:

		explicit GraphicsPipeLine(const GraphicsPipeLineResourceNum& initParam);
		~GraphicsPipeLine();

	public:

		// ���[�g�V�O�l�`�������
		unsigned int createRootSignature(ID3D12Device* device, const RootSignatureInitParam& initParam);

	public:

		// �p�C�v���C���X�e�[�g�����
		unsigned int createPipeLineState(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

	public:

		// �O���t�B�b�N�p�C�v���C�����R�}���h���X�g�ɓo�^����
		void set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		std::unique_ptr<RootSignature> m_rootSignature;
		std::unique_ptr<PipeLineState> m_pipeLineState;
	};
}
#endif // !GRAPHICS_PIPE_LINE_H_