#include "TktkDX12Wrapper/Resource/Buffer/BufferResource.h"

#include "TktkDX12Wrapper/Resource/Buffer/Vertex/VertexBuffer.h"
#include "TktkDX12Wrapper/Resource/Buffer/Index/IndexBuffer.h"
#include "TktkDX12Wrapper/Resource/Buffer/Constant/ConstantBuffer.h"
#include "TktkDX12Wrapper/Resource/Buffer/Texture/TextureBuffer.h"
#include "TktkDX12Wrapper/Resource/Buffer/DepthStencil/DepthStencilBuffer.h"
#include "TktkDX12Wrapper/Resource/Buffer/RenderTarget/RenderTargetBuffer.h"

namespace tktk
{
	BufferResource::BufferResource(const BufferResourceNum& initParam)
	{
		m_vertexBuffer			= std::make_unique<VertexBuffer>(initParam.vertexBufferContainerInitParam);
		m_indexBuffer			= std::make_unique<IndexBuffer>(initParam.indexBufferContainerInitParam);
		m_constantBuffer		= std::make_unique<ConstantBuffer>(initParam.cbufferContainerInitParam);
		m_textureBuffer			= std::make_unique<TextureBuffer>(initParam.textureBufferStaticNodeNum);
		m_depthStencilBuffer	= std::make_unique<DepthStencilBuffer>(initParam.dsbufferStaticNodeNum);
		m_renderTargetBuffer	= std::make_unique<RenderTargetBuffer>(initParam.rtbufferStaticNodeNum);
	}

	// デストラクタを非インライン化する
	BufferResource::~BufferResource() = default;

	void BufferResource::deleteUploadBufferAll()
	{
		m_vertexBuffer->deleteUploadBufferAll();
		m_indexBuffer->deleteUploadBufferAll();
		m_constantBuffer->deleteUploadBufferAll();
	}

	unsigned int BufferResource::createVertexBuffer(ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		return m_vertexBuffer->create(device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void BufferResource::updateVertexBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_vertexBuffer->updateBuffer(handle, device, commandList, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void BufferResource::setVertexBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_vertexBuffer->set(handle, commandList);
	}

	unsigned int BufferResource::createIndexBuffer(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray)
	{
		return m_indexBuffer->create(device, indexDataArray);
	}

	void BufferResource::updateIndexBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray)
	{
		m_indexBuffer->updateBuffer(handle, device, commandList, indexDataArray);
	}

	void BufferResource::setIndexBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_indexBuffer->set(handle, commandList);
	}

	unsigned int BufferResource::createCBuffer(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		return m_constantBuffer->create(device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void BufferResource::createCbv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_constantBuffer->createCbv(handle, device, heapHandle);
	}

	void BufferResource::updateCBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_constantBuffer->updateBuffer(handle, device, commandList, constantBufferTypeSize, constantBufferDataTopPos);
	}

	unsigned int BufferResource::cpuPriorityCreateTextureBuffer(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_textureBuffer->cpuPriorityCreate(device, formatParam, dataParam);
	}

	unsigned int BufferResource::gpuPriorityCreateTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_textureBuffer->gpuPriorityCreate(device, commandList, formatParam, dataParam);
	}

	unsigned int BufferResource::cpuPriorityLoadTextureBuffer(ID3D12Device* device, const std::string& texDataPath)
	{
		return m_textureBuffer->cpuPriorityLoad(device, texDataPath);
	}

	unsigned int BufferResource::gpuPriorityLoadTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath)
	{
		return m_textureBuffer->gpuPriorityLoad(device, commandList, texDataPath);
	}

	void BufferResource::createSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_textureBuffer->createSrv(handle, device, heapHandle);
	}

	const tktkMath::Vector3& BufferResource::getTextureSizePx(unsigned int handle) const
	{
		return m_textureBuffer->getTextureSizePx(handle);
	}

	unsigned int BufferResource::createDsBuffer(ID3D12Device* device, const DepthStencilBufferInitParam& initParam)
	{
		return m_depthStencilBuffer->create(device, initParam);
	}

	void BufferResource::createDsv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_depthStencilBuffer->createDsv(handle, device, heapHandle);
	}

	void BufferResource::createDsSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_depthStencilBuffer->createSrv(handle, device, heapHandle);
	}

	void BufferResource::beginWriteDsBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBuffer->beginWrite(handle, commandList);
	}

	void BufferResource::endWriteDsBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBuffer->endWrite(handle, commandList);
	}

	void BufferResource::allBeginWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBuffer->allBeginWrite(commandList);
	}

	void BufferResource::allEndWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBuffer->allEndWrite(commandList);
	}

	const tktkMath::Vector2& BufferResource::getDepthStencilSizePx(unsigned int handle) const
	{
		return m_depthStencilBuffer->getDepthStencilSizePx(handle);
	}

	unsigned int BufferResource::createRtBuffer(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		return m_renderTargetBuffer->create(device, renderTargetSize, clearColor);
	}

	unsigned int BufferResource::createRtBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		return m_renderTargetBuffer->create(swapChain, backBufferIndex);
	}

	void BufferResource::createRtv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_renderTargetBuffer->createRtv(handle, device, heapHandle);
	}

	void BufferResource::createRtSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_renderTargetBuffer->createSrv(handle, device, heapHandle);
	}

	void BufferResource::beginWriteBasicRtBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBuffer->beginWriteBasicRtBuffer(handle, commandList);
	}

	void BufferResource::endWriteBasicRtBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBuffer->endWriteBasicRtBuffer(handle, commandList);
	}

	void BufferResource::beginWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBuffer->beginWriteBackBuffer(handle, commandList);
	}

	void BufferResource::endWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBuffer->endWriteBackBuffer(handle, commandList);
	}

	const tktkMath::Vector2& BufferResource::getRenderTargetSizePx(unsigned int handle) const
	{
		return m_renderTargetBuffer->getRenderTargetSizePx(handle);
	}
}