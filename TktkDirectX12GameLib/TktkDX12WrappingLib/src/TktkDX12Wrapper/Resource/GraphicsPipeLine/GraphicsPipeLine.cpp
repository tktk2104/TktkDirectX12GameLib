#include "TktkDX12Wrapper/Resource/GraphicsPipeLine/GraphicsPipeLine.h"

#include "TktkDX12Wrapper/Resource/GraphicsPipeLine/RootSignature/RootSignature.h"
#include "TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineState.h"

namespace tktk
{
	GraphicsPipeLine::GraphicsPipeLine(const GraphicsPipeLineResourceNum& initParam)
	{
		m_rootSignature = std::make_unique<RootSignature>(initParam.rootSignatureContainerInitParam);
		m_pipeLineState = std::make_unique<PipeLineState>(initParam.pipeLineStateContainerInitParam);
	}

	// デストラクタを非インライン化する
	GraphicsPipeLine::~GraphicsPipeLine() = default;

	size_t GraphicsPipeLine::createRootSignature(ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		return m_rootSignature->create(device, initParam);
	}

	void GraphicsPipeLine::eraseRootSignature(size_t handle)
	{
		m_rootSignature->erase(handle);
	}

	size_t GraphicsPipeLine::createPipeLineState(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		return m_pipeLineState->create(device, initParam, shaderFilePath, m_rootSignature->getPtr(initParam.rootSignatureHandle));
	}

	void GraphicsPipeLine::erasePipeLineState(size_t handle)
	{
		m_pipeLineState->erase(handle);
	}

	void GraphicsPipeLine::set(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_rootSignature->set(m_pipeLineState->getUseRootSignatureIndex(handle), commandList);
		m_pipeLineState->set(handle, commandList);
	}
}