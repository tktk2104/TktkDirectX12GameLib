#include "TktkDX12Wrapper/Resource/DX3DResource.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

#include "TktkDX12Wrapper/Resource/_SystemResourceHandleGetter/SystemResourceHandleGetter.h"
#include "TktkDX12Wrapper/Resource/Viewport/Viewport.h"
#include "TktkDX12Wrapper/Resource/ScissorRect/ScissorRect.h"
#include "TktkDX12Wrapper/Resource/GraphicsPipeLine/GraphicsPipeLine.h"
#include "TktkDX12Wrapper/Resource/DescriptorHeap/DescriptorHeap.h"
#include "TktkDX12Wrapper/Resource/Buffer/BufferResource.h"

namespace tktk
{
	DX3DResource::DX3DResource(const DX3DResourceNum& resNum)
	{
		m_sysResHandleGetter	= std::make_unique<SystemResourceHandleGetter>();
		m_viewport				= std::make_unique<Viewport>(resNum.viewPortNum);
		m_scissorRect			= std::make_unique<ScissorRect>(resNum.scissorRectNum);
		m_graphicsPipeLine		= std::make_unique<GraphicsPipeLine>(resNum.graphicsPipeLineResourceNum);
		m_descriptorHeap		= std::make_unique<DescriptorHeap>(resNum.descriptorHeapNum);
		m_bufferResource		= std::make_unique<BufferResource>(resNum.bufferResourceNum);
	}

	// デストラクタを非インライン化する
	DX3DResource::~DX3DResource() = default;

	unsigned int DX3DResource::createViewport(const std::vector<ViewportInitParam>& initParamArray)
	{
		return m_viewport->create(initParamArray);
	}

	unsigned int DX3DResource::createScissorRect(const std::vector<ScissorRectInitParam>& initParamArray)
	{
		return m_scissorRect->create(initParamArray);
	}

	unsigned int DX3DResource::createRootSignature(ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		return m_graphicsPipeLine->createRootSignature(device, initParam);
	}

	unsigned int DX3DResource::createPipeLineState(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		return m_graphicsPipeLine->createPipeLineState(device, initParam, shaderFilePath);
	}

