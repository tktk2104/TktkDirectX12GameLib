#include "TktkDX12Wrapper/_BaseObjects/DX3DBaseObjects.h"

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix4.h>
#include "TktkDX12Wrapper/SwapChain/SwapChain.h"
#include "TktkDX12Wrapper/Fence/Fence.h"
#include "TktkDX12Wrapper/Resource/DX3DResource.h"

namespace tktk
{
	DX3DBaseObjects::DX3DBaseObjects(const DX3DBaseObjectsInitParam& initParam)
		: m_backGroundColor(initParam.backGroundColor)
	{
		// DX12のリソースの管理クラスを作る
		m_dX3DResource	= std::make_unique<DX3DResource>(initParam.resourceNum);

#ifdef _DEBUG
		if (initParam.craeteDebugLayer)
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
		if (initParam.craeteDebugLayer) CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&m_factory));
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
		commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		commandQueueDesc.NodeMask = 0;
		commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		m_device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&m_commandQueue));
		
		// スワップチェーンを作る
		m_swapChain = std::make_unique<SwapChain>(initParam.hwnd, m_factory, m_commandQueue, initParam.windowSize);

		// フェンスを作る
		m_fence		= std::make_unique<Fence>(m_device);

		// 初回リセット
		m_commandList->Close();
		m_commandAllocator->Reset();
		m_commandList->Reset(m_commandAllocator, nullptr);

		// ビューポートを作る
		setSystemHandle(
			SystemViewportType::Basic,
			m_dX3DResource->createViewport({ { initParam.windowSize, tktkMath::Vector2_v::zero, 1.0f, 0.0f } })
		);

		// シザー矩形を作る
		setSystemHandle(
			SystemScissorRectType::Basic,
			m_dX3DResource->createScissorRect({ { tktkMath::Vector2_v::zero, initParam.windowSize } })
		);

		// スワップチェーンのバックバッファーをディスクリプタヒープで使うための準備
		setSystemHandle(SystemRtBufferType::BackBuffer_1, m_dX3DResource->createRtBuffer(m_swapChain->getPtr(), 0U));
		setSystemHandle(SystemRtBufferType::BackBuffer_2, m_dX3DResource->createRtBuffer(m_swapChain->getPtr(), 1U));

		// バックバッファー用のディスクリプタヒープを作る
		{
			RtvDescriptorHeapInitParam rtvDescriptorHeapInitParam{};
			rtvDescriptorHeapInitParam.shaderVisible = false;
			rtvDescriptorHeapInitParam.descriptorParamArray.resize(2U);
			rtvDescriptorHeapInitParam.descriptorParamArray.at(0U).type = RtvDescriptorType::normal;
			rtvDescriptorHeapInitParam.descriptorParamArray.at(0U).handle	= getSystemHandle(SystemRtBufferType::BackBuffer_1);
			rtvDescriptorHeapInitParam.descriptorParamArray.at(1U).type = RtvDescriptorType::normal;
			rtvDescriptorHeapInitParam.descriptorParamArray.at(1U).handle	= getSystemHandle(SystemRtBufferType::BackBuffer_2);

			setSystemHandle(SystemRtvDescriptorHeapType::BackBuffer, m_dX3DResource->createRtvDescriptorHeap(m_device, rtvDescriptorHeapInitParam));
		}

		// デフォルトの深度バッファーを作る
		{
			DepthStencilBufferInitParam dsbInitParam{};
			dsbInitParam.depthStencilSize = initParam.windowSize;
			dsbInitParam.useAsShaderResource = false;

			setSystemHandle(SystemDsBufferType::Basic, m_dX3DResource->createDsBuffer(m_device, dsbInitParam));
		}

		// デフォルトの深度ディスクリプタヒープを作る
		{
			DsvDescriptorHeapInitParam dsvDescriptorHeapInitParam{};
			dsvDescriptorHeapInitParam.shaderVisible = false;
			dsvDescriptorHeapInitParam.descriptorParamArray.push_back({ DsvDescriptorType::normal, getSystemHandle(SystemDsBufferType::Basic) });

			setSystemHandle(SystemDsvDescriptorHeapType::Basic, m_dX3DResource->createDsvDescriptorHeap(m_device, dsvDescriptorHeapInitParam));
		}

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

			setSystemHandle(SystemTextureBufferType::White, m_dX3DResource->cpuPriorityCreateTextureBuffer(m_device, formatParam, dataParam));
		}
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

	void DX3DBaseObjects::beginDraw()
	{
		// 現在のバックバッファーを識別するインデックスを更新する
		m_swapChain->updateBackBufferIndex();
		
		// 現在のバックバッファーの種類を「m_curBackBufferIndex」から求める
		auto curBackBufferType = (m_swapChain->getCurBackBufferIndex() == 0) ? SystemRtBufferType::BackBuffer_1 : SystemRtBufferType::BackBuffer_2;
		
		// バックバッファをレンダーターゲット状態にする
		m_dX3DResource->beginWriteBackBuffer(getSystemHandle(curBackBufferType), m_commandList);

		// 現在のバックバッファーをを描画先に設定する
		m_dX3DResource->setBackBufferView(m_device, m_commandList, m_swapChain->getCurBackBufferIndex());

		// 現在のバックバッファーを指定した単色で塗りつぶす
		m_dX3DResource->clearRtv(getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer), m_device, m_commandList, m_swapChain->getCurBackBufferIndex(), m_backGroundColor);
		
		// 全てのデプスステンシルビューをクリアする
		m_dX3DResource->clearDsvAll(m_device, m_commandList);

		// ビューポートを設定する
		m_dX3DResource->setViewport(getSystemHandle(SystemViewportType::Basic), m_commandList);
		
		// シザー矩形を設定する
		m_dX3DResource->setScissorRect(getSystemHandle(SystemScissorRectType::Basic), m_commandList);
	}

	void DX3DBaseObjects::endDraw()
	{
		// 現在のバックバッファーの種類を「m_curBackBufferIndex」から求める
		auto curBackBufferType = (m_swapChain->getCurBackBufferIndex() == 0) ? SystemRtBufferType::BackBuffer_1 : SystemRtBufferType::BackBuffer_2;
		
		// バックバッファをプリセット状態にする
		m_dX3DResource->endWriteBackBuffer(getSystemHandle(curBackBufferType), m_commandList);

		// コマンドリストを実行する
		executeCommandList();

		// 画面をフリップする
		m_swapChain->flipScreen();
	}

	unsigned int DX3DBaseObjects::createRootSignature(const RootSignatureInitParam& initParam)
	{
		return m_dX3DResource->createRootSignature(m_device, initParam);
	}

	unsigned int DX3DBaseObjects::createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		unsigned int handle = m_dX3DResource->createPipeLineState(m_device, initParam, shaderFilePath);

		// 初回セット（※最初にセットした時のみ重たい処理となるので、作成直後に先行でセットする）
		m_dX3DResource->setPipeLineState(handle, m_commandList);

		return handle;
	}

	unsigned int DX3DBaseObjects::createCopyBuffer(const CopyBufferInitParam& initParam)
	{
		return m_dX3DResource->createCopyBuffer(m_device, initParam);
	}

	unsigned int DX3DBaseObjects::copyCopyBuffer(unsigned int originalHandle)
	{
		return m_dX3DResource->copyCopyBuffer(m_device, originalHandle);
	}

	unsigned int DX3DBaseObjects::createVertexBuffer(unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		return m_dX3DResource->createVertexBuffer(m_device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	unsigned int DX3DBaseObjects::createIndexBuffer(const std::vector<unsigned short>& indices)
	{
		return m_dX3DResource->createIndexBuffer(m_device, indices);
	}

	unsigned int DX3DBaseObjects::createCBuffer(unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		return m_dX3DResource->createCBuffer(m_device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	unsigned int DX3DBaseObjects::createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		return m_dX3DResource->createRtBuffer(m_device, renderTargetSize, clearColor);
	}

	unsigned int DX3DBaseObjects::createDsBuffer(const DepthStencilBufferInitParam& initParam)
	{
		return m_dX3DResource->createDsBuffer(m_device, initParam);
	}

	unsigned int DX3DBaseObjects::createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam)
	{
		return m_dX3DResource->createBasicDescriptorHeap(m_device, initParam);
	}

	unsigned int DX3DBaseObjects::createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam)
	{
		return m_dX3DResource->createRtvDescriptorHeap(m_device, initParam);
	}

	unsigned int DX3DBaseObjects::createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam)
	{
		return m_dX3DResource->createDsvDescriptorHeap(m_device, initParam);
	}

	unsigned int DX3DBaseObjects::cpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_dX3DResource->cpuPriorityCreateTextureBuffer(m_device, formatParam, dataParam);
	}

	unsigned int DX3DBaseObjects::gpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_dX3DResource->gpuPriorityCreateTextureBuffer(m_device, m_commandList, formatParam, dataParam);
	}

	unsigned int DX3DBaseObjects::cpuPriorityLoadTextureBuffer(const std::string& texDataPath)
	{
		return m_dX3DResource->cpuPriorityLoadTextureBuffer(m_device, texDataPath);
	}

	unsigned int DX3DBaseObjects::gpuPriorityLoadTextureBuffer(const std::string& texDataPath)
	{
		return m_dX3DResource->gpuPriorityLoadTextureBuffer(m_device, m_commandList, texDataPath);
	}

	void DX3DBaseObjects::eraseViewport(unsigned int handle)
	{
		m_dX3DResource->eraseViewport(handle);
	}

	void DX3DBaseObjects::eraseScissorRect(unsigned int handle)
	{
		m_dX3DResource->eraseScissorRect(handle);
	}

	void DX3DBaseObjects::eraseRootSignature(unsigned int handle)
	{
		m_dX3DResource->eraseRootSignature(handle);
	}

	void DX3DBaseObjects::erasePipeLineState(unsigned int handle)
	{
		m_dX3DResource->erasePipeLineState(handle);
	}

	void DX3DBaseObjects::eraseCopyBuffer(unsigned int handle)
	{
		m_dX3DResource->eraseCopyBuffer(handle);
	}

	void DX3DBaseObjects::eraseVertexBuffer(unsigned int handle)
	{
		m_dX3DResource->eraseVertexBuffer(handle);
	}

	void DX3DBaseObjects::eraseIndexBuffer(unsigned int handle)
	{
		m_dX3DResource->eraseIndexBuffer(handle);
	}

	void DX3DBaseObjects::eraseCBuffer(unsigned int handle)
	{
		m_dX3DResource->eraseCBuffer(handle);
	}

	void DX3DBaseObjects::eraseTextureBuffer(unsigned int handle)
	{
		m_dX3DResource->eraseTextureBuffer(handle);
	}

	void DX3DBaseObjects::eraseDsBuffer(unsigned int handle)
	{
		m_dX3DResource->eraseDsBuffer(handle);
	}

	void DX3DBaseObjects::eraseRtBuffer(unsigned int handle)
	{
		m_dX3DResource->eraseRtBuffer(handle);
	}

	void DX3DBaseObjects::eraseBasicDescriptorHeap(unsigned int handle)
	{
		m_dX3DResource->eraseBasicDescriptorHeap(handle);
	}

	void DX3DBaseObjects::eraseRtvDescriptorHeap(unsigned int handle)
	{
		m_dX3DResource->eraseRtvDescriptorHeap(handle);
	}

	void DX3DBaseObjects::eraseDsvDescriptorHeap(unsigned int handle)
	{
		m_dX3DResource->eraseDsvDescriptorHeap(handle);
	}

	void DX3DBaseObjects::setBackGroundColor(const tktkMath::Color& backGroundColor)
	{
		m_backGroundColor = backGroundColor;
	}

	void DX3DBaseObjects::updateCopyBuffer(unsigned int handle, unsigned int bufferSize, const void* bufferDataTopPos)
	{
		m_dX3DResource->updateCopyBuffer(handle, bufferSize, bufferDataTopPos);
	}

	void DX3DBaseObjects::copyBuffer(unsigned int handle) const
	{
		m_dX3DResource->copyBuffer(handle, m_commandList);
	}

	void DX3DBaseObjects::updateVertexBuffer(unsigned int handle, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_dX3DResource->updateVertexBuffer(handle, m_device, m_commandList, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX3DBaseObjects::updateIndexBuffer(unsigned int handle, const std::vector<unsigned short>& indexDataArray)
	{
		m_dX3DResource->updateIndexBuffer(handle, m_device, m_commandList, indexDataArray);
	}

	void DX3DBaseObjects::updateCBuffer(unsigned int handle, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dX3DResource->updateCBuffer(handle, m_device, m_commandList, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DBaseObjects::clearRtv(unsigned int handle, unsigned int rtvLocationIndex, const tktkMath::Color& color) const
	{
		m_dX3DResource->clearRtv(handle, m_device, m_commandList, rtvLocationIndex, color);
	}

	const tktkMath::Vector3& DX3DBaseObjects::getTextureBufferSizePx(unsigned int handle) const
	{
		return m_dX3DResource->getTextureBufferSizePx(handle);
	}

	const tktkMath::Vector2& DX3DBaseObjects::getDsBufferSizePx(unsigned int handle) const
	{
		return m_dX3DResource->getDsBufferSizePx(handle);
	}

	const tktkMath::Vector2& DX3DBaseObjects::getRtBufferSizePx(unsigned int handle) const
	{
		return m_dX3DResource->getRtBufferSizePx(handle);
	}

	void DX3DBaseObjects::setRtv(unsigned int rtvDescriptorHeapHandle, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		m_dX3DResource->setRtv(rtvDescriptorHeapHandle, m_device, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::setRtvAndDsv(unsigned int rtvDescriptorHeapHandle, unsigned int dsvDescriptorHeapHandle, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		m_dX3DResource->setRtvAndDsv(rtvDescriptorHeapHandle, dsvDescriptorHeapHandle, m_device, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::setOnlyDsv(unsigned int handle) const
	{
		m_dX3DResource->setOnlyDsv(handle, m_device, m_commandList);
	}

	void DX3DBaseObjects::setBackBufferView() const
	{
		m_dX3DResource->setBackBufferView(m_device, m_commandList, m_swapChain->getCurBackBufferIndex());
	}

	void DX3DBaseObjects::setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapHandle) const
	{
		m_dX3DResource->setBackBufferViewAndDsv(dsvDescriptorHeapHandle, m_device, m_commandList, m_swapChain->getCurBackBufferIndex());
	}

	void DX3DBaseObjects::unSetRtv(unsigned int rtvDescriptorHeapHandle, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		m_dX3DResource->unSetRtv(rtvDescriptorHeapHandle, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::unSetDsv(unsigned int dsvDescriptorHeapHandle) const
	{
		m_dX3DResource->unSetDsv(dsvDescriptorHeapHandle, m_commandList);
	}

	void DX3DBaseObjects::setViewport(unsigned int handle) const
	{
		m_dX3DResource->setViewport(handle, m_commandList);
	}

	void DX3DBaseObjects::setScissorRect(unsigned int handle) const
	{
		m_dX3DResource->setScissorRect(handle, m_commandList);
	}

	void DX3DBaseObjects::setPipeLineState(unsigned int handle) const
	{
		m_dX3DResource->setPipeLineState(handle, m_commandList);
	}

	void DX3DBaseObjects::setVertexBuffer(unsigned int handle) const
	{
		m_dX3DResource->setVertexBuffer(handle, m_commandList);
	}

	void DX3DBaseObjects::setIndexBuffer(unsigned int handle) const
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

	void DX3DBaseObjects::setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology) const
	{
		m_commandList->IASetPrimitiveTopology(topology);
	}

	void DX3DBaseObjects::drawInstanced(unsigned int vertexCountPerInstance, unsigned int instanceCount, unsigned int baseVertexLocation, unsigned int startInstanceLocation) const
	{
		m_commandList->DrawInstanced(vertexCountPerInstance, instanceCount, baseVertexLocation, startInstanceLocation);
	}

	void DX3DBaseObjects::drawIndexedInstanced(unsigned int indexCountPerInstance, unsigned int instanceCount, unsigned int startIndexLocation, unsigned int baseVertexLocation, unsigned int startInstanceLocation) const
	{
		m_commandList->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
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

		// コピー元バッファを削除する
		m_dX3DResource->deleteUploadBufferAll();
	}

	unsigned int DX3DBaseObjects::getSystemHandle(SystemViewportType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	unsigned int DX3DBaseObjects::getSystemHandle(SystemScissorRectType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	unsigned int DX3DBaseObjects::getSystemHandle(SystemVertexBufferType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	unsigned int DX3DBaseObjects::getSystemHandle(SystemIndexBufferType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	unsigned int DX3DBaseObjects::getSystemHandle(SystemCBufferType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	unsigned int DX3DBaseObjects::getSystemHandle(SystemTextureBufferType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	unsigned int DX3DBaseObjects::getSystemHandle(SystemRtBufferType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	unsigned int DX3DBaseObjects::getSystemHandle(SystemDsBufferType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	unsigned int DX3DBaseObjects::getSystemHandle(SystemBasicDescriptorHeapType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	unsigned int DX3DBaseObjects::getSystemHandle(SystemRtvDescriptorHeapType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	unsigned int DX3DBaseObjects::getSystemHandle(SystemDsvDescriptorHeapType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	unsigned int DX3DBaseObjects::getSystemHandle(SystemRootSignatureType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	unsigned int DX3DBaseObjects::getSystemHandle(SystemPipeLineStateType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	void DX3DBaseObjects::setSystemHandle(SystemViewportType type, unsigned int handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemScissorRectType type, unsigned int handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemVertexBufferType type, unsigned int handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemIndexBufferType type, unsigned int handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemCBufferType type, unsigned int handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemTextureBufferType type, unsigned int handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemRtBufferType type, unsigned int handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemDsBufferType type, unsigned int handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemBasicDescriptorHeapType type, unsigned int handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemRtvDescriptorHeapType type, unsigned int handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemDsvDescriptorHeapType type, unsigned int handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemRootSignatureType type, unsigned int handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemPipeLineStateType type, unsigned int handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}
}