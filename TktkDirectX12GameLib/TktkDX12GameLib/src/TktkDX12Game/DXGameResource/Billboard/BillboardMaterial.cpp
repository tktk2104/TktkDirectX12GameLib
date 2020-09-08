#include "TktkDX12Game/DXGameResource/Billboard/BillboardMaterial.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Billboard/BillboardCbufferData.h"

namespace tktk
{
	BillboardMaterial::BillboardMaterial(const ShaderFilePaths& shaderFilePaths, const tktkContainer::ResourceContainerInitParam& initParam)
		: m_billboardMaterialArray(initParam)
	{
		// ビルボード用のルートシグネチャを作る
		createRootSignature();

		// ビルボード用のグラフィックパイプラインステートを作る
		createGraphicsPipeLineState(shaderFilePaths);

		// スプライト用の定数バッファを作る
		DX12GameManager::setSystemHandle(SystemCBufferType::Billboard, DX12GameManager::createCBuffer(BillboardCbufferData()));
	}

	unsigned int BillboardMaterial::create(const BillboardMaterialInitParam& initParam)
	{
		return m_billboardMaterialArray.create(initParam);
	}

	void BillboardMaterial::drawBillboard(unsigned int handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const
	{
		m_billboardMaterialArray.getMatchHandlePtr(handle)->drawBillboard(drawFuncArgs);
	}

	void BillboardMaterial::updateTransformCbuffer(unsigned int handle, unsigned int copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs) const
	{
		m_billboardMaterialArray.getMatchHandlePtr(handle)->updateTransformCbuffer(copyBufferHandle, updateArgs);
	}

	void BillboardMaterial::updateTransformCbufferUseClippingParam(unsigned int handle, unsigned int copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const
	{
		m_billboardMaterialArray.getMatchHandlePtr(handle)->updateTransformCbufferUseClippingParam(copyBufferHandle, updateArgs, clippingParam);
	}

	void BillboardMaterial::createRootSignature() const
	{
		RootSignatureInitParam initParam{};
		initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		initParam.rootParamArray.resize(2U);
		{/* テクスチャ用のルートパラメータ */
			initParam.rootParamArray.at(0U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			initParam.rootParamArray.at(0U).descriptorTable = {
				{ 1U, D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 0U }
			};
		}
		{/* 定数バッファ用のルートパラメータ */
			initParam.rootParamArray.at(1U).shaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			initParam.rootParamArray.at(1U).descriptorTable = {
				{ 2U, D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 0U }
			};
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
		DX12GameManager::setSystemHandle(SystemRootSignatureType::Billboard, DX12GameManager::createRootSignature(initParam));
	}

	void BillboardMaterial::createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const
	{
		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
		renderTargetBlendDesc.BlendEnable = true;
		renderTargetBlendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		renderTargetBlendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
		renderTargetBlendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		renderTargetBlendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		renderTargetBlendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
		renderTargetBlendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		renderTargetBlendDesc.LogicOpEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		PipeLineStateInitParam initParam{};
		initParam.rasterizerDesc.MultisampleEnable = false;
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rasterizerDesc.DepthClipEnable = true;
		initParam.sampleMask = 0xffffffff;
		initParam.blendDesc.AlphaToCoverageEnable = false;
		initParam.blendDesc.IndependentBlendEnable = false;
		initParam.blendDesc.RenderTarget[0] = renderTargetBlendDesc;
		initParam.inputLayoutArray = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		initParam.renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };
		initParam.useDepth = true;
		initParam.writeDepth = true;
		initParam.depthFunc = D3D12_COMPARISON_FUNC_LESS;
		initParam.rootSignatureHandle = DX12GameManager::getSystemHandle(SystemRootSignatureType::Billboard);

		DX12GameManager::setSystemHandle(SystemPipeLineStateType::Billboard, DX12GameManager::createPipeLineState(initParam, shaderFilePaths));
	}
}