#include "TktkDX12Wrapper/Resource/GraphicsPipeLine/RootSignature/RootSignatureData.h"

namespace tktk
{
	RootSignatureData::RootSignatureData(ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		// ルートパラメーターの数だけメモリを確保する
		std::vector<D3D12_ROOT_PARAMETER> rootParamArray;
		rootParamArray.reserve(initParam.rootParamArray.size());

		// ディスクリプターレンジの値を代入する配列をルートパラメーターの数だけ確保する
		std::vector<std::vector<D3D12_DESCRIPTOR_RANGE>> descriptorTableArray;
		descriptorTableArray.resize(initParam.rootParamArray.size());

		// ルートパラメーターの数だけループする
		for (unsigned int i = 0; i < initParam.rootParamArray.size(); i++)
		{
			// ※補助変数
			const auto& rootParamInitParam	= initParam.rootParamArray.at(i);
			auto&		descriptorTable		= descriptorTableArray.at(i);

			// このルートパラメーターが持っているディスクリプタレンジの数だけメモリを確保する
			descriptorTable.reserve(rootParamInitParam.descriptorTable.size());

			// ディスクリプタレンジの数だけループする
			for (unsigned int j = 0; j < rootParamInitParam.descriptorTable.size(); j++)
			{
				// ※補助変数
				const auto& descriptorRangeInitParam = rootParamInitParam.descriptorTable.at(j);

				// ディスクリプタレンジの設定をする
				D3D12_DESCRIPTOR_RANGE descriptorRange{};
				descriptorRange.NumDescriptors						= descriptorRangeInitParam.numDescriptors;
				descriptorRange.RangeType							= descriptorRangeInitParam.type;
				descriptorRange.BaseShaderRegister					= descriptorRangeInitParam.startRegisterNum + j;
				descriptorRange.OffsetInDescriptorsFromTableStart	= D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

				descriptorTable.push_back(descriptorRange);
			}

			// ルートパラメータの設定をする
			D3D12_ROOT_PARAMETER rootParam{};
			rootParam.ShaderVisibility						= rootParamInitParam.shaderVisibility;
			rootParam.ParameterType							= D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParam.DescriptorTable.pDescriptorRanges		= descriptorTable.data();
			rootParam.DescriptorTable.NumDescriptorRanges	= descriptorTable.size();

			rootParamArray.push_back(rootParam);
		}

		// サンプラーデスクの数だけメモリを確保する
		std::vector<D3D12_STATIC_SAMPLER_DESC> samplerDescArray;
		samplerDescArray.reserve(initParam.samplerDescArray.size());

		// サンプラーデスクの数だけループする
		for (const auto& node : initParam.samplerDescArray)
		{
			// サンプラーデスクの設定をする
			D3D12_STATIC_SAMPLER_DESC samplerDesc{};
			samplerDesc.AddressU			= node.addressU;
			samplerDesc.AddressV			= node.addressV;
			samplerDesc.AddressW			= node.addressW;
			samplerDesc.BorderColor			= node.bordercolor;
			samplerDesc.Filter				= node.filter;
			samplerDesc.MaxLOD				= node.maxLod;
			samplerDesc.MinLOD				= node.minLod;
			samplerDesc.ShaderVisibility	= node.shaderVisibility;
			samplerDesc.ComparisonFunc		= node.comparisonFunc;
			samplerDesc.ShaderRegister		= node.shaderRegister;

			samplerDescArray.push_back(samplerDesc);
		}

		// ルートシグネチャの設定をする
		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
		rootSignatureDesc.Flags				= initParam.flag;
		rootSignatureDesc.pParameters		= rootParamArray.data();
		rootSignatureDesc.NumParameters		= rootParamArray.size();
		rootSignatureDesc.pStaticSamplers	= samplerDescArray.data();
		rootSignatureDesc.NumStaticSamplers = samplerDescArray.size();

		// ルートシグネチャを作る
		ID3DBlob* rootSigBlob{ nullptr };
		ID3DBlob* errorBlob{ nullptr };
		D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
		device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature));
		rootSigBlob->Release();
	}

	RootSignatureData::~RootSignatureData()
	{
		if (m_rootSignature != nullptr)
		{
			m_rootSignature->Release();
		}
	}

	RootSignatureData::RootSignatureData(RootSignatureData&& other) noexcept
		: m_rootSignature(other.m_rootSignature)
	{
		other.m_rootSignature = nullptr;
	}

	ID3D12RootSignature* RootSignatureData::getPtr() const
	{
		return m_rootSignature;
	}

	void RootSignatureData::set(ID3D12GraphicsCommandList* commandList) const
	{
		commandList->SetGraphicsRootSignature(m_rootSignature);
	}
}