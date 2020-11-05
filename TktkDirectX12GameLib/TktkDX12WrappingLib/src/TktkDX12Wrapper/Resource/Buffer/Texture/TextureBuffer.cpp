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

	size_t TextureBuffer::cpuPriorityCreate(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_textureBufferDataArray.create(device, formatParam, dataParam);
	}

	size_t TextureBuffer::gpuPriorityCreate(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_textureBufferDataArray.create(device, commandList, formatParam, dataParam);
	}

	size_t TextureBuffer::cpuPriorityLoad(ID3D12Device* device, const std::string& texDataPath)
	{
		TexBufFormatParam formatParam{};
		TexBuffData dataParam{};

		auto extension = texDataPath.substr(texDataPath.size() - 3U, 3U);

		if (extension == "bmp")
		{
			formatParam.resourceDimension	= D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format				= DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize			= 1U;
			formatParam.mipLevels			= 1U;
			formatParam.sampleDescCount		= 1U;
			formatParam.sampleDescQuality	= 0U;

			tktkFileIo::lodebmp::loadData outData{};
			tktkFileIo::lodebmp::load(&outData, texDataPath);
			dataParam.width		= outData.width;
			dataParam.height	= outData.height;
			dataParam.textureData.resize(outData.data.size());
			std::copy(std::begin(outData.data), std::end(outData.data), std::begin(dataParam.textureData));
		}
		else if (extension == "png")
		{
			formatParam.resourceDimension	= D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format				= DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize			= 1U;
			formatParam.mipLevels			= 1U;
			formatParam.sampleDescCount		= 1U;
			formatParam.sampleDescQuality	= 0U;

			auto error = lodepng::decode(dataParam.textureData, dataParam.width, dataParam.height, texDataPath.c_str());
#ifdef _DEBUG
			if (error != 0)
			{
				throw std::runtime_error("can not open " + texDataPath);
			}
#endif // _DEBUG
		}
		return cpuPriorityCreate(device, formatParam, dataParam);
	}

	size_t TextureBuffer::gpuPriorityLoad(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath)
	{
		TexBufFormatParam formatParam{};
		TexBuffData dataParam{};

		auto extension = texDataPath.substr(texDataPath.size() - 3U, 3U);

		if (extension == "bmp")
		{
			formatParam.resourceDimension	= D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format				= DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize			= 1U;
			formatParam.mipLevels			= 1U;
			formatParam.sampleDescCount		= 1U;
			formatParam.sampleDescQuality	= 0U;

			tktkFileIo::lodebmp::loadData outData{};
			tktkFileIo::lodebmp::load(&outData, texDataPath);
			dataParam.width		= outData.width;
			dataParam.height	= outData.height;
			dataParam.textureData.resize(outData.data.size());
			std::copy(std::begin(outData.data), std::end(outData.data), std::begin(dataParam.textureData));
		}
		else if (extension == "png")
		{
			formatParam.resourceDimension	= D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format				= DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize			= 1U;
			formatParam.mipLevels			= 1U;
			formatParam.sampleDescCount		= 1U;
			formatParam.sampleDescQuality	= 0U;

			auto error = lodepng::decode(dataParam.textureData, dataParam.width, dataParam.height, texDataPath.c_str());
#ifdef _DEBUG
			if (error != 0)
			{
				throw std::runtime_error("can not open " + texDataPath);
			}
#endif // _DEBUG
		}
		return gpuPriorityCreate(device, commandList, formatParam, dataParam);
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
}