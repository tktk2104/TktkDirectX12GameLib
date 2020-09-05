#include "TktkDX12Game/DXGameResource/Billboard/BillboardMaterial.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Billboard/BillboardTransformCbufferData.h"
#include "TktkDX12Game/DXGameResource/Billboard/BillboardMaterialCbufferData.h"

namespace tktk
{
	BillboardMaterial::BillboardMaterial(const ShaderFilePaths& shaderFilePaths, const tktkContainer::ResourceContainerInitParam& initParam)
		: m_billboardMaterialArray(initParam)
	{
		// ビルボード用のグラフィックパイプラインステートを作る
		createGraphicsPipeLineState(shaderFilePaths);

		// スプライト用の定数バッファを作る
		DX12GameManager::setSystemHandle(SystemCBufferType::BillboardTransform, DX12GameManager::createCBuffer(BillboardTransformCbufferData()));
		DX12GameManager::setSystemHandle(SystemCBufferType::BillboardMaterial, DX12GameManager::createCBuffer(BillboardMaterialCbufferData()));
	}

	unsigned int BillboardMaterial::create(const BillboardMaterialInitParam& initParam)
	{
		return m_billboardMaterialArray.create(initParam);
	}

	void BillboardMaterial::drawBillboard(unsigned int handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const
	{
		m_billboardMaterialArray.getMatchHandlePtr(handle)->drawBillboard(drawFuncArgs);
	}

	void BillboardMaterial::updateTransformCbuffer(unsigned int handle, unsigned int copyBufferHandle, const BillboardTransformCbufferUpdateFuncArgs& updateArgs) const
	{
		m_billboardMaterialArray.getMatchHandlePtr(handle)->updateTransformCbuffer(copyBufferHandle, updateArgs);
	}

	void BillboardMaterial::updateTransformCbufferUseClippingParam(unsigned int handle, unsigned int copyBufferHandle, const BillboardTransformCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const
	{
		m_billboardMaterialArray.getMatchHandlePtr(handle)->updateTransformCbufferUseClippingParam(copyBufferHandle, updateArgs, clippingParam);
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
		initParam.rasterizerDesc.DepthClipEnable = false;
		initParam.sampleMask = 0xffffffff;
		initParam.blendDesc.AlphaToCoverageEnable = false;
		initParam.blendDesc.IndependentBlendEnable = false;
		initParam.blendDesc.RenderTarget[0] = renderTargetBlendDesc;
		initParam.inputLayoutArray = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		initParam.renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };
		initParam.rootSignatureHandle = DX12GameManager::getSystemHandle(SystemRootSignatureType::Sprite); // ルートシグネチャはスプライトの物を使いまわす

		DX12GameManager::setSystemHandle(SystemPipeLineStateType::Billboard, DX12GameManager::createPipeLineState(initParam, shaderFilePaths));
	}
}