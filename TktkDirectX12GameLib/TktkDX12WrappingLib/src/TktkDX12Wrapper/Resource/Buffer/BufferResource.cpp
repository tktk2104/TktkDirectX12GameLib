#include "TktkDX12Wrapper/Resource/Buffer/BufferResource.h"

#include <TktkFileIo/lodepng.h>
#include <TktkFileIo/lodebmp.h>
#include "TktkDX12Wrapper/Resource/Buffer/Upload/UploadBuffer.h"
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
		m_uploadBuffer			= std::make_unique<UploadBuffer>(initParam.copyBufferContainerInitParam);
		m_vertexBuffer			= std::make_unique<VertexBuffer>(initParam.vertexBufferContainerInitParam);
		m_indexBuffer			= std::make_unique<IndexBuffer>(initParam.indexBufferContainerInitParam);
		m_constantBuffer		= std::make_unique<ConstantBuffer>(initParam.cbufferContainerInitParam);
		m_textureBuffer			= std::make_unique<TextureBuffer>(initParam.textureBufferStaticNodeNum);
		m_depthStencilBuffer	= std::make_unique<DepthStencilBuffer>(initParam.dsbufferStaticNodeNum);
		m_renderTargetBuffer	= std::make_unique<RenderTargetBuffer>(initParam.rtbufferStaticNodeNum);
	}

	// デストラクタを非インライン化する
	BufferResource::~BufferResource() = default;

	size_t BufferResource::createUploadBuffer(ID3D12Device* device, const UploadBufferInitParam& initParam)
	{
		return m_uploadBuffer->create(device, initParam);
	}

	void BufferResource::createTempUploadBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const UploadBufferInitParam& initParam)
	{
		ID3D12Resource* targetBuffer = nullptr;

		switch (initParam.targetBufferType)
		{
		case BufferType::renderTarget:

			m_renderTargetBuffer->getBufferPtr(m_uploadBuffer->getTargetBufferHandle(initParam.targetBufferHandle));
			break;

		case BufferType::depthStencil:

			m_depthStencilBuffer->getBufferPtr(m_uploadBuffer->getTargetBufferHandle(initParam.targetBufferHandle));
			break;

		case BufferType::vertex:

			m_vertexBuffer->getBufferPtr(m_uploadBuffer->getTargetBufferHandle(initParam.targetBufferHandle));
			break;

		case BufferType::index:

			m_indexBuffer->getBufferPtr(m_uploadBuffer->getTargetBufferHandle(initParam.targetBufferHandle));
			break;

		case BufferType::constant:

			m_constantBuffer->getBufferPtr(m_uploadBuffer->getTargetBufferHandle(initParam.targetBufferHandle));
			break;

		case BufferType::texture:

			m_textureBuffer->getBufferPtr(m_uploadBuffer->getTargetBufferHandle(initParam.targetBufferHandle));
			break;
		}

		m_uploadBuffer->createTempBuffer(device, commandList, initParam, targetBuffer);
	}

	size_t BufferResource::duplicateUploadBuffer(ID3D12Device* device, size_t originalHandle)
	{
		return m_uploadBuffer->duplicate(device, originalHandle);
	}

	void BufferResource::clearTempUploadBuffer()
	{
		m_uploadBuffer->clearTempBuffer();
	}

	void BufferResource::eraseUploadBuffer(size_t handle)
	{
		m_uploadBuffer->erase(handle);
	}

	void BufferResource::updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData)
	{
		m_uploadBuffer->updateBuffer(handle, bufferData);
	}

	void BufferResource::copyBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		switch (m_uploadBuffer->getTargetBufferType(handle))
		{
		case BufferType::renderTarget:

			m_uploadBuffer->copyBuffer(handle, commandList, m_renderTargetBuffer->getBufferPtr(m_uploadBuffer->getTargetBufferHandle(handle)));
			break;

		case BufferType::depthStencil:

			m_uploadBuffer->copyBuffer(handle, commandList, m_depthStencilBuffer->getBufferPtr(m_uploadBuffer->getTargetBufferHandle(handle)));
			break;

		case BufferType::vertex:

			m_uploadBuffer->copyBuffer(handle, commandList, m_vertexBuffer->getBufferPtr(m_uploadBuffer->getTargetBufferHandle(handle)));
			break;

		case BufferType::index:

			m_uploadBuffer->copyBuffer(handle, commandList, m_indexBuffer->getBufferPtr(m_uploadBuffer->getTargetBufferHandle(handle)));
			break;

		case BufferType::constant:

			m_uploadBuffer->copyBuffer(handle, commandList, m_constantBuffer->getBufferPtr(m_uploadBuffer->getTargetBufferHandle(handle)));
			break;

		case BufferType::texture:

			m_uploadBuffer->copyTexture(
				handle,
				commandList,
				m_textureBuffer->getBufferPtr(m_uploadBuffer->getTargetBufferHandle(handle)),
				m_textureBuffer->createSrcCopyLoaction(m_uploadBuffer->getTargetBufferHandle(handle))
			);
			break;
		}
	}

	size_t BufferResource::createVertexBuffer(ID3D12Device* device, const VertexDataCarrier& vertexData)
	{
		return m_vertexBuffer->create(device, vertexData);
	}

	void BufferResource::eraseVertexBuffer(size_t handle)
	{
		m_vertexBuffer->erase(handle);
	}

	void BufferResource::updateVertexBuffer(size_t handle, const VertexDataCarrier& vertexData)
	{
		m_vertexBuffer->update(handle, vertexData);
	}

	void BufferResource::setVertexBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_vertexBuffer->set(handle, commandList);
	}

	void BufferResource::setVertexBuffer(size_t meshVertHandle, size_t instancingVertHandle, ID3D12GraphicsCommandList* commandList) const
	{
		m_vertexBuffer->set(meshVertHandle, instancingVertHandle, commandList);
	}

	size_t BufferResource::createIndexBuffer(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray)
	{
		return m_indexBuffer->create(device, indexDataArray);
	}

	void BufferResource::eraseIndexBuffer(size_t handle)
	{
		m_indexBuffer->erase(handle);
	}

	void BufferResource::setIndexBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_indexBuffer->set(handle, commandList);
	}

	size_t BufferResource::createCBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const CopySourceDataCarrier& constantBufferData)
	{
		size_t createdHandle = m_constantBuffer->create(device, constantBufferData.dataSize);

		auto initParam = UploadBufferInitParam(BufferType::constant, createdHandle, constantBufferData.dataSize, constantBufferData.dataTopPos);

		m_uploadBuffer->createTempBuffer(
			device,
			commandList,
			initParam,
			m_constantBuffer->getBufferPtr(createdHandle)
		);

		return createdHandle;
	}

	void BufferResource::eraseCBuffer(size_t handle)
	{
		m_constantBuffer->erase(handle);
	}

	void BufferResource::createCbv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_constantBuffer->createCbv(handle, device, heapHandle);
	}

	size_t BufferResource::createTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		size_t createdHandle = m_textureBuffer->create(device, formatParam, dataParam);

		UploadBufferInitParam initParam = UploadBufferInitParam::create(BufferType::texture, createdHandle, dataParam.textureData);

		auto srcCopyLoaction = m_textureBuffer->createSrcCopyLoaction(createdHandle);

		m_uploadBuffer->createTempBuffer(
			device,
			commandList,
			initParam,
			srcCopyLoaction.PlacedFootprint.Footprint.RowPitch,
			srcCopyLoaction.PlacedFootprint.Footprint.Width * m_textureBuffer->getPixDataSizeByte(createdHandle),
			srcCopyLoaction.PlacedFootprint.Footprint.Height,
			m_textureBuffer->getBufferPtr(createdHandle),
			srcCopyLoaction
		);

		return createdHandle;
	}

	size_t BufferResource::loadTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath)
	{
		TexBufFormatParam formatParam{};
		TexBuffData dataParam{};

		auto extension = texDataPath.substr(texDataPath.size() - 3U, 3U);

		if (extension == "bmp")
		{
			formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize = 1U;
			formatParam.mipLevels = 1U;
			formatParam.sampleDescCount = 1U;
			formatParam.sampleDescQuality = 0U;

			tktkFileIo::lodebmp::loadData outData{};
			tktkFileIo::lodebmp::load(&outData, texDataPath);
			dataParam.width = outData.width;
			dataParam.height = outData.height;
			dataParam.textureData.resize(outData.data.size());
			std::copy(std::begin(outData.data), std::end(outData.data), std::begin(dataParam.textureData));
		}
		else if (extension == "png")
		{
			formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize = 1U;
			formatParam.mipLevels = 1U;
			formatParam.sampleDescCount = 1U;
			formatParam.sampleDescQuality = 0U;

			auto error = lodepng::decode(dataParam.textureData, dataParam.width, dataParam.height, texDataPath.c_str());
#ifdef _DEBUG
			if (error != 0)
			{
				throw std::runtime_error("can not open " + texDataPath);
			}
#endif // _DEBUG
		}

		size_t createdHandle = m_textureBuffer->create(device, formatParam, dataParam);

		UploadBufferInitParam initParam = UploadBufferInitParam::create(BufferType::texture, createdHandle, dataParam.textureData);

		auto srcCopyLoaction = m_textureBuffer->createSrcCopyLoaction(createdHandle);

		m_uploadBuffer->createTempBuffer(
			device,
			commandList,
			initParam,
			srcCopyLoaction.PlacedFootprint.Footprint.RowPitch,
			srcCopyLoaction.PlacedFootprint.Footprint.Width * m_textureBuffer->getPixDataSizeByte(createdHandle),
			srcCopyLoaction.PlacedFootprint.Footprint.Height,
			m_textureBuffer->getBufferPtr(createdHandle),
			srcCopyLoaction
		);

		return createdHandle;
	}

	void BufferResource::eraseTextureBuffer(size_t handle)
	{
		m_textureBuffer->erase(handle);
	}

	void BufferResource::createSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_textureBuffer->createSrv(handle, device, heapHandle);
	}

	const tktkMath::Vector3& BufferResource::getTextureSizePx(size_t handle) const
	{
		return m_textureBuffer->getTextureSizePx(handle);
	}

	size_t BufferResource::createDsBuffer(ID3D12Device* device, const DepthStencilBufferInitParam& initParam)
	{
		return m_depthStencilBuffer->create(device, initParam);
	}

	void BufferResource::eraseDsBuffer(size_t handle)
	{
		m_depthStencilBuffer->erase(handle);
	}

	void BufferResource::createDsv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_depthStencilBuffer->createDsv(handle, device, heapHandle);
	}

	void BufferResource::createDsSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_depthStencilBuffer->createSrv(handle, device, heapHandle);
	}

	void BufferResource::beginWriteDsBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBuffer->beginWrite(handle, commandList);
	}

	void BufferResource::endWriteDsBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
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

	const tktkMath::Vector2& BufferResource::getDepthStencilSizePx(size_t handle) const
	{
		return m_depthStencilBuffer->getDepthStencilSizePx(handle);
	}

	size_t BufferResource::createRtBuffer(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		return m_renderTargetBuffer->create(device, renderTargetSize, clearColor);
	}

	size_t BufferResource::createRtBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		return m_renderTargetBuffer->create(swapChain, backBufferIndex);
	}

	void BufferResource::eraseRtBuffer(size_t handle)
	{
		m_renderTargetBuffer->erase(handle);
	}

	void BufferResource::createRtv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_renderTargetBuffer->createRtv(handle, device, heapHandle);
	}

	void BufferResource::createRtSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_renderTargetBuffer->createSrv(handle, device, heapHandle);
	}

	const tktkMath::Color& BufferResource::getRtBufferClearColor(size_t handle) const
	{
		return m_renderTargetBuffer->getClearColor(handle);
	}

	void BufferResource::beginWriteBasicRtBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBuffer->beginWriteBasicRtBuffer(handle, commandList);
	}

	void BufferResource::endWriteBasicRtBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBuffer->endWriteBasicRtBuffer(handle, commandList);
	}

	void BufferResource::beginWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBuffer->beginWriteBackBuffer(handle, commandList);
	}

	void BufferResource::endWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBuffer->endWriteBackBuffer(handle, commandList);
	}

	const tktkMath::Vector2& BufferResource::getRenderTargetSizePx(size_t handle) const
	{
		return m_renderTargetBuffer->getRenderTargetSizePx(handle);
	}
}