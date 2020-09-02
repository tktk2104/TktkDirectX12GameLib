#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Mesh/BasicMesh.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BasicMesh::BasicMesh(const std::string& writeShadowMapVsFilePath, const tktkContainer::ResourceContainerInitParam& initParam)
		: m_basicMeshArray(initParam)
	{
		createWriteShadowMapRootSignature();
		createWriteShadowMapGraphicsPipeLineState(writeShadowMapVsFilePath);
	
		// 通常メッシュ版シャドウマップ描画用のディスクリプタヒープを作る
		{
			BasicDescriptorHeapInitParam initParam{};
			initParam.shaderVisible = true;
			initParam.descriptorTableParamArray.resize(1U);

			{ /* コンスタントバッファービューのディスクリプタの情報 */
				auto& cbufferViewDescriptorParam = initParam.descriptorTableParamArray.at(0U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// 
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform)	},
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::BoneMatCbuffer)	}
				};
			}

			DX12GameManager::setSystemHandle(SystemBasicDescriptorHeapType::BasicMeshShadowMap, DX12GameManager::createBasicDescriptorHeap(initParam));
		}
	}

	unsigned int BasicMesh::craete(const BasicMeshInitParam& initParam)
	{
		return m_basicMeshArray.create(initParam);
	}

	unsigned int BasicMesh::copy(unsigned int originalHandle)
	{
		return m_basicMeshArray.create(*m_basicMeshArray.getMatchHandlePtr(originalHandle));
	}

	void BasicMesh::setMaterialHandle(unsigned int meshHandle, unsigned int materialSlot, unsigned int materialHandle)
	{
		m_basicMeshArray.getMatchHandlePtr(meshHandle)->setMaterialHandle(materialSlot, materialHandle);
	}

	void BasicMesh::writeShadowMap(unsigned int handle) const
	{
		// シャドウマップへの書き込みを行う
		m_basicMeshArray.getMatchHandlePtr(handle)->writeShadowMap();
	}

	void BasicMesh::drawMesh(unsigned int handle, const MeshDrawFuncBaseArgs& baseArgs) const
	{
		// メッシュのライティングに使用するライト情報を定数バッファに書き込む
		DX12GameManager::updateLightCBuffer(baseArgs.lightHandle);

		// メッシュの描画を行う
		m_basicMeshArray.getMatchHandlePtr(handle)->drawMesh(baseArgs);
	}

	void BasicMesh::createWriteShadowMapRootSignature() const
	{
		RootSignatureInitParam initParam{};
		initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		initParam.rootParamArray.resize(1U);
		{/* 定数バッファ用のルートパラメータ */
			initParam.rootParamArray.at(0).shaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
			initParam.rootParamArray.at(0).descriptorTable = {
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
		DX12GameManager::setSystemHandle(SystemRootSignatureType::ShadowMap, DX12GameManager::createRootSignature(initParam));
	}

	void BasicMesh::createWriteShadowMapGraphicsPipeLineState(const std::string& writeShadowMapVsFilePath) const
	{
		PipeLineStateInitParam initParam{};
		initParam.rasterizerDesc.MultisampleEnable = false;
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rasterizerDesc.DepthClipEnable = true;
		initParam.blendDesc.AlphaToCoverageEnable = false;
		initParam.blendDesc.IndependentBlendEnable = false;
		initParam.inputLayoutArray = {
			{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "BLENDINDICES",	0, DXGI_FORMAT_R8G8B8A8_SINT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "BINORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		initParam.useDepth = true;
		initParam.writeDepth = true;
		initParam.depthFunc = D3D12_COMPARISON_FUNC_LESS;
		initParam.rootSignatureHandle = DX12GameManager::getSystemHandle(SystemRootSignatureType::ShadowMap);

		ShaderFilePaths shaderFilePaths{};
		shaderFilePaths.vsFilePath = writeShadowMapVsFilePath;
		shaderFilePaths.psFilePath = "";

		DX12GameManager::setSystemHandle(SystemPipeLineStateType::ShadowMap, DX12GameManager::createPipeLineState(initParam, shaderFilePaths));
	}
}