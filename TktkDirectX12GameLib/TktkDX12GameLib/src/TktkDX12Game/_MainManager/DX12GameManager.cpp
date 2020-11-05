#include "TktkDX12Game/_MainManager/DX12GameManager.h"

#include <TktkMath/Random.h>
#include <TktkDX12Wrapper/Window/Window.h>
#include <TktkDX12Wrapper/_BaseObjects/DX3DBaseObjects.h>
#include "TktkDX12Game/GameObject/GameObjectManager.h"
#include "TktkDX12Game/GameObject/GameObject.h"
#include "TktkDX12Game/DXGameResource/DXGameResource.h"
#include "TktkDX12Game/DXGameResource/_HandleGetter/DXGameResourceHandleGetter.h"
#include "TktkDX12Game/DXGameResource/_HandleGetter/SystemDXGameResourceHandleGetter.h"
#include "TktkDX12Game/Input/Mouse/Mouse.h"
#include "TktkDX12Game/Input/DirectInputWrapper/DirectInputWrapper.h"
#include "TktkDX12Game/Input/_InputManager/InputManager.h"
#include "TktkDX12Game/Time/ElapsedTimer.h"

#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Maker/BoxMeshMaker.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Maker/SphereMeshMaker.h"

namespace tktk
{
	bool												DX12GameManager::m_isGameExit{ false };
	std::unique_ptr<GameObjectManager>					DX12GameManager::m_gameObjectManager;
	std::unique_ptr<ComponentManager>					DX12GameManager::m_componentManager;
	std::unique_ptr<Window>								DX12GameManager::m_window;
	std::unique_ptr<DX3DBaseObjects>					DX12GameManager::m_dx3dBaseObjects;
	std::unique_ptr<DXGameResource>						DX12GameManager::m_dxGameResource;
	std::unique_ptr<DXGameResourceHandleGetter>			DX12GameManager::m_resHandleGetter;
	std::unique_ptr<SystemDXGameResourceHandleGetter>	DX12GameManager::m_systemDXGameResourceHandleGetter;
	std::unique_ptr<DirectInputWrapper>					DX12GameManager::m_directInputWrapper;
	std::unique_ptr<Mouse>								DX12GameManager::m_mouse;
	std::unique_ptr<InputManager>						DX12GameManager::m_inputManager;
	std::unique_ptr<ElapsedTimer>						DX12GameManager::m_elapsedTimer;

	void DX12GameManager::initialize(const DX12GameManagerInitParam& gameManagerInitParam)
	{
		// 乱数の初期化
		tktkMath::Random::randomize();

		m_gameObjectManager		= std::make_unique<GameObjectManager>();
		m_componentManager		= std::make_unique<ComponentManager>();
		m_window				= std::make_unique<Window>(gameManagerInitParam.windowParam);

		{
			DX3DBaseObjectsInitParam dX3DBaseObjectsInitParam{};
			dX3DBaseObjectsInitParam.resourceNum		= gameManagerInitParam.dx3dResNum;
			dX3DBaseObjectsInitParam.hwnd				= m_window->getHWND();
			dX3DBaseObjectsInitParam.windowSize			= gameManagerInitParam.windowParam.windowSize;
			dX3DBaseObjectsInitParam.backGroundColor	= tktkMath::Color_v::black;
			dX3DBaseObjectsInitParam.craeteDebugLayer	= gameManagerInitParam.craeteDebugLayer;

			m_dx3dBaseObjects = std::make_unique<DX3DBaseObjects>(dX3DBaseObjectsInitParam);
		}

		{
			DXGameBaseShaderFilePaths dxGameBaseShaderFilePaths{};

#ifdef _M_AMD64 /* x64ビルドなら */

			dxGameBaseShaderFilePaths.spriteShaderFilePaths.vsFilePath								= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x64/SpriteVertexShader.cso";
			dxGameBaseShaderFilePaths.spriteShaderFilePaths.psFilePath								= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x64/SpritePixelShader.cso";
			dxGameBaseShaderFilePaths.line2DShaderFilePaths.vsFilePath								= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x64/Line2DVertexShader.cso";
			dxGameBaseShaderFilePaths.line2DShaderFilePaths.psFilePath								= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x64/Line2DPixelShader.cso";
			dxGameBaseShaderFilePaths.billboardShaderFilePaths.vsFilePath							= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x64/BillboardVertexShader.cso";
			dxGameBaseShaderFilePaths.billboardShaderFilePaths.psFilePath							= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x64/BillboardPixelShader.cso";
			dxGameBaseShaderFilePaths.meshResourceShaderFilePaths.basicShaderFilePaths.vsFilePath	= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x64/BasicMeshVertexShader.cso";
			dxGameBaseShaderFilePaths.meshResourceShaderFilePaths.basicShaderFilePaths.psFilePath	= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x64/BasicMeshPixelShader.cso";
			dxGameBaseShaderFilePaths.meshResourceShaderFilePaths.monoColorShaderPsFilePath			= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x64/BasicMonoColorMeshPixelShader.cso";
			dxGameBaseShaderFilePaths.meshResourceShaderFilePaths.writeShadowMapVsFilePath			= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x64/BasicMeshShadowVertexShader.cso";
			dxGameBaseShaderFilePaths.postEffectShaderFilePaths.postEffectVSFilePath				= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x64/PostEffectVertexShader.cso";
			dxGameBaseShaderFilePaths.postEffectShaderFilePaths.monochromePSFilePath				= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x64/MonochromePixelShader.cso";
#else

			dxGameBaseShaderFilePaths.spriteShaderFilePaths.vsFilePath								= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x86/SpriteVertexShader.cso";
			dxGameBaseShaderFilePaths.spriteShaderFilePaths.psFilePath								= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x86/SpritePixelShader.cso";
			dxGameBaseShaderFilePaths.line2DShaderFilePaths.vsFilePath								= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x86/Line2DVertexShader.cso";
			dxGameBaseShaderFilePaths.line2DShaderFilePaths.psFilePath								= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x86/Line2DPixelShader.cso";
			dxGameBaseShaderFilePaths.billboardShaderFilePaths.vsFilePath							= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x86/BillboardVertexShader.cso";
			dxGameBaseShaderFilePaths.billboardShaderFilePaths.psFilePath							= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x86/BillboardPixelShader.cso";
			dxGameBaseShaderFilePaths.meshResourceShaderFilePaths.basicShaderFilePaths.vsFilePath	= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x86/BasicMeshVertexShader.cso";
			dxGameBaseShaderFilePaths.meshResourceShaderFilePaths.basicShaderFilePaths.psFilePath	= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x86/BasicMeshPixelShader.cso";
			dxGameBaseShaderFilePaths.meshResourceShaderFilePaths.monoColorShaderPsFilePath			= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x86/BasicMonoColorMeshPixelShader.cso";
			dxGameBaseShaderFilePaths.meshResourceShaderFilePaths.writeShadowMapVsFilePath			= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x86/BasicMeshShadowVertexShader.cso";
			dxGameBaseShaderFilePaths.postEffectShaderFilePaths.postEffectVSFilePath				= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x86/PostEffectVertexShader.cso";
			dxGameBaseShaderFilePaths.postEffectShaderFilePaths.monochromePSFilePath				= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/x86/MonochromePixelShader.cso";
#endif // _M_AMD64

			

			m_dxGameResource = std::make_unique<DXGameResource>(gameManagerInitParam.dxGameResourceNum, dxGameBaseShaderFilePaths);
		}

		m_resHandleGetter		= std::make_unique<DXGameResourceHandleGetter>();
		m_systemDXGameResourceHandleGetter	= std::make_unique<SystemDXGameResourceHandleGetter>();
		m_mouse								= std::make_unique<Mouse>();
		m_directInputWrapper				= std::make_unique<DirectInputWrapper>(gameManagerInitParam.windowParam.hInstance, m_window->getHWND());
		m_elapsedTimer						= std::make_unique<ElapsedTimer>();

		// シャドウマップの深度バッファーを作る
		{
			DepthStencilBufferInitParam initParam{};
			initParam.depthStencilSize = gameManagerInitParam.windowParam.windowSize;
			initParam.useAsShaderResource = true;

			setSystemHandle(SystemDsBufferType::ShadowMap, createDsBuffer(initParam));
		}

		// シャドウマップの深度ディスクリプタヒープを作る
		{
			DsvDescriptorHeapInitParam initParam{};
			initParam.shaderVisible = false;
			initParam.descriptorParamArray.push_back({ DsvDescriptorType::normal, getSystemHandle(SystemDsBufferType::ShadowMap) });

			setSystemHandle(SystemDsvDescriptorHeapType::ShadowMap, createDsvDescriptorHeap(initParam));
		}

		// デフォルトの通常カメラを作る
		DX12GameManager::setSystemHandle(SystemCameraType::DefaultCamera, DX12GameManager::createCamera());

		// デフォルトのシャドウマップカメラを作る
		DX12GameManager::setSystemHandle(SystemCameraType::DefaultShadowMapCamera, DX12GameManager::createCamera());

		// デフォルトのライトを作る
		DX12GameManager::setSystemHandle(SystemLightType::DefaultLight, DX12GameManager::createLight({ 0.1f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 0.0f }));

		// 立方体メッシュを作る
		BoxMeshMaker::make();

		// 球体メッシュを作る
		SphereMeshMaker::make();
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
				m_elapsedTimer->update();
				m_directInputWrapper->update();
				m_mouse->update();
				m_dxGameResource->updateScene();
				m_dxGameResource->updateSound();

				// 前フレームに追加された要素をメインリストに移動する
				m_gameObjectManager->movePreFrameAddedNode();
				m_componentManager->movePreFrameAddedNode();

				// 更新処理
				m_gameObjectManager->update();
				m_componentManager->update();

				// 描画処理
				m_dx3dBaseObjects->beginDraw();
				m_componentManager->draw();
				m_dx3dBaseObjects->endDraw();

				// 死亡している要素をメインリストから削除する
				m_gameObjectManager->removeDeadObject();
				m_componentManager->removeDeadComponent();
			}
		}
		m_dxGameResource->clearSound();
	}

	void DX12GameManager::exit()
	{
		m_isGameExit = true;
	}

	const tktkMath::Vector2& DX12GameManager::getWindowSize()
	{
		return m_window->getWindowSize();
	}

	size_t DX12GameManager::addScene(const SceneDataInitParam& initParam)
	{
		return m_dxGameResource->createScene(initParam);
	}

	size_t DX12GameManager::addSceneAndAttachId(ResourceIdCarrier id, const SceneDataInitParam& initParam)
	{
		auto createdHandle = m_dxGameResource->createScene(initParam);
		m_resHandleGetter->setSceneHandle(id, createdHandle);
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
		m_gameObjectManager->runHandleMessageAll(type, attachment);
	}

	GameObjectPtr DX12GameManager::createGameObject()
	{
		return m_gameObjectManager->createGameObject();
	}

	GameObjectPtr DX12GameManager::findGameObjectWithTag(GameObjectTagCarrier tag)
	{
		return m_gameObjectManager->findGameObjectWithTag(tag);
	}

	std::forward_list<GameObjectPtr> DX12GameManager::findGameObjectsWithTag(GameObjectTagCarrier tag)
	{
		return m_gameObjectManager->findGameObjectsWithTag(tag);
	}

	void DX12GameManager::destroyGameObjectsWithTag(GameObjectTagCarrier tag)
	{
		m_gameObjectManager->destroyGameObjectsWithTag(tag);
	}

	void DX12GameManager::addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup)
	{
		m_componentManager->addCollisionGroup(firstGroup, secondGroup);
	}

	void DX12GameManager::executeCommandList()
	{
		m_dx3dBaseObjects->executeCommandList();
	}

	void DX12GameManager::setBackGroundColor(const tktkMath::Color& backGroundColor)
	{
		m_dx3dBaseObjects->setBackGroundColor(backGroundColor);
	}

	void DX12GameManager::setRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount)
	{
		m_dx3dBaseObjects->setRtv(rtvDescriptorHeapHandle, startRtvLocationIndex, rtvCount);
	}

	void DX12GameManager::setRtvAndDsv(size_t rtvDescriptorHeapHandle, size_t dsvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount)
	{
		m_dx3dBaseObjects->setRtvAndDsv(rtvDescriptorHeapHandle, dsvDescriptorHeapHandle, startRtvLocationIndex, rtvCount);
	}

	void DX12GameManager::setOnlyDsv(size_t dsvDescriptorHeapHandle)
	{
		m_dx3dBaseObjects->setOnlyDsv(dsvDescriptorHeapHandle);
	}

	void DX12GameManager::setBackBufferView()
	{
		m_dx3dBaseObjects->setBackBufferView();
	}

	void DX12GameManager::setBackBufferViewAndDsv(size_t dsvDescriptorHeapHandle)
	{
		m_dx3dBaseObjects->setBackBufferViewAndDsv(dsvDescriptorHeapHandle);
	}

	void DX12GameManager::unSetRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount)
	{
		m_dx3dBaseObjects->unSetRtv(rtvDescriptorHeapHandle, startRtvLocationIndex, rtvCount);
	}

	void DX12GameManager::unSetDsv(size_t dsvDescriptorHeapHandle)
	{
		m_dx3dBaseObjects->unSetDsv(dsvDescriptorHeapHandle);
	}

	void DX12GameManager::setViewport(size_t handle)
	{
		m_dx3dBaseObjects->setViewport(handle);
	}

	void DX12GameManager::setScissorRect(size_t handle)
	{
		m_dx3dBaseObjects->setScissorRect(handle);
	}

	void DX12GameManager::setPipeLineState(size_t handle)
	{
		m_dx3dBaseObjects->setPipeLineState(handle);
	}

	void DX12GameManager::setVertexBuffer(size_t handle)
	{
		m_dx3dBaseObjects->setVertexBuffer(handle);
	}

	void DX12GameManager::setIndexBuffer(size_t handle)
	{
		m_dx3dBaseObjects->setIndexBuffer(handle);
	}

	void DX12GameManager::setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray)
	{
		m_dx3dBaseObjects->setDescriptorHeap(heapParamArray);
	}

	void DX12GameManager::setBlendFactor(const std::array<float, 4>& blendFactor)
	{
		m_dx3dBaseObjects->setBlendFactor(blendFactor);
	}

	void DX12GameManager::setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology)
	{
		m_dx3dBaseObjects->setPrimitiveTopology(topology);
	}

	void DX12GameManager::drawInstanced(size_t vertexCountPerInstance, size_t instanceCount, size_t baseVertexLocation, size_t startInstanceLocation)
	{
		m_dx3dBaseObjects->drawInstanced(vertexCountPerInstance, instanceCount, baseVertexLocation, startInstanceLocation);
	}

	void DX12GameManager::drawIndexedInstanced(size_t indexCountPerInstance, size_t instanceCount, size_t startIndexLocation, size_t baseVertexLocation, size_t startInstanceLocation)
	{
		m_dx3dBaseObjects->drawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
	}

	size_t DX12GameManager::createRootSignature(const RootSignatureInitParam& initParam)
	{
		return m_dx3dBaseObjects->createRootSignature(initParam);
	}

	size_t DX12GameManager::createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		return m_dx3dBaseObjects->createPipeLineState(initParam, shaderFilePath);
	}

	size_t DX12GameManager::createUploadBuffer(const UploadBufferInitParam& initParam)
	{
		return m_dx3dBaseObjects->createUploadBuffer(initParam);
	}

	size_t DX12GameManager::duplicateUploadBuffer(size_t originalHandle)
	{
		return m_dx3dBaseObjects->duplicateUploadBuffer(originalHandle);
	}

	size_t DX12GameManager::createVertexBuffer(const VertexDataCarrier& vertexData)
	{
		return m_dx3dBaseObjects->createVertexBuffer(vertexData);
	}

	size_t DX12GameManager::createIndexBuffer(const std::vector<unsigned short>& indices)
	{
		return m_dx3dBaseObjects->createIndexBuffer(indices);
	}

	size_t DX12GameManager::createCBuffer(const CopySourceDataCarrier& constantBufferData)
	{
		return m_dx3dBaseObjects->createCBuffer(constantBufferData);
	}

	size_t DX12GameManager::createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		return m_dx3dBaseObjects->createRtBuffer(renderTargetSize, clearColor);
	}

	size_t DX12GameManager::createDsBuffer(const DepthStencilBufferInitParam& initParam)
	{
		return m_dx3dBaseObjects->createDsBuffer(initParam);
	}

	size_t DX12GameManager::createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam)
	{
		return m_dx3dBaseObjects->createBasicDescriptorHeap(initParam);
	}

	size_t DX12GameManager::createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam)
	{
		return m_dx3dBaseObjects->createRtvDescriptorHeap(initParam);
	}

	size_t DX12GameManager::createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam)
	{
		return m_dx3dBaseObjects->createDsvDescriptorHeap(initParam);
	}

	size_t DX12GameManager::cpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_dx3dBaseObjects->cpuPriorityCreateTextureBuffer(formatParam, dataParam);
	}

	size_t DX12GameManager::gpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_dx3dBaseObjects->gpuPriorityCreateTextureBuffer(formatParam, dataParam);
	}

	size_t DX12GameManager::cpuPriorityLoadTextureBuffer(const std::string& texDataPath)
	{
		return m_dx3dBaseObjects->cpuPriorityLoadTextureBuffer(texDataPath);
	}

	size_t DX12GameManager::gpuPriorityLoadTextureBuffer(const std::string& texDataPath)
	{
		return m_dx3dBaseObjects->gpuPriorityLoadTextureBuffer(texDataPath);
	}

	void DX12GameManager::eraseViewport(size_t handle)
	{
		m_dx3dBaseObjects->eraseViewport(handle);
	}

	void DX12GameManager::eraseScissorRect(size_t handle)
	{
		m_dx3dBaseObjects->eraseScissorRect(handle);
	}

	void DX12GameManager::eraseRootSignature(size_t handle)
	{
		m_dx3dBaseObjects->eraseRootSignature(handle);
	}

	void DX12GameManager::erasePipeLineState(size_t handle)
	{
		m_dx3dBaseObjects->erasePipeLineState(handle);
	}

	void DX12GameManager::eraseUploadBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseUploadBuffer(handle);
	}

	void DX12GameManager::eraseVertexBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseVertexBuffer(handle);
	}

	void DX12GameManager::eraseIndexBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseIndexBuffer(handle);
	}

	void DX12GameManager::eraseCBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseCBuffer(handle);
	}

	void DX12GameManager::eraseTextureBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseTextureBuffer(handle);
	}

	void DX12GameManager::eraseDsBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseDsBuffer(handle);
	}

	void DX12GameManager::eraseRtBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseRtBuffer(handle);
	}

	void DX12GameManager::eraseBasicDescriptorHeap(size_t handle)
	{
		m_dx3dBaseObjects->eraseBasicDescriptorHeap(handle);
	}

	void DX12GameManager::eraseRtvDescriptorHeap(size_t handle)
	{
		m_dx3dBaseObjects->eraseRtvDescriptorHeap(handle);
	}

	void DX12GameManager::eraseDsvDescriptorHeap(size_t handle)
	{
		m_dx3dBaseObjects->eraseDsvDescriptorHeap(handle);
	}

	void DX12GameManager::updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData)
	{
		m_dx3dBaseObjects->updateUploadBuffer(handle, bufferData);
	}

	void DX12GameManager::copyBuffer(size_t handle)
	{
		m_dx3dBaseObjects->copyBuffer(handle);
	}

	void DX12GameManager::clearRtv(size_t handle, size_t rtvLocationIndex, const tktkMath::Color& color)
	{
		m_dx3dBaseObjects->clearRtv(handle, rtvLocationIndex, color);
	}

	const tktkMath::Vector3& DX12GameManager::getTextureBufferSizePx(size_t handle)
	{
		return m_dx3dBaseObjects->getTextureBufferSizePx(handle);
	}

	const tktkMath::Vector2& DX12GameManager::getDsBufferSizePx(size_t handle)
	{
		return m_dx3dBaseObjects->getDsBufferSizePx(handle);
	}

	const tktkMath::Vector2& DX12GameManager::getRtBufferSizePx(size_t handle)
	{
		return m_dx3dBaseObjects->getRtBufferSizePx(handle);
	}

	size_t DX12GameManager::createSpriteMaterial(const SpriteMaterialInitParam& initParam)
	{
		return m_dxGameResource->createSpriteMaterial(initParam);
	}

	size_t DX12GameManager::createSpriteMaterialAndAttachId(ResourceIdCarrier id, const SpriteMaterialInitParam& initParam)
	{
		auto createdHandle = m_dxGameResource->createSpriteMaterial(initParam);
		m_resHandleGetter->setSpriteMaterialHandle(id, createdHandle);
		return createdHandle;
	}

	void DX12GameManager::drawSprite(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameResource->drawSprite(handle, drawFuncArgs);
	}

	void DX12GameManager::updateSpriteTransformCbuffer(size_t handle, size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate)
	{
		m_dxGameResource->updateSpriteTransformCbuffer(handle, copyBufferHandle, worldMatrix, spriteCenterRate);
	}

	void DX12GameManager::updateSpriteTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate, const SpriteClippingParam& clippingParam)
	{
		m_dxGameResource->updateSpriteTransformCbufferUseClippingParam(handle, copyBufferHandle, worldMatrix, spriteCenterRate, clippingParam);
	}

	size_t DX12GameManager::createLine2DMaterial()
	{
		return m_dxGameResource->createLine();
	}

	size_t DX12GameManager::createLine2DMaterialAndAttachId(ResourceIdCarrier id)
	{
		auto createdHandle = m_dxGameResource->createLine();
		m_resHandleGetter->setLine2DMaterialHandle(id, createdHandle);
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

	size_t DX12GameManager::createBillboardMaterial(const BillboardMaterialInitParam& initParam)
	{
		return m_dxGameResource->createBillboardMaterial(initParam);
	}

	size_t DX12GameManager::createBillboardMaterialAndAttachId(ResourceIdCarrier id, const BillboardMaterialInitParam& initParam)
	{
		auto createdHandle = m_dxGameResource->createBillboardMaterial(initParam);
		m_resHandleGetter->setBillboardMaterialHandle(id, createdHandle);
		return createdHandle;
	}

	void DX12GameManager::drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs)
	{
		m_dxGameResource->drawBillboard(handle, drawFuncArgs);
	}

	void DX12GameManager::updateBillboardCbuffer(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs)
	{
		m_dxGameResource->updateBillboardCbuffer(handle, copyBufferHandle, updateArgs);
	}

	void DX12GameManager::updateBillboardCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam)
	{
		m_dxGameResource->updateBillboardCbufferUseClippingParam(handle, copyBufferHandle, updateArgs, clippingParam);
	}

	size_t DX12GameManager::createBasicMesh(const BasicMeshInitParam& initParam)
	{
		return m_dxGameResource->createBasicMesh(initParam);
	}

	size_t DX12GameManager::createBasicMeshAndAttachId(ResourceIdCarrier id, const BasicMeshInitParam& initParam)
	{
		auto createdHandle = m_dxGameResource->createBasicMesh(initParam);
		m_resHandleGetter->setBasicMeshHandle(id, createdHandle);
		return createdHandle;
	}

	size_t DX12GameManager::copyBasicMesh(size_t originalHandle)
	{
		return m_dxGameResource->copyBasicMesh(originalHandle);
	}

	size_t DX12GameManager::copyBasicMeshAndAttachId(ResourceIdCarrier id, size_t originalHandle)
	{
		auto createdHandle = m_dxGameResource->copyBasicMesh(originalHandle);
		m_resHandleGetter->setBasicMeshHandle(id, createdHandle);
		return createdHandle;
	}

	size_t DX12GameManager::createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam)
	{
		return m_dxGameResource->createBasicMeshMaterial(initParam);
	}

	size_t DX12GameManager::createBasicMeshMaterialAndAttachId(ResourceIdCarrier id, const BasicMeshMaterialInitParam& initParam)
	{
		auto createdHandle = m_dxGameResource->createBasicMeshMaterial(initParam);
		m_resHandleGetter->setBasicMeshMaterialHandle(id, createdHandle);
		return createdHandle;
	}

	size_t DX12GameManager::copyBasicMeshMaterial(size_t originalHandle)
	{
		return m_dxGameResource->copyBasicMeshMaterial(originalHandle);
	}

	size_t DX12GameManager::copyBasicMeshMaterialAndAttachId(ResourceIdCarrier id, size_t originalHandle)
	{
		auto createdHandle = m_dxGameResource->copyBasicMeshMaterial(m_resHandleGetter->getBasicMeshMaterialHandle(id));
		m_resHandleGetter->setBasicMeshMaterialHandle(id, createdHandle);
		return createdHandle;
	}

	void DX12GameManager::setMaterialHandle(size_t handle, size_t materialSlot, size_t materialHandle)
	{
		m_dxGameResource->setMaterialHandle(handle, materialSlot, materialHandle);
	}

	void DX12GameManager::writeBasicMeshShadowMap(size_t handle)
	{
		m_dxGameResource->writeBasicMeshShadowMap(handle);
	}

	void DX12GameManager::setMaterialData(size_t handle)
	{
		m_dxGameResource->setMaterialData(handle);
	}

	void DX12GameManager::drawBasicMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs)
	{
		m_dxGameResource->drawBasicMesh(handle, baseArgs);
	}

	BasicMeshLoadPmdReturnValue DX12GameManager::loadPmd(const BasicMeshLoadPmdArgs& args)
	{
		return m_dxGameResource->loadPmd(args);
	}

	BasicMeshLoadPmxReturnValue DX12GameManager::loadPmx(const BasicMeshLoadPmxArgs& args)
	{
		return m_dxGameResource->loadPmx(args);
	}

	size_t DX12GameManager::createSkeleton(const SkeletonInitParam& initParam)
	{
		return m_dxGameResource->createSkeleton(initParam);
	}

	size_t DX12GameManager::copySkeleton(size_t originalHandle)
	{
		return m_dxGameResource->copySkeleton(originalHandle);
	}

	size_t DX12GameManager::createSkeletonUploadBufferHandle(size_t handle)
	{
		return m_dxGameResource->createSkeletonUploadBufferHandle(handle);
	}

	size_t DX12GameManager::createSkeletonAndAttachId(ResourceIdCarrier id, const SkeletonInitParam& initParam)
	{
		auto createdHandle = m_dxGameResource->createSkeleton(initParam);
		m_resHandleGetter->setSkeletonHandle(id, createdHandle);
		return createdHandle;
	}

	void DX12GameManager::updateBoneMatrixCbuffer(size_t handle, size_t copyBufferHandle)
	{
		m_dxGameResource->updateBoneMatrixCbuffer(handle, copyBufferHandle);
	}

	void DX12GameManager::resetBoneMatrixCbuffer()
	{
		m_dxGameResource->resetBoneMatrixCbuffer();
	}

	size_t DX12GameManager::loadMotion(const std::string& motionFileName)
	{
		return m_dxGameResource->loadMotion(motionFileName);
	}

	size_t DX12GameManager::loadMotionAndAttachId(ResourceIdCarrier id, const std::string& motionFileName)
	{
		auto createdHandle = m_dxGameResource->loadMotion(motionFileName);
		m_resHandleGetter->setMotionHandle(id, createdHandle);
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
		size_t curFrame,
		size_t preFrame,
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

	size_t DX12GameManager::createPostEffectMaterial(const PostEffectMaterialInitParam& initParam)
	{
		return m_dxGameResource->createPostEffectMaterial(initParam);
	}

	size_t DX12GameManager::createPostEffectMaterialAndAttachId(ResourceIdCarrier id, const PostEffectMaterialInitParam& initParam)
	{
		auto createdhandle = m_dxGameResource->createPostEffectMaterial(initParam);
		m_resHandleGetter->setPostEffectMaterialHandle(id, createdhandle);
		return createdhandle;
	}

	void DX12GameManager::drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameResource->drawPostEffect(handle, drawFuncArgs);
	}

	size_t DX12GameManager::createCamera()
	{
		return m_dxGameResource->createCamera();
	}

	size_t DX12GameManager::createCameraAndAttachId(ResourceIdCarrier id)
	{
		auto createdHandle = m_dxGameResource->createCamera();
		m_resHandleGetter->setCameraHandle(id, createdHandle);
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
		m_resHandleGetter->setLightHandle(id, createdHandle);
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
		m_resHandleGetter->setSoundHandle(id, createdhandle);
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

	bool DX12GameManager::isPushCommand(int commandId)
	{
		return m_inputManager->isPush(commandId);
	}

	bool DX12GameManager::isTriggerCommand(int commandId)
	{
		return m_inputManager->isTrigger(commandId);
	}

	const tktkMath::Vector2& DX12GameManager::moveVec()
	{
		return m_inputManager->moveVec();
	}

	const tktkMath::Vector2& DX12GameManager::lookVec()
	{
		return m_inputManager->lookVec();
	}

	void DX12GameManager::addCommand(int commandId, KeybordKeyType keyType)
	{
		m_inputManager->addCommand(commandId, keyType);
	}

	void DX12GameManager::addCommand(int commandId, GamePadBtnType btnType)
	{
		m_inputManager->addCommand(commandId, btnType);
	}

	void DX12GameManager::addCommand(int commandId, MouseButtonType btnType)
	{
		m_inputManager->addCommand(commandId, btnType);
	}

	void DX12GameManager::addDirectionCommand(DirectionCommandType directionCommand, KeybordKeyType keyType)
	{
		m_inputManager->addDirectionCommand(directionCommand, keyType);
	}

	void DX12GameManager::addDirectionCommand(DirectionCommandType directionCommand, GamePadBtnType btnType)
	{
		m_inputManager->addDirectionCommand(directionCommand, btnType);
	}

	void DX12GameManager::addDirectionCommand(DirectionCommandType directionCommand, MouseButtonType btnType)
	{
		m_inputManager->addDirectionCommand(directionCommand, btnType);
	}

	bool DX12GameManager::isMousePush(MouseButtonType buttonType)
	{
		return m_mouse->isPush(buttonType);
	}

	bool DX12GameManager::isMouseTrigger(MouseButtonType buttonType)
	{
		return m_mouse->isTrigger(buttonType);
	}

	tktkMath::Vector2 DX12GameManager::mousePos()
	{
		return m_mouse->mousePos(m_window->getHWND());
	}

	bool DX12GameManager::isKeybordPush(KeybordKeyType keyType)
	{
		return m_directInputWrapper->isPush(keyType);
	}

	bool DX12GameManager::isKeybordTrigger(KeybordKeyType keyType)
	{
		return m_directInputWrapper->isTrigger(keyType);
	}

	tktkMath::Vector2 DX12GameManager::getLstick()
	{
		return m_directInputWrapper->getLstick();
	}

	tktkMath::Vector2 DX12GameManager::getRstick()
	{
		return m_directInputWrapper->getRstick();
	}

	bool DX12GameManager::isPadPush(GamePadBtnType btnType)
	{
		return m_directInputWrapper->isPush(btnType);
	}

	bool DX12GameManager::isPadTrigger(GamePadBtnType btnType)
	{
		return m_directInputWrapper->isTrigger(btnType);
	}

	void DX12GameManager::resetElapsedTime()
	{
		m_elapsedTimer->reset();
	}

	float DX12GameManager::deltaTime()
	{
		return m_elapsedTimer->deltaTime();
	}

	float DX12GameManager::noScaleDeltaTime()
	{
		return m_elapsedTimer->noScaleDeltaTime();
	}

	float DX12GameManager::getCurTimeSec()
	{
		return m_elapsedTimer->getCurTimeSec();
	}

	void DX12GameManager::setMaximumDeltaTime(float maximumDeltaTime)
	{
		m_elapsedTimer->setMaximumDeltaTime(maximumDeltaTime);
	}

	float DX12GameManager::getTimeScale()
	{
		return m_elapsedTimer->getTimeScale();
	}

	void DX12GameManager::setTimeScale(float timeScaleRate)
	{
		m_elapsedTimer->setTimeScale(timeScaleRate);
	}

	void DX12GameManager::setBaseFps(unsigned int baseFps)
	{
		m_elapsedTimer->setBaseFps(baseFps);
	}

	unsigned int DX12GameManager::getBaseFps()
	{
		return m_elapsedTimer->getBaseFps();
	}

	float DX12GameManager::fps()
	{
		return m_elapsedTimer->fps();
	}

	size_t DX12GameManager::getSystemHandle(SystemViewportType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemScissorRectType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemVertexBufferType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemIndexBufferType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemCBufferType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemTextureBufferType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemDsBufferType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemRootSignatureType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemPipeLineStateType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemCameraType type)
	{
		return m_systemDXGameResourceHandleGetter->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemLightType type)
	{
		return m_systemDXGameResourceHandleGetter->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemBasicMeshType type)
	{
		return m_systemDXGameResourceHandleGetter->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType type)
	{
		return m_systemDXGameResourceHandleGetter->getSystemHandle(type);
	}

	size_t DX12GameManager::getSystemHandle(SystemPostEffectMaterialType type)
	{
		return m_systemDXGameResourceHandleGetter->getSystemHandle(type);
	}

	void DX12GameManager::setSystemHandle(SystemViewportType type, size_t handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemScissorRectType type, size_t handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemVertexBufferType type, size_t handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemIndexBufferType type, size_t handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemCBufferType type, size_t handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemTextureBufferType type, size_t handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemRtBufferType type, size_t handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemDsBufferType type, size_t handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemBasicDescriptorHeapType type, size_t handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemRtvDescriptorHeapType type, size_t handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemDsvDescriptorHeapType type, size_t handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemRootSignatureType type, size_t handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemPipeLineStateType type, size_t handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemCameraType type, size_t handle)
	{
		m_systemDXGameResourceHandleGetter->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemLightType type, size_t handle)
	{
		m_systemDXGameResourceHandleGetter->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemBasicMeshType type, size_t handle)
	{
		m_systemDXGameResourceHandleGetter->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemBasicMeshMaterialType type, size_t handle)
	{
		m_systemDXGameResourceHandleGetter->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemPostEffectMaterialType type, size_t handle)
	{
		m_systemDXGameResourceHandleGetter->setSystemHandle(type, handle);
	}

	void DX12GameManager::addMaterialAppendParamImpl(size_t handle, size_t cbufferHandle, size_t dataSize, void* dataTopPos)
	{
		m_dxGameResource->addMaterialAppendParam(handle, cbufferHandle, dataSize, dataTopPos);
	}

	void DX12GameManager::updateMaterialAppendParamImpl(size_t handle, size_t cbufferHandle, size_t dataSize, const void* dataTopPos)
	{
		m_dxGameResource->updateMaterialAppendParam(handle, cbufferHandle, dataSize, dataTopPos);
	}

	size_t DX12GameManager::getSceneHandle(ResourceIdCarrier id)
	{
		return m_resHandleGetter->getSceneHandle(id);
	}

	size_t DX12GameManager::getSoundHandle(ResourceIdCarrier id)
	{
		return m_resHandleGetter->getSoundHandle(id);
	}

	size_t DX12GameManager::getPostEffectMaterialHandle(ResourceIdCarrier id)
	{
		return m_resHandleGetter->getPostEffectMaterialHandle(id);
	}

	size_t DX12GameManager::getSpriteMaterialHandle(ResourceIdCarrier id)
	{
		return m_resHandleGetter->getSpriteMaterialHandle(id);
	}

	size_t DX12GameManager::getLine2DMaterialHandle(ResourceIdCarrier id)
	{
		return m_resHandleGetter->getLine2DMaterialHandle(id);
	}

	size_t DX12GameManager::getBillboardMaterialHandle(ResourceIdCarrier id)
	{
		return m_resHandleGetter->getBillboardMaterialHandle(id);
	}

	size_t DX12GameManager::getSkeletonHandle(ResourceIdCarrier id)
	{
		return m_resHandleGetter->getSkeletonHandle(id);
	}

	size_t DX12GameManager::getMotionHandle(ResourceIdCarrier id)
	{
		return m_resHandleGetter->getMotionHandle(id);
	}

	size_t DX12GameManager::getBasicMeshHandle(ResourceIdCarrier id)
	{
		return m_resHandleGetter->getBasicMeshHandle(id);
	}

	size_t DX12GameManager::getBasicMeshMaterialHandle(ResourceIdCarrier id)
	{
		return m_resHandleGetter->getBasicMeshMaterialHandle(id);
	}

	size_t DX12GameManager::getCameraHandle(ResourceIdCarrier id)
	{
		return m_resHandleGetter->getCameraHandle(id);
	}

	size_t DX12GameManager::getLightHandle(ResourceIdCarrier id)
	{
		return m_resHandleGetter->getLightHandle(id);
	}
}