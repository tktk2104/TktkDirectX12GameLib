#include "TktkDX12Game/_MainManager/DX12GameManager.h"

/* InitParams */
#include <TktkDX12Wrapper/_BaseObjects/DX3DBaseObjectsInitParam.h>
#include "TktkDX12Game/DXGameResource/DXGameResourceInitParam.h"

#include <TktkMath/Random.h>
#include "TktkDX12Game/GraphicManager/GraphicManager.h"
#include "TktkDX12Game/DXGameResource/DXGameResource.h"
#include "TktkDX12Game/UtilityProcessManager/UtilityProcessManager.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/DefaultComponents/StateMachine/StateMachine.h"
#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawFuncRunner.h"
#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawer.h"
#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawFuncRunner.h"
#include "TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawer.h"
#include "TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawFuncRunner.h"
#include "TktkDX12BaseComponents/3D/ShadowMapWriter/WriteMeshShadowMapFuncRunner.h"

#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/Structs/DrawGameAreaCBufferData.h"

namespace tktk
{
	bool												DX12GameManager::m_isGameExit{ false };
	GameObjectPtr										DX12GameManager::m_postEffectObject;
	std::unique_ptr<GraphicManager>						DX12GameManager::m_graphicManager;
	std::unique_ptr<DXGameResource>						DX12GameManager::m_dxGameResource;
	std::unique_ptr<UtilityProcessManager>				DX12GameManager::m_utilityProcessManager;

	void DX12GameManager::initialize(const DX12GameManagerInitParam& gameManagerInitParam)
	{
		// 乱数の初期化
		tktkMath::Random::randomize();

		// DirectX12の処理などを行うクラスを作る
		DX3DBaseObjectsInitParam dX3DBaseObjectsParam{};
		dX3DBaseObjectsParam.resourceNum		= gameManagerInitParam.dx3dResNum;
		dX3DBaseObjectsParam.windowSize			= gameManagerInitParam.windowParam.windowSize;
		dX3DBaseObjectsParam.createDebugLayer	= gameManagerInitParam.createDebugLayer;
		m_graphicManager = std::make_unique<GraphicManager>(gameManagerInitParam.windowParam, dX3DBaseObjectsParam);

		// 入力、音再生機能などの初期化を行う
		m_utilityProcessManager = std::make_unique<UtilityProcessManager>(gameManagerInitParam.windowParam.hInstance, m_graphicManager->getHWND(), 0.1f);

		// バックバッファのハンドルを取得する
		auto backBufferRtBufferHandle = m_graphicManager->createBackBufferRtBuffer();
		setSystemHandle(SystemRtBufferType::BackBuffer_1, backBufferRtBufferHandle.at(0U));
		setSystemHandle(SystemRtBufferType::BackBuffer_2, backBufferRtBufferHandle.at(1U));

		// バックバッファのディスクリプタヒープを作る
		setSystemHandle(SystemRtvDescriptorHeapType::BackBuffer, m_graphicManager->createBackBufferRtvDescriptorHeap(backBufferRtBufferHandle));

		// ゲームの描画エリア用のレンダーターゲットディスクリプタヒープを作る
		{
			size_t createdRtBufferHandle = m_graphicManager->createRtBuffer(m_graphicManager->getDrawGameAreaSize(), tktkMath::Color_v::black);
			setSystemHandle(SystemRtBufferType::DrawGameArea, createdRtBufferHandle);

			RtvDescriptorHeapInitParam initParam{};
			initParam.descriptorParamArray	= { { RtvDescriptorType::normal, createdRtBufferHandle } };
			setSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea, m_graphicManager->createRtvDescriptorHeap(initParam));
		}

		// ポストエフェクト描画用のレンダーターゲットディスクリプタヒープを作る
		{
			size_t createdRtBufferHandle = m_graphicManager->createRtBuffer(m_graphicManager->getDrawGameAreaSize(), tktkMath::Color_v::black);
			setSystemHandle(SystemRtBufferType::PostEffectTarget, createdRtBufferHandle);

			RtvDescriptorHeapInitParam initParam{};
			initParam.descriptorParamArray	= { { RtvDescriptorType::normal, createdRtBufferHandle } };
			setSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget, m_graphicManager->createRtvDescriptorHeap(initParam));
		}
		
		// デフォルトのビューポートを作る
		setSystemHandle(SystemViewportType::Basic, createViewport({ { m_graphicManager->getDrawGameAreaSize(), tktkMath::Vector2_v::zero, 1.0f, 0.0f } }));

		// デフォルトのシザー矩形を作る
		setSystemHandle(SystemScissorRectType::Basic, createScissorRect({ { tktkMath::Vector2_v::zero, m_graphicManager->getDrawGameAreaSize() } }));

		// シャドウマップのビューポートを作る
		setSystemHandle(SystemViewportType::WriteShadow, createViewport({ { { 2048.0f, 2048.0f }, tktkMath::Vector2_v::zero, 1.0f, 0.0f } }));

		// シャドウマップのシザー矩形を作る
		setSystemHandle(SystemScissorRectType::WriteShadow, createScissorRect({ { tktkMath::Vector2_v::zero, { 2048.0f, 2048.0f } } }));

		// 白テクスチャを作る
		{
			TexBufFormatParam formatParam{};
			formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize = 1U;
			formatParam.mipLevels = 1U;
			formatParam.sampleDescCount = 1U;
			formatParam.sampleDescQuality = 0U;

			TexBuffData dataParam{};
			dataParam.textureData = {
				255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255,
				255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255,
				255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255,
				255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255
			};
			dataParam.width = 4U;
			dataParam.height = 4U;

			setSystemHandle(SystemTextureBufferType::White4x4, cpuPriorityCreateTextureBuffer(formatParam, dataParam));
		}

		// 黒テクスチャを作る
		{
			TexBufFormatParam formatParam{};
			formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize = 1U;
			formatParam.mipLevels = 1U;
			formatParam.sampleDescCount = 1U;
			formatParam.sampleDescQuality = 0U;

			TexBuffData dataParam{};
			dataParam.textureData = {
				0, 0, 0, 255, /**/ 0, 0, 0, 255, /**/ 0, 0, 0, 255, /**/ 0, 0, 0, 255,
				0, 0, 0, 255, /**/ 0, 0, 0, 255, /**/ 0, 0, 0, 255, /**/ 0, 0, 0, 255,
				0, 0, 0, 255, /**/ 0, 0, 0, 255, /**/ 0, 0, 0, 255, /**/ 0, 0, 0, 255,
				0, 0, 0, 255, /**/ 0, 0, 0, 255, /**/ 0, 0, 0, 255, /**/ 0, 0, 0, 255
			};
			dataParam.width = 4U;
			dataParam.height = 4U;

			setSystemHandle(SystemTextureBufferType::Black4x4, cpuPriorityCreateTextureBuffer(formatParam, dataParam));
		}

		// 平らな法線テクスチャを作る
		{
			TexBufFormatParam formatParam{};
			formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize = 1U;
			formatParam.mipLevels = 1U;
			formatParam.sampleDescCount = 1U;
			formatParam.sampleDescQuality = 0U;

			TexBuffData dataParam{};
			dataParam.textureData = {
				0, 0, 255, 255, /**/ 0, 0, 255, 255, /**/ 0, 0, 255, 255, /**/ 0, 0, 255, 255,
				0, 0, 255, 255, /**/ 0, 0, 255, 255, /**/ 0, 0, 255, 255, /**/ 0, 0, 255, 255,
				0, 0, 255, 255, /**/ 0, 0, 255, 255, /**/ 0, 0, 255, 255, /**/ 0, 0, 255, 255,
				0, 0, 255, 255, /**/ 0, 0, 255, 255, /**/ 0, 0, 255, 255, /**/ 0, 0, 255, 255
			};
			dataParam.width = 4U;
			dataParam.height = 4U;

			setSystemHandle(SystemTextureBufferType::FlatNormal4x4, cpuPriorityCreateTextureBuffer(formatParam, dataParam));
		}

		// デフォルトの深度バッファーを作る
		{
			DepthStencilBufferInitParam initParam{};
			initParam.depthStencilSize = m_graphicManager->getDrawGameAreaSize();
			initParam.useAsShaderResource = false;

			setSystemHandle(SystemDsBufferType::Basic, createDsBuffer(initParam));
		}

		// デフォルトの深度ディスクリプタヒープを作る
		{
			DsvDescriptorHeapInitParam initParam{};
			initParam.descriptorParamArray.push_back({ DsvDescriptorType::normal, getSystemHandle(SystemDsBufferType::Basic) });

			setSystemHandle(SystemDsvDescriptorHeapType::Basic, createDsvDescriptorHeap(initParam));
		}

		// シャドウマップの深度バッファーを作る
		{
			DepthStencilBufferInitParam initParam{};
			initParam.depthStencilSize = { 2048.0f, 2048.0f };
			initParam.useAsShaderResource = true;

			setSystemHandle(SystemDsBufferType::ShadowMap, createDsBuffer(initParam));
		}

		// シャドウマップの深度ディスクリプタヒープを作る
		{
			DsvDescriptorHeapInitParam initParam{};
			initParam.descriptorParamArray.push_back({ DsvDescriptorType::normal, getSystemHandle(SystemDsBufferType::ShadowMap) });

			setSystemHandle(SystemDsvDescriptorHeapType::ShadowMap, createDsvDescriptorHeap(initParam));
		}

#ifdef _M_AMD64 /* x64ビルドなら */
		std::string shaderFolderPath = gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x64/";
#else
		std::string shaderFolderPath = gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x86/";
#endif // _M_AMD64

		// ゲームのリソース管理クラスの初期化を行う
		DXGameResourceInitParam dxGameResParam;

		auto& draw3DParamInit = dxGameResParam.draw3DParam;
		draw3DParamInit.lightMgrParam	= gameManagerInitParam.lightContainerParam;
		draw3DParamInit.cameraMgrParam	= gameManagerInitParam.cameraContainerParam;

		auto& shaderResInit = dxGameResParam.dxGameShaderResParam;
		shaderResInit.postEffectMatMgrParam.containerParam			= gameManagerInitParam.postEffectMatContainerParam;
		shaderResInit.line2DMatMgrParam.containerParam				= gameManagerInitParam.line2DMatContainerParam;
		shaderResInit.spriteMatMgrParam.containerParam				= gameManagerInitParam.spriteMatContainerParam;
		shaderResInit.billboardMatMgrParam.containerParam			= gameManagerInitParam.billboardMatContainerParam;
		shaderResInit.meshResParam.meshMgrParam						= gameManagerInitParam.meshContainerParam;
		shaderResInit.meshResParam.meshMatMgrParam					= gameManagerInitParam.meshMatContainerParam;
		shaderResInit.meshResParam.skeletonMgrParam					= gameManagerInitParam.skeletonContainerParam;
		shaderResInit.meshResParam.motionMgrParam					= gameManagerInitParam.motionContainerParam;

		shaderResInit.postEffectMatMgrParam.drawGameAreaVSFilePath			= shaderFolderPath + "DrawGameAreaVertexShader.cso"; 
		shaderResInit.postEffectMatMgrParam.drawGameAreaPSFilePath			= shaderFolderPath + "DrawGameAreaPixelShader.cso";
		shaderResInit.postEffectMatMgrParam.postEffectVSFilePath			= shaderFolderPath + "PostEffectVertexShader.cso";
		shaderResInit.postEffectMatMgrParam.monochromePSFilePath			= shaderFolderPath + "MonochromePixelShader.cso";
		shaderResInit.line2DMatMgrParam.shaderFilePaths.vsFilePath			= shaderFolderPath + "Line2DVertexShader.cso";
		shaderResInit.line2DMatMgrParam.shaderFilePaths.psFilePath			= shaderFolderPath + "Line2DPixelShader.cso";
		shaderResInit.spriteMatMgrParam.shaderFilePaths.vsFilePath			= shaderFolderPath + "SpriteVertexShader.cso";
		shaderResInit.spriteMatMgrParam.shaderFilePaths.psFilePath			= shaderFolderPath + "SpritePixelShader.cso";
		shaderResInit.billboardMatMgrParam.shaderFilePaths.vsFilePath		= shaderFolderPath + "BillboardVertexShader.cso";
		shaderResInit.billboardMatMgrParam.shaderFilePaths.psFilePath		= shaderFolderPath + "BillboardPixelShader.cso";
		shaderResInit.meshResParam.shaderFilePaths.simpleMeshVS				= shaderFolderPath + "SimpleMeshVertexShader.cso";
		shaderResInit.meshResParam.shaderFilePaths.skinningMeshVS			= shaderFolderPath + "SkinningMeshVertexShader.cso";
		shaderResInit.meshResParam.shaderFilePaths.basicMeshPS				= shaderFolderPath + "BasicMeshPixelShader.cso";
		shaderResInit.meshResParam.shaderFilePaths.monoColorSimpleMeshVS	= shaderFolderPath + "MonoColorSimpleMeshVertexShader.cso";
		shaderResInit.meshResParam.shaderFilePaths.monoColorSkinningMeshVS	= shaderFolderPath + "MonoColorSkinningMeshVertexShader.cso";
		shaderResInit.meshResParam.shaderFilePaths.monoColorMeshPS			= shaderFolderPath + "MonoColorMeshPixelShader.cso";
		shaderResInit.meshResParam.shaderFilePaths.simpleMeshShadowMapVs	= shaderFolderPath + "SimpleMeshShadowMapVertexShader.cso";
		shaderResInit.meshResParam.shaderFilePaths.skinningMeshShadowMapVs	= shaderFolderPath + "SkinningMeshShadowMapVertexShader.cso";

		auto& otherResInit = dxGameResParam.otherResParam;
		otherResInit.sceneMgrParam = gameManagerInitParam.sceneContainerParam;
		otherResInit.soundMgrParam = gameManagerInitParam.soundContainerParam;

		m_dxGameResource = std::make_unique<DXGameResource>(dxGameResParam);

		// ポストエフェクトを描画するコンポーネントを持つオブジェクト
		m_postEffectObject = m_dxGameResource->createGameObject();

		// デフォルトの通常カメラを作る
		setSystemHandle(SystemCameraType::DefaultCamera, createCamera());
		
		// デフォルトのシャドウマップカメラを作る
		setSystemHandle(SystemCameraType::DefaultShadowMapCamera, createCamera());
		
		// デフォルトのライトを作る
		setSystemHandle(SystemLightType::DefaultLight, createLight({ 0.1f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 0.0f }));

		// ステートマシンの実行タイミングを設定する
		addRunFuncPriority<StateMachine>(1100.0f);

		// メッシュのインスタンス描画に使用する頂点バッファを設定するコンポーネントの実行タイミングを設定する
		addRunFuncPriority<MeshDrawer>(1200.0f);

		// ビルボードのインスタンス描画に使用する頂点バッファを設定するコンポーネントの実行タイミングを設定する
		addRunFuncPriority<BillboardDrawer>(1200.0f);

		// 初期から存在するメッシュを作る
		m_dxGameResource->createSystemMesh();

		// 描画エリア描画用のポストエフェクトマテリアルを作る
		{
			PostEffectMaterialInitParam materialInitParam{};
			materialInitParam.usePipeLineStateHandle				= m_utilityProcessManager->getSystemHandle(SystemPipeLineStateType::DrawGameArea);
			materialInitParam.useDescriptorHeapHandle				= m_utilityProcessManager->getSystemHandle(SystemBasicDescriptorHeapType::DrawGameArea);
			materialInitParam.autoClearRtvDescriptorHeapHandleArray = { m_utilityProcessManager->getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea) };

			auto drawFuncRunnerInitParam = PostEffectDrawFuncRunnerInitParam::create();
			drawFuncRunnerInitParam.rtvDescriptorHeapHandle = m_utilityProcessManager->getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

			auto createdHandle = m_dxGameResource->createPostEffectMaterial(materialInitParam);
			m_postEffectObject->createComponent<PostEffectDrawFuncRunner>(createdHandle, drawFuncRunnerInitParam);

			addPostEffectMaterialAppendParam(createdHandle, PostEffectMaterialAppendParamInitParam(
				m_utilityProcessManager->getSystemHandle(SystemCBufferType::DrawGameArea),
				std::make_shared<DrawGameAreaCBufferData>(DrawGameAreaCBufferData{ m_graphicManager->getDrawGameAreaSize(), m_graphicManager->getScreenSize() })
			));
		}
	}

	void DX12GameManager::run()
	{
		MSG msg{};

		while (true)
		{
			bool canRunDX12Func = true;

			if (msg.message == WM_QUIT || m_isGameExit)
			{
				break;
			}
			else if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				switch (msg.message)
				{
				case WM_MOUSEMOVE:
				case WM_LBUTTONDOWN:
				case WM_LBUTTONUP:
				case WM_LBUTTONDBLCLK:
				case WM_RBUTTONDOWN:
				case WM_RBUTTONUP:
				case WM_RBUTTONDBLCLK:
				case WM_MBUTTONDOWN:
				case WM_MBUTTONUP:
				case WM_MBUTTONDBLCLK:
				case WM_XBUTTONDOWN:
				case WM_XBUTTONUP:
				case WM_XBUTTONDBLCLK:
				case WM_MOUSEWHEEL:
				case WM_MOUSEHWHEEL:
				case WM_NCMOUSEMOVE:
				case WM_NCLBUTTONDOWN:
				case WM_NCLBUTTONUP:
				case WM_NCLBUTTONDBLCLK:
				case WM_NCRBUTTONDOWN:
				case WM_NCRBUTTONUP:
				case WM_NCRBUTTONDBLCLK:
				case WM_NCMBUTTONDOWN:
				case WM_NCMBUTTONUP:
				case WM_NCMBUTTONDBLCLK:
				case WM_NCXBUTTONDOWN:
				case WM_NCXBUTTONUP:
				case WM_NCXBUTTONDBLCLK:
				case WM_KEYFIRST:
				case WM_KEYUP:
				case WM_CHAR:
				case WM_DEADCHAR:
				case WM_SYSKEYDOWN:
				case WM_SYSKEYUP:
				case WM_SYSCHAR:
				case WM_SYSDEADCHAR:
				case WM_UNICHAR:
					break;

				default:

					// 処理かっ飛ばし
					canRunDX12Func = false;
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (canRunDX12Func)
			{
				// 更新処理
				m_utilityProcessManager->update();
				m_dxGameResource->update();

				// 描画処理
				m_graphicManager->beginDraw();
				m_dxGameResource->draw();
				m_graphicManager->endDraw();

				// 死亡している要素をメインリストから削除する
				m_dxGameResource->removeDeadInstance();
			}
		}
		m_dxGameResource->clearSound();
	}

	void DX12GameManager::exit()
	{
		m_isGameExit = true;
	}

	const tktkMath::Vector2& DX12GameManager::getDrawGameAreaSize()
	{
		return m_graphicManager->getDrawGameAreaSize();
	}

	const tktkMath::Vector2& DX12GameManager::getScreenSize()
	{
		return m_graphicManager->getScreenSize();
	}
	
	size_t DX12GameManager::addScene(const SceneInitParam& initParam)
	{
		return m_dxGameResource->createScene(initParam);
	}
	
	size_t DX12GameManager::addSceneAndAttachId(ResourceIdCarrier id, const SceneInitParam& initParam)
	{
		auto createdHandle = m_dxGameResource->createScene(initParam);
		m_utilityProcessManager->setSceneHandle(id, createdHandle);
		return createdHandle;
	}
	
	void DX12GameManager::setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag)
	{
		m_dxGameResource->setSceneEndDestroyGameObjectTag(handle, tag);
	}
	
	void DX12GameManager::enableScene(size_t handle)
	{
		m_dxGameResource->enableScene(handle);
	}
	
	void DX12GameManager::disableScene(size_t handle)
	{
		m_dxGameResource->disableScene(handle);
	}
	
	void DX12GameManager::sendMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment)
	{
		m_dxGameResource->runHandleMessageAll(type, attachment);
	}
	
	GameObjectPtr DX12GameManager::createGameObject()
	{
		return m_dxGameResource->createGameObject();
	}
	
	GameObjectPtr DX12GameManager::findGameObjectWithTag(GameObjectTagCarrier tag)
	{
		return m_dxGameResource->findGameObjectWithTag(tag);
	}
	
	std::forward_list<GameObjectPtr> DX12GameManager::findGameObjectsWithTag(GameObjectTagCarrier tag)
	{
		return m_dxGameResource->findGameObjectsWithTag(tag);
	}
	
	void DX12GameManager::destroyGameObjectsWithTag(GameObjectTagCarrier tag)
	{
		m_dxGameResource->destroyGameObjectsWithTag(tag);
	}

	void DX12GameManager::addRunFuncPriority(std::type_index type, float priority)
	{
		m_dxGameResource->addRunFuncPriority(type, priority);
	}

	void DX12GameManager::addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup)
	{
		m_dxGameResource->addCollisionGroup(firstGroup, secondGroup);
	}

	ComponentBasePtr DX12GameManager::addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const GameObjectPtr& user, const std::shared_ptr<ComponentBase>& componentPtr)
	{
		return m_dxGameResource->addComponent(type, vtablePtrBundle, listVtablePtr, user, componentPtr);
	}
	
	void DX12GameManager::executeCommandList()
	{
		m_graphicManager->executeCommandList();
	}
	
	void DX12GameManager::setRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount)
	{
		m_graphicManager->setRtv(rtvDescriptorHeapHandle, startRtvLocationIndex, rtvCount);
	}
	
	void DX12GameManager::setRtvAndDsv(size_t rtvDescriptorHeapHandle, size_t dsvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount)
	{
		m_graphicManager->setRtvAndDsv(rtvDescriptorHeapHandle, dsvDescriptorHeapHandle, startRtvLocationIndex, rtvCount);
	}
	
	void DX12GameManager::setOnlyDsv(size_t dsvDescriptorHeapHandle)
	{
		m_graphicManager->setOnlyDsv(dsvDescriptorHeapHandle);
	}
	
	void DX12GameManager::setBackBufferView()
	{
		m_graphicManager->setBackBufferView();
	}
	
	void DX12GameManager::setBackBufferViewAndDsv(size_t dsvDescriptorHeapHandle)
	{
		m_graphicManager->setBackBufferViewAndDsv(dsvDescriptorHeapHandle);
	}
	
	void DX12GameManager::unSetRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount)
	{
		m_graphicManager->unSetRtv(rtvDescriptorHeapHandle, startRtvLocationIndex, rtvCount);
	}
	
	void DX12GameManager::unSetDsv(size_t dsvDescriptorHeapHandle)
	{
		m_graphicManager->unSetDsv(dsvDescriptorHeapHandle);
	}
	
	void DX12GameManager::setViewport(size_t handle)
	{
		m_graphicManager->setViewport(handle);
	}
	
	void DX12GameManager::setScissorRect(size_t handle)
	{
		m_graphicManager->setScissorRect(handle);
	}
	
	void DX12GameManager::setPipeLineState(size_t handle)
	{
		m_graphicManager->setPipeLineState(handle);
	}
	
	void DX12GameManager::setVertexBuffer(size_t handle)
	{
		m_graphicManager->setVertexBuffer(handle);
	}

	void DX12GameManager::setVertexBuffer(size_t meshVertHandle, size_t instancingVertHandle)
	{
		m_graphicManager->setVertexBuffer(meshVertHandle, instancingVertHandle);
	}
	
	void DX12GameManager::setIndexBuffer(size_t handle)
	{
		m_graphicManager->setIndexBuffer(handle);
	}
	
	void DX12GameManager::setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray)
	{
		m_graphicManager->setDescriptorHeap(heapParamArray);
	}
	
	void DX12GameManager::setBlendFactor(const std::array<float, 4>& blendFactor)
	{
		m_graphicManager->setBlendFactor(blendFactor);
	}
	
	void DX12GameManager::setPrimitiveTopology(PrimitiveTopology topology)
	{
		m_graphicManager->setPrimitiveTopology(topology);
	}
	
	void DX12GameManager::drawInstanced(size_t vertexCountPerInstance, size_t instanceCount, size_t baseVertexLocation, size_t startInstanceLocation)
	{
		m_graphicManager->drawInstanced(vertexCountPerInstance, instanceCount, baseVertexLocation, startInstanceLocation);
	}
	
	void DX12GameManager::drawIndexedInstanced(size_t indexCountPerInstance, size_t instanceCount, size_t startIndexLocation, size_t baseVertexLocation, size_t startInstanceLocation)
	{
		m_graphicManager->drawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
	}
	
	size_t DX12GameManager::createViewport(const std::vector<ViewportInitParam>& initParamArray)
	{
		return m_graphicManager->createViewport(initParamArray);
	}

	size_t DX12GameManager::createScissorRect(const std::vector<ScissorRectInitParam>& initParamArray)
	{
		return m_graphicManager->createScissorRect(initParamArray);
	}

	size_t DX12GameManager::createRootSignature(const RootSignatureInitParam& initParam)
	{
		return m_graphicManager->createRootSignature(initParam);
	}
	
	size_t DX12GameManager::createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		return m_graphicManager->createPipeLineState(initParam, shaderFilePath);
	}
	
	size_t DX12GameManager::createUploadBuffer(const UploadBufferInitParam& initParam)
	{
		return m_graphicManager->createUploadBuffer(initParam);
	}
	
	size_t DX12GameManager::duplicateUploadBuffer(size_t originalHandle)
	{
		return m_graphicManager->duplicateUploadBuffer(originalHandle);
	}
	
	size_t DX12GameManager::createVertexBuffer(const VertexDataCarrier& vertexData)
	{
		return m_graphicManager->createVertexBuffer(vertexData);
	}
	
	size_t DX12GameManager::createIndexBuffer(const std::vector<unsigned short>& indices)
	{
		return m_graphicManager->createIndexBuffer(indices);
	}
	
	size_t DX12GameManager::createCBuffer(const CopySourceDataCarrier& constantBufferData)
	{
		return m_graphicManager->createCBuffer(constantBufferData);
	}
	
	size_t DX12GameManager::createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		return m_graphicManager->createRtBuffer(renderTargetSize, clearColor);
	}
	
	size_t DX12GameManager::createDsBuffer(const DepthStencilBufferInitParam& initParam)
	{
		return m_graphicManager->createDsBuffer(initParam);
	}
	
	size_t DX12GameManager::createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam)
	{
		return m_graphicManager->createBasicDescriptorHeap(initParam);
	}
	
	size_t DX12GameManager::createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam)
	{
		return m_graphicManager->createRtvDescriptorHeap(initParam);
	}
	
	size_t DX12GameManager::createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam)
	{
		return m_graphicManager->createDsvDescriptorHeap(initParam);
	}
	
	size_t DX12GameManager::cpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_graphicManager->cpuPriorityCreateTextureBuffer(formatParam, dataParam);
	}
	
	size_t DX12GameManager::gpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_graphicManager->gpuPriorityCreateTextureBuffer(formatParam, dataParam);
	}
	
	size_t DX12GameManager::cpuPriorityLoadTextureBuffer(const std::string& texDataPath)
	{
		return m_graphicManager->cpuPriorityLoadTextureBuffer(texDataPath);
	}
	
	size_t DX12GameManager::gpuPriorityLoadTextureBuffer(const std::string& texDataPath)
	{
		return m_graphicManager->gpuPriorityLoadTextureBuffer(texDataPath);
	}
	
	void DX12GameManager::eraseViewport(size_t handle)
	{
		m_graphicManager->eraseViewport(handle);
	}
	
	void DX12GameManager::eraseScissorRect(size_t handle)
	{
		m_graphicManager->eraseScissorRect(handle);
	}
	
	void DX12GameManager::eraseRootSignature(size_t handle)
	{
		m_graphicManager->eraseRootSignature(handle);
	}
	
	void DX12GameManager::erasePipeLineState(size_t handle)
	{
		m_graphicManager->erasePipeLineState(handle);
	}
	
	void DX12GameManager::eraseUploadBuffer(size_t handle)
	{
		m_graphicManager->eraseUploadBuffer(handle);
	}
	
	void DX12GameManager::eraseVertexBuffer(size_t handle)
	{
		m_graphicManager->eraseVertexBuffer(handle);
	}
	
	void DX12GameManager::eraseIndexBuffer(size_t handle)
	{
		m_graphicManager->eraseIndexBuffer(handle);
	}
	
	void DX12GameManager::eraseCBuffer(size_t handle)
	{
		m_graphicManager->eraseCBuffer(handle);
	}
	
	void DX12GameManager::eraseTextureBuffer(size_t handle)
	{
		m_graphicManager->eraseTextureBuffer(handle);
	}
	
	void DX12GameManager::eraseDsBuffer(size_t handle)
	{
		m_graphicManager->eraseDsBuffer(handle);
	}
	
	void DX12GameManager::eraseRtBuffer(size_t handle)
	{
		m_graphicManager->eraseRtBuffer(handle);
	}
	
	void DX12GameManager::eraseBasicDescriptorHeap(size_t handle)
	{
		m_graphicManager->eraseBasicDescriptorHeap(handle);
	}
	
	void DX12GameManager::eraseRtvDescriptorHeap(size_t handle)
	{
		m_graphicManager->eraseRtvDescriptorHeap(handle);
	}
	
	void DX12GameManager::eraseDsvDescriptorHeap(size_t handle)
	{
		m_graphicManager->eraseDsvDescriptorHeap(handle);
	}
	
	void DX12GameManager::updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData)
	{
		m_graphicManager->updateUploadBuffer(handle, bufferData);
	}

	void DX12GameManager::updateVertexBuffer(size_t handle, const VertexDataCarrier& vertexData)
	{
		m_graphicManager->updateVertexBuffer(handle, vertexData);
	}
	
	void DX12GameManager::copyBuffer(size_t handle)
	{
		m_graphicManager->copyBuffer(handle);
	}
	
	void DX12GameManager::clearRtv(size_t handle, size_t rtvLocationIndex)
	{
		m_graphicManager->clearRtv(handle, rtvLocationIndex);
	}
	
	const tktkMath::Vector3& DX12GameManager::getTextureBufferSizePx(size_t handle)
	{
		return m_graphicManager->getTextureBufferSizePx(handle);
	}
	
	const tktkMath::Vector2& DX12GameManager::getDsBufferSizePx(size_t handle)
	{
		return m_graphicManager->getDsBufferSizePx(handle);
	}
	
	const tktkMath::Vector2& DX12GameManager::getRtBufferSizePx(size_t handle)
	{
		return m_graphicManager->getRtBufferSizePx(handle);
	}
	
	size_t DX12GameManager::createSpriteMaterial(const SpriteMaterialInitParam& initParam)
	{
		return m_dxGameResource->createSpriteMaterial(initParam);
	}
	
	size_t DX12GameManager::createSpriteMaterialAndAttachId(ResourceIdCarrier id, const SpriteMaterialInitParam& initParam)
	{
		auto createdHandle = m_dxGameResource->createSpriteMaterial(initParam);
		m_utilityProcessManager->setSpriteMaterialHandle(id, createdHandle);
		return createdHandle;
	}

	const tktkMath::Vector2& DX12GameManager::getSpriteTextureSize(size_t handle)
	{
		return m_dxGameResource->getSpriteTextureSize(handle);
	}
	
	void DX12GameManager::drawSprite(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameResource->drawSprite(handle, drawFuncArgs);
	}
	
	void DX12GameManager::updateSpriteTransformCbuffer(size_t handle, size_t copyBufferHandle, const SpriteCBufferUpdateFuncArgs& cbufferUpdateArgs)
	{
		m_dxGameResource->updateSpriteTransformCbuffer(handle, copyBufferHandle, cbufferUpdateArgs);
	}
	
	void DX12GameManager::updateSpriteTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const SpriteCBufferUpdateFuncArgs& cbufferUpdateArgs, const SpriteClippingParam& clippingParam)
	{
		m_dxGameResource->updateSpriteTransformCbufferUseClippingParam(handle, copyBufferHandle, cbufferUpdateArgs, clippingParam);
	}
	
	size_t DX12GameManager::createLine2DMaterial()
	{
		return m_dxGameResource->createLine();
	}
	
	size_t DX12GameManager::createLine2DMaterialAndAttachId(ResourceIdCarrier id)
	{
		auto createdHandle = m_dxGameResource->createLine();
		m_utilityProcessManager->setLine2DMaterialHandle(id, createdHandle);
		return createdHandle;
	}
	
	void DX12GameManager::eraseLine(size_t handle)
	{
		m_dxGameResource->eraseLine(handle);
	}
	
	void DX12GameManager::drawLine(size_t handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameResource->drawLine(handle, drawFuncArgs);
	}
	
	size_t DX12GameManager::createBillboardMaterial(const BillboardMaterialInitParam& initParam, const BillboardDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		auto createdHandle = m_dxGameResource->createBillboardMaterial(initParam);

		createComponent<BillboardDrawFuncRunner>(GameObjectPtr(), createdHandle, funcRunnerInitParam);

		return createdHandle;
	}
	
	size_t DX12GameManager::createBillboardMaterialAndAttachId(ResourceIdCarrier id, const BillboardMaterialInitParam& initParam, const BillboardDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		auto createdHandle = m_dxGameResource->createBillboardMaterial(initParam);

		createComponent<BillboardDrawFuncRunner>(GameObjectPtr(), createdHandle, funcRunnerInitParam);

		m_utilityProcessManager->setBillboardMaterialHandle(id, createdHandle);

		return createdHandle;
	}

	const tktkMath::Vector2& DX12GameManager::getBillboardTextureSize(size_t handle)
	{
		return m_dxGameResource->getBillboardTextureSize(handle);
	}

	void DX12GameManager::clearBillboardInstanceParam(size_t handle)
	{
		m_dxGameResource->clearBillboardInstanceParam(handle);
	}

	void DX12GameManager::addBillboardInstanceVertParam(size_t handle, const BillboardMaterialInstanceVertData& instanceParam)
	{
		m_dxGameResource->addBillboardInstanceVertParam(handle, instanceParam);
	}
	
	void DX12GameManager::drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs)
	{
		m_dxGameResource->drawBillboard(handle, drawFuncArgs);
	}
	
	size_t DX12GameManager::createMesh(const MeshInitParam& meshInitParam, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		auto createdHandle = m_dxGameResource->createMesh(meshInitParam);

		createComponent<MeshDrawFuncRunner>(GameObjectPtr(), createdHandle, funcRunnerInitParam);

		if (funcRunnerInitParam.m_writeShadowMap)
		{
			createComponent<WriteMeshShadowMapFuncRunner>(GameObjectPtr(), createdHandle, funcRunnerInitParam.m_useBone);
		}

		return createdHandle;
	}
	
	size_t DX12GameManager::createMeshAndAttachId(ResourceIdCarrier id, const MeshInitParam& meshInitParam, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		auto createdHandle = m_dxGameResource->createMesh(meshInitParam);

		createComponent<MeshDrawFuncRunner>(GameObjectPtr(), createdHandle, funcRunnerInitParam);

		m_utilityProcessManager->setMeshHandle(id, createdHandle);

		if (funcRunnerInitParam.m_writeShadowMap)
		{
			createComponent<WriteMeshShadowMapFuncRunner>(GameObjectPtr(), createdHandle, funcRunnerInitParam.m_useBone);
		}

		return createdHandle;
	}
	
	size_t DX12GameManager::copyMesh(size_t originalHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		auto createdHandle = m_dxGameResource->copyMesh(originalHandle);

		createComponent<MeshDrawFuncRunner>(GameObjectPtr(), createdHandle, funcRunnerInitParam);

		if (funcRunnerInitParam.m_writeShadowMap)
		{
			createComponent<WriteMeshShadowMapFuncRunner>(GameObjectPtr(), createdHandle, funcRunnerInitParam.m_useBone);
		}

		return createdHandle;
	}
	
	size_t DX12GameManager::copyMeshAndAttachId(ResourceIdCarrier id, size_t originalHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		auto createdHandle = m_dxGameResource->copyMesh(originalHandle);

		createComponent<MeshDrawFuncRunner>(GameObjectPtr(), createdHandle, funcRunnerInitParam);

		m_utilityProcessManager->setMeshHandle(id, createdHandle);

		if (funcRunnerInitParam.m_writeShadowMap)
		{
			createComponent<WriteMeshShadowMapFuncRunner>(GameObjectPtr(), createdHandle, funcRunnerInitParam.m_useBone);
		}

		return createdHandle;
	}
	
	size_t DX12GameManager::createMeshMaterial(const MeshMaterialInitParam& initParam)
	{
		return m_dxGameResource->createMeshMaterial(initParam);
	}
	
	size_t DX12GameManager::createMeshMaterialAndAttachId(ResourceIdCarrier id, const MeshMaterialInitParam& initParam)
	{
		auto createdHandle = m_dxGameResource->createMeshMaterial(initParam);
		m_utilityProcessManager->setMeshMaterialHandle(id, createdHandle);
		return createdHandle;
	}
	
	size_t DX12GameManager::copyMeshMaterial(size_t originalHandle)
	{
		return m_dxGameResource->copyMeshMaterial(originalHandle);
	}
	
	size_t DX12GameManager::copyMeshMaterialAndAttachId(ResourceIdCarrier id, size_t originalHandle)
	{
		auto createdHandle = m_dxGameResource->copyMeshMaterial(m_utilityProcessManager->getBasicMeshMaterialHandle(id));
		m_utilityProcessManager->setMeshMaterialHandle(id, createdHandle);
		return createdHandle;
	}

	size_t DX12GameManager::makeBoxMesh(size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		return m_dxGameResource->makeBoxMesh(albedoMapTextureHandle, funcRunnerInitParam);
	}

	size_t DX12GameManager::makeBoxMeshAndAttachId(ResourceIdCarrier id, size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		auto createdHandle = m_dxGameResource->makeBoxMesh(albedoMapTextureHandle, funcRunnerInitParam);
		m_utilityProcessManager->setMeshHandle(id, createdHandle);
		return createdHandle;
	}

	size_t DX12GameManager::makeSkyBoxMesh(size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		return m_dxGameResource->makeSkyBoxMesh(skyBoxTextureHandle, funcRunnerInitParam);
	}

	size_t DX12GameManager::makeSkyBoxMeshAndAttachId(ResourceIdCarrier id, size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		auto createdHandle = m_dxGameResource->makeSkyBoxMesh(skyBoxTextureHandle, funcRunnerInitParam);
		m_utilityProcessManager->setMeshHandle(id, createdHandle);
		return createdHandle;
	}

	MeshLoadPmdReturnValue DX12GameManager::loadPmd(const MeshLoadPmdArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		return m_dxGameResource->loadPmd(args, funcRunnerInitParam);
	}

	MeshLoadPmxReturnValue DX12GameManager::loadPmx(const MeshLoadPmxArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		return m_dxGameResource->loadPmx(args, funcRunnerInitParam);
	}
	
	void DX12GameManager::setMeshMaterialHandle(size_t handle, size_t materialSlot, size_t materialHandle)
	{
		m_dxGameResource->setMeshMaterialHandle(handle, materialSlot, materialHandle);
	}
	
	void DX12GameManager::setMeshMaterialData(size_t handle)
	{
		m_dxGameResource->setMeshMaterialData(handle);
	}

	void DX12GameManager::addMeshMaterialAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam)
	{
		m_dxGameResource->addMeshMaterialAppendParam(handle, initParam);
	}

	void DX12GameManager::updateMeshMaterialAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs)
	{
		m_dxGameResource->updateMeshMaterialAppendParam(handle, updateFuncArgs);
	}

	void DX12GameManager::clearMeshInstanceParam(size_t handle)
	{
		m_dxGameResource->clearMeshInstanceParam(handle);
	}

	void DX12GameManager::addMeshInstanceVertParam(size_t handle, const CopySourceDataCarrier& instanceParam)
	{
		m_dxGameResource->addMeshInstanceVertParam(handle, instanceParam);
	}

	void DX12GameManager::addMeshInstanceBoneMatrix(size_t meshHandle, size_t skeletonHandle)
	{
		m_dxGameResource->addMeshInstanceBoneMatrix(meshHandle, skeletonHandle);
	}

	void DX12GameManager::writeMeshShadowMap(size_t handle)
	{
		m_dxGameResource->writeMeshShadowMap(handle);
	}

	void DX12GameManager::writeMeshShadowMapUseBone(size_t handle)
	{
		m_dxGameResource->writeMeshShadowMapUseBone(handle);
	}

	void DX12GameManager::drawMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs)
	{
		m_dxGameResource->drawMesh(handle, baseArgs);
	}

	void DX12GameManager::drawMeshUseBone(size_t handle, const MeshDrawFuncBaseArgs& baseArgs)
	{
		m_dxGameResource->drawMeshUseBone(handle, baseArgs);
	}
	
	size_t DX12GameManager::createSkeleton(const SkeletonInitParam& initParam)
	{
		return m_dxGameResource->createSkeleton(initParam);
	}
	
	size_t DX12GameManager::copySkeleton(size_t originalHandle)
	{
		return m_dxGameResource->copySkeleton(originalHandle);
	}
	
	size_t DX12GameManager::createSkeletonAndAttachId(ResourceIdCarrier id, const SkeletonInitParam& initParam)
	{
		auto createdHandle = m_dxGameResource->createSkeleton(initParam);
		m_utilityProcessManager->setSkeletonHandle(id, createdHandle);
		return createdHandle;
	}
	
	size_t DX12GameManager::loadMotion(const std::string& motionFileName)
	{
		return m_dxGameResource->loadMotion(motionFileName);
	}
	
	size_t DX12GameManager::loadMotionAndAttachId(ResourceIdCarrier id, const std::string& motionFileName)
	{
		auto createdHandle = m_dxGameResource->loadMotion(motionFileName);
		m_utilityProcessManager->setMotionHandle(id, createdHandle);
		return createdHandle;
	}
	
	size_t DX12GameManager::getMotionEndFrameNo(size_t handle)
	{
		return m_dxGameResource->getMotionEndFrameNo(handle);
	}
	
	void DX12GameManager::updateMotion(
		size_t skeletonHandle,
		size_t curMotionHandle,
		size_t preMotionHandle,
		float curFrame,
		float preFrame,
		float amount
	)
	{
		m_dxGameResource->updateMotion(
			skeletonHandle,
			curMotionHandle,
			preMotionHandle,
			curFrame,
			preFrame,
			amount
		);
	}
	
	size_t DX12GameManager::createPostEffectMaterial(const PostEffectMaterialInitParam& initParam, const PostEffectDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		auto createdHandle = m_dxGameResource->createPostEffectMaterial(initParam);
		auto createdComponent = m_postEffectObject->createComponent<PostEffectDrawFuncRunner>(createdHandle, funcRunnerInitParam);
		createdComponent->setActive(false);
		return createdHandle;
	}
	
	size_t DX12GameManager::createPostEffectMaterialAndAttachId(ResourceIdCarrier id, const PostEffectMaterialInitParam& initParam, const PostEffectDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		auto createdHandle = m_dxGameResource->createPostEffectMaterial(initParam);
		auto createdComponent = m_postEffectObject->createComponent<PostEffectDrawFuncRunner>(createdHandle, funcRunnerInitParam);
		createdComponent->setActive(false);
		m_utilityProcessManager->setPostEffectMaterialHandle(id, createdHandle);
		return createdHandle;
	}
	
	void DX12GameManager::drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameResource->drawPostEffect(handle, drawFuncArgs);
	}

	void DX12GameManager::addPostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamInitParam& initParam)
	{
		m_dxGameResource->addPostEffectMaterialAppendParam(handle, initParam);
	}

	void DX12GameManager::updatePostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamUpdateFuncArgs& updateFuncArgs)
	{
		m_dxGameResource->updatePostEffectMaterialAppendParam(handle, updateFuncArgs);
	}

	void DX12GameManager::startPostEffect(size_t handle)
	{
		auto postEffectDrawFuncRunnerList = m_postEffectObject->getComponents<PostEffectDrawFuncRunner>();

		for (const auto& drawFuncRunner : postEffectDrawFuncRunnerList)
		{
			if (drawFuncRunner->getPostEffectMaterialHandle() == handle) drawFuncRunner->setActive(true);
			else drawFuncRunner->setActive(false);
		}
	}

	void DX12GameManager::stopPostEffect()
	{
		auto postEffectDrawFuncRunnerList = m_postEffectObject->getComponents<PostEffectDrawFuncRunner>();

		for (const auto& drawFuncRunner : postEffectDrawFuncRunnerList)
		{
			if (drawFuncRunner->getPostEffectMaterialHandle() == getSystemHandle(SystemPostEffectMaterialType::DrawGameArea)) drawFuncRunner->setActive(true);
			else drawFuncRunner->setActive(false);
		}
	}
	
	size_t DX12GameManager::createCamera()
	{
		return m_dxGameResource->createCamera();
	}
	
	size_t DX12GameManager::createCameraAndAttachId(ResourceIdCarrier id)
	{
		auto createdHandle = m_dxGameResource->createCamera();
		m_utilityProcessManager->setCameraHandle(id, createdHandle);
		return createdHandle;
	}
	
	const tktkMath::Matrix4& DX12GameManager::getViewMatrix(size_t cameraHandle)
	{
		return m_dxGameResource->getViewMatrix(cameraHandle);
	}
	
	void DX12GameManager::setViewMatrix(size_t cameraHandle, const tktkMath::Matrix4& view)
	{
		m_dxGameResource->setViewMatrix(cameraHandle, view);
	}
	
	const tktkMath::Matrix4& DX12GameManager::getProjectionMatrix(size_t cameraHandle)
	{
		return m_dxGameResource->getProjectionMatrix(cameraHandle);
	}
	
	void DX12GameManager::setProjectionMatrix(size_t cameraHandle, const tktkMath::Matrix4& projection)
	{
		m_dxGameResource->setProjectionMatrix(cameraHandle, projection);
	}
	
	size_t DX12GameManager::createLight(const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular, const tktkMath::Vector3& position)
	{
		return m_dxGameResource->createLight(ambient, diffuse, speqular, position);
	}
	
	size_t DX12GameManager::createLightAndAttachId(ResourceIdCarrier id, const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular, const tktkMath::Vector3& position)
	{
		auto createdHandle = m_dxGameResource->createLight(ambient, diffuse, speqular, position);
		m_utilityProcessManager->setLightHandle(id, createdHandle);
		return createdHandle;
	}
	
	void DX12GameManager::updateLightCBuffer(size_t handle)
	{
		m_dxGameResource->updateLightCBuffer(handle);
	}
	
	void DX12GameManager::setLightAmbient(size_t handle, const tktkMath::Color& ambient)
	{
		m_dxGameResource->setLightAmbient(handle, ambient);
	}
	
	void DX12GameManager::setLightDiffuse(size_t handle, const tktkMath::Color& diffuse)
	{
		m_dxGameResource->setLightDiffuse(handle, diffuse);
	}
	
	void DX12GameManager::setLightSpeqular(size_t handle, const tktkMath::Color& speqular)
	{
		m_dxGameResource->setLightSpeqular(handle, speqular);
	}
	
	void DX12GameManager::setLightPosition(size_t handle, const tktkMath::Vector3& position)
	{
		m_dxGameResource->setLightPosition(handle, position);
	}
	
	size_t DX12GameManager::loadSound(const std::string& fileName)
	{
		return m_dxGameResource->loadSound(fileName);
	}
	
	size_t DX12GameManager::loadSoundAndAttachId(ResourceIdCarrier id, const std::string& fileName)
	{
		auto createdhandle = m_dxGameResource->loadSound(fileName);;
		m_utilityProcessManager->setSoundHandle(id, createdhandle);
		return createdhandle;
	}
	
	void DX12GameManager::playSound(size_t handle, bool loopPlay)
	{
		m_dxGameResource->playSound(handle, loopPlay);
	}
	
	void DX12GameManager::stopSound(size_t handle)
	{
		m_dxGameResource->stopSound(handle);
	}
	
	void DX12GameManager::pauseSound(size_t handle)
	{
		m_dxGameResource->pauseSound(handle);
	}
	
	void DX12GameManager::setMasterVolume(float volume)
	{
		m_dxGameResource->setMasterVolume(volume);
	}
	
	bool DX12GameManager::isPush(CommandIdCarrier commandId)
	{
		return m_utilityProcessManager->isPush(commandId);
	}
	
	bool DX12GameManager::isTrigger(CommandIdCarrier commandId)
	{
		return m_utilityProcessManager->isTrigger(commandId);
	}
	
	const tktkMath::Vector2& DX12GameManager::moveVec()
	{
		return m_utilityProcessManager->moveVec();
	}
	
	const tktkMath::Vector2& DX12GameManager::lookVec()
	{
		return m_utilityProcessManager->lookVec();
	}
	
	void DX12GameManager::addCommand(CommandIdCarrier commandId, KeybordKeyType keyType)
	{
		m_utilityProcessManager->addCommand(commandId, keyType);
	}
	
	void DX12GameManager::addCommand(CommandIdCarrier commandId, GamePadBtnType btnType)
	{
		m_utilityProcessManager->addCommand(commandId, btnType);
	}
	
	void DX12GameManager::addCommand(CommandIdCarrier commandId, MouseBtnType btnType)
	{
		m_utilityProcessManager->addCommand(commandId, btnType);
	}
	
	void DX12GameManager::addDirectionCommand(DirectionCommandId directionCommand, KeybordKeyType keyType)
	{
		m_utilityProcessManager->addDirectionCommand(directionCommand, keyType);
	}
	
	void DX12GameManager::addDirectionCommand(DirectionCommandId directionCommand, GamePadBtnType btnType)
	{
		m_utilityProcessManager->addDirectionCommand(directionCommand, btnType);
	}
	
	void DX12GameManager::addDirectionCommand(DirectionCommandId directionCommand, MouseBtnType btnType)
	{
		m_utilityProcessManager->addDirectionCommand(directionCommand, btnType);
	}
	
	bool DX12GameManager::isPush(MouseBtnType buttonType)
	{
		return m_utilityProcessManager->isPush(buttonType);
	}
	
	bool DX12GameManager::isTrigger(MouseBtnType buttonType)
	{
		return m_utilityProcessManager->isTrigger(buttonType);
	}
	
	tktkMath::Vector2 DX12GameManager::mousePos()
	{
		return m_utilityProcessManager->mousePos(m_graphicManager->getHWND());
	}
	
	bool DX12GameManager::isPush(KeybordKeyType keyType)
	{
		return m_utilityProcessManager->isPush(keyType);
	}
	
	bool DX12GameManager::isTrigger(KeybordKeyType keyType)
	{
		return m_utilityProcessManager->isTrigger(keyType);
	}
	
	tktkMath::Vector2 DX12GameManager::getLstick()
	{
		return m_utilityProcessManager->getLstick();
	}
	
	tktkMath::Vector2 DX12GameManager::getRstick()
	{
		return m_utilityProcessManager->getRstick();
	}
	
	bool DX12GameManager::isPush(GamePadBtnType btnType)
	{
		return m_utilityProcessManager->isPush(btnType);
	}
	
	bool DX12GameManager::isTrigger(GamePadBtnType btnType)
	{
		return m_utilityProcessManager->isTrigger(btnType);
	}
	
	void DX12GameManager::resetElapsedTime()
	{
		m_utilityProcessManager->resetElapsedTime();
	}
	
	float DX12GameManager::deltaTime()
	{
		return m_utilityProcessManager->deltaTime();
	}
	
	float DX12GameManager::noScaleDeltaTime()
	{
		return m_utilityProcessManager->noScaleDeltaTime();
	}
	
	float DX12GameManager::getCurTimeSec()
	{
		return m_utilityProcessManager->getCurTimeSec();
	}
	
	void DX12GameManager::setMaximumDeltaTime(float maximumDeltaTime)
	{
		m_utilityProcessManager->setMaximumDeltaTime(maximumDeltaTime);
	}
	
	float DX12GameManager::getTimeScale()
	{
		return m_utilityProcessManager->getTimeScale();
	}
	
	void DX12GameManager::setTimeScale(float timeScaleRate)
	{
		m_utilityProcessManager->setTimeScale(timeScaleRate);
	}
	
	void DX12GameManager::setBaseFps(unsigned int baseFps)
	{
		m_utilityProcessManager->setBaseFps(baseFps);
	}
	
	unsigned int DX12GameManager::getBaseFps()
	{
		return m_utilityProcessManager->getBaseFps();
	}
	
	float DX12GameManager::fps()
	{
		return m_utilityProcessManager->fps();
	}
	
	size_t DX12GameManager::getSystemHandle(SystemViewportType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemScissorRectType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemVertexBufferType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemIndexBufferType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemCBufferType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemTextureBufferType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemRtBufferType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemDsBufferType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemRootSignatureType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemPipeLineStateType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemCameraType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemLightType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemMeshType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemMeshMaterialType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	size_t DX12GameManager::getSystemHandle(SystemPostEffectMaterialType type)
	{
		return m_utilityProcessManager->getSystemHandle(type);
	}
	
	void DX12GameManager::setSystemHandle(SystemViewportType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemScissorRectType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemVertexBufferType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemIndexBufferType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemCBufferType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemTextureBufferType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemRtBufferType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemDsBufferType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemBasicDescriptorHeapType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemRtvDescriptorHeapType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemDsvDescriptorHeapType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemRootSignatureType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemPipeLineStateType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemCameraType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemLightType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemMeshType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemMeshMaterialType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	void DX12GameManager::setSystemHandle(SystemPostEffectMaterialType type, size_t handle)
	{
		m_utilityProcessManager->setSystemHandle(type, handle);
	}
	
	size_t DX12GameManager::getSceneHandle(ResourceIdCarrier id)
	{
		return m_utilityProcessManager->getSceneHandle(id);
	}
	
	size_t DX12GameManager::getSoundHandle(ResourceIdCarrier id)
	{
		return m_utilityProcessManager->getSoundHandle(id);
	}
	
	size_t DX12GameManager::getPostEffectMaterialHandle(ResourceIdCarrier id)
	{
		return m_utilityProcessManager->getPostEffectMaterialHandle(id);
	}
	
	size_t DX12GameManager::getSpriteMaterialHandle(ResourceIdCarrier id)
	{
		return m_utilityProcessManager->getSpriteMaterialHandle(id);
	}
	
	size_t DX12GameManager::getLine2DMaterialHandle(ResourceIdCarrier id)
	{
		return m_utilityProcessManager->getLine2DMaterialHandle(id);
	}
	
	size_t DX12GameManager::getBillboardMaterialHandle(ResourceIdCarrier id)
	{
		return m_utilityProcessManager->getBillboardMaterialHandle(id);
	}
	
	size_t DX12GameManager::getSkeletonHandle(ResourceIdCarrier id)
	{
		return m_utilityProcessManager->getSkeletonHandle(id);
	}
	
	size_t DX12GameManager::getMotionHandle(ResourceIdCarrier id)
	{
		return m_utilityProcessManager->getMotionHandle(id);
	}
	
	size_t DX12GameManager::getBasicMeshHandle(ResourceIdCarrier id)
	{
		return m_utilityProcessManager->getBasicMeshHandle(id);
	}
	
	size_t DX12GameManager::getBasicMeshMaterialHandle(ResourceIdCarrier id)
	{
		return m_utilityProcessManager->getBasicMeshMaterialHandle(id);
	}
	
	size_t DX12GameManager::getCameraHandle(ResourceIdCarrier id)
	{
		return m_utilityProcessManager->getCameraHandle(id);
	}
	
	size_t DX12GameManager::getLightHandle(ResourceIdCarrier id)
	{
		return m_utilityProcessManager->getLightHandle(id);
	}
}