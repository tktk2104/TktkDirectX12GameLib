#include "TktkDX12Game/GraphicManager/GraphicManager.h"

#include <TktkDX12Wrapper/_BaseObjects/DX3DBaseObjects.h>
#include "TktkDX12Game/GraphicManager/Window/Window.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	GraphicManager::GraphicManager(const WindowInitParam& windowInitParam, const DX3DBaseObjectsInitParam& baseObjectsInitParam)
	{
		m_window			= std::make_unique<Window>(windowInitParam);

		DX3DBaseObjectsInitParam tempInitParam = baseObjectsInitParam;
		tempInitParam.hwnd = m_window->getHWND();

		m_dx3dBaseObjects	= std::make_unique<DX3DBaseObjects>(tempInitParam);
	}

	// デストラクタを非インライン化する
	GraphicManager::~GraphicManager() = default;

	HWND GraphicManager::getHWND() const
	{
		return m_window->getHWND();
	}

	const tktkMath::Vector2& GraphicManager::getDrawGameAreaSize() const
	{
		return m_window->getDrawGameAreaSize();
	}

	const tktkMath::Vector2& GraphicManager::getScreenSize() const
	{
		return m_window->getScreenSize();
	}

	void GraphicManager::beginDraw()
	{
		// 現在のバックバッファーの種類を「m_curBackBufferIndex」から求める
		auto curBackBufferType = (m_dx3dBaseObjects->getCurBackBufferIndex() == 0U) ? SystemRtBufferType::BackBuffer_1 : SystemRtBufferType::BackBuffer_2;

		// バックバッファをレンダーターゲット状態にする
		m_dx3dBaseObjects->beginWriteBackBuffer(DX12GameManager::getSystemHandle(curBackBufferType));

		// 現在のバックバッファービューをを描画先に設定する
		m_dx3dBaseObjects->setBackBufferView(DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer));

		// 現在のバックバッファーを指定した単色で塗りつぶす
		m_dx3dBaseObjects->clearRtv(DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer), m_dx3dBaseObjects->getCurBackBufferIndex());

		// 全てのデプスステンシルビューをクリアする
		m_dx3dBaseObjects->clearDsvAll();

		// ビューポートを設定する
		m_dx3dBaseObjects->setViewport(DX12GameManager::getSystemHandle(SystemViewportType::Basic));
		
		// シザー矩形を設定する
		m_dx3dBaseObjects->setScissorRect(DX12GameManager::getSystemHandle(SystemScissorRectType::Basic));
	}

	void GraphicManager::endDraw()
	{
		// 現在のバックバッファーの種類を「m_curBackBufferIndex」から求める
		auto curBackBufferType = (m_dx3dBaseObjects->getCurBackBufferIndex() == 0U) ? SystemRtBufferType::BackBuffer_1 : SystemRtBufferType::BackBuffer_2;

		// バックバッファをプリセット状態にする
		m_dx3dBaseObjects->endWriteBackBuffer(DX12GameManager::getSystemHandle(curBackBufferType));

		// コマンドリストを実行する
		m_dx3dBaseObjects->executeCommandList();

		// 画面をフリップする
		m_dx3dBaseObjects->flipScreen();
	}

	size_t GraphicManager::createViewport(const std::vector<ViewportInitParam>& initParamArray)
	{
		return m_dx3dBaseObjects->createViewport(initParamArray);
	}

	size_t GraphicManager::createScissorRect(const std::vector<ScissorRectInitParam>& initParamArray)
	{
		return m_dx3dBaseObjects->createScissorRect(initParamArray);
	}

	size_t GraphicManager::createRootSignature(const RootSignatureInitParam& initParam)
	{
		return m_dx3dBaseObjects->createRootSignature(initParam);
	}

	size_t GraphicManager::createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		return m_dx3dBaseObjects->createPipeLineState(initParam, shaderFilePath);
	}

	size_t GraphicManager::createUploadBuffer(const UploadBufferInitParam& initParam)
	{
		return m_dx3dBaseObjects->createUploadBuffer(initParam);
	}

	void GraphicManager::createTempUploadBuffer(const UploadBufferInitParam& initParam)
	{
		m_dx3dBaseObjects->createTempUploadBuffer(initParam);
	}

	size_t GraphicManager::duplicateUploadBuffer(size_t originalHandle)
	{
		return m_dx3dBaseObjects->duplicateUploadBuffer(originalHandle);
	}

	size_t GraphicManager::createVertexBuffer(const VertexDataCarrier& vertexData)
	{
		return m_dx3dBaseObjects->createVertexBuffer(vertexData);
	}

	size_t GraphicManager::createIndexBuffer(const std::vector<unsigned short>& indices)
	{
		return m_dx3dBaseObjects->createIndexBuffer(indices);
	}

	size_t GraphicManager::createCBuffer(const CopySourceDataCarrier& constantBufferData)
	{
		return m_dx3dBaseObjects->createCBuffer(constantBufferData);
	}

	size_t GraphicManager::createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		return m_dx3dBaseObjects->createRtBuffer(renderTargetSize, clearColor);
	}

	std::array<size_t, 2U> GraphicManager::createBackBufferRtBuffer()
	{
		return m_dx3dBaseObjects->createBackBufferRtBuffer();
	}

	size_t GraphicManager::createDsBuffer(const DepthStencilBufferInitParam& initParam)
	{
		return m_dx3dBaseObjects->createDsBuffer(initParam);
	}

	size_t GraphicManager::createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam)
	{
		return m_dx3dBaseObjects->createBasicDescriptorHeap(initParam);
	}

	size_t GraphicManager::createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam)
	{
		return m_dx3dBaseObjects->createRtvDescriptorHeap(initParam);
	}

	size_t GraphicManager::createBackBufferRtvDescriptorHeap(const std::array<size_t, 2U>& backBufferRtBufferHandles)
	{
		return m_dx3dBaseObjects->createBackBufferRtvDescriptorHeap(backBufferRtBufferHandles);
	}

	size_t GraphicManager::createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam)
	{
		return m_dx3dBaseObjects->createDsvDescriptorHeap(initParam);
	}

	size_t GraphicManager::createTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_dx3dBaseObjects->createTextureBuffer(formatParam, dataParam);
	}

	size_t GraphicManager::loadTextureBuffer(const std::string& texDataPath)
	{
		return m_dx3dBaseObjects->loadTextureBuffer(texDataPath);
	}

	void GraphicManager::eraseViewport(size_t handle)
	{
		m_dx3dBaseObjects->eraseViewport(handle);
	}

	void GraphicManager::eraseScissorRect(size_t handle)
	{
		m_dx3dBaseObjects->eraseScissorRect(handle);
	}

	void GraphicManager::eraseRootSignature(size_t handle)
	{
		m_dx3dBaseObjects->eraseRootSignature(handle);
	}

	void GraphicManager::erasePipeLineState(size_t handle)
	{
		m_dx3dBaseObjects->erasePipeLineState(handle);
	}

	void GraphicManager::eraseUploadBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseUploadBuffer(handle);
	}

	void GraphicManager::eraseVertexBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseVertexBuffer(handle);
	}

	void GraphicManager::eraseIndexBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseIndexBuffer(handle);
	}

	void GraphicManager::eraseCBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseCBuffer(handle);
	}

	void GraphicManager::eraseTextureBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseTextureBuffer(handle);
	}

	void GraphicManager::eraseDsBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseDsBuffer(handle);
	}

	void GraphicManager::eraseRtBuffer(size_t handle)
	{
		m_dx3dBaseObjects->eraseRtBuffer(handle);
	}

	void GraphicManager::eraseBasicDescriptorHeap(size_t handle)
	{
		m_dx3dBaseObjects->eraseBasicDescriptorHeap(handle);
	}

	void GraphicManager::eraseRtvDescriptorHeap(size_t handle)
	{
		m_dx3dBaseObjects->eraseRtvDescriptorHeap(handle);
	}

	void GraphicManager::eraseDsvDescriptorHeap(size_t handle)
	{
		m_dx3dBaseObjects->eraseDsvDescriptorHeap(handle);
	}

	void GraphicManager::updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData)
	{
		m_dx3dBaseObjects->updateUploadBuffer(handle, bufferData);
	}

	void GraphicManager::updateVertexBuffer(size_t handle, const VertexDataCarrier& vertexData)
	{
		m_dx3dBaseObjects->updateVertexBuffer(handle, vertexData);
	}

	void GraphicManager::copyBuffer(size_t handle) const
	{
		m_dx3dBaseObjects->copyBuffer(handle);
	}

	void GraphicManager::clearRtv(size_t handle, size_t rtvLocationIndex) const
	{
		m_dx3dBaseObjects->clearRtv(handle, rtvLocationIndex);
	}

	const tktkMath::Vector3& GraphicManager::getTextureBufferSizePx(size_t handle) const
	{
		return m_dx3dBaseObjects->getTextureBufferSizePx(handle);
	}

	const tktkMath::Vector2& GraphicManager::getDsBufferSizePx(size_t handle) const
	{
		return m_dx3dBaseObjects->getDsBufferSizePx(handle);
	}

	const tktkMath::Vector2& GraphicManager::getRtBufferSizePx(size_t handle) const
	{
		return m_dx3dBaseObjects->getRtBufferSizePx(handle);
	}

	void GraphicManager::setRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const
	{
		m_dx3dBaseObjects->setRtv(rtvDescriptorHeapHandle, startRtvLocationIndex, rtvCount);
	}

	void GraphicManager::setRtvAndDsv(size_t rtvDescriptorHeapHandle, size_t dsvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const
	{
		m_dx3dBaseObjects->setRtvAndDsv(rtvDescriptorHeapHandle, dsvDescriptorHeapHandle, startRtvLocationIndex, rtvCount);
	}

	void GraphicManager::setOnlyDsv(size_t handle) const
	{
		m_dx3dBaseObjects->setOnlyDsv(handle);
	}

	void GraphicManager::setBackBufferView() const
	{
		m_dx3dBaseObjects->setBackBufferView(DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer));
	}

	void GraphicManager::setBackBufferViewAndDsv(size_t dsvDescriptorHeapHandle) const
	{
		m_dx3dBaseObjects->setBackBufferViewAndDsv(DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer), dsvDescriptorHeapHandle);
	}

	void GraphicManager::unSetRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const
	{
		m_dx3dBaseObjects->unSetRtv(rtvDescriptorHeapHandle, startRtvLocationIndex, rtvCount);
	}

	void GraphicManager::unSetDsv(size_t dsvDescriptorHeapHandle) const
	{
		m_dx3dBaseObjects->unSetDsv(dsvDescriptorHeapHandle);
	}

	void GraphicManager::setViewport(size_t handle) const
	{
		m_dx3dBaseObjects->setViewport(handle);
	}

	void GraphicManager::setScissorRect(size_t handle) const
	{
		m_dx3dBaseObjects->setScissorRect(handle);
	}

	void GraphicManager::setPipeLineState(size_t handle) const
	{
		m_dx3dBaseObjects->setPipeLineState(handle);
	}

	void GraphicManager::setVertexBuffer(size_t handle) const
	{
		m_dx3dBaseObjects->setVertexBuffer(handle);
	}

	void GraphicManager::setVertexBuffer(size_t meshVertHandle, size_t instancingVertHandle) const
	{
		m_dx3dBaseObjects->setVertexBuffer(meshVertHandle, instancingVertHandle);
	}

	void GraphicManager::setIndexBuffer(size_t handle) const
	{
		m_dx3dBaseObjects->setIndexBuffer(handle);
	}

	void GraphicManager::setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray) const
	{
		m_dx3dBaseObjects->setDescriptorHeap(heapParamArray);
	}

	void GraphicManager::setBlendFactor(const std::array<float, 4>& blendFactor) const
	{
		m_dx3dBaseObjects->setBlendFactor(blendFactor);
	}

	void GraphicManager::setPrimitiveTopology(PrimitiveTopology topology) const
	{
		m_dx3dBaseObjects->setPrimitiveTopology(topology);
	}

	void GraphicManager::drawInstanced(size_t vertexCountPerInstance, size_t instanceCount, size_t baseVertexLocation, size_t startInstanceLocation) const
	{
		m_dx3dBaseObjects->drawInstanced(vertexCountPerInstance, instanceCount, baseVertexLocation, startInstanceLocation);
	}

	void GraphicManager::drawIndexedInstanced(size_t indexCountPerInstance, size_t instanceCount, size_t startIndexLocation, size_t baseVertexLocation, size_t startInstanceLocation) const
	{
		m_dx3dBaseObjects->drawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
	}

	void GraphicManager::executeCommandList()
	{
		m_dx3dBaseObjects->executeCommandList();
	}
}