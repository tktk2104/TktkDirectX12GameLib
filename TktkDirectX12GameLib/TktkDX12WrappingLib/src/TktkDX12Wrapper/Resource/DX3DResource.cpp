#include "TktkDX12Wrapper/Resource/DX3DResource.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

#include "TktkDX12Wrapper/Resource/Viewport/Viewport.h"
#include "TktkDX12Wrapper/Resource/ScissorRect/ScissorRect.h"
#include "TktkDX12Wrapper/Resource/GraphicsPipeLine/GraphicsPipeLine.h"
#include "TktkDX12Wrapper/Resource/DescriptorHeap/DescriptorHeap.h"
#include "TktkDX12Wrapper/Resource/Buffer/BufferResource.h"

namespace tktk
{
	DX3DResource::DX3DResource(const DX3DResourceNum& resNum)
	{
		m_viewport				= std::make_unique<Viewport>(resNum.viewPortNum);
		m_scissorRect			= std::make_unique<ScissorRect>(resNum.scissorRectNum);
		m_graphicsPipeLine		= std::make_unique<GraphicsPipeLine>(resNum.graphicsPipeLineResourceNum);
		m_descriptorHeap		= std::make_unique<DescriptorHeap>(resNum.descriptorHeapNum);
		m_bufferResource		= std::make_unique<BufferResource>(resNum.bufferResourceNum);
	}

	// デストラクタを非インライン化する
	DX3DResource::~DX3DResource() = default;

	size_t DX3DResource::createViewport(const std::vector<ViewportInitParam>& initParamArray)
	{
		return m_viewport->create(initParamArray);
	}

	size_t DX3DResource::createScissorRect(const std::vector<ScissorRectInitParam>& initParamArray)
	{
		return m_scissorRect->create(initParamArray);
	}

	size_t DX3DResource::createRootSignature(ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		return m_graphicsPipeLine->createRootSignature(device, initParam);
	}

	size_t DX3DResource::createPipeLineState(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		return m_graphicsPipeLine->createPipeLineState(device, initParam, shaderFilePath);
	}

	size_t DX3DResource::createUploadBuffer(ID3D12Device* device, const UploadBufferInitParam& initParam)
	{
		return m_bufferResource->createUploadBuffer(device, initParam);
	}

	void DX3DResource::createTempUploadBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const UploadBufferInitParam& initParam)
	{
		m_bufferResource->createTempUploadBuffer(device, commandList, initParam);
	}

	size_t DX3DResource::duplicateUploadBuffer(ID3D12Device* device, size_t originalHandle)
	{
		return m_bufferResource->duplicateUploadBuffer(device, originalHandle);
	}

	size_t DX3DResource::createVertexBuffer(ID3D12Device* device, const VertexDataCarrier& vertexData)
	{
		return m_bufferResource->createVertexBuffer(device, vertexData);
	}

	size_t DX3DResource::createIndexBuffer(ID3D12Device* device, const std::vector<unsigned short>& indices)
	{
		return m_bufferResource->createIndexBuffer(device, indices);
	}

	size_t DX3DResource::createCBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const CopySourceDataCarrier& constantBufferData)
	{
		return m_bufferResource->createCBuffer(device, commandList, constantBufferData);
	}

	size_t DX3DResource::createRtBuffer(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		return m_bufferResource->createRtBuffer(device, renderTargetSize, clearColor);
	}

	size_t DX3DResource::createRtBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		return m_bufferResource->createRtBuffer(swapChain, backBufferIndex);
	}

	size_t DX3DResource::createDsBuffer(ID3D12Device* device, const DepthStencilBufferInitParam& initParam)
	{
		return m_bufferResource->createDsBuffer(device, initParam);
	}

	size_t DX3DResource::createTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_bufferResource->createTextureBuffer(device, commandList, formatParam, dataParam);
	}

	size_t DX3DResource::loadTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath)
	{
		return m_bufferResource->loadTextureBuffer(device, commandList, texDataPath);
	}

	size_t DX3DResource::createBasicDescriptorHeap(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		// バッファを割り当てていないディスクリプタヒープを作る
		size_t handle = m_descriptorHeap->createBasicDescriptorHeap(device, initParam);

		// 全てのディスクリプタの先頭アドレスの配列を取得する
		auto cpuHeapHandleArray = m_descriptorHeap->getCpuBasicHeapHandleArray(handle, device);

		// 設定しているディスクリプタの番号
		size_t curDescriptorIndex = 0U;

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

	size_t DX3DResource::createRtvDescriptorHeap(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		// バッファを割り当てていないディスクリプタヒープを作る
		size_t handle = m_descriptorHeap->createRtvDescriptorHeap(device, initParam);

		auto cpuHeapHandleArray = m_descriptorHeap->getCpuRtvHeapHandleArray(handle, device);

		for (size_t i = 0; i < initParam.descriptorParamArray.size(); i++)
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

	size_t DX3DResource::createDsvDescriptorHeap(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam)
	{
		// バッファを割り当てていないディスクリプタヒープを作る
		size_t handle = m_descriptorHeap->createDsvDescriptorHeap(device, initParam);

		auto cpuHeapHandleArray = m_descriptorHeap->getCpuDsvHeapHandleArray(handle, device);

		for (size_t i = 0; i < initParam.descriptorParamArray.size(); i++)
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

	void DX3DResource::eraseViewport(size_t handle)
	{
		m_viewport->erase(handle);
	}

	void DX3DResource::eraseScissorRect(size_t handle)
	{
		m_scissorRect->erase(handle);
	}

	void DX3DResource::eraseRootSignature(size_t handle)
	{
		m_graphicsPipeLine->eraseRootSignature(handle);
	}

	void DX3DResource::erasePipeLineState(size_t handle)
	{
		m_graphicsPipeLine->erasePipeLineState(handle);
	}

	void DX3DResource::eraseUploadBuffer(size_t handle)
	{
		m_bufferResource->eraseUploadBuffer(handle);
	}

	void DX3DResource::eraseVertexBuffer(size_t handle)
	{
		m_bufferResource->eraseVertexBuffer(handle);
	}

	void DX3DResource::eraseIndexBuffer(size_t handle)
	{
		m_bufferResource->eraseIndexBuffer(handle);
	}

	void DX3DResource::eraseCBuffer(size_t handle)
	{
		m_bufferResource->eraseCBuffer(handle);
	}

	void DX3DResource::eraseTextureBuffer(size_t handle)
	{
		m_bufferResource->eraseTextureBuffer(handle);
	}

	void DX3DResource::eraseDsBuffer(size_t handle)
	{
		m_bufferResource->eraseDsBuffer(handle);
	}

	void DX3DResource::eraseRtBuffer(size_t handle)
	{
		m_bufferResource->eraseRtBuffer(handle);
	}

	void DX3DResource::eraseBasicDescriptorHeap(size_t handle)
	{
		m_descriptorHeap->eraseBasicDescriptorHeap(handle);
	}

	void DX3DResource::eraseRtvDescriptorHeap(size_t handle)
	{
		m_descriptorHeap->eraseRtvDescriptorHeap(handle);
	}

	void DX3DResource::eraseDsvDescriptorHeap(size_t handle)
	{
		m_descriptorHeap->eraseDsvDescriptorHeap(handle);
	}

	void DX3DResource::clearTempUploadBuffer()
	{
		m_bufferResource->clearTempUploadBuffer();
	}

	void DX3DResource::updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData)
	{
		m_bufferResource->updateUploadBuffer(handle, bufferData);
	}

	void DX3DResource::updateVertexBuffer(size_t handle, const VertexDataCarrier& vertexData)
	{
		m_bufferResource->updateVertexBuffer(handle, vertexData);
	}

	void DX3DResource::copyBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource->copyBuffer(handle, commandList);
	}

	void DX3DResource::clearRtv(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t rtvLocationIndex) const
	{
		const auto& rtBufferHandleArray = m_descriptorHeap->getRtvDescriptorHeapUseBufferHandleArray(handle);
		const auto& clearColor = m_bufferResource->getRtBufferClearColor(rtBufferHandleArray.at(rtvLocationIndex));

		auto cpuHeapHandleArray = m_descriptorHeap->getCpuRtvHeapHandleArray(handle, device);
		commandList->ClearRenderTargetView(cpuHeapHandleArray.at(rtvLocationIndex), (float*)&clearColor, 0U, nullptr);
	}

	void DX3DResource::clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource->allBeginWriteDsBuffer(commandList);

		m_descriptorHeap->clearDsvAll(device, commandList);

		m_bufferResource->allEndWriteDsBuffer(commandList);
	}

	const tktkMath::Vector3& DX3DResource::getTextureBufferSizePx(size_t handle) const
	{
		return m_bufferResource->getTextureSizePx(handle);
	}

	const tktkMath::Vector2& DX3DResource::getDsBufferSizePx(size_t handle) const
	{
		return m_bufferResource->getDepthStencilSizePx(handle);
	}

	const tktkMath::Vector2& DX3DResource::getRtBufferSizePx(size_t handle) const
	{
		return m_bufferResource->getRenderTargetSizePx(handle);
	}

	const std::vector<size_t>& DX3DResource::getRtvDescriptorHeapUseBufferHandleArray(size_t handle) const
	{
		return m_descriptorHeap->getRtvDescriptorHeapUseBufferHandleArray(handle);
	}

	const std::vector<size_t>& DX3DResource::getDsvDescriptorHeapUseBufferHandleArray(size_t handle) const
	{
		return m_descriptorHeap->getDsvDescriptorHeapUseBufferHandleArray(handle);
	}

	void DX3DResource::setRtv(size_t rtvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, size_t rtvCount) const
	{
		// 使用するレンダーターゲットバッファーを取得して、書き込み状態に設定する
		auto rtvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getRtvDescriptorHeapUseBufferHandleArray(rtvDescriptorHeapHandle);
		for (size_t i = 0; i < rtvCount; i++)
		{
			m_bufferResource->beginWriteBasicRtBuffer(rtvDescriptorHeapUseBufferIdArray.at(startRtvLocationIndex + i), commandList);
		}

		// 「レンダーターゲット用のディスクリプタヒープ」を設定する
		m_descriptorHeap->setRtv(rtvDescriptorHeapHandle, device, commandList, startRtvLocationIndex, static_cast<unsigned int>(rtvCount));
	}

	void DX3DResource::setRtvAndDsv(size_t rtvDescriptorHeapHandle, size_t dsvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, size_t rtvCount) const
	{
		// 使用するレンダーターゲットバッファーを取得して、書き込み状態に設定する
		auto rtvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getRtvDescriptorHeapUseBufferHandleArray(rtvDescriptorHeapHandle);
		for (size_t i = 0; i < rtvCount; i++)
		{
			m_bufferResource->beginWriteBasicRtBuffer(rtvDescriptorHeapUseBufferIdArray.at(startRtvLocationIndex + i), commandList);
		}

		// 使用する深度ステンシルバッファーを取得して、書き込み状態に設定する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getDsvDescriptorHeapUseBufferHandleArray(dsvDescriptorHeapHandle);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource->beginWriteDsBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}

		// 「レンダーターゲット用のディスクリプタヒープ」と「深度ステンシル用のディスクリプタヒープ」を設定する
		m_descriptorHeap->setRtvAndDsv(rtvDescriptorHeapHandle, dsvDescriptorHeapHandle, device, commandList, startRtvLocationIndex, static_cast<unsigned int>(rtvCount));
	}

	void DX3DResource::setOnlyDsv(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		// 使用する深度ステンシルバッファーを取得して、書き込み状態に設定する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getDsvDescriptorHeapUseBufferHandleArray(handle);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource->beginWriteDsBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}

		// 「深度ステンシル用のディスクリプタヒープ」を設定する
		m_descriptorHeap->setOnlyDsv(handle, device, commandList);
	}

	void DX3DResource::setBackBufferView(size_t backBufferRtvDescriptorHeap, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const
	{
		// バックバッファはフレームの初めに書き込み状態に設定されているのでそのまま ディスクリプタヒープを設定できる
		m_descriptorHeap->setRtv(backBufferRtvDescriptorHeap, device, commandList, backBufferIndex, 1U);
	}

	void DX3DResource::setBackBufferViewAndDsv(size_t backBufferRtvDescriptorHeap, size_t dsvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const
	{
		// 使用する深度ステンシルバッファーを取得して、書き込み状態に設定する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getDsvDescriptorHeapUseBufferHandleArray(dsvDescriptorHeapHandle);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource->beginWriteDsBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}

		// 「バックバッファー用のディスクリプタヒープ」と「深度ステンシル用のディスクリプタヒープ」を設定する
		m_descriptorHeap->setRtvAndDsv(backBufferRtvDescriptorHeap, dsvDescriptorHeapHandle, device, commandList, backBufferIndex, 1U);
	}

	void DX3DResource::unSetRtv(size_t rtvDescriptorHeapHandle, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, size_t rtvCount) const
	{
		// 使用していたレンダーターゲットバッファーを取得して、ピクセルシェーダーで使用する状態に変更する
		auto rtvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getRtvDescriptorHeapUseBufferHandleArray(rtvDescriptorHeapHandle);
		for (size_t i = 0; i < rtvCount; i++)
		{
			m_bufferResource->endWriteBasicRtBuffer(rtvDescriptorHeapUseBufferIdArray.at(startRtvLocationIndex + i), commandList);
		}
	}

	void DX3DResource::unSetDsv(size_t dsvDescriptorHeapHandle, ID3D12GraphicsCommandList* commandList) const
	{
		// 使用していた深度ステンシルバッファーを取得して、ピクセルシェーダーで使用する状態に変更する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap->getDsvDescriptorHeapUseBufferHandleArray(dsvDescriptorHeapHandle);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource->endWriteDsBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}
	}

	void DX3DResource::beginWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource->beginWriteBackBuffer(handle, commandList);
	}

	void DX3DResource::endWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource->endWriteBackBuffer(handle, commandList);
	}

	void DX3DResource::setViewport(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_viewport->set(handle, commandList);
	}

	void DX3DResource::setScissorRect(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_scissorRect->set(handle, commandList);
	}

	void DX3DResource::setPipeLineState(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_graphicsPipeLine->set(handle, commandList);
	}

	void DX3DResource::setVertexBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource->setVertexBuffer(handle, commandList);
	}

	void DX3DResource::setVertexBuffer(size_t meshVertHandle, size_t instancingVertHandle, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource->setVertexBuffer(meshVertHandle, instancingVertHandle, commandList);
	}

	void DX3DResource::setIndexBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_bufferResource->setIndexBuffer(handle, commandList);
	}

	void DX3DResource::setDescriptorHeap(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray) const
	{
		m_descriptorHeap->set(device, commandList, heapParamArray);
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