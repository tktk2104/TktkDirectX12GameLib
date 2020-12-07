#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/PostEffectMaterialManager.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/Structs/PostEffectMaterialManagerInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/PostEffectMaterialData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/Structs/DrawGameAreaCBufferData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/PostEffectMaterialAppendParam.h"

namespace tktk
{
	// ゲームの描画エリア描画用のポストエフェクトパイプラインを作る
	inline void createDrawGameAreaPipeLine(const std::string& vsFilePath, const std::string& psFilePath);

	// ゲームの描画エリア描画用のディスクリプタヒープを作る
	inline void createDrawGameAreaDescriptorHeap();


	PostEffectMaterialManager::PostEffectMaterialManager(const PostEffectMaterialManagerInitParam& initParam)
		: m_postEffectMaterialArray(initParam.containerParam)
	{
		// ゲームの描画エリア描画用のポストエフェクト定数バッファを作る
		DX12GameManager::setSystemHandle(SystemCBufferType::DrawGameArea, DX12GameManager::createCBuffer(DrawGameAreaCBufferData()));

		// ゲームの描画エリア描画用のポストエフェクトパイプラインを作る
		createDrawGameAreaPipeLine(initParam.drawGameAreaVSFilePath, initParam.drawGameAreaPSFilePath);

		// ゲームの描画エリア描画用のディスクリプタヒープを作る
		createDrawGameAreaDescriptorHeap();

		// モノクロのポストエフェクト用のルートシグネチャを作る
		{
			RootSignatureInitParam initParam{};
			initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

			initParam.rootParamArray.resize(1U);
			{/* テクスチャ用のルートパラメータ */
				initParam.rootParamArray.at(0).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
				initParam.rootParamArray.at(0).descriptorTable.resize(1U);
				{
					initParam.rootParamArray.at(0).descriptorTable.at(0).numDescriptors = 1;
					initParam.rootParamArray.at(0).descriptorTable.at(0).type			= D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
				}
			}

			initParam.samplerDescArray.resize(1U);
			{/* サンプラーの設定 */
				initParam.samplerDescArray.at(0).addressU			= D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				initParam.samplerDescArray.at(0).addressV			= D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				initParam.samplerDescArray.at(0).addressW			= D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				initParam.samplerDescArray.at(0).bordercolor		= D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
				initParam.samplerDescArray.at(0).filter				= D3D12_FILTER_MIN_MAG_MIP_LINEAR;
				initParam.samplerDescArray.at(0).maxLod				= D3D12_FLOAT32_MAX;
				initParam.samplerDescArray.at(0).minLod				= 0.0f;
				initParam.samplerDescArray.at(0).shaderVisibility	= D3D12_SHADER_VISIBILITY_PIXEL;
				initParam.samplerDescArray.at(0).comparisonFunc		= D3D12_COMPARISON_FUNC_NEVER;
			}
			DX12GameManager::setSystemHandle(SystemRootSignatureType::PostEffectMonochrome, DX12GameManager::createRootSignature(initParam));
		}

		// モノクロのポストエフェクト用のパイプラインステートを作る
		{
			D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
			renderTargetBlendDesc.BlendEnable			= false;
			renderTargetBlendDesc.LogicOpEnable			= false;
			renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			PipeLineStateInitParam pipelineInitParam{};
			pipelineInitParam.rasterizerDesc.MultisampleEnable	= false;
			pipelineInitParam.rasterizerDesc.CullMode			= D3D12_CULL_MODE_NONE;
			pipelineInitParam.rasterizerDesc.FillMode			= D3D12_FILL_MODE_SOLID;
			pipelineInitParam.rasterizerDesc.DepthClipEnable	= true;
			pipelineInitParam.blendDesc.AlphaToCoverageEnable	= false;
			pipelineInitParam.blendDesc.IndependentBlendEnable	= false;
			pipelineInitParam.blendDesc.RenderTarget[0]			= renderTargetBlendDesc;
			pipelineInitParam.inputLayoutArray = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
			};
			pipelineInitParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			pipelineInitParam.renderTargetFormatArray			= { DXGI_FORMAT_R8G8B8A8_UNORM };
			pipelineInitParam.rootSignatureHandle				= DX12GameManager::getSystemHandle(SystemRootSignatureType::PostEffectMonochrome);

			ShaderFilePaths filePaths{};
			filePaths.vsFilePath = initParam.postEffectVSFilePath;
			filePaths.psFilePath = initParam.monochromePSFilePath;

			DX12GameManager::setSystemHandle(SystemPipeLineStateType::PostEffectMonochrome, DX12GameManager::createPipeLineState(pipelineInitParam, filePaths));
		}
	}

	// デストラクタを非インライン化する
	PostEffectMaterialManager::~PostEffectMaterialManager() = default;

	size_t PostEffectMaterialManager::create(const PostEffectMaterialInitParam& initParam)
	{
		return m_postEffectMaterialArray.create(initParam);
	}

	void PostEffectMaterialManager::drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_postEffectMaterialArray.getMatchHandlePtr(handle)->drawPostEffect(drawFuncArgs);
	}

	void PostEffectMaterialManager::addPostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamInitParam& initParam)
	{
		m_postEffectMaterialArray.getMatchHandlePtr(handle)->addAppendParam(initParam);
	}

	void PostEffectMaterialManager::updatePostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamUpdateFuncArgs& updateFuncArgs)
	{
		m_postEffectMaterialArray.getMatchHandlePtr(handle)->updateAppendParam(updateFuncArgs);
	}

	// ゲームの描画エリア描画用のポストエフェクトパイプラインを作る
	void createDrawGameAreaPipeLine(const std::string& vsFilePath, const std::string& psFilePath)
	{
		RootSignatureInitParam rootSignatureInitParam{};
		rootSignatureInitParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		rootSignatureInitParam.rootParamArray.resize(2U);
		{/* 定数バッファ用のルートパラメータ */
			rootSignatureInitParam.rootParamArray.at(0U).shaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
			rootSignatureInitParam.rootParamArray.at(0U).descriptorTable.resize(1U);
			{
				rootSignatureInitParam.rootParamArray.at(0U).descriptorTable.at(0U).numDescriptors = 1;
				rootSignatureInitParam.rootParamArray.at(0U).descriptorTable.at(0U).type = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
			}
		}
		{/* テクスチャ用のルートパラメータ */
			rootSignatureInitParam.rootParamArray.at(1U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			rootSignatureInitParam.rootParamArray.at(1U).descriptorTable.resize(1U);
			{
				rootSignatureInitParam.rootParamArray.at(1U).descriptorTable.at(0U).numDescriptors = 1;
				rootSignatureInitParam.rootParamArray.at(1U).descriptorTable.at(0U).type = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			}
		}

		rootSignatureInitParam.samplerDescArray.resize(1U);
		{/* サンプラーの設定 */
			rootSignatureInitParam.samplerDescArray.at(0).addressU			= D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			rootSignatureInitParam.samplerDescArray.at(0).addressV			= D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			rootSignatureInitParam.samplerDescArray.at(0).addressW			= D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			rootSignatureInitParam.samplerDescArray.at(0).bordercolor		= D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
			rootSignatureInitParam.samplerDescArray.at(0).filter			= D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			rootSignatureInitParam.samplerDescArray.at(0).maxLod			= D3D12_FLOAT32_MAX;
			rootSignatureInitParam.samplerDescArray.at(0).minLod			= 0.0f;
			rootSignatureInitParam.samplerDescArray.at(0).shaderVisibility	= D3D12_SHADER_VISIBILITY_PIXEL;
			rootSignatureInitParam.samplerDescArray.at(0).comparisonFunc	= D3D12_COMPARISON_FUNC_NEVER;
		}
		DX12GameManager::setSystemHandle(SystemRootSignatureType::PostEffectDrawGameArea, DX12GameManager::createRootSignature(rootSignatureInitParam));

		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
		renderTargetBlendDesc.BlendEnable			= false;
		renderTargetBlendDesc.LogicOpEnable			= false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		PipeLineStateInitParam pipelineInitParam{};
		pipelineInitParam.rasterizerDesc.MultisampleEnable	= false;
		pipelineInitParam.rasterizerDesc.CullMode			= D3D12_CULL_MODE_NONE;
		pipelineInitParam.rasterizerDesc.FillMode			= D3D12_FILL_MODE_SOLID;
		pipelineInitParam.rasterizerDesc.DepthClipEnable	= true;
		pipelineInitParam.blendDesc.AlphaToCoverageEnable	= false;
		pipelineInitParam.blendDesc.IndependentBlendEnable	= false;
		pipelineInitParam.blendDesc.RenderTarget[0]			= renderTargetBlendDesc;
		pipelineInitParam.inputLayoutArray = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		pipelineInitParam.primitiveTopology			= D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		pipelineInitParam.renderTargetFormatArray	= { DXGI_FORMAT_R8G8B8A8_UNORM };
		pipelineInitParam.rootSignatureHandle		= DX12GameManager::getSystemHandle(SystemRootSignatureType::PostEffectDrawGameArea);

		ShaderFilePaths filePaths{};
		filePaths.vsFilePath = vsFilePath;
		filePaths.psFilePath = psFilePath;

		DX12GameManager::setSystemHandle(SystemPipeLineStateType::DrawGameArea, DX12GameManager::createPipeLineState(pipelineInitParam, filePaths));
	}

	void createDrawGameAreaDescriptorHeap()
	{
		// ディスクリプタヒープを作る
		BasicDescriptorHeapInitParam basicDescriptorHeapInitParam{};
		basicDescriptorHeapInitParam.shaderVisible = true;
		basicDescriptorHeapInitParam.descriptorTableParamArray.resize(2U);

		basicDescriptorHeapInitParam.descriptorTableParamArray.at(0U).type = BasicDescriptorType::constantBuffer;
		// 描画範囲描画定数バッファの１種類
		basicDescriptorHeapInitParam.descriptorTableParamArray.at(0U).descriptorParamArray = { { BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::DrawGameArea) } };

		basicDescriptorHeapInitParam.descriptorTableParamArray.at(1U).type = BasicDescriptorType::textureBuffer;
		// レンダーターゲットテクスチャの１種類
		basicDescriptorHeapInitParam.descriptorTableParamArray.at(1U).descriptorParamArray = { { BufferType::renderTarget, DX12GameManager::getSystemHandle(SystemRtBufferType::DrawGameArea) } };

		DX12GameManager::setSystemHandle(SystemBasicDescriptorHeapType::DrawGameArea, DX12GameManager::createBasicDescriptorHeap(basicDescriptorHeapInitParam));
	}
}