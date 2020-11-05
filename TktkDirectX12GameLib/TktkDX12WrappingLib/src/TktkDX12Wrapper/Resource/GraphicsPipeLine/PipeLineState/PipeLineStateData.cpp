#include "TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateData.h"

namespace tktk
{
	PipeLineStateData::PipeLineStateData(
		ID3D12Device* device,
		const PipeLineStateInitParam& initParam,
		const std::vector<char>& vsByteArray,
		const std::vector<char>& psByteArray,
		ID3D12RootSignature* rootSignaturePtr
	)
	{
		m_rootSignatureHandle = initParam.rootSignatureHandle;


		D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipeLineStateDesc{};
		graphicsPipeLineStateDesc.pRootSignature					= rootSignaturePtr;
		graphicsPipeLineStateDesc.VS.pShaderBytecode				= (vsByteArray.size() == 0LU) ? nullptr : vsByteArray.data();
		graphicsPipeLineStateDesc.VS.BytecodeLength					= vsByteArray.size();
		graphicsPipeLineStateDesc.PS.pShaderBytecode				= (psByteArray.size() == 0LU) ? nullptr : psByteArray.data();
		graphicsPipeLineStateDesc.PS.BytecodeLength					= psByteArray.size();
		graphicsPipeLineStateDesc.SampleMask						= initParam.sampleMask;
		graphicsPipeLineStateDesc.RasterizerState					= initParam.rasterizerDesc;
		graphicsPipeLineStateDesc.BlendState						= initParam.blendDesc;
		graphicsPipeLineStateDesc.InputLayout.pInputElementDescs	= initParam.inputLayoutArray.data();
		graphicsPipeLineStateDesc.IBStripCutValue					= D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		graphicsPipeLineStateDesc.PrimitiveTopologyType				= initParam.primitiveTopology;

#ifdef _M_AMD64 /* x64ƒrƒ‹ƒh‚È‚ç */
		graphicsPipeLineStateDesc.InputLayout.NumElements			= static_cast<unsigned int>(initParam.inputLayoutArray.size());
		graphicsPipeLineStateDesc.NumRenderTargets					= static_cast<unsigned int>(initParam.renderTargetFormatArray.size());
#else
		graphicsPipeLineStateDesc.InputLayout.NumElements			= initParam.inputLayoutArray.size();
		graphicsPipeLineStateDesc.NumRenderTargets					= initParam.renderTargetFormatArray.size();
#endif // WIN64

		if (graphicsPipeLineStateDesc.NumRenderTargets == 0U)
		{
			graphicsPipeLineStateDesc.RTVFormats[0] = DXGI_FORMAT_UNKNOWN;
		}
		else
		{
			for (unsigned int i = 0; i < graphicsPipeLineStateDesc.NumRenderTargets; i++)
			{
				graphicsPipeLineStateDesc.RTVFormats[i] = initParam.renderTargetFormatArray.at(i);
			}
		}
		graphicsPipeLineStateDesc.SampleDesc.Count = 1;
		graphicsPipeLineStateDesc.SampleDesc.Quality = 0;

		graphicsPipeLineStateDesc.DepthStencilState.DepthEnable = initParam.useDepth;

		if (initParam.useDepth)
		{
			graphicsPipeLineStateDesc.DepthStencilState.DepthWriteMask = (initParam.writeDepth) ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO;
			graphicsPipeLineStateDesc.DepthStencilState.DepthFunc = initParam.depthFunc;
			graphicsPipeLineStateDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		}

		device->CreateGraphicsPipelineState(&graphicsPipeLineStateDesc, IID_PPV_ARGS(&m_pipeLineState));
	}

	PipeLineStateData::~PipeLineStateData()
	{
		if (m_pipeLineState != nullptr)
		{
			m_pipeLineState->Release();
		}
	}

	PipeLineStateData::PipeLineStateData(PipeLineStateData&& other) noexcept
		: m_rootSignatureHandle(other.m_rootSignatureHandle)
		, m_pipeLineState(other.m_pipeLineState)
	{
		m_pipeLineState = nullptr;
	}

	size_t PipeLineStateData::getUseRootSignatureHandle() const
	{
		return m_rootSignatureHandle;
	}

	void PipeLineStateData::set(ID3D12GraphicsCommandList* commandList) const
	{
		commandList->SetPipelineState(m_pipeLineState);
	}
}