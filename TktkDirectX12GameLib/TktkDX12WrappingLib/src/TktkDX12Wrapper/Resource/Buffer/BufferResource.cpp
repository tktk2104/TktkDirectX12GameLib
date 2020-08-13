#include "TktkDX12Wrapper/Resource/Buffer/BufferResource.h"

namespace tktk
{
	BufferResource::BufferResource(const BufferResourceInitParam& initParam)
		: m_vertexBuffer(initParam.vertexBufferNum)
		, m_indexBuffer(initParam.indexBufferNum)
		, m_constantBuffer(initParam.constantBufferNum)
		, m_textureBuffer(initParam.textureBufferNum)
		, m_depthStencilBuffer(initParam.depthStencilBufferNum)
		, m_renderTargetBuffer(initParam.renderTargetBufferNum)
	{
	}

	void BufferResource::deleteUploadBufferAll()
	{
		m_vertexBuffer.deleteUploadBufferAll();
		m_indexBuffer.deleteUploadBufferAll();
		m_constantBuffer.deleteUploadBufferAll();
	}

	void BufferResource::createVertexBuffer(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_vertexBuffer.create(id, device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void BufferResource::updateVertexBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_vertexBuffer.updateBuffer(id, device, commandList, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void BufferResource::setVertexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_vertexBuffer.set(id, commandList);
	}

	void BufferResource::createIndexBuffer(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray)
	{
		m_indexBuffer.create(id, device, indexDataArray);
	}

	void BufferResource::updateIndexBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray)
	{
		m_indexBuffer.updateBuffer(id, device, commandList, indexDataArray);
	}

	void BufferResource::setIndexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_indexBuffer.set(id, commandList);
	}

	void BufferResource::createCBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_constantBuffer.create(id, device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void BufferResource::createCbv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_constantBuffer.createCbv(id, device, heapHandle);
	}

	void BufferResource::updateCBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_constantBuffer.updateBuffer(id, device, commandList, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void BufferResource::cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBuffer.cpuPriorityCreate(id, device, formatParam, dataParam);
	}

	void BufferResource::gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBuffer.gpuPriorityCreate(id, device, commandList, formatParam, dataParam);
	}

	void BufferResource::cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const std::string& texDataPath)
	{
		m_textureBuffer.cpuPriorityLoad(id, device, texDataPath);
	}

	void BufferResource::gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath)
	{
		m_textureBuffer.gpuPriorityLoad(id, device, commandList, texDataPath);
	}

	void BufferResource::createSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_textureBuffer.createSrv(id, device, heapHandle);
	}

	const tktkMath::Vector3& BufferResource::getTextureSizePx(unsigned int id) const
	{
		return m_textureBuffer.getTextureSizePx(id);
	}

	void BufferResource::createDsBuffer(unsigned int id, ID3D12Device* device, const DepthStencilBufferInitParam& initParam)
	{
		m_depthStencilBuffer.create(id, device, initParam);
	}

	void BufferResource::createDsv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_depthStencilBuffer.createDsv(id, device, heapHandle);
	}

	void BufferResource::createDsSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_depthStencilBuffer.createSrv(id, device, heapHandle);
	}

	void BufferResource::beginWriteDsBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBuffer.beginWrite(id, commandList);
	}

	void BufferResource::endWriteDsBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBuffer.endWrite(id, commandList);
	}

	void BufferResource::allBeginWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBuffer.allBeginWrite(commandList);
	}

	void BufferResource::allEndWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBuffer.allEndWrite(commandList);
	}

	const tktkMath::Vector2& BufferResource::getDepthStencilSizePx(unsigned int id) const
	{
		return m_depthStencilBuffer.getDepthStencilSizePx(id);
	}

	void BufferResource::createRtBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		m_renderTargetBuffer.create(id, device, renderTargetSize, clearColor);
	}

	void BufferResource::createRtBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		m_renderTargetBuffer.create(id, swapChain, backBufferIndex);
	}

	void BufferResource::createRtv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_renderTargetBuffer.createRtv(id, device, heapHandle);
	}

	void BufferResource::createRtSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_renderTargetBuffer.createSrv(id, device, heapHandle);
	}

	void BufferResource::beginWriteBasicRtBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBuffer.beginWriteBasicRtBuffer(id, commandList);
	}

	void BufferResource::endWriteBasicRtBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBuffer.endWriteBasicRtBuffer(id, commandList);
	}

	void BufferResource::beginWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBuffer.beginWriteBackBuffer(id, commandList);
	}

	void BufferResource::endWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBuffer.endWriteBackBuffer(id, commandList);
	}

	const tktkMath::Vector2& BufferResource::getRenderTargetSizePx(unsigned int id) const
	{
		return m_renderTargetBuffer.getRenderTargetSizePx(id);
	}
}