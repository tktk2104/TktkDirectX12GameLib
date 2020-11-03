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
	std::unique_ptr<DXGameResourceHandleGetter>			DX12GameManager::m_dxGameResourceHandleGetter;
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

		m_dxGameResourceHandleGetter		= std::make_unique<DXGameResourceHandleGetter>();
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

	void DX12GameManager::enableScene(unsigned int handle)
	{
		m_dxGameResource->enableScene(handle);
	}

	void DX12GameManager::disableScene(unsigned int handle)
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

	void DX12GameManager::executeCommandList()
	{
		m_dx3dBaseObjects->executeCommandList();
	}

	void DX12GameManager::setBackGroundColor(const tktkMath::Color& backGroundColor)
	{
		m_dx3dBaseObjects->setBackGroundColor(backGroundColor);
	}

	void DX12GameManager::setRtv(unsigned int rtvDescriptorHeapHandle, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dx3dBaseObjects->setRtv(rtvDescriptorHeapHandle, startRtvLocationIndex, rtvCount);
	}

	void DX12GameManager::setRtvAndDsv(unsigned int rtvDescriptorHeapHandle, unsigned int dsvDescriptorHeapHandle, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dx3dBaseObjects->setRtvAndDsv(rtvDescriptorHeapHandle, dsvDescriptorHeapHandle, startRtvLocationIndex, rtvCount);
	}

	void DX12GameManager::setOnlyDsv(unsigned int dsvDescriptorHeapHandle)
	{
		m_dx3dBaseObjects->setOnlyDsv(dsvDescriptorHeapHandle);
	}

	void DX12GameManager::setBackBufferView()
	{
		m_dx3dBaseObjects->setBackBufferView();
	}

	void DX12GameManager::setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapHandle)
	{
		m_dx3dBaseObjects->setBackBufferViewAndDsv(dsvDescriptorHeapHandle);
	}

	void DX12GameManager::unSetRtv(unsigned int rtvDescriptorHeapHandle, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dx3dBaseObjects->unSetRtv(rtvDescriptorHeapHandle, startRtvLocationIndex, rtvCount);
	}

	void DX12GameManager::unSetDsv(unsigned int dsvDescriptorHeapHandle)
	{
		m_dx3dBaseObjects->unSetDsv(dsvDescriptorHeapHandle);
	}

	void DX12GameManager::setViewport(unsigned int handle)
	{
		m_dx3dBaseObjects->setViewport(handle);
	}

	void DX12GameManager::setScissorRect(unsigned int handle)
	{
		m_dx3dBaseObjects->setScissorRect(handle);
	}

	void DX12GameManager::setPipeLineState(unsigned int handle)
	{
		m_dx3dBaseObjects->setPipeLineState(handle);
	}

	void DX12GameManager::setVertexBuffer(unsigned int handle)
	{
		m_dx3dBaseObjects->setVertexBuffer(handle);
	}

	void DX12GameManager::setIndexBuffer(unsigned int handle)
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

	void DX12GameManager::drawInstanced(unsigned int vertexCountPerInstance, unsigned int instanceCount, unsigned int baseVertexLocation, unsigned int startInstanceLocation)
	{
		m_dx3dBaseObjects->drawInstanced(vertexCountPerInstance, instanceCount, baseVertexLocation, startInstanceLocation);
	}

	void DX12GameManager::drawIndexedInstanced(unsigned int indexCountPerInstance, unsigned int instanceCount, unsigned int startIndexLocation, unsigned int baseVertexLocation, unsigned int startInstanceLocation)
	{
		m_dx3dBaseObjects->drawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
	}

	unsigned int DX12GameManager::createRootSignature(const RootSignatureInitParam& initParam)
	{
		return m_dx3dBaseObjects->createRootSignature(initParam);
	}

	unsigned int DX12GameManager::createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		return m_dx3dBaseObjects->createPipeLineState(initParam, shaderFilePath);
	}

	unsigned int DX12GameManager::copyCopyBuffer(unsigned int originalHandle)
	{
		return m_dx3dBaseObjects->copyCopyBuffer(originalHandle);
	}

	unsigned int DX12GameManager::createIndexBuffer(const std::vector<unsigned short>& indices)
	{
		return m_dx3dBaseObjects->createIndexBuffer(indices);
	}

	unsigned int DX12GameManager::createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		return m_dx3dBaseObjects->createRtBuffer(renderTargetSize, clearColor);
	}

	unsigned int DX12GameManager::createDsBuffer(const DepthStencilBufferInitParam& initParam)
	{
		return m_dx3dBaseObjects->createDsBuffer(initParam);
	}

	unsigned int DX12GameManager::createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam)
	{
		return m_dx3dBaseObjects->createBasicDescriptorHeap(initParam);
	}

	unsigned int DX12GameManager::createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam)
	{
		return m_dx3dBaseObjects->createRtvDescriptorHeap(initParam);
	}

	unsigned int DX12GameManager::createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam)
	{
		return m_dx3dBaseObjects->createDsvDescriptorHeap(initParam);
	}

	unsigned int DX12GameManager::cpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_dx3dBaseObjects->cpuPriorityCreateTextureBuffer(formatParam, dataParam);
	}

	unsigned int DX12GameManager::gpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_dx3dBaseObjects->gpuPriorityCreateTextureBuffer(formatParam, dataParam);
	}

	unsigned int DX12GameManager::cpuPriorityLoadTextureBuffer(const std::string& texDataPath)
	{
		return m_dx3dBaseObjects->cpuPriorityLoadTextureBuffer(texDataPath);
	}

	unsigned int DX12GameManager::gpuPriorityLoadTextureBuffer(const std::string& texDataPath)
	{
		return m_dx3dBaseObjects->gpuPriorityLoadTextureBuffer(texDataPath);
	}

	void DX12GameManager::eraseViewport(unsigned int handle)
	{
		m_dx3dBaseObjects->eraseViewport(handle);
	}

	void DX12GameManager::eraseScissorRect(unsigned int handle)
	{
		m_dx3dBaseObjects->eraseScissorRect(handle);
	}

	void DX12GameManager::eraseRootSignature(unsigned int handle)
	{
		m_dx3dBaseObjects->eraseRootSignature(handle);
	}

	void DX12GameManager::erasePipeLineState(unsigned int handle)
	{
		m_dx3dBaseObjects->erasePipeLineState(handle);
	}

	void DX12GameManager::eraseCopyBuffer(unsigned int handle)
	{
		m_dx3dBaseObjects->eraseCopyBuffer(handle);
	}

	void DX12GameManager::eraseVertexBuffer(unsigned int handle)
	{
		m_dx3dBaseObjects->eraseVertexBuffer(handle);
	}

	void DX12GameManager::eraseIndexBuffer(unsigned int handle)
	{
		m_dx3dBaseObjects->eraseIndexBuffer(handle);
	}

	void DX12GameManager::eraseCBuffer(unsigned int handle)
	{
		m_dx3dBaseObjects->eraseCBuffer(handle);
	}

	void DX12GameManager::eraseTextureBuffer(unsigned int handle)
	{
		m_dx3dBaseObjects->eraseTextureBuffer(handle);
	}

	void DX12GameManager::eraseDsBuffer(unsigned int handle)
	{
		m_dx3dBaseObjects->eraseDsBuffer(handle);
	}

	void DX12GameManager::eraseRtBuffer(unsigned int handle)
	{
		m_dx3dBaseObjects->eraseRtBuffer(handle);
	}

	void DX12GameManager::eraseBasicDescriptorHeap(unsigned int handle)
	{
		m_dx3dBaseObjects->eraseBasicDescriptorHeap(handle);
	}

	void DX12GameManager::eraseRtvDescriptorHeap(unsigned int handle)
	{
		m_dx3dBaseObjects->eraseRtvDescriptorHeap(handle);
	}

	void DX12GameManager::eraseDsvDescriptorHeap(unsigned int handle)
	{
		m_dx3dBaseObjects->eraseDsvDescriptorHeap(handle);
	}

	void DX12GameManager::copyBuffer(unsigned int handle)
	{
		m_dx3dBaseObjects->copyBuffer(handle);
	}

	void DX12GameManager::clearRtv(unsigned int handle, unsigned int rtvLocationIndex, const tktkMath::Color& color)
	{
		m_dx3dBaseObjects->clearRtv(handle, rtvLocationIndex, color);
	}

	const tktkMath::Vector3& DX12GameManager::getTextureBufferSizePx(unsigned int handle)
	{
		return m_dx3dBaseObjects->getTextureBufferSizePx(handle);
	}

	const tktkMath::Vector2& DX12GameManager::getDsBufferSizePx(unsigned int handle)
	{
		return m_dx3dBaseObjects->getDsBufferSizePx(handle);
	}

	const tktkMath::Vector2& DX12GameManager::getRtBufferSizePx(unsigned int handle)
	{
		return m_dx3dBaseObjects->getRtBufferSizePx(handle);
	}

	unsigned int DX12GameManager::createSpriteMaterial(const SpriteMaterialInitParam& initParam)
	{
		return m_dxGameResource->createSpriteMaterial(initParam);
	}

	void DX12GameManager::drawSprite(unsigned int handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameResource->drawSprite(handle, drawFuncArgs);
	}

	void DX12GameManager::updateSpriteTransformCbuffer(unsigned int handle, unsigned int copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate)
	{
		m_dxGameResource->updateSpriteTransformCbuffer(handle, copyBufferHandle, worldMatrix, spriteCenterRate);
	}

	void DX12GameManager::updateSpriteTransformCbufferUseClippingParam(unsigned int handle, unsigned int copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate, const SpriteClippingParam& clippingParam)
	{
		m_dxGameResource->updateSpriteTransformCbufferUseClippingParam(handle, copyBufferHandle, worldMatrix, spriteCenterRate, clippingParam);
	}

	unsigned int DX12GameManager::createLine2DMaterial()
	{
		return m_dxGameResource->createLine();
	}

	void DX12GameManager::drawLine(unsigned int handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameResource->drawLine(handle, drawFuncArgs);
	}

	unsigned int DX12GameManager::createBillboardMaterial(const BillboardMaterialInitParam& initParam)
	{
		return m_dxGameResource->createBillboardMaterial(initParam);
	}

	void DX12GameManager::drawBillboard(unsigned int handle, const BillboardDrawFuncBaseArgs& drawFuncArgs)
	{
		m_dxGameResource->drawBillboard(handle, drawFuncArgs);
	}

	void DX12GameManager::updateBillboardCbuffer(unsigned int handle, unsigned int copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs)
	{
		m_dxGameResource->updateBillboardCbuffer(handle, copyBufferHandle, updateArgs);
	}

	void DX12GameManager::updateBillboardCbufferUseClippingParam(unsigned int handle, unsigned int copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam)
	{
		m_dxGameResource->updateBillboardCbufferUseClippingParam(handle, copyBufferHandle, updateArgs, clippingParam);
	}

	unsigned int DX12GameManager::createBasicMesh(const BasicMeshInitParam& initParam)
	{
		return m_dxGameResource->createBasicMesh(initParam);
	}

	unsigned int DX12GameManager::copyBasicMesh(unsigned int originalHandle)
	{
		return m_dxGameResource->copyBasicMesh(originalHandle);
	}

	unsigned int DX12GameManager::createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam)
	{
		return m_dxGameResource->createBasicMeshMaterial(initParam);
	}

	unsigned int DX12GameManager::copyBasicMeshMaterial(unsigned int originalHandle)
	{
		return m_dxGameResource->copyBasicMeshMaterial(originalHandle);
	}

	void DX12GameManager::setMaterialHandle(unsigned int meshHandle, unsigned int materialSlot, unsigned int materialHandle)
	{
		m_dxGameResource->setMaterialHandle(meshHandle, materialSlot, materialHandle);
	}

	void DX12GameManager::writeBasicMeshShadowMap(unsigned int handle)
	{
		m_dxGameResource->writeBasicMeshShadowMap(handle);
	}

	void DX12GameManager::setMaterialData(unsigned int handle)
	{
		m_dxGameResource->setMaterialData(handle);
	}

	void DX12GameManager::drawBasicMesh(unsigned int handle, const MeshDrawFuncBaseArgs& baseArgs)
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

	unsigned int DX12GameManager::createSkeleton(const SkeletonInitParam& initParam)
	{
		return m_dxGameResource->createSkeleton(initParam);
	}

	unsigned int DX12GameManager::copySkeleton(unsigned int originalHandle)
	{
		return m_dxGameResource->copySkeleton(originalHandle);
	}

	unsigned int DX12GameManager::createSkeletonCopyBufferHandle(unsigned int handle)
	{
		return m_dxGameResource->createSkeletonCopyBufferHandle(handle);
	}

	void DX12GameManager::updateBoneMatrixCbuffer(unsigned int handle, unsigned int copyBufferHandle)
	{
		m_dxGameResource->updateBoneMatrixCbuffer(handle, copyBufferHandle);
	}

	void DX12GameManager::resetBoneMatrixCbuffer()
	{
		m_dxGameResource->resetBoneMatrixCbuffer();
	}

	unsigned int DX12GameManager::loadMotion(const std::string& motionFileName)
	{
		return m_dxGameResource->loadMotion(motionFileName);
	}

	unsigned int DX12GameManager::getMotionEndFrameNo(unsigned int handle)
	{
		return m_dxGameResource->getMotionEndFrameNo(handle);
	}

	void DX12GameManager::updateMotion(
		unsigned int skeletonHandle,
		unsigned int curMotionHandle,
		unsigned int preMotionHandle,
		unsigned int curFrame,
		unsigned int preFrame,
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

	unsigned int DX12GameManager::createPostEffectMaterial(const PostEffectMaterialInitParam& initParam)
	{
		return m_dxGameResource->createPostEffectMaterial(initParam);
	}

	void DX12GameManager::drawPostEffect(unsigned int handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameResource->drawPostEffect(handle, drawFuncArgs);
	}

	unsigned int DX12GameManager::createCamera()
	{
		return m_dxGameResource->createCamera();
	}

	const tktkMath::Matrix4& DX12GameManager::getViewMatrix(unsigned int cameraHandle)
	{
		return m_dxGameResource->getViewMatrix(cameraHandle);
	}

	void DX12GameManager::setViewMatrix(unsigned int cameraHandle, const tktkMath::Matrix4& view)
	{
		m_dxGameResource->setViewMatrix(cameraHandle, view);
	}

	const tktkMath::Matrix4& DX12GameManager::getProjectionMatrix(unsigned int cameraHandle)
	{
		return m_dxGameResource->getProjectionMatrix(cameraHandle);
	}

	void DX12GameManager::setProjectionMatrix(unsigned int cameraHandle, const tktkMath::Matrix4& projection)
	{
		m_dxGameResource->setProjectionMatrix(cameraHandle, projection);
	}

	unsigned int DX12GameManager::createLight(const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular, const tktkMath::Vector3& position)
	{
		return m_dxGameResource->createLight(ambient, diffuse, speqular, position);
	}

	void DX12GameManager::updateLightCBuffer(unsigned int handle)
	{
		m_dxGameResource->updateLightCBuffer(handle);
	}

	void DX12GameManager::setLightAmbient(unsigned int handle, const tktkMath::Color& ambient)
	{
		m_dxGameResource->setLightAmbient(handle, ambient);
	}

	void DX12GameManager::setLightDiffuse(unsigned int handle, const tktkMath::Color& diffuse)
	{
		m_dxGameResource->setLightDiffuse(handle, diffuse);
	}

	void DX12GameManager::setLightSpeqular(unsigned int handle, const tktkMath::Color& speqular)
	{
		m_dxGameResource->setLightSpeqular(handle, speqular);
	}

	void DX12GameManager::setLightPosition(unsigned int handle, const tktkMath::Vector3& position)
	{
		m_dxGameResource->setLightPosition(handle, position);
	}

	unsigned int DX12GameManager::loadSound(const std::string& fileName)
	{
		return m_dxGameResource->loadSound(fileName);
	}

	void DX12GameManager::playSound(unsigned int handle, bool loopPlay)
	{
		m_dxGameResource->playSound(handle, loopPlay);
	}

	void DX12GameManager::stopSound(unsigned int handle)
	{
		m_dxGameResource->stopSound(handle);
	}

	void DX12GameManager::pauseSound(unsigned int handle)
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

	void DX12GameManager::setSceneHandle(int id, unsigned int handle)
	{
		m_dxGameResourceHandleGetter->setSceneHandle(id, handle);
	}

	void DX12GameManager::setSoundHandle(int id, unsigned int handle)
	{
		m_dxGameResourceHandleGetter->setSoundHandle(id, handle);
	}

	void DX12GameManager::setPostEffectMaterialHandle(int id, unsigned int handle)
	{
		m_dxGameResourceHandleGetter->setPostEffectMaterialHandle(id, handle);
	}

	void DX12GameManager::setSpriteMaterialHandle(int id, unsigned int handle)
	{
		m_dxGameResourceHandleGetter->setSpriteMaterialHandle(id, handle);
	}

	void DX12GameManager::setLine2DMaterialHandle(int id, unsigned int handle)
	{
		m_dxGameResourceHandleGetter->setLine2DMaterialHandle(id, handle);
	}

	void DX12GameManager::setBillboardMaterialHandle(int id, unsigned int handle)
	{
		m_dxGameResourceHandleGetter->setBillboardMaterialHandle(id, handle);
	}

	void DX12GameManager::setSkeletonHandle(int id, unsigned int handle)
	{
		m_dxGameResourceHandleGetter->setSkeletonHandle(id, handle);
	}

	void DX12GameManager::setMotionHandle(int id, unsigned int handle)
	{
		m_dxGameResourceHandleGetter->setMotionHandle(id, handle);
	}

	void DX12GameManager::setBasicMeshHandle(int id, unsigned int handle)
	{
		m_dxGameResourceHandleGetter->setBasicMeshHandle(id, handle);
	}

	void DX12GameManager::setBasicMeshMaterialHandle(int id, unsigned int handle)
	{
		m_dxGameResourceHandleGetter->setBasicMeshMaterialHandle(id, handle);
	}

	void DX12GameManager::setCameraHandle(int id, unsigned int handle)
	{
		m_dxGameResourceHandleGetter->setCameraHandle(id, handle);
	}

	void DX12GameManager::setLightHandle(int id, unsigned int handle)
	{
		m_dxGameResourceHandleGetter->setLightHandle(id, handle);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemViewportType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemScissorRectType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemVertexBufferType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemIndexBufferType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemCBufferType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemTextureBufferType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemDsBufferType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemRootSignatureType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemPipeLineStateType type)
	{
		return m_dx3dBaseObjects->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemCameraType type)
	{
		return m_systemDXGameResourceHandleGetter->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemLightType type)
	{
		return m_systemDXGameResourceHandleGetter->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemBasicMeshType type)
	{
		return m_systemDXGameResourceHandleGetter->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType type)
	{
		return m_systemDXGameResourceHandleGetter->getSystemHandle(type);
	}

	unsigned int DX12GameManager::getSystemHandle(SystemPostEffectMaterialType type)
	{
		return m_systemDXGameResourceHandleGetter->getSystemHandle(type);
	}

	void DX12GameManager::setSystemHandle(SystemViewportType type, unsigned int handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemScissorRectType type, unsigned int handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemVertexBufferType type, unsigned int handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemIndexBufferType type, unsigned int handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemCBufferType type, unsigned int handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemTextureBufferType type, unsigned int handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemRtBufferType type, unsigned int handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemDsBufferType type, unsigned int handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemBasicDescriptorHeapType type, unsigned int handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemRtvDescriptorHeapType type, unsigned int handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemDsvDescriptorHeapType type, unsigned int handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemRootSignatureType type, unsigned int handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemPipeLineStateType type, unsigned int handle)
	{
		m_dx3dBaseObjects->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemCameraType type, unsigned int handle)
	{
		m_systemDXGameResourceHandleGetter->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemLightType type, unsigned int handle)
	{
		m_systemDXGameResourceHandleGetter->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemBasicMeshType type, unsigned int handle)
	{
		m_systemDXGameResourceHandleGetter->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemBasicMeshMaterialType type, unsigned int handle)
	{
		m_systemDXGameResourceHandleGetter->setSystemHandle(type, handle);
	}

	void DX12GameManager::setSystemHandle(SystemPostEffectMaterialType type, unsigned int handle)
	{
		m_systemDXGameResourceHandleGetter->setSystemHandle(type, handle);
	}

	void DX12GameManager::addCollisionGroupImpl(int firstGroup, int secondGroup)
	{
		m_componentManager->addCollisionGroup(firstGroup, secondGroup);
	}

	unsigned int DX12GameManager::createCopyBufferImpl(const CopyBufferInitParam& initParam)
	{
		return m_dx3dBaseObjects->createCopyBuffer(initParam);
	}

	unsigned int DX12GameManager::createVertexBufferImpl(unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		return m_dx3dBaseObjects->createVertexBuffer(vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	unsigned int DX12GameManager::createCbufferImpl(unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		return m_dx3dBaseObjects->createCBuffer(constantBufferTypeSize, constantBufferDataTopPos);
	}

	unsigned int DX12GameManager::createSceneImpl(const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr)
	{
		return m_dxGameResource->createScene(scenePtr, vtablePtr);
	}

	void DX12GameManager::setSceneEndDestroyGameObjectTagImpl(unsigned int handle, int tag)
	{
		return m_dxGameResource->setSceneEndDestroyGameObjectTag(handle, tag);
	}

	void DX12GameManager::updateCopyBufferImpl(unsigned int handle, unsigned int bufferSize, const void* bufferDataTopPos)
	{
		m_dx3dBaseObjects->updateCopyBuffer(handle, bufferSize, bufferDataTopPos);
	}

	void DX12GameManager::addMaterialAppendParamImpl(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos)
	{
		m_dxGameResource->addMaterialAppendParam(handle, cbufferHandle, dataSize, dataTopPos);
	}

	void DX12GameManager::updateMaterialAppendParamImpl(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, const void* dataTopPos)
	{
		m_dxGameResource->updateMaterialAppendParam(handle, cbufferHandle, dataSize, dataTopPos);
	}

	unsigned int DX12GameManager::getSceneHandleImpl(int id)
	{
		return m_dxGameResourceHandleGetter->getSceneHandle(id);
	}

	unsigned int DX12GameManager::getSoundHandleImpl(int id)
	{
		return m_dxGameResourceHandleGetter->getSoundHandle(id);
	}

	unsigned int DX12GameManager::getPostEffectMaterialHandleImpl(int id)
	{
		return m_dxGameResourceHandleGetter->getPostEffectMaterialHandle(id);
	}

	unsigned int DX12GameManager::getSpriteMaterialHandleImpl(int id)
	{
		return m_dxGameResourceHandleGetter->getSpriteMaterialHandle(id);
	}

	unsigned int DX12GameManager::getLine2DMaterialHandleImpl(int id)
	{
		return m_dxGameResourceHandleGetter->getLine2DMaterialHandle(id);
	}

	unsigned int DX12GameManager::getBillboardMaterialHandle(int id)
	{
		return m_dxGameResourceHandleGetter->getBillboardMaterialHandle(id);
	}

	unsigned int DX12GameManager::getSkeletonHandleImpl(int id)
	{
		return m_dxGameResourceHandleGetter->getSkeletonHandle(id);
	}

	unsigned int DX12GameManager::getMotionHandleImpl(int id)
	{
		return m_dxGameResourceHandleGetter->getMotionHandle(id);
	}

	unsigned int DX12GameManager::getBasicMeshHandleImpl(int id)
	{
		return m_dxGameResourceHandleGetter->getBasicMeshHandle(id);
	}

	unsigned int DX12GameManager::getBasicMeshMaterialHandleImpl(int id)
	{
		return m_dxGameResourceHandleGetter->getBasicMeshMaterialHandle(id);
	}

	unsigned int DX12GameManager::getCameraHandleImpl(int id)
	{
		return m_dxGameResourceHandleGetter->getCameraHandle(id);
	}

	unsigned int DX12GameManager::getLightHandleImpl(int id)
	{
		return m_dxGameResourceHandleGetter->getLightHandle(id);
	}
}