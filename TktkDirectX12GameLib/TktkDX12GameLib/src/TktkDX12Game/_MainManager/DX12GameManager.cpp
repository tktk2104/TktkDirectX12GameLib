#include "TktkDX12Game/_MainManager/DX12GameManager.h"

#include <TktkDX12Wrapper/Window/Window.h>
#include <TktkDX12Wrapper/_BaseObjects/DX3DBaseObjects.h>
#include "TktkDX12Game/GameObject/GameObjectManager.h"
#include "TktkDX12Game/GameObject/GameObject.h"
#include "TktkDX12Game/DXGameResource/DXGameResource.h"
#include "TktkDX12Game/DXGameResource/_SystemDXGameResourceIdGetter/SystemDXGameResourceIdGetter.h"
#include "TktkDX12Game/Input/Mouse/Mouse.h"
#include "TktkDX12Game/Input/DirectInputWrapper/DirectInputWrapper.h"
#include "TktkDX12Game/Time/ElapsedTimer.h"

namespace tktk
{
	std::unique_ptr<GameObjectManager>				DX12GameManager::m_gameObjectManager;
	std::unique_ptr<ComponentManager>				DX12GameManager::m_componentManager;
	std::unique_ptr<Window>							DX12GameManager::m_window;
	std::unique_ptr<DX3DBaseObjects>				DX12GameManager::m_dx3dBaseObjects;
	std::unique_ptr<DXGameResource>					DX12GameManager::m_dxGameResource;
	std::unique_ptr<SystemDXGameResourceIdGetter>	DX12GameManager::m_systemDXGameResourceIdGetter;
	std::unique_ptr<DirectInputWrapper>				DX12GameManager::m_directInputWrapper;
	std::unique_ptr<Mouse>							DX12GameManager::m_mouse;
	std::unique_ptr<ElapsedTimer>					DX12GameManager::m_elapsedTimer;

	void DX12GameManager::initialize(const DX12GameManagerInitParam& gameManagerInitParam)
	{
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
			DXGameResourceNum dxGameResourceNum = gameManagerInitParam.dxGameResourceNum;

			// コンストラクタ内で「DXGameResourceNum」の値を書き換える
			m_systemDXGameResourceIdGetter = std::make_unique<SystemDXGameResourceIdGetter>(&dxGameResourceNum);

			DXGameBaseShaderFilePaths dxGameBaseShaderFilePaths{};
			dxGameBaseShaderFilePaths.spriteShaderFilePaths.vsFilePath					= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/SpriteVertexShader.cso";
			dxGameBaseShaderFilePaths.spriteShaderFilePaths.psFilePath					= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/SpritePixelShader.cso";
			dxGameBaseShaderFilePaths.line2DShaderFilePaths.vsFilePath					= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/Line2DVertexShader.cso";
			dxGameBaseShaderFilePaths.line2DShaderFilePaths.psFilePath					= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/Line2DPixelShader.cso";
			dxGameBaseShaderFilePaths.basicMeshShaderFilePaths.vsFilePath				= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/BasicMeshVertexShader.cso";
			dxGameBaseShaderFilePaths.basicMeshShaderFilePaths.psFilePath				= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/BasicMeshPixelShader.cso";
			dxGameBaseShaderFilePaths.monoColorShaderPsFilePath							= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/BasicMonoColorMeshPixelShader.cso";
			dxGameBaseShaderFilePaths.writeShadowMapVsFilePath							= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/BasicMeshShadowVertexShader.cso";
			dxGameBaseShaderFilePaths.postEffectShaderFilePaths.postEffectVSFilePath	= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/PostEffectVertexShader.cso";
			dxGameBaseShaderFilePaths.postEffectShaderFilePaths.monochromePSFilePath	= gameManagerInitParam.tktkLibResFolderPath + "TktkLibRes/shader/MonochromePixelShader.cso";

			m_dxGameResource = std::make_unique<DXGameResource>(dxGameResourceNum, dxGameBaseShaderFilePaths);
		}
		m_mouse					= std::make_unique<Mouse>();
		m_directInputWrapper	= std::make_unique<DirectInputWrapper>(gameManagerInitParam.windowParam.hInstance, m_window->getHWND());
		m_elapsedTimer			= std::make_unique<ElapsedTimer>();

		// シャドウマップの深度バッファーを作る
		{
			DepthStencilBufferInitParam initParam{};
			initParam.depthStencilSize = gameManagerInitParam.windowParam.windowSize;
			initParam.useAsShaderResource = true;

			createDsBuffer(getSystemId(SystemDsBufferType::ShadowMap), initParam);
		}

		// シャドウマップの深度ディスクリプタヒープを作る
		{
			DsvDescriptorHeapInitParam initParam{};
			initParam.shaderVisible = false;
			initParam.descriptorParamArray.push_back({ DsvDescriptorType::normal, getSystemId(SystemDsBufferType::ShadowMap) });

			createDsvDescriptorHeap(getSystemId(SystemDsvDescriptorHeapType::ShadowMap), initParam);
		}

		// 球体メッシュを作る
		SphereMeshMaker::make();
	}

	void DX12GameManager::run()
	{
		MSG msg{};

		while (true)
		{
			bool canRunDX12Func = true;

			if (msg.message == WM_QUIT)
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
				m_gameObjectManager->update();
				m_componentManager->update();

				m_dx3dBaseObjects->beginDraw();
				m_componentManager->draw();
				m_dx3dBaseObjects->endDraw();
			}
		}
		m_dxGameResource->clearSound();
	}

	const tktkMath::Vector2& DX12GameManager::getWindowSize()
	{
		return m_window->getWindowSize();
	}

	void DX12GameManager::enableScene(unsigned int id)
	{
		m_dxGameResource->enableScene(id);
	}

	void DX12GameManager::disableScene(unsigned int id)
	{
		m_dxGameResource->disableScene(id);
	}

	void DX12GameManager::sendMessageAll(unsigned int messageId, const MessageAttachment& value)
	{
		m_gameObjectManager->runHandleMessageAll(messageId, value);
	}

	GameObjectPtr DX12GameManager::createGameObject()
	{
		return m_gameObjectManager->createGameObject();
	}

	GameObjectPtr DX12GameManager::findGameObjectWithTag(int tag)
	{
		return m_gameObjectManager->findGameObjectWithTag(tag);
	}
	
	std::forward_list<GameObjectPtr> DX12GameManager::findGameObjectsWithTag(int tag)
	{
		return m_gameObjectManager->findGameObjectsWithTag(tag);
	}

	void DX12GameManager::addCollisionGroup(int firstGroup, int secondGroup)
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

	void DX12GameManager::setRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dx3dBaseObjects->setRtv(rtvDescriptorHeapId, startRtvLocationIndex, rtvCount);
	}

	void DX12GameManager::setRtvAndDsv(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dx3dBaseObjects->setRtvAndDsv(rtvDescriptorHeapId, dsvDescriptorHeapId, startRtvLocationIndex, rtvCount);
	}

	void DX12GameManager::setOnlyDsv(unsigned int dsvDescriptorHeapId)
	{
		m_dx3dBaseObjects->setOnlyDsv(dsvDescriptorHeapId);
	}

	void DX12GameManager::setBackBufferView()
	{
		m_dx3dBaseObjects->setBackBufferView();
	}

	void DX12GameManager::setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapId)
	{
		m_dx3dBaseObjects->setBackBufferViewAndDsv(dsvDescriptorHeapId);
	}

	void DX12GameManager::unSetRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dx3dBaseObjects->unSetRtv(rtvDescriptorHeapId, startRtvLocationIndex, rtvCount);
	}

	void DX12GameManager::unSetDsv(unsigned int dsvDescriptorHeapId)
	{
		m_dx3dBaseObjects->unSetDsv(dsvDescriptorHeapId);
	}

	void DX12GameManager::setViewport(unsigned int id)
	{
		m_dx3dBaseObjects->setViewport(id);
	}

	void DX12GameManager::setScissorRect(unsigned int id)
	{
		m_dx3dBaseObjects->setScissorRect(id);
	}

	void DX12GameManager::setPipeLineState(unsigned int id)
	{
		m_dx3dBaseObjects->setPipeLineState(id);
	}

	void DX12GameManager::setVertexBuffer(unsigned int id)
	{
		m_dx3dBaseObjects->setVertexBuffer(id);
	}

	void DX12GameManager::setIndexBuffer(unsigned int id)
	{
		m_dx3dBaseObjects->setIndexBuffer(id);
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

	void DX12GameManager::createRootSignature(unsigned int id, const RootSignatureInitParam& initParam)
	{
		m_dx3dBaseObjects->createRootSignature(id, initParam);
	}

	void DX12GameManager::createPipeLineState(unsigned int graphicsPipeLineId, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		m_dx3dBaseObjects->createPipeLineState(graphicsPipeLineId, initParam, shaderFilePath);
	}

	void DX12GameManager::createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices)
	{
		m_dx3dBaseObjects->createIndexBuffer(id, indices);
	}

	void DX12GameManager::createRtBuffer(unsigned int id, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		m_dx3dBaseObjects->createRtBuffer(id, renderTargetSize, clearColor);
	}

	void DX12GameManager::createDsBuffer(unsigned int id, const DepthStencilBufferInitParam& initParam)
	{
		m_dx3dBaseObjects->createDsBuffer(id, initParam);
	}

	void DX12GameManager::createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam)
	{
		m_dx3dBaseObjects->createBasicDescriptorHeap(id, initParam);
	}

	void DX12GameManager::createRtvDescriptorHeap(unsigned int id, const RtvDescriptorHeapInitParam& initParam)
	{
		m_dx3dBaseObjects->createRtvDescriptorHeap(id, initParam);
	}

	void DX12GameManager::createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam)
	{
		m_dx3dBaseObjects->createDsvDescriptorHeap(id, initParam);
	}

	void DX12GameManager::cpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_dx3dBaseObjects->cpuPriorityCreateTextureBuffer(id, formatParam, dataParam);
	}

	void DX12GameManager::gpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_dx3dBaseObjects->gpuPriorityCreateTextureBuffer(id, formatParam, dataParam);
	}

	void DX12GameManager::cpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath)
	{
		m_dx3dBaseObjects->cpuPriorityLoadTextureBuffer(id, texDataPath);
	}

	void DX12GameManager::gpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath)
	{
		m_dx3dBaseObjects->gpuPriorityLoadTextureBuffer(id, texDataPath);
	}

	void DX12GameManager::updateIndexBuffer(unsigned int id, const std::vector<unsigned short>& indexDataArray)
	{
		m_dx3dBaseObjects->updateIndexBuffer(id, indexDataArray);
	}

	void DX12GameManager::clearRtv(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color)
	{
		m_dx3dBaseObjects->clearRtv(id, rtvLocationIndex, color);
	}

	const tktkMath::Vector3& DX12GameManager::getTextureBufferSizePx(unsigned int id)
	{
		return m_dx3dBaseObjects->getTextureBufferSizePx(id);
	}

	const tktkMath::Vector2& DX12GameManager::getDsBufferSizePx(unsigned int id)
	{
		return m_dx3dBaseObjects->getDsBufferSizePx(id);
	}

	const tktkMath::Vector2& DX12GameManager::getRtBufferSizePx(unsigned int id)
	{
		return m_dx3dBaseObjects->getRtBufferSizePx(id);
	}

	void DX12GameManager::createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam)
	{
		m_dxGameResource->createSpriteMaterial(id, initParam);
	}

	void DX12GameManager::drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameResource->drawSprite(id, drawFuncArgs);
	}

	void DX12GameManager::createLine(unsigned int id, const Line2DMaterialDataInitParam& initParam)
	{
		m_dxGameResource->createLine(id, initParam);
	}

	void DX12GameManager::drawLine(unsigned int id, const Line2DMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameResource->drawLine(id, drawFuncArgs);
	}

	void DX12GameManager::createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam)
	{
		m_dxGameResource->createBasicMesh(id, initParam);
	}

	void DX12GameManager::copyBasicMesh(unsigned int id, unsigned int originalId)
	{
		m_dxGameResource->copyBasicMesh(id, originalId);
	}

	void DX12GameManager::createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam)
	{
		m_dxGameResource->createBasicMeshMaterial(id, initParam);
	}

	void DX12GameManager::copyBasicMeshMaterial(unsigned int id, unsigned int originalId)
	{
		m_dxGameResource->copyBasicMeshMaterial(id, originalId);
	}

	void DX12GameManager::setMaterialId(unsigned int id, unsigned int materialSlot, unsigned int materialId)
	{
		m_dxGameResource->setMaterialId(id, materialSlot, materialId);
	}

	void DX12GameManager::writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData)
	{
		m_dxGameResource->writeBasicMeshShadowMap(id, transformBufferData);
	}

	void DX12GameManager::setMaterialData(unsigned int id)
	{
		m_dxGameResource->setMaterialData(id);
	}

	void DX12GameManager::drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs)
	{
		m_dxGameResource->drawBasicMesh(id, baseArgs);
	}

	BasicMeshLoadPmdReturnValue DX12GameManager::loadPmd(const BasicMeshLoadPmdArgs& args)
	{
		return m_dxGameResource->loadPmd(args);
	}

	void DX12GameManager::createSkeleton(unsigned int id, const SkeletonInitParam& initParam)
	{
		m_dxGameResource->createSkeleton(id, initParam);
	}

	void DX12GameManager::updateBoneMatrixCbuffer(unsigned int id)
	{
		m_dxGameResource->updateBoneMatrixCbuffer(id);
	}

	void DX12GameManager::resetBoneMatrixCbuffer()
	{
		m_dxGameResource->resetBoneMatrixCbuffer();
	}

	void DX12GameManager::loadMotion(unsigned int id, const std::string& motionFileName)
	{
		m_dxGameResource->loadMotion(id, motionFileName);
	}

	void DX12GameManager::updateMotion(unsigned int skeletonId, unsigned int motionId, unsigned int curFrame)
	{
		m_dxGameResource->updateMotion(skeletonId, motionId, curFrame);
	}

	void DX12GameManager::createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam)
	{
		m_dxGameResource->createPostEffectMaterial(id, initParam);
	}

	void DX12GameManager::drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameResource->drawPostEffect(id, drawFuncArgs);
	}

	void DX12GameManager::createCamera(unsigned int id)
	{
		m_dxGameResource->createCamera(id);
	}

	const tktkMath::Matrix4& DX12GameManager::getViewMatrix(unsigned int cameraId)
	{
		return m_dxGameResource->getViewMatrix(cameraId);
	}

	void DX12GameManager::setViewMatrix(unsigned int cameraId, const tktkMath::Matrix4& view)
	{
		m_dxGameResource->setViewMatrix(cameraId, view);
	}

	const tktkMath::Matrix4& DX12GameManager::getProjectionMatrix(unsigned int cameraId)
	{
		return m_dxGameResource->getProjectionMatrix(cameraId);
	}

	void DX12GameManager::setProjectionMatrix(unsigned int cameraId, const tktkMath::Matrix4& projection)
	{
		m_dxGameResource->setProjectionMatrix(cameraId, projection);
	}

	void DX12GameManager::createLight(unsigned int id, const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular, const tktkMath::Vector3& position)
	{
		m_dxGameResource->createLight(id, ambient, diffuse, speqular, position);
	}

	void DX12GameManager::updateLightCBuffer(unsigned int id)
	{
		m_dxGameResource->updateLightCBuffer(id);
	}

	void DX12GameManager::setLightAmbient(unsigned int id, const tktkMath::Color& ambient)
	{
		m_dxGameResource->setLightAmbient(id, ambient);
	}

	void DX12GameManager::setLightDiffuse(unsigned int id, const tktkMath::Color& diffuse)
	{
		m_dxGameResource->setLightDiffuse(id, diffuse);
	}

	void DX12GameManager::setLightSpeqular(unsigned int id, const tktkMath::Color& speqular)
	{
		m_dxGameResource->setLightSpeqular(id, speqular);
	}

	void DX12GameManager::setLightPosition(unsigned int id, const tktkMath::Vector3& position)
	{
		m_dxGameResource->setLightPosition(id, position);
	}

	void DX12GameManager::loadSound(unsigned int id, const std::string& fileName)
	{
		m_dxGameResource->loadSound(id, fileName);
	}

	void DX12GameManager::playSound(unsigned int id, bool loopPlay)
	{
		m_dxGameResource->playSound(id, loopPlay);
	}

	void DX12GameManager::stopSound(unsigned int id)
	{
		m_dxGameResource->stopSound(id);
	}

	void DX12GameManager::pauseSound(unsigned int id)
	{
		m_dxGameResource->pauseSound(id);
	}

	void DX12GameManager::setMasterVolume(float volume)
	{
		m_dxGameResource->setMasterVolume(volume);
	}

	bool DX12GameManager::isPush(MouseButtonType buttonType)
	{
		return m_mouse->isPush(buttonType);
	}

	bool DX12GameManager::isTrigger(MouseButtonType buttonType)
	{
		return m_mouse->isTrigger(buttonType);
	}

	tktkMath::Vector2 DX12GameManager::mousePos()
	{
		return m_mouse->mousePos();
	}

	bool DX12GameManager::isPush(KeybordKeyType keyType)
	{
		return m_directInputWrapper->isPush(keyType);
	}

	bool DX12GameManager::isTrigger(KeybordKeyType keyType)
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

	bool DX12GameManager::isPush(GamePadBtnType btnType)
	{
		return m_directInputWrapper->isPush(btnType);
	}

	bool DX12GameManager::isTrigger(GamePadBtnType btnType)
	{
		return m_directInputWrapper->isTrigger(btnType);
	}

	void DX12GameManager::reset()
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

	unsigned int DX12GameManager::getSystemId(SystemViewportType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemScissorRectType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemVertexBufferType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemIndexBufferType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemCBufferType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemTextureBufferType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemDsBufferType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemBasicDescriptorHeapType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemRtvDescriptorHeapType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemDsvDescriptorHeapType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemRootSignatureType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemPipeLineStateType type)
	{
		return m_dx3dBaseObjects->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemBasicMeshType type)
	{
		return m_systemDXGameResourceIdGetter->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemBasicMeshMaterialType type)
	{
		return m_systemDXGameResourceIdGetter->getSystemId(type);
	}

	unsigned int DX12GameManager::getSystemId(SystemPostEffectMaterialType type)
	{
		return m_systemDXGameResourceIdGetter->getSystemId(type);
	}

	void DX12GameManager::createSceneImpl(unsigned int id, const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr)
	{
		m_dxGameResource->createScene(id, scenePtr, vtablePtr);
	}

	void DX12GameManager::createVertexBufferImpl(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_dx3dBaseObjects->createVertexBuffer(id, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX12GameManager::createCbufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dx3dBaseObjects->createCBuffer(id, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX12GameManager::updateVertexBufferImpl(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_dx3dBaseObjects->updateVertexBuffer(id, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX12GameManager::updateCbufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dx3dBaseObjects->updateCBuffer(id, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX12GameManager::addMaterialAppendParamImpl(unsigned int id, unsigned int cbufferId, unsigned int dataSize, void* dataTopPos)
	{
		m_dxGameResource->addMaterialAppendParam(id, cbufferId, dataSize, dataTopPos);
	}

	void DX12GameManager::updateMaterialAppendParamImpl(unsigned int id, unsigned int cbufferId, unsigned int dataSize, const void* dataTopPos)
	{
		m_dxGameResource->updateMaterialAppendParam(id, cbufferId, dataSize, dataTopPos);
	}
}