	unsigned int DX3DResource::createVertexBuffer(ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		return m_bufferResource->createVertexBuffer(device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	unsigned int DX3DResource::createIndexBuffer(ID3D12Device* device, const std::vector<unsigned short>& indices)
	{
		return m_bufferResource->createIndexBuffer(device, indices);
	}

	unsigned int DX3DResource::createCBuffer(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		return m_bufferResource->createCBuffer(device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	unsigned int DX3DResource::createRtBuffer(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		return m_bufferResource->createRtBuffer(device, renderTargetSize, clearColor);
	}

	unsigned int DX3DResource::createRtBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		return m_bufferResource->createRtBuffer(swapChain, backBufferIndex);
	}

	unsigned int DX3DResource::createDsBuffer(ID3D12Device* device, const DepthStencilBufferInitParam& initParam)
	{
		return m_bufferResource->createDsBuffer(device, initParam);
	}

	unsigned int DX3DResource::cpuPriorityCreateTextureBuffer(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_bufferResource->cpuPriorityCreateTextureBuffer(device, formatParam, dataParam);
	}

	unsigned int DX3DResource::gpuPriorityCreateTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_bufferResource->gpuPriorityCreateTextureBuffer(device, commandList, formatParam, dataParam);
	}

	unsigned int DX3DResource::cpuPriorityLoadTextureBuffer(ID3D12Device* device, const std::string& texDataPath)
	{
		return m_bufferResource->cpuPriorityLoadTextureBuffer(device, texDataPath);
	}

	unsigned int DX3DResource::gpuPriorityLoadTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath)
	{
		return m_bufferResource->gpuPriorityLoadTextureBuffer(device, commandList, texDataPath);
	}

	unsigned int DX3DResource::createBasicDescriptorHeap(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		// バッファを割り当てていないディスクリプタヒープを作る
		 unsigned int handle = m_descriptorHeap->createBasicDescriptorHeap(device, initParam);

		// 全てのディスクリプタの先頭アドレスの配列を取得する
		auto cpuHeapHandleArray = m_descriptorHeap->getCpuBasicHeapHandleArray(handle, device);

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
		return handle;
	}

	unsigned int DX3DResource::createRtvDescriptorHeap(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		// バッファを割り当てていないディスクリプタヒープを作る
		unsigned int handle = m_descriptorHeap->createRtvDescriptorHeap(device, initParam);

		auto cpuHeapHandleArray = m_descriptorHeap->getCpuRtvHeapHandleArray(handle, device);

		for (unsigned int i = 0; i < initParam.descriptorParamArray.size(); i++)
		{
			switch (initParam.descriptorParamArray.at(i).type)
			{
			case RtvDescriptorType::normal:

				m_bufferResource->createRtv(initParam.descriptorParamArray.at(i).handle, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
		return handle;
	}

	unsigned int DX3DResource::createDsvDescriptorHeap(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam)
	{
		// バッファを割り当てていないディスクリプタヒープを作る
		unsigned int handle = m_descriptorHeap->createDsvDescriptorHeap(device, initParam);

		auto cpuHeapHandleArray = m_descriptorHeap->getCpuDsvHeapHandleArray(handle, device);

		for (unsigned int i = 0; i < initParam.descriptorParamArray.size(); i++)
		{
			switch (initParam.descriptorParamArray.at(i).type)
			{
			case DsvDescriptorType::normal:

				m_bufferResource->createDsv(initParam.descriptorParamArray.at(i).handle, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
		return handle;
	}

	void DX3DResource::eraseViewport(unsigned int handle)
	{
		m_viewport->erase(handle);
	}

	void DX3DResource::eraseScissorRect(unsigned int handle)
	{
		m_scissorRect->erase(handle);
	}

	void DX3DResource::eraseRootSignature(unsigned int handle)
	{
		m_graphicsPipeLine->eraseRootSignature(handle);
	}

	void DX3DResource::erasePipeLineState(unsigned int handle)
	{
		m_graphicsPipeLine->erasePipeLineState(handle);
	}

	void DX3DResource::eraseVertexBuffer(unsigned int handle)
	{
		m_bufferResource->eraseVertexBuffer(handle);
	}

	void DX3DResource::eraseIndexBuffer(unsigned int handle)
	{
		m_bufferResource->eraseIndexBuffer(handle);
	}

	void DX3DResource::eraseCBuffer(unsigned int handle)
	{
		m_bufferResource->eraseCBuffer(handle);
	}

	void DX3DResource::eraseTextureBuffer(unsigned int handle)
	{
		m_bufferResource->eraseTextureBuffer(handle);
	}

	void DX3DResource::eraseDsBuffer(unsigned int handle)
	{
		m_bufferResource->eraseDsBuffer(handle);
	}

	void DX3DResource::eraseRtBuffer(unsigned int handle)
	{
		m_bufferResource->eraseRtBuffer(handle);
	}

	void DX3DResource::eraseBasicDescriptorHeap(unsigned int handle)
	{
		m_descriptorHeap->eraseBasicDescriptorHeap(handle);
	}

	void DX3DResource::eraseRtvDescriptorHeap(unsigned int handle)
	{
		m_descriptorHeap->eraseRtvDescriptorHeap(handle);
	}

	void DX3DResource::eraseDsvDescriptorHeap(unsigned int handle)
	{
		m_descriptorHeap->eraseDsvDescriptorHeap(handle);
	}

	void DX3DResource::updateVertexBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_bufferResource->updateVertexBuffer(handle, device, commandList, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX3DResource::updateIndexBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray)
	{
		m_bufferResource->updateIndexBuffer(handle, device, commandList, indexDataArray);
	}

	void DX3DResource::updateCBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_bufferResource->updateCBuffer(handle, device, commandList, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DResource::deleteUploadBufferAll()
	{
		m_bufferResource->deleteUploadBufferAll();
	}

	void DX3DResource::clearRtv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color) const
	{
		m_descriptorHeap->clearRtv(handle, device, commandList, rtvLocationIndex, color);
	}

	void DX3DResource::clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource->allBeginWriteDsBuffer(commandList);

		m_descriptorHeap->clearDsvAll(device, commandList);

		m_bufferResource->allEndWriteDsBuffer(commandList);
	}

	const tktkMath::Vector3& DX3DResource::getTextureBufferSizePx(unsigned int handle) const
	{
		return m_bufferResource->getTextureSizePx(handle);
	}

	const tktkMath::Vector2& DX3DResource::getDsBufferSizePx(unsigned int handle) const
	{
		return m_bufferResource->getDepthStencilSizePx(handle);
	}

	const tktkMath::Vector2& DX3DResource::getRtBufferSizePx(unsigned int handle) const
	{
		return m_bufferResource->getRenderTargetSizePx(handle);
	}

	const std::vector<unsigned int>& DX3DResource::getRtvDescriptorHeapUseBufferIdArray(unsigned int handle) const
	{
		return m_descriptorHeap->getRtvDescriptorHeapUseBufferIdArray(handle);
	}

	const std::vector<unsigned int>& DX3DResource::getDsvDescriptorHeapUseBufferIdArray(unsigned int handle) const
	{
		return m_descriptorHeap->getDsvDescriptorHeapUseBufferIdArray(handle);
	}

	void DX3DResource::setRtv(unsigned int rtvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		// 使用するレンダーターゲットバッファーを取得して、書き込み状態に設定する
		auto rtvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getRtvDescriptorHeapUseBufferIdArray(rtvDescriptorHeapHandle);
		for (unsigned int i = 0; i < rtvCount; i++)
		{
			m_bufferResource->beginWriteBasicRtBuffer(rtvDescriptorHeapUseBufferIdArray.at(startRtvLocationIndex + i), commandList);
		}

		// 「レンダーターゲット用のディスクリプタヒープ」を設定する
		m_descriptorHeap->setRtv(rtvDescriptorHeapHandle, device, commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DResource::setRtvAndDsv(unsigned int rtvDescriptorHeapHandle, unsigned int dsvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		// 使用するレンダーターゲットバッファーを取得して、書き込み状態に設定する
		auto rtvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getRtvDescriptorHeapUseBufferIdArray(rtvDescriptorHeapHandle);
		for (unsigned int i = 0; i < rtvCount; i++)
		{
			m_bufferResource->beginWriteBasicRtBuffer(rtvDescriptorHeapUseBufferIdArray.at(startRtvLocationIndex + i), commandList);
		}

		// 使用する深度ステンシルバッファーを取得して、書き込み状態に設定する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getDsvDescriptorHeapUseBufferIdArray(dsvDescriptorHeapHandle);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource->beginWriteDsBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}

		// 「レンダーターゲット用のディスクリプタヒープ」と「深度ステンシル用のディスクリプタヒープ」を設定する
		m_descriptorHeap->setRtvAndDsv(rtvDescriptorHeapHandle, dsvDescriptorHeapHandle, device, commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DResource::setOnlyDsv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		// 使用する深度ステンシルバッファーを取得して、書き込み状態に設定する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getDsvDescriptorHeapUseBufferIdArray(handle);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource->beginWriteDsBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}

		// 「深度ステンシル用のディスクリプタヒープ」を設定する
		m_descriptorHeap->setOnlyDsv(handle, device, commandList);
	}

	void DX3DResource::setBackBufferView(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const
	{
		// バックバッファはフレームの初めに書き込み状態に設定されているのでそのまま ディスクリプタヒープを設定できる
		m_descriptorHeap->setRtv(getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer), device, commandList, backBufferIndex, 1U);
	}

	void DX3DResource::setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const
	{
		// 使用する深度ステンシルバッファーを取得して、書き込み状態に設定する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getDsvDescriptorHeapUseBufferIdArray(dsvDescriptorHeapHandle);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource->beginWriteDsBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}

		// 「バックバッファー用のディスクリプタヒープ」と「深度ステンシル用のディスクリプタヒープ」を設定する
		m_descriptorHeap->setRtvAndDsv(getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer), dsvDescriptorHeapHandle, device, commandList, backBufferIndex, 1U);
	}

	void DX3DResource::unSetRtv(unsigned int rtvDescriptorHeapHandle, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		// 使用していたレンダーターゲットバッファーを取得して、ピクセルシェーダーで使用する状態に変更する
		auto rtvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getRtvDescriptorHeapUseBufferIdArray(rtvDescriptorHeapHandle);
		for (unsigned int i = 0; i < rtvCount; i++)
		{
			m_bufferResource->endWriteBasicRtBuffer(rtvDescriptorHeapUseBufferIdArray.at(startRtvLocationIndex + i), commandList);
		}
	}

	void DX3DResource::unSetDsv(unsigned int dsvDescriptorHeapHandle, ID3D12GraphicsCommandList* commandList) const
	{
		// 使用していた深度ステンシルバッファーを取得して、ピクセルシェーダーで使用する状態に変更する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getDsvDescriptorHeapUseBufferIdArray(dsvDescriptorHeapHandle);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource->endWriteDsBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}
	}

	void DX3DResource::beginWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource->beginWriteBackBuffer(handle, commandList);
	}

	void DX3DResource::endWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource->endWriteBackBuffer(handle, commandList);
	}

	void DX3DResource::setViewport(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_viewport->set(handle, commandList);
	}

	void DX3DResource::setScissorRect(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_scissorRect->set(handle, commandList);
	}

	void DX3DResource::setPipeLineState(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_graphicsPipeLine->set(handle, commandList);
	}

	void DX3DResource::setVertexBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource->setVertexBuffer(handle, commandList);
	}

	void DX3DResource::setIndexBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource->setIndexBuffer(handle, commandList);
	}

	void DX3DResource::setDescriptorHeap(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray) const
	{
		m_descriptorHeap->set(device, commandList, heapParamArray);
	}

	unsigned int DX3DResource::getSystemHandle(SystemViewportType type) const
	{
		return m_sysResHandleGetter->getSystemHandle(type);
	}

	unsigned int DX3DResource::getSystemHandle(SystemScissorRectType type) const
	{
		return m_sysResHandleGetter->getSystemHandle(type);
	}

	unsigned int DX3DResource::getSystemHandle(SystemVertexBufferType type) const
	{
		return m_sysResHandleGetter->getSystemHandle(type);
	}

	unsigned int DX3DResource::getSystemHandle(SystemIndexBufferType type) const
	{
		return m_sysResHandleGetter->getSystemHandle(type);
	}

	unsigned int DX3DResource::getSystemHandle(SystemCBufferType type) const
	{
		return m_sysResHandleGetter->getSystemHandle(type);
	}

	unsigned int DX3DResource::getSystemHandle(SystemTextureBufferType type) const
	{
		return m_sysResHandleGetter->getSystemHandle(type);
	}

	unsigned int DX3DResource::getSystemHandle(SystemRtBufferType type) const
	{
		return m_sysResHandleGetter->getSystemHandle(type);
	}

	unsigned int DX3DResource::getSystemHandle(SystemDsBufferType type) const
	{
		return m_sysResHandleGetter->getSystemHandle(type);
	}

	unsigned int DX3DResource::getSystemHandle(SystemBasicDescriptorHeapType type) const
	{
		return m_sysResHandleGetter->getSystemHandle(type);
	}

	unsigned int DX3DResource::getSystemHandle(SystemRtvDescriptorHeapType type) const
	{
		return m_sysResHandleGetter->getSystemHandle(type);
	}

	unsigned int DX3DResource::getSystemHandle(SystemDsvDescriptorHeapType type) const
	{
		return m_sysResHandleGetter->getSystemHandle(type);
	}

	unsigned int DX3DResource::getSystemHandle(SystemRootSignatureType type) const
	{
		return m_sysResHandleGetter->getSystemHandle(type);
	}

	unsigned int DX3DResource::getSystemHandle(SystemPipeLineStateType type) const
	{
		return m_sysResHandleGetter->getSystemHandle(type);
	}

	void DX3DResource::setSystemHandle(SystemViewportType type, unsigned int handle)
	{
		m_sysResHandleGetter->setSystemHandle(type, handle);
	}

	void DX3DResource::setSystemHandle(SystemScissorRectType type, unsigned int handle)
	{
		m_sysResHandleGetter->setSystemHandle(type, handle);
	}

	void DX3DResource::setSystemHandle(SystemVertexBufferType type, unsigned int handle)
	{
		m_sysResHandleGetter->setSystemHandle(type, handle);
	}

	void DX3DResource::setSystemHandle(SystemIndexBufferType type, unsigned int handle)
	{
		m_sysResHandleGetter->setSystemHandle(type, handle);
	}

	void DX3DResource::setSystemHandle(SystemCBufferType type, unsigned int handle)
	{
		m_sysResHandleGetter->setSystemHandle(type, handle);
	}

	void DX3DResource::setSystemHandle(SystemTextureBufferType type, unsigned int handle)
	{
		m_sysResHandleGetter->setSystemHandle(type, handle);
	}

	void DX3DResource::setSystemHandle(SystemRtBufferType type, unsigned int handle)
	{
		m_sysResHandleGetter->setSystemHandle(type, handle);
	}

	void DX3DResource::setSystemHandle(SystemDsBufferType type, unsigned int handle)
	{
		m_sysResHandleGetter->setSystemHandle(type, handle);
	}

	void DX3DResource::setSystemHandle(SystemBasicDescriptorHeapType type, unsigned int handle)
	{
		m_sysResHandleGetter->setSystemHandle(type, handle);
	}

	void DX3DResource::setSystemHandle(SystemRtvDescriptorHeapType type, unsigned int handle)
	{
		m_sysResHandleGetter->setSystemHandle(type, handle);
	}

	void DX3DResource::setSystemHandle(SystemDsvDescriptorHeapType type, unsigned int handle)
	{
		m_sysResHandleGetter->setSystemHandle(type, handle);
	}

	void DX3DResource::setSystemHandle(SystemRootSignatureType type, unsigned int handle)
	{
		m_sysResHandleGetter->setSystemHandle(type, handle);
	}

	void DX3DResource::setSystemHandle(SystemPipeLineStateType type, unsigned int handle)
	{
		m_sysResHandleGetter->setSystemHandle(type, handle);
	}

	void DX3DResource::createBasicDescriptorCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const
	{
#ifdef _DEBUG
		if (useBufferParam.type != BufferType::constant) throw std::runtime_error("useBuffer Type Error -not cbuffer-");
#endif // _DEBUG

		m_bufferResource->createCbv(useBufferParam.handle, device, cpuHandle);
	}

	void DX3DResource::createBasicDescriptorSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const
	{
		switch (useBufferParam.type)
		{
		case BufferType::texture:

			m_bufferResource->createSrv(useBufferParam.handle, device, cpuHandle);
			break;

		case BufferType::renderTarget:

			m_bufferResource->createRtSrv(useBufferParam.handle, device, cpuHandle);
			break;

		case BufferType::depthStencil:

			m_bufferResource->createDsSrv(useBufferParam.handle, device, cpuHandle);
			break;

		default:
#ifdef _DEBUG
			throw std::runtime_error("useBuffer Type Error -not ShaderResourceView-");
#endif // _DEBUG
			break;
		}
	}
}