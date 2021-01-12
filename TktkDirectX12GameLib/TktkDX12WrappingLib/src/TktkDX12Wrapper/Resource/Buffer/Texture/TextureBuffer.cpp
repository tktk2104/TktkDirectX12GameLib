#include "TktkDX12Wrapper/Resource/Buffer/Texture/TextureBuffer.h"
#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG
#include <TktkFileIo/BinaryFileReader.h>
#include <TktkFileIo/lodepng.h>
#include <TktkFileIo/lodebmp.h>


namespace tktk
{
	TextureBuffer::TextureBuffer(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_textureBufferDataArray(initParam)
	{
	}

	size_t TextureBuffer::create(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_textureBufferDataArray.create(device, formatParam, dataParam);
	}

	void TextureBuffer::erase(size_t handle)
	{
		m_textureBufferDataArray.erase(handle);
	}

	void TextureBuffer::createSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_textureBufferDataArray.getMatchHandlePtr(handle)->createSrv(device, heapHandle);
	}

	const tktkMath::Vector3& TextureBuffer::getTextureSizePx(size_t handle) const
	{
		return m_textureBufferDataArray.getMatchHandlePtr(handle)->getTextureSizePx();
	}

	ID3D12Resource* TextureBuffer::getBufferPtr(size_t handle) const
	{
		return m_textureBufferDataArray.getMatchHandlePtr(handle)->getBufferPtr();
	}

	size_t TextureBuffer::getPixDataSizeByte(size_t handle) const
	{
		return m_textureBufferDataArray.getMatchHandlePtr(handle)->getPixDataSizeByte();
	}

	D3D12_TEXTURE_COPY_LOCATION TextureBuffer::createSrcCopyLoaction(size_t handle) const
	{
		return m_textureBufferDataArray.getMatchHandlePtr(handle)->createSrcCopyLoaction();
	}
}