#include "LoadingScene.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "../GameObject/Cursor/CursorScript.h"
#include "../Enum/_ResourceIds/ResourceIds.h"
#include "../TutorialCode/GameObject/ElementShape/VertexColor2DPolygonConstantBufferData.h"

void LoadingScene::start()
{
	// テクスチャを読み込む
	{
		tktk::DX12GameManager::gpuPriorityLoadTextureBuffer(toInt(TextureBufferId::Test), "res/test.png");
		tktk::DX12GameManager::executeCommandList();
	}

	// スプライトのマテリアルを作る
	{
		tktk::SpriteMaterialInitParam initParam{};
		initParam.createDescriptorHeapId	= toInt(BasicDescriptorHeapId::TestTexture);
		initParam.srvBufferType				= tktk::BufferType::texture;
		initParam.useBufferId				= toInt(TextureBufferId::Test);
		/*initParam.srvBufferType = tktk::BufferType::depthStencil;
		initParam.useBufferId = tktk::DX12GameManager::getSystemId(tktk::SystemDsBufferType::ShadowMap);*/

		tktk::DX12GameManager::createSpriteMaterial(toInt(SpriteMaterialId::Test), initParam);
	}

	// メッシュをロードする
	{
		tktk::BasicMeshLoadPmdArgs loadArgs{};
		loadArgs.filePath = "res/Model/初音ミク.pmd";
		loadArgs.createDescriptorHeapIdStartNum		= toInt(BasicDescriptorHeapId::MikuMatStart);
		loadArgs.createVertexBufferId				= toInt(VertexBufferId::Miku);
		loadArgs.createIndexBufferId				= toInt(IndexBufferId::Miku);
		loadArgs.createBasicMeshId					= toInt(BasicMeshId::Miku);
		loadArgs.createSkeletonId					= toInt(SkeletonId::Miku);
		loadArgs.createBasicMeshMaterialIdStartNum	= toInt(BasicMeshMaterialId::MikuMatStart);;
		loadArgs.createTextureIdStartNum			= toInt(TextureBufferId::MikuTexStart);

		auto result = tktk::DX12GameManager::loadPmd(loadArgs);

		if (result.createDescriptorHeapIdEndNum		!= toInt(BasicDescriptorHeapId::MikuMatEnd)	||
			result.createBasicMeshMaterialIdEndNum	!= toInt(BasicMeshMaterialId::MikuMatEnd)	||
			result.createTextureIdEndNum			!= toInt(TextureBufferId::MikuTexEnd)				)
		{
			//throw std::runtime_error("load Pmd error");
		}
	}

	// モーションをロードする
	{
		tktk::DX12GameManager::loadMotion(toInt(MotionId::motion1), "res/Motion/pose.vmd");
		tktk::DX12GameManager::loadMotion(toInt(MotionId::motion2), "res/Motion/motion.vmd");
	}

	// レンダーターゲットバッファを作る
	{
		tktk::DX12GameManager::createRtBuffer(toInt(RenderTargetBufferId::PostEffectTest), tktk::DX12GameManager::getWindowSize(), tktkMath::Color_v::red);
	}

	// レンダーターゲットビューを作る
	{
		tktk::RtvDescriptorHeapInitParam initParam{};
		initParam.shaderVisible = false;
		initParam.descriptorParamArray.resize(1U);
		initParam.descriptorParamArray.at(0U).type	= tktk::RtvDescriptorType::normal;
		initParam.descriptorParamArray.at(0U).id	= toInt(RenderTargetBufferId::PostEffectTest);

		tktk::DX12GameManager::createRtvDescriptorHeap(toInt(RtvDescriptorHeapId::PostEffectTest), initParam);
	}

	// モノクロのポストエフェクト用のディスクリプタヒープを作る
	{
		// ディスクリプタヒープを作る
		tktk::BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(1U);

		{ /* シェーダーリソースビューのディスクリプタの情報 */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = tktk::BasicDescriptorType::textureBuffer;

			// レンダーターゲットテクスチャの１種類
			srvDescriptorParam.descriptorParamArray = {
				{ tktk::BufferType::renderTarget,		toInt(RenderTargetBufferId::PostEffectTest) }
			};
		}

		tktk::DX12GameManager::createBasicDescriptorHeap(toInt(BasicDescriptorHeapId::PostEffectTest), descriptorHeapInitParam);
	}

	// モノクロのポストエフェクトを作る
	{
		tktk::PostEffectMaterialInitParam initParam{};
		initParam.usePipeLineStateId = tktk::DX12GameManager::getSystemId(tktk::SystemPipeLineStateType::PostEffectMonochrome);
		initParam.useDescriptorHeapId = toInt(BasicDescriptorHeapId::PostEffectTest);

		tktk::DX12GameManager::createPostEffectMaterial(toInt(PostEffectMaterialId::PostEffectTest), initParam);
	}

	// サウンドをロードする
	{
		tktk::DX12GameManager::loadSound(toInt(SoundId::TestSe), "res/Sound/damage.wav");
		tktk::DX12GameManager::loadSound(toInt(SoundId::TestBgm), "res/Sound/kendo.wav");
	}

	// カメラを作る
	{
		// 通常カメラ
		tktk::DX12GameManager::createCamera(toInt(CameraId::Basic));

		// シャドウマップカメラ
		tktk::DX12GameManager::createCamera(toInt(CameraId::ShadowMap));
	}

	// ライトを作る
	{
		// 通常ライト
		tktk::DX12GameManager::createLight(
			toInt(LightId::Basic),
			{ 0.3f, 1.0f },
			{ 0.3f, 1.0f },
			{ 0.3f, 1.0f },
			{ 0.0f }
		);
	}

	// 頂点カラーシェーダー用の定数バッファを作る
	tktk::DX12GameManager::createCBuffer(toInt(CbufferId::VertexColorPolygon), VertexColor2DPolygonConstantBufferData());

	// 頂点カラーシェーダー用のディスクリプタヒープを作る
	{
		// ディスクリプタヒープを作る
		tktk::BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(1U);

		{ /* コンスタントバッファービューのディスクリプタの情報 */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			cbufferViewDescriptorParam.type = tktk::BasicDescriptorType::constantBuffer;

			// 頂点カラー定数バッファの１種類
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ tktk::BufferType::constant,		toInt(CbufferId::VertexColorPolygon) }
			};
		}

		tktk::DX12GameManager::createBasicDescriptorHeap(toInt(BasicDescriptorHeapId::VertexColorPolygon), descriptorHeapInitParam);
	}

	// 頂点カラーシェーダー用のルートシグネチャを作る
	{
		tktk::RootSignatureInitParam initParam{};
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
		initParam.samplerDescArray.resize(0U);
		//{/* サンプラーの設定 */
		//	initParam.samplerDescArray.at(0).addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		//	initParam.samplerDescArray.at(0).addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		//	initParam.samplerDescArray.at(0).addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		//	initParam.samplerDescArray.at(0).bordercolor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
		//	initParam.samplerDescArray.at(0).filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		//	initParam.samplerDescArray.at(0).maxLod = D3D12_FLOAT32_MAX;
		//	initParam.samplerDescArray.at(0).minLod = 0.0f;
		//	initParam.samplerDescArray.at(0).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		//	initParam.samplerDescArray.at(0).comparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		//}
		tktk::DX12GameManager::createRootSignature(toInt(RootSignatureId::VertexColorPolygon), initParam);
	}

	// 頂点カラーシェーダー用のパイプラインステートを作る
	{
		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
		renderTargetBlendDesc.BlendEnable			= true;
		renderTargetBlendDesc.SrcBlend				= D3D12_BLEND_SRC_ALPHA;
		renderTargetBlendDesc.DestBlend				= D3D12_BLEND_INV_SRC_ALPHA;
		renderTargetBlendDesc.BlendOp				= D3D12_BLEND_OP_ADD;
		renderTargetBlendDesc.SrcBlendAlpha			= D3D12_BLEND_ONE;
		renderTargetBlendDesc.DestBlendAlpha		= D3D12_BLEND_ZERO;
		renderTargetBlendDesc.BlendOpAlpha			= D3D12_BLEND_OP_ADD;
		renderTargetBlendDesc.LogicOpEnable			= false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		tktk::PipeLineStateInitParam initParam{};
		initParam.rasterizerDesc.MultisampleEnable = false;
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rasterizerDesc.DepthClipEnable = false;
		initParam.sampleMask = 0xffffffff;
		initParam.blendDesc.AlphaToCoverageEnable = false;
		initParam.blendDesc.IndependentBlendEnable = true;
		initParam.blendDesc.RenderTarget[0] = renderTargetBlendDesc;
		initParam.inputLayoutArray = {
			{ "POSITION",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};
		initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		initParam.renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };
		initParam.rootSignatureId = toInt(RootSignatureId::VertexColorPolygon);

		tktk::ShaderFilePaths shaderFilePaths{};
		shaderFilePaths.vsFilePath = "res/Shader/VertexColor2DPolygonVertexShader.cso";
		shaderFilePaths.psFilePath = "res/Shader/VertexColor2DPolygonPixelShader.cso";

		tktk::DX12GameManager::createPipeLineState(toInt(PipeLineStateId::VertexColorPolygon), initParam, shaderFilePaths);
	}

	// 2Dラインマテリアルを作る
	{
		tktk::Line2DMaterialDataInitParam initParam;
		initParam.createVertexBufferId = toInt(VertexBufferId::ElementShapeGuide);
		tktk::DX12GameManager::createLine(toInt(Line2DMaterialId::ElementShapeGuide), initParam);

		initParam.createVertexBufferId = toInt(VertexBufferId::CollideDebug1);
		tktk::DX12GameManager::createLine(toInt(Line2DMaterialId::CollideDebug1), initParam);

		initParam.createVertexBufferId = toInt(VertexBufferId::CollideDebug2);
		tktk::DX12GameManager::createLine(toInt(Line2DMaterialId::CollideDebug2), initParam);
	}

	//// 球体メッシュマテリアルをコピーする
	//for (unsigned int i = toInt(BasicMeshMaterialId::ElementSphereStart); i <= toInt(BasicMeshMaterialId::ElementSphereEnd); i++)
	//{
	//	tktk::DX12GameManager::copyBasicMeshMaterial(i, tktk::DX12GameManager::getSystemId(tktk::SystemBasicMeshMaterialType::Sphere));
	//}

	//// 球体メッシュをコピーする
	//for (unsigned int i = toInt(BasicMeshId::ElementSphereStart); i <= toInt(BasicMeshId::ElementSphereEnd); i++)
	//{
	//	tktk::DX12GameManager::copyBasicMesh(i, tktk::DX12GameManager::getSystemId(tktk::SystemBasicMeshType::Sphere));
	//}

	tktk::DX12GameManager::addUpdatePriority<CursorScript>(-10.0f);

	// 読み込みシーンを無効にする
	tktk::DX12GameManager::disableScene(toInt(SceneId::Loading));

	// メインシーンを有効にする
	tktk::DX12GameManager::enableScene(toInt(SceneId::Main));
}
