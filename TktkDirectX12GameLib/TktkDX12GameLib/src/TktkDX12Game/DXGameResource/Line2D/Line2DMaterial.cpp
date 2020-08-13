#include "TktkDX12Game/DXGameResource/Line2D/Line2DMaterial.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Line2D/Line2DConstantBufferData.h"

namespace tktk
{
	Line2DMaterial::Line2DMaterial(const ShaderFilePaths& shaderFilePaths, unsigned int line2DMaterialNum)
		: m_line2DMaterialArray(line2DMaterialNum)
	{
		// 2Dライン描画用のルートシグネチャを作る
		createRootSignature();

		// 2Dライン用のグラフィックパイプラインステートを作る
		createGraphicsPipeLineState(shaderFilePaths);

		// ライン用の定数バッファを作る
		DX12GameManager::createCBuffer(DX12GameManager::getSystemId(SystemCBufferType::Line2D), Line2DConstantBufferData());

		// 2Dライン用のディスクリプタヒープを作る
		createBasicDescriptorHeap();
	}

	void Line2DMaterial::create(unsigned int id, const Line2DMaterialDataInitParam& initParam)
	{
		m_line2DMaterialArray.emplaceAt(id, initParam);
	}

	void Line2DMaterial::drawLine(unsigned int id, const Line2DMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_line2DMaterialArray.at(id)->drawLine(drawFuncArgs);
	}

	void Line2DMaterial::createBasicDescriptorHeap() const
	{
		// ディスクリプタヒープを作る
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(1U);

		{ /* コンスタントバッファービューのディスクリプタの情報 */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// ２Ｄライン定数バッファの１種類
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemCBufferType::Line2D) }
			};
		}

		DX12GameManager::createBasicDescriptorHeap(DX12GameManager::getSystemId(SystemBasicDescriptorHeapType::Line2D), descriptorHeapInitParam);
	}

	// ２Ｄライン描画用のルートシグネチャを作る
	void Line2DMaterial::createRootSignature() const
	{
		RootSignatureInitParam initParam{};
		initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		initParam.rootParamArray.resize(1U);
		{/* 定数バッファ用のルートパラメータ */
			initParam.rootParamArray.at(0).shaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			initParam.rootParamArray.at(0).descriptorTable.resize(1U);
			{
				initParam.rootParamArray.at(0).descriptorTable.at(0).numDescriptors = 1U;
				initParam.rootParamArray.at(0).descriptorTable.at(0).type = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
			}
		}
		initParam.samplerDescArray.resize(1U);
		{/* サンプラーの設定 */
			initParam.samplerDescArray.at(0).addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.samplerDescArray.at(0).addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.samplerDescArray.at(0).addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.samplerDescArray.at(0).bordercolor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
			initParam.samplerDescArray.at(0).filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			initParam.samplerDescArray.at(0).maxLod = D3D12_FLOAT32_MAX;
			initParam.samplerDescArray.at(0).minLod = 0.0f;
			initParam.samplerDescArray.at(0).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			initParam.samplerDescArray.at(0).comparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		}
		DX12GameManager::createRootSignature(DX12GameManager::getSystemId(SystemRootSignatureType::Line2D), initParam);
	}

	// ２Ｄライン描画用のパイプラインステートを作る
	void Line2DMaterial::createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const
	{
		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
		renderTargetBlendDesc.BlendEnable		= true;
		renderTargetBlendDesc.SrcBlend			= D3D12_BLEND_SRC_ALPHA;
		renderTargetBlendDesc.DestBlend			= D3D12_BLEND_INV_SRC_ALPHA;
		renderTargetBlendDesc.BlendOp			= D3D12_BLEND_OP_ADD;
		renderTargetBlendDesc.SrcBlendAlpha		= D3D12_BLEND_ONE;
		renderTargetBlendDesc.DestBlendAlpha	= D3D12_BLEND_ZERO;
		renderTargetBlendDesc.BlendOpAlpha		= D3D12_BLEND_OP_ADD;
		renderTargetBlendDesc.LogicOpEnable		= false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		PipeLineStateInitParam initParam{};
		initParam.rasterizerDesc.MultisampleEnable = false;
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rasterizerDesc.DepthClipEnable = false;
		initParam.sampleMask = 0xffffffff;
		initParam.blendDesc.AlphaToCoverageEnable = false;
		initParam.blendDesc.IndependentBlendEnable = true;
		initParam.blendDesc.RenderTarget[0] = renderTargetBlendDesc;
		initParam.inputLayoutArray = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
		initParam.renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };
		initParam.rootSignatureId = DX12GameManager::getSystemId(SystemRootSignatureType::Line2D);

		DX12GameManager::createPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::Line2D), initParam, shaderFilePaths);
	}
}