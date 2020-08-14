#include "TktkDX12Wrapper/Resource/DX3DResource.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	DX3DResource::DX3DResource(DX3DResourceInitParam initParam)
		: m_sysResIdGetter(&initParam)	// <=【※ここの初期化時に「initParam」の値にデフォルトのリソースの数が足されます】
		, m_viewport(initParam.viewPortNum)
		, m_scissorRect(initParam.scissorRectNum)
		, m_graphicsPipeLine(initParam.pipeLineStateNum, initParam.rootSignatureNum)
		, m_descriptorHeap(initParam.descriptorHeapNum)
		, m_bufferResource(initParam.bufferResourceNum)
	{
	}

	void DX3DResource::createViewport(unsigned int id, const std::vector<ViewportInitParam>& initParamArray)
	{
		m_viewport.create(id, initParamArray);
	}

	void DX3DResource::createScissorRect(unsigned int id, const std::vector<ScissorRectInitParam>& initParamArray)
	{
		m_scissorRect.create(id, initParamArray);
	}

	void DX3DResource::createRootSignature(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		m_graphicsPipeLine.createRootSignature(id, device, initParam);
	}

	void DX3DResource::createPipeLineState(unsigned int id, ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		m_graphicsPipeLine.createPipeLineState(id, device, initParam, shaderFilePath);
	}

	void DX3DResource::createVertexBuffer(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_bufferResource.createVertexBuffer(id, device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX3DResource::createIndexBuffer(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indices)
	{
		m_bufferResource.createIndexBuffer(id, device, indices);
	}

	void DX3DResource::createCBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_bufferResource.createCBuffer(id, device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DResource::createRtBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		m_bufferResource.createRtBuffer(id, device, renderTargetSize, clearColor);
	}

	void DX3DResource::createRtBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		m_bufferResource.createRtBuffer(id, swapChain, backBufferIndex);
	}

	void DX3DResource::createDsBuffer(unsigned int id, ID3D12Device* device, const DepthStencilBufferInitParam& initParam)
	{
		m_bufferResource.createDsBuffer(id, device, initParam);
	}

	void DX3DResource::cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_bufferResource.cpuPriorityCreateTextureBuffer(id, device, formatParam, dataParam);
	}

	void DX3DResource::gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_bufferResource.gpuPriorityCreateTextureBuffer(id, device, commandList, formatParam, dataParam);
	}

	void DX3DResource::cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const std::string& texDataPath)
	{
		m_bufferResource.cpuPriorityLoadTextureBuffer(id, device, texDataPath);
	}

	void DX3DResource::gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath)
	{
		m_bufferResource.gpuPriorityLoadTextureBuffer(id, device, commandList, texDataPath);
	}

	void DX3DResource::createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		// バッファを割り当てていないディスクリプタヒープを作る
		m_descriptorHeap.createBasicDescriptorHeap(id, device, initParam);

		// 全てのディスクリプタの先頭アドレスの配列を取得する
		auto cpuHeapHandleArray = m_descriptorHeap.getCpuBasicHeapHandleArray(id, device);

		// 設定しているディスクリプタの番号
		unsigned int curDescriptorIndex = 0U;

		for (const auto& descriptorParam : initParam.descriptorTableParamArray)
		{
			for (const auto& node : descriptorParam.descriptorParamArray)
			{
				switch (descriptorParam.type)
				{
				case BasicDescriptorType::constantBuffer:

					createBasicDescriptorCbv(device, cpuHeapHandleArray.at(curDescriptorIndex), node);
					break;

				case BasicDescriptorType::textureBuffer:

					createBasicDescriptorSrv(device, cpuHeapHandleArray.at(curDescriptorIndex), node);
					break;
				}

				curDescriptorIndex++;
			}
		}
	}

	void DX3DResource::createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		// バッファを割り当てていないディスクリプタヒープを作る
		m_descriptorHeap.createRtvDescriptorHeap(id, device, initParam);

		auto cpuHeapHandleArray = m_descriptorHeap.getCpuRtvHeapHandleArray(id, device);

		for (unsigned int i = 0; i < initParam.descriptorParamArray.size(); i++)
		{
			switch (initParam.descriptorParamArray.at(i).type)
			{
			case RtvDescriptorType::normal:

				m_bufferResource.createRtv(initParam.descriptorParamArray.at(i).id, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
	}

	void DX3DResource::createDsvDescriptorHeap(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam)
	{
		// バッファを割り当てていないディスクリプタヒープを作る
		m_descriptorHeap.createDsvDescriptorHeap(id, device, initParam);

		auto cpuHeapHandleArray = m_descriptorHeap.getCpuDsvHeapHandleArray(id, device);

		for (unsigned int i = 0; i < initParam.descriptorParamArray.size(); i++)
		{
			switch (initParam.descriptorParamArray.at(i).type)
			{
			case DsvDescriptorType::normal:

				m_bufferResource.createDsv(initParam.descriptorParamArray.at(i).id, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
	}

	void DX3DResource::updateVertexBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_bufferResource.updateVertexBuffer(id, device, commandList, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX3DResource::updateIndexBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray)
	{
		m_bufferResource.updateIndexBuffer(id, device, commandList, indexDataArray);
	}

	void DX3DResource::updateCBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_bufferResource.updateCBuffer(id, device, commandList, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DResource::deleteUploadBufferAll()
	{
		m_bufferResource.deleteUploadBufferAll();
	}

	void DX3DResource::clearRtv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color) const
	{
		m_descriptorHeap.clearRtv(id, device, commandList, rtvLocationIndex, color);
	}

	void DX3DResource::clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource.allBeginWriteDsBuffer(commandList);

		m_descriptorHeap.clearDsvAll(device, commandList);

		m_bufferResource.allEndWriteDsBuffer(commandList);
	}

	const tktkMath::Vector3& DX3DResource::getTextureBufferSizePx(unsigned int id) const
	{
		return m_bufferResource.getTextureSizePx(id);
	}

	const tktkMath::Vector2& DX3DResource::getDsBufferSizePx(unsigned int id) const
	{
		return m_bufferResource.getDepthStencilSizePx(id);
	}

	const tktkMath::Vector2& DX3DResource::getRtBufferSizePx(unsigned int id) const
	{
		return m_bufferResource.getRenderTargetSizePx(id);
	}

	const std::vector<unsigned int>& DX3DResource::getRtvDescriptorHeapUseBufferIdArray(unsigned int id) const
	{
		return m_descriptorHeap.getRtvDescriptorHeapUseBufferIdArray(id);
	}

	const std::vector<unsigned int>& DX3DResource::getDsvDescriptorHeapUseBufferIdArray(unsigned int id) const
	{
		return m_descriptorHeap.getDsvDescriptorHeapUseBufferIdArray(id);
	}

	void DX3DResource::setRtv(unsigned int rtvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		// 使用するレンダーターゲットバッファーを取得して、書き込み状態に設定する
		auto rtvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getRtvDescriptorHeapUseBufferIdArray(rtvDescriptorHeapId);
		for (unsigned int i = 0; i < rtvCount; i++)
		{
			m_bufferResource.beginWriteBasicRtBuffer(rtvDescriptorHeapUseBufferIdArray.at(startRtvLocationIndex + i), commandList);
		}

		// 「レンダーターゲット用のディスクリプタヒープ」を設定する
		m_descriptorHeap.setRtv(rtvDescriptorHeapId, device, commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DResource::setRtvAndDsv(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		// 使用するレンダーターゲットバッファーを取得して、書き込み状態に設定する
		auto rtvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getRtvDescriptorHeapUseBufferIdArray(rtvDescriptorHeapId);
		for (unsigned int i = 0; i < rtvCount; i++)
		{
			m_bufferResource.beginWriteBasicRtBuffer(rtvDescriptorHeapUseBufferIdArray.at(startRtvLocationIndex + i), commandList);
		}

		// 使用する深度ステンシルバッファーを取得して、書き込み状態に設定する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getDsvDescriptorHeapUseBufferIdArray(dsvDescriptorHeapId);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource.beginWriteDsBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}

		// 「レンダーターゲット用のディスクリプタヒープ」と「深度ステンシル用のディスクリプタヒープ」を設定する
		m_descriptorHeap.setRtvAndDsv(rtvDescriptorHeapId, dsvDescriptorHeapId, device, commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DResource::setOnlyDsv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		// 使用する深度ステンシルバッファーを取得して、書き込み状態に設定する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getDsvDescriptorHeapUseBufferIdArray(id);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource.beginWriteDsBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}

		// 「深度ステンシル用のディスクリプタヒープ」を設定する
		m_descriptorHeap.setOnlyDsv(id, device, commandList);
	}

	void DX3DResource::setBackBufferView(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const
	{
		// バックバッファはフレームの初めに書き込み状態に設定されているのでそのまま ディスクリプタヒープを設定できる
		m_descriptorHeap.setRtv(getSystemId(SystemRtvDescriptorHeapType::BackBuffer), device, commandList, backBufferIndex, 1U);
	}

	void DX3DResource::setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const
	{
		// 使用する深度ステンシルバッファーを取得して、書き込み状態に設定する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getDsvDescriptorHeapUseBufferIdArray(dsvDescriptorHeapId);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource.beginWriteDsBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}

		// 「バックバッファー用のディスクリプタヒープ」と「深度ステンシル用のディスクリプタヒープ」を設定する
		m_descriptorHeap.setRtvAndDsv(getSystemId(SystemRtvDescriptorHeapType::BackBuffer), dsvDescriptorHeapId, device, commandList, backBufferIndex, 1U);
	}

	void DX3DResource::unSetRtv(unsigned int rtvDescriptorHeapId, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		// 使用していたレンダーターゲットバッファーを取得して、ピクセルシェーダーで使用する状態に変更する
		auto rtvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getRtvDescriptorHeapUseBufferIdArray(rtvDescriptorHeapId);
		for (unsigned int i = 0; i < rtvCount; i++)
		{
			m_bufferResource.endWriteBasicRtBuffer(rtvDescriptorHeapUseBufferIdArray.at(startRtvLocationIndex + i), commandList);
		}
	}

	void DX3DResource::unSetDsv(unsigned int dsvDescriptorHeapId, ID3D12GraphicsCommandList* commandList) const
	{
		// 使用していた深度ステンシルバッファーを取得して、ピクセルシェーダーで使用する状態に変更する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getDsvDescriptorHeapUseBufferIdArray(dsvDescriptorHeapId);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource.endWriteDsBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}
	}

	void DX3DResource::beginWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource.beginWriteBackBuffer(id, commandList);
	}

	void DX3DResource::endWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource.endWriteBackBuffer(id, commandList);
	}

	void DX3DResource::setViewport(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_viewport.set(id, commandList);
	}

	void DX3DResource::setScissorRect(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_scissorRect.set(id, commandList);
	}

	void DX3DResource::setPipeLineState(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_graphicsPipeLine.set(id, commandList);
	}

	void DX3DResource::setVertexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource.setVertexBuffer(id, commandList);
	}

	void DX3DResource::setIndexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource.setIndexBuffer(id, commandList);
	}

	void DX3DResource::setDescriptorHeap(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray) const
	{
		m_descriptorHeap.set(device, commandList, heapParamArray);
	}

	unsigned int DX3DResource::getSystemId(SystemViewportType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}

	unsigned int DX3DResource::getSystemId(SystemScissorRectType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}

	unsigned int DX3DResource::getSystemId(SystemVertexBufferType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}

	unsigned int DX3DResource::getSystemId(SystemIndexBufferType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}

	unsigned int DX3DResource::getSystemId(SystemCBufferType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}

	unsigned int DX3DResource::getSystemId(SystemTextureBufferType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}

	unsigned int DX3DResource::getSystemId(SystemRtBufferType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}

	unsigned int DX3DResource::getSystemId(SystemDsBufferType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}

	unsigned int DX3DResource::getSystemId(SystemBasicDescriptorHeapType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}

	unsigned int DX3DResource::getSystemId(SystemRtvDescriptorHeapType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}

	unsigned int DX3DResource::getSystemId(SystemDsvDescriptorHeapType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}

	unsigned int DX3DResource::getSystemId(SystemRootSignatureType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}

	unsigned int DX3DResource::getSystemId(SystemPipeLineStateType type) const
	{
		return m_sysResIdGetter.getSystemId(type);
	}

	void DX3DResource::createBasicDescriptorCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const
	{
#ifdef _DEBUG
		if (useBufferParam.type != BufferType::constant) throw std::runtime_error("useBuffer Type Error -not cbuffer-");
#endif // _DEBUG

		m_bufferResource.createCbv(useBufferParam.id, device, cpuHandle);
	}

	void DX3DResource::createBasicDescriptorSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const
	{
		switch (useBufferParam.type)
		{
		case BufferType::texture:

			m_bufferResource.createSrv(useBufferParam.id, device, cpuHandle);
			break;

		case BufferType::renderTarget:

			m_bufferResource.createRtSrv(useBufferParam.id, device, cpuHandle);
			break;

		case BufferType::depthStencil:

			m_bufferResource.createDsSrv(useBufferParam.id, device, cpuHandle);
			break;

		default:
#ifdef _DEBUG
			throw std::runtime_error("useBuffer Type Error -not ShaderResourceView-");
#endif // _DEBUG
			break;
		}
	}
}