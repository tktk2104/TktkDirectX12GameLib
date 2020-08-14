#include "TktkDX12Wrapper/_BaseObjects/DX3DBaseObjects.h"

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	DX3DBaseObjects::DX3DBaseObjects(const DX3DResourceNum& initParam, HWND hwnd, const tktkMath::Vector2& windowSize, const tktkMath::Color& backGroundColor, bool craeteDebugLayer)
		: m_dX3DResource(initParam)
		, m_backGroundColor(backGroundColor)
	{
#ifdef _DEBUG
		if (craeteDebugLayer)
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
		if (craeteDebugLayer) CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&m_factory));
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
		
		// スワップチェーンを初期化する
		m_swapChain.initialize(hwnd, m_factory, m_commandQueue, windowSize);

		// フェンスを初期化する
		m_fence.initialize(m_device);

		// 初回リセット
		m_commandList->Close();
		m_commandAllocator->Reset();
		m_commandList->Reset(m_commandAllocator, nullptr);

		// ビューポートを作る
		m_dX3DResource.createViewport(getSystemId(SystemViewportType::Basic), { { windowSize, tktkMath::Vector2_v::zero, 1.0f, 0.0f } });

		// シザー矩形を作る
		m_dX3DResource.createScissorRect(getSystemId(SystemScissorRectType::Basic), { { tktkMath::Vector2_v::zero, windowSize } });

		// スワップチェーンのバックバッファーをディスクリプタヒープで使うための準備
		m_dX3DResource.createRtBuffer(getSystemId(SystemRtBufferType::BackBuffer_1), m_swapChain.getPtr(), 0U);
		m_dX3DResource.createRtBuffer(getSystemId(SystemRtBufferType::BackBuffer_2), m_swapChain.getPtr(), 1U);

		// バックバッファー用のディスクリプタヒープを作る
		{
			RtvDescriptorHeapInitParam initParam{};
			initParam.shaderVisible = false;
			initParam.descriptorParamArray.resize(2U);
			initParam.descriptorParamArray.at(0U).type = RtvDescriptorType::normal;
			initParam.descriptorParamArray.at(0U).id = getSystemId(SystemRtBufferType::BackBuffer_1);
			initParam.descriptorParamArray.at(1U).type = RtvDescriptorType::normal;
			initParam.descriptorParamArray.at(1U).id = getSystemId(SystemRtBufferType::BackBuffer_2);

			m_dX3DResource.createRtvDescriptorHeap(getSystemId(SystemRtvDescriptorHeapType::BackBuffer), m_device, initParam);
		}

		// デフォルトの深度バッファーを作る
		{
			DepthStencilBufferInitParam initParam{};
			initParam.depthStencilSize = windowSize;
			initParam.useAsShaderResource = false;

			m_dX3DResource.createDsBuffer(getSystemId(SystemDsBufferType::Basic), m_device, initParam);
		}

		// デフォルトの深度ディスクリプタヒープを作る
		{
			DsvDescriptorHeapInitParam initParam{};
			initParam.shaderVisible = false;
			initParam.descriptorParamArray.push_back({ DsvDescriptorType::normal, getSystemId(SystemDsBufferType::Basic) });

			m_dX3DResource.createDsvDescriptorHeap(getSystemId(SystemDsvDescriptorHeapType::Basic), m_device, initParam);
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

			m_dX3DResource.cpuPriorityCreateTextureBuffer(getSystemId(SystemTextureBufferType::White), m_device, formatParam, dataParam);
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
		m_swapChain.updateBackBufferIndex();
		
		// 現在のバックバッファーの種類を「m_curBackBufferIndex」から求める
		auto curBackBufferType = (m_swapChain.getCurBackBufferIndex() == 0) ? SystemRtBufferType::BackBuffer_1 : SystemRtBufferType::BackBuffer_2;
		
		// バックバッファをレンダーターゲット状態にする
		m_dX3DResource.beginWriteBackBuffer(getSystemId(curBackBufferType), m_commandList);

		// 現在のバックバッファーをを描画先に設定する
		m_dX3DResource.setBackBufferView(m_device, m_commandList, m_swapChain.getCurBackBufferIndex());

		// 現在のバックバッファーを指定した単色で塗りつぶす
		m_dX3DResource.clearRtv(getSystemId(SystemRtvDescriptorHeapType::BackBuffer), m_device, m_commandList, m_swapChain.getCurBackBufferIndex(), m_backGroundColor);
		
		// 全てのデプスステンシルビューをクリアする
		m_dX3DResource.clearDsvAll(m_device, m_commandList);

		// ビューポートを設定する
		m_dX3DResource.setViewport(getSystemId(SystemViewportType::Basic), m_commandList);
		
		// シザー矩形を設定する
		m_dX3DResource.setScissorRect(getSystemId(SystemScissorRectType::Basic), m_commandList);
	}

	void DX3DBaseObjects::endDraw()
	{
		// 現在のバックバッファーの種類を「m_curBackBufferIndex」から求める
		auto curBackBufferType = (m_swapChain.getCurBackBufferIndex() == 0) ? SystemRtBufferType::BackBuffer_1 : SystemRtBufferType::BackBuffer_2;
		
		// バックバッファをプリセット状態にする
		m_dX3DResource.endWriteBackBuffer(getSystemId(curBackBufferType), m_commandList);

		// コマンドリストを実行する
		executeCommandList();

		// 画面をフリップする
		m_swapChain.flipScreen();
	}

	void DX3DBaseObjects::createRootSignature(unsigned int id, const RootSignatureInitParam& initParam)
	{
		m_dX3DResource.createRootSignature(id, m_device, initParam);
	}

	void DX3DBaseObjects::createPipeLineState(unsigned int id, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		m_dX3DResource.createPipeLineState(id, m_device, initParam, shaderFilePath);

		// 初回セット（※最初にセットした時のみ重たい処理となるので、作成直後に先行でセットする）
		m_dX3DResource.setPipeLineState(id, m_commandList);
	}

	void DX3DBaseObjects::createVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_dX3DResource.createVertexBuffer(id, m_device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX3DBaseObjects::createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices)
	{
		m_dX3DResource.createIndexBuffer(id, m_device, indices);
	}

	void DX3DBaseObjects::createCBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dX3DResource.createCBuffer(id, m_device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DBaseObjects::createRtBuffer(unsigned int id, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		m_dX3DResource.createRtBuffer(id, m_device, renderTargetSize, clearColor);
	}

	void DX3DBaseObjects::createDsBuffer(unsigned int id, const DepthStencilBufferInitParam& initParam)
	{
		m_dX3DResource.createDsBuffer(id, m_device, initParam);
	}

	void DX3DBaseObjects::createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam)
	{
		m_dX3DResource.createBasicDescriptorHeap(id, m_device, initParam);
	}

	void DX3DBaseObjects::createRtvDescriptorHeap(unsigned int id, const RtvDescriptorHeapInitParam& initParam)
	{
		m_dX3DResource.createRtvDescriptorHeap(id, m_device, initParam);
	}

	void DX3DBaseObjects::createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam)
	{
		m_dX3DResource.createDsvDescriptorHeap(id, m_device, initParam);
	}

	void DX3DBaseObjects::cpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_dX3DResource.cpuPriorityCreateTextureBuffer(id, m_device, formatParam, dataParam);
	}

	void DX3DBaseObjects::gpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_dX3DResource.gpuPriorityCreateTextureBuffer(id, m_device, m_commandList, formatParam, dataParam);
	}

	void DX3DBaseObjects::cpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath)
	{
		m_dX3DResource.cpuPriorityLoadTextureBuffer(id, m_device, texDataPath);
	}

	void DX3DBaseObjects::gpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath)
	{
		m_dX3DResource.gpuPriorityLoadTextureBuffer(id, m_device, m_commandList, texDataPath);
	}

	void DX3DBaseObjects::setBackGroundColor(const tktkMath::Color& backGroundColor)
	{
		m_backGroundColor = backGroundColor;
	}

	void DX3DBaseObjects::updateVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_dX3DResource.updateVertexBuffer(id, m_device, m_commandList, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX3DBaseObjects::updateIndexBuffer(unsigned int id, const std::vector<unsigned short>& indexDataArray)
	{
		m_dX3DResource.updateIndexBuffer(id, m_device, m_commandList, indexDataArray);
	}

	void DX3DBaseObjects::updateCBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dX3DResource.updateCBuffer(id, m_device, m_commandList, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DBaseObjects::clearRtv(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color) const
	{
		m_dX3DResource.clearRtv(id, m_device, m_commandList, rtvLocationIndex, color);
	}

	const tktkMath::Vector3& DX3DBaseObjects::getTextureBufferSizePx(unsigned int id) const
	{
		return m_dX3DResource.getTextureBufferSizePx(id);
	}

	const tktkMath::Vector2& DX3DBaseObjects::getDsBufferSizePx(unsigned int id) const
	{
		return m_dX3DResource.getDsBufferSizePx(id);
	}

	const tktkMath::Vector2& DX3DBaseObjects::getRtBufferSizePx(unsigned int id) const
	{
		return m_dX3DResource.getRtBufferSizePx(id);
	}

	void DX3DBaseObjects::setRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		m_dX3DResource.setRtv(rtvDescriptorHeapId, m_device, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::setRtvAndDsv(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		m_dX3DResource.setRtvAndDsv(dsvDescriptorHeapId, dsvDescriptorHeapId, m_device, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::setOnlyDsv(unsigned int id) const
	{
		m_dX3DResource.setOnlyDsv(id, m_device, m_commandList);
	}

	void DX3DBaseObjects::setBackBufferView() const
	{
		m_dX3DResource.setBackBufferView(m_device, m_commandList, m_swapChain.getCurBackBufferIndex());
	}

	void DX3DBaseObjects::setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapId) const
	{
		m_dX3DResource.setBackBufferViewAndDsv(dsvDescriptorHeapId, m_device, m_commandList, m_swapChain.getCurBackBufferIndex());
	}

	void DX3DBaseObjects::unSetRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		m_dX3DResource.unSetRtv(rtvDescriptorHeapId, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::unSetDsv(unsigned int dsvDescriptorHeapId) const
	{
		m_dX3DResource.unSetDsv(dsvDescriptorHeapId, m_commandList);
	}

	void DX3DBaseObjects::setViewport(unsigned int id) const
	{
		m_dX3DResource.setViewport(id, m_commandList);
	}

	void DX3DBaseObjects::setScissorRect(unsigned int id) const
	{
		m_dX3DResource.setScissorRect(id, m_commandList);
	}

	void DX3DBaseObjects::setPipeLineState(unsigned int id) const
	{
		m_dX3DResource.setPipeLineState(id, m_commandList);
	}

	void DX3DBaseObjects::setVertexBuffer(unsigned int id) const
	{
		m_dX3DResource.setVertexBuffer(id, m_commandList);
	}

	void DX3DBaseObjects::setIndexBuffer(unsigned int id) const
	{
		m_dX3DResource.setIndexBuffer(id, m_commandList);
	}

	void DX3DBaseObjects::setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray) const
	{
		m_dX3DResource.setDescriptorHeap(m_device, m_commandList, heapParamArray);
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
		m_fence.waitGpuProcess(m_commandQueue);

		// コマンドアロケータをリセットする
		m_commandAllocator->Reset();

		// コマンドリストをリセットする
		m_commandList->Reset(m_commandAllocator, nullptr);

		// コピー元バッファを削除する
		m_dX3DResource.deleteUploadBufferAll();
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemViewportType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemScissorRectType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemVertexBufferType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemIndexBufferType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemCBufferType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemTextureBufferType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemRtBufferType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemDsBufferType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemBasicDescriptorHeapType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemRtvDescriptorHeapType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemDsvDescriptorHeapType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemRootSignatureType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemPipeLineStateType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}
}