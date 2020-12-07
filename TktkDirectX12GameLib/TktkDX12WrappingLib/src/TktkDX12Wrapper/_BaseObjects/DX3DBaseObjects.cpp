#include "TktkDX12Wrapper/_BaseObjects/DX3DBaseObjects.h"

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix4.h>
#include "TktkDX12Wrapper/SwapChain/SwapChain.h"
#include "TktkDX12Wrapper/Fence/Fence.h"
#include "TktkDX12Wrapper/Resource/DX3DResource.h"

namespace tktk
{
	DX3DBaseObjects::DX3DBaseObjects(const DX3DBaseObjectsInitParam& initParam)
	{
		// DX12のリソースの管理クラスを作る
		m_dX3DResource	= std::make_unique<DX3DResource>(initParam.resourceNum);

#ifdef _DEBUG
		if (initParam.createDebugLayer)
		{
			ID3D12Debug* debugLayer{ nullptr };
			D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
			debugLayer->EnableDebugLayer();

			ID3D12Debug1* debugLayer1{ nullptr };
			debugLayer->QueryInterface(IID_PPV_ARGS(&debugLayer1));
			debugLayer1->SetEnableGPUBasedValidation(true);

			debugLayer1->Release();
			debugLayer->Release();
		}
#endif // _DEBUG

		// デバイスを作る
		D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&m_device));

		// ファクトリを作る
#ifdef _DEBUG
		if (initParam.createDebugLayer) CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&m_factory));
		else CreateDXGIFactory1(IID_PPV_ARGS(&m_factory));
#else
		CreateDXGIFactory1(IID_PPV_ARGS(&m_factory));
#endif

		// コマンドアロケータを作る
		m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator));

		// コマンドリストを作る
		m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator, nullptr, IID_PPV_ARGS(&m_commandList));

		// コマンドキューを作る
		D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
		commandQueueDesc.Flags		= D3D12_COMMAND_QUEUE_FLAG_NONE;
		commandQueueDesc.NodeMask	= 0;
		commandQueueDesc.Priority	= D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		commandQueueDesc.Type		= D3D12_COMMAND_LIST_TYPE_DIRECT;
		m_device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&m_commandQueue));
		
		// スワップチェーンを作る
		m_swapChain = std::make_unique<SwapChain>(initParam.hwnd, m_factory, m_commandQueue, initParam.windowSize);

		// フェンスを作る
		m_fence		= std::make_unique<Fence>(m_device);

		// 初回リセット
		m_commandList->Close();
		m_commandAllocator->Reset();
		m_commandList->Reset(m_commandAllocator, nullptr);
		m_swapChain->updateBackBufferIndex();
	}

	DX3DBaseObjects::~DX3DBaseObjects()
	{
		if (m_device != nullptr)
		{
			m_device->Release();
		}

		if (m_factory != nullptr)
		{
			m_factory->Release();
		}

		if (m_commandAllocator != nullptr)
		{
			m_commandAllocator->Release();
		}

		if (m_commandList != nullptr)
		{
			m_commandList->Release();
		}

		if (m_commandQueue != nullptr)
		{
			m_commandQueue->Release();
		}
	}

	size_t DX3DBaseObjects::createViewport(const std::vector<ViewportInitParam>& initParamArray)
	{
		return m_dX3DResource->createViewport(initParamArray);
	}

	size_t DX3DBaseObjects::createScissorRect(const std::vector<ScissorRectInitParam>& initParamArray)
	{
		return m_dX3DResource->createScissorRect(initParamArray);
	}

	size_t DX3DBaseObjects::createRootSignature(const RootSignatureInitParam& initParam)
	{
		return m_dX3DResource->createRootSignature(m_device, initParam);
	}

	size_t DX3DBaseObjects::createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		size_t handle = m_dX3DResource->createPipeLineState(m_device, initParam, shaderFilePath);

		// 初回セット（※最初にセットした時のみ重たい処理となるので、作成直後に先行でセットする）
		m_dX3DResource->setPipeLineState(handle, m_commandList);

		return handle;
	}

	size_t DX3DBaseObjects::createUploadBuffer(const UploadBufferInitParam& initParam)
	{
		return m_dX3DResource->createUploadBuffer(m_device, initParam);
	}

	size_t DX3DBaseObjects::duplicateUploadBuffer(size_t originalHandle)
	{
		return m_dX3DResource->duplicateUploadBuffer(m_device, originalHandle);
	}

	size_t DX3DBaseObjects::createVertexBuffer(const VertexDataCarrier& vertexData)
	{
		return m_dX3DResource->createVertexBuffer(m_device, vertexData);
	}

	size_t DX3DBaseObjects::createIndexBuffer(const std::vector<unsigned short>& indices)
	{
		return m_dX3DResource->createIndexBuffer(m_device, indices);
	}

	size_t DX3DBaseObjects::createCBuffer(const CopySourceDataCarrier& constantBufferData)
	{
		return m_dX3DResource->createCBuffer(m_device, constantBufferData);
	}

	size_t DX3DBaseObjects::createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		return m_dX3DResource->createRtBuffer(m_device, renderTargetSize, clearColor);
	}

	std::array<size_t, 2U> DX3DBaseObjects::createBackBufferRtBuffer()
	{
		auto result = std::array<size_t, 2U>();
		result.at(0U) = m_dX3DResource->createRtBuffer(m_swapChain->getPtr(), 0U);
		result.at(1U) = m_dX3DResource->createRtBuffer(m_swapChain->getPtr(), 1U);
		return result;
	}

	size_t DX3DBaseObjects::createDsBuffer(const DepthStencilBufferInitParam& initParam)
	{
		return m_dX3DResource->createDsBuffer(m_device, initParam);
	}

	size_t DX3DBaseObjects::createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam)
	{
		return m_dX3DResource->createBasicDescriptorHeap(m_device, initParam);
	}

	size_t DX3DBaseObjects::createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam)
	{
		return m_dX3DResource->createRtvDescriptorHeap(m_device, initParam);
	}

	size_t DX3DBaseObjects::createBackBufferRtvDescriptorHeap(const std::array<size_t, 2U>& backBufferRtBufferHandles)
	{
		RtvDescriptorHeapInitParam rtvDescriptorHeapInitParam{};
		rtvDescriptorHeapInitParam.descriptorParamArray.resize(2U);
		rtvDescriptorHeapInitParam.descriptorParamArray.at(0U).type		= RtvDescriptorType::normal;
		rtvDescriptorHeapInitParam.descriptorParamArray.at(0U).handle	= backBufferRtBufferHandles.at(0U);
		rtvDescriptorHeapInitParam.descriptorParamArray.at(1U).type		= RtvDescriptorType::normal;
		rtvDescriptorHeapInitParam.descriptorParamArray.at(1U).handle	= backBufferRtBufferHandles.at(1U);
		return m_dX3DResource->createRtvDescriptorHeap(m_device, rtvDescriptorHeapInitParam);
	}

	size_t DX3DBaseObjects::createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam)
	{
		return m_dX3DResource->createDsvDescriptorHeap(m_device, initParam);
	}

	size_t DX3DBaseObjects::cpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_dX3DResource->cpuPriorityCreateTextureBuffer(m_device, formatParam, dataParam);
	}

	size_t DX3DBaseObjects::gpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_dX3DResource->gpuPriorityCreateTextureBuffer(m_device, m_commandList, formatParam, dataParam);
	}

	size_t DX3DBaseObjects::cpuPriorityLoadTextureBuffer(const std::string& texDataPath)
	{
		return m_dX3DResource->cpuPriorityLoadTextureBuffer(m_device, texDataPath);
	}

	size_t DX3DBaseObjects::gpuPriorityLoadTextureBuffer(const std::string& texDataPath)
	{
		return m_dX3DResource->gpuPriorityLoadTextureBuffer(m_device, m_commandList, texDataPath);
	}

	void DX3DBaseObjects::eraseViewport(size_t handle)
	{
		m_dX3DResource->eraseViewport(handle);
	}

	void DX3DBaseObjects::eraseScissorRect(size_t handle)
	{
		m_dX3DResource->eraseScissorRect(handle);
	}

	void DX3DBaseObjects::eraseRootSignature(size_t handle)
	{
		m_dX3DResource->eraseRootSignature(handle);
	}

	void DX3DBaseObjects::erasePipeLineState(size_t handle)
	{
		m_dX3DResource->erasePipeLineState(handle);
	}

	void DX3DBaseObjects::eraseUploadBuffer(size_t handle)
	{
		m_dX3DResource->eraseUploadBuffer(handle);
	}

	void DX3DBaseObjects::eraseVertexBuffer(size_t handle)
	{
		m_dX3DResource->eraseVertexBuffer(handle);
	}

	void DX3DBaseObjects::eraseIndexBuffer(size_t handle)
	{
		m_dX3DResource->eraseIndexBuffer(handle);
	}

	void DX3DBaseObjects::eraseCBuffer(size_t handle)
	{
		m_dX3DResource->eraseCBuffer(handle);
	}

	void DX3DBaseObjects::eraseTextureBuffer(size_t handle)
	{
		m_dX3DResource->eraseTextureBuffer(handle);
	}

	void DX3DBaseObjects::eraseDsBuffer(size_t handle)
	{
		m_dX3DResource->eraseDsBuffer(handle);
	}

	void DX3DBaseObjects::eraseRtBuffer(size_t handle)
	{
		m_dX3DResource->eraseRtBuffer(handle);
	}

	void DX3DBaseObjects::eraseBasicDescriptorHeap(size_t handle)
	{
		m_dX3DResource->eraseBasicDescriptorHeap(handle);
	}

	void DX3DBaseObjects::eraseRtvDescriptorHeap(size_t handle)
	{
		m_dX3DResource->eraseRtvDescriptorHeap(handle);
	}

	void DX3DBaseObjects::eraseDsvDescriptorHeap(size_t handle)
	{
		m_dX3DResource->eraseDsvDescriptorHeap(handle);
	}

	void DX3DBaseObjects::updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData)
	{
		m_dX3DResource->updateUploadBuffer(handle, bufferData);
	}

	void DX3DBaseObjects::updateVertexBuffer(size_t handle, const VertexDataCarrier& vertexData)
	{
		m_dX3DResource->updateVertexBuffer(handle, vertexData);
	}

	void DX3DBaseObjects::copyBuffer(size_t handle) const
	{
		m_dX3DResource->copyBuffer(handle, m_commandList);
	}

	void DX3DBaseObjects::clearRtv(size_t handle, size_t rtvLocationIndex) const
	{
		m_dX3DResource->clearRtv(handle, m_device, m_commandList, rtvLocationIndex);
	}

	void DX3DBaseObjects::clearDsvAll()
	{
		m_dX3DResource->clearDsvAll(m_device, m_commandList);
	}

	unsigned int DX3DBaseObjects::getCurBackBufferIndex() const
	{
		return m_swapChain->getCurBackBufferIndex();
	}

	const tktkMath::Vector3& DX3DBaseObjects::getTextureBufferSizePx(size_t handle) const
	{
		return m_dX3DResource->getTextureBufferSizePx(handle);
	}

	const tktkMath::Vector2& DX3DBaseObjects::getDsBufferSizePx(size_t handle) const
	{
		return m_dX3DResource->getDsBufferSizePx(handle);
	}

	const tktkMath::Vector2& DX3DBaseObjects::getRtBufferSizePx(size_t handle) const
	{
		return m_dX3DResource->getRtBufferSizePx(handle);
	}

	void DX3DBaseObjects::setRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const
	{
		m_dX3DResource->setRtv(rtvDescriptorHeapHandle, m_device, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::setRtvAndDsv(size_t rtvDescriptorHeapHandle, size_t dsvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const
	{
		m_dX3DResource->setRtvAndDsv(rtvDescriptorHeapHandle, dsvDescriptorHeapHandle, m_device, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::setOnlyDsv(size_t handle) const
	{
		m_dX3DResource->setOnlyDsv(handle, m_device, m_commandList);
	}

	void DX3DBaseObjects::setBackBufferView(size_t backBufferRtvDescriptorHeap) const
	{
		m_dX3DResource->setBackBufferView(backBufferRtvDescriptorHeap, m_device, m_commandList, m_swapChain->getCurBackBufferIndex());
	}

	void DX3DBaseObjects::setBackBufferViewAndDsv(size_t backBufferRtvDescriptorHeap, size_t dsvDescriptorHeapHandle) const
	{
		m_dX3DResource->setBackBufferViewAndDsv(backBufferRtvDescriptorHeap, dsvDescriptorHeapHandle, m_device, m_commandList, m_swapChain->getCurBackBufferIndex());
	}

	void DX3DBaseObjects::unSetRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const
	{
		m_dX3DResource->unSetRtv(rtvDescriptorHeapHandle, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::unSetDsv(size_t dsvDescriptorHeapHandle) const
	{
		m_dX3DResource->unSetDsv(dsvDescriptorHeapHandle, m_commandList);
	}

	void DX3DBaseObjects::setViewport(size_t handle) const
	{
		m_dX3DResource->setViewport(handle, m_commandList);
	}

	void DX3DBaseObjects::setScissorRect(size_t handle) const
	{
		m_dX3DResource->setScissorRect(handle, m_commandList);
	}

	void DX3DBaseObjects::setPipeLineState(size_t handle) const
	{
		m_dX3DResource->setPipeLineState(handle, m_commandList);
	}

	void DX3DBaseObjects::setVertexBuffer(size_t handle) const
	{
		m_dX3DResource->setVertexBuffer(handle, m_commandList);
	}

	void DX3DBaseObjects::setVertexBuffer(size_t meshVertHandle, size_t instancingVertHandle) const
	{
		m_dX3DResource->setVertexBuffer(meshVertHandle, instancingVertHandle, m_commandList);
	}

	void DX3DBaseObjects::setIndexBuffer(size_t handle) const
	{
		m_dX3DResource->setIndexBuffer(handle, m_commandList);
	}

	void DX3DBaseObjects::setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray) const
	{
		m_dX3DResource->setDescriptorHeap(m_device, m_commandList, heapParamArray);
	}

	void DX3DBaseObjects::setBlendFactor(const std::array<float, 4>& blendFactor) const
	{
		m_commandList->OMSetBlendFactor(blendFactor.data());
	}

	void DX3DBaseObjects::setPrimitiveTopology(PrimitiveTopology topology) const
	{
		m_commandList->IASetPrimitiveTopology(static_cast<D3D12_PRIMITIVE_TOPOLOGY>(topology));
	}

	void DX3DBaseObjects::beginWriteBackBuffer(size_t backBufferHandle)
	{
		// バックバッファをレンダーターゲット状態にする
		m_dX3DResource->beginWriteBackBuffer(backBufferHandle, m_commandList);
	}

	void DX3DBaseObjects::endWriteBackBuffer(size_t backBufferHandle)
	{
		// バックバッファをプリセット状態にする
		m_dX3DResource->endWriteBackBuffer(backBufferHandle, m_commandList);
	}

	void DX3DBaseObjects::drawInstanced(size_t vertexCountPerInstance, size_t instanceCount, size_t baseVertexLocation, size_t startInstanceLocation) const
	{
		m_commandList->DrawInstanced(
			static_cast<unsigned int>(vertexCountPerInstance),
			static_cast<unsigned int>(instanceCount),
			static_cast<unsigned int>(baseVertexLocation),
			static_cast<unsigned int>(startInstanceLocation)
		);
	}

	void DX3DBaseObjects::drawIndexedInstanced(size_t indexCountPerInstance, size_t instanceCount, size_t startIndexLocation, size_t baseVertexLocation, size_t startInstanceLocation) const
	{
		m_commandList->DrawIndexedInstanced(
			static_cast<unsigned int>(indexCountPerInstance),
			static_cast<unsigned int>(instanceCount),
			static_cast<unsigned int>(startIndexLocation),
			static_cast<unsigned int>(baseVertexLocation),
			static_cast<unsigned int>(startInstanceLocation)
		);
	}

	void DX3DBaseObjects::executeCommandList()
	{
		// コマンドリストを閉じる
		m_commandList->Close();

		// コマンドリストを実行する
		ID3D12CommandList* commandLists[] = { m_commandList };
		m_commandQueue->ExecuteCommandLists(1, commandLists);

		// GPU処理が終わるまで待つ
		m_fence->waitGpuProcess(m_commandQueue);

		// コマンドアロケータをリセットする
		m_commandAllocator->Reset();

		// コマンドリストをリセットする
		m_commandList->Reset(m_commandAllocator, nullptr);
	}

	void DX3DBaseObjects::flipScreen() const
	{
		m_swapChain->flipScreen();
		m_swapChain->updateBackBufferIndex();
	}
}