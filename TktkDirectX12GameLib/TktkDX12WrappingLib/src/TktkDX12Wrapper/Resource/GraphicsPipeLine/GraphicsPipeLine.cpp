#include "TktkDX12Wrapper/Resource/GraphicsPipeLine/GraphicsPipeLine.h"

namespace tktk
{
	GraphicsPipeLine::GraphicsPipeLine(unsigned int pipeLineNum, unsigned int rootSignatureNum)
		: m_rootSignature(rootSignatureNum)
		, m_pipeLineState(pipeLineNum)
	{
	}

	void GraphicsPipeLine::createRootSignature(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		m_rootSignature.create(id, device, initParam);
	}

	void GraphicsPipeLine::createPipeLineState(unsigned int id, ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		m_pipeLineState.createPipeLineState(id, device, initParam, shaderFilePath, m_rootSignature.getPtr(initParam.rootSignatureId));
	}

	void GraphicsPipeLine::set(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_rootSignature.set(m_pipeLineState.getUseRootSignatureIndex(id), commandList);
		m_pipeLineState.set(id, commandList);
	}
}