#include "TktkDX12Wrapper/Resource/Buffer/Vertex/VertexBufferData.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	VertexBufferData::VertexBufferData(ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Format = DXGI_FORMAT_UNKNOWN;
		resDesc.Width = static_cast<UINT64>(vertexTypeSize) * vertexDataCount;
		resDesc.Height = 1;
		resDesc.DepthOrArraySize = 1;
		resDesc.MipLevels = 1;
		resDesc.SampleDesc.Count = 1;
		resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_vertexBuffer)
		);

		{
			void* mappedVertexData{ nullptr };
			m_vertexBuffer->Map(0, nullptr, &mappedVertexData);
			memcpy(mappedVertexData, vertexDataTopPos, vertexTypeSize * vertexDataCount);
			m_vertexBuffer->Unmap(0, nullptr);
		}

		m_vertexBufferView.BufferLocation	= m_vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.SizeInBytes		= vertexTypeSize * vertexDataCount;
		m_vertexBufferView.StrideInBytes	= vertexTypeSize;
	}

	VertexBufferData::~VertexBufferData()
	{
		if (m_vertexBuffer != nullptr)
		{
			m_vertexBuffer->Release();
		}
	}

	VertexBufferData::VertexBufferData(VertexBufferData&& other) noexcept
		: m_vertexBuffer(other.m_vertexBuffer)
		, m_vertexBufferView(other.m_vertexBufferView)
		, m_uploadBufferList(std::move(other.m_uploadBufferList))
	{
		m_vertexBuffer = nullptr;
		m_uploadBufferList.clear();
	}

	void VertexBufferData::set(ID3D12GraphicsCommandList* commandList) const
	{
		commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
	}

	void VertexBufferData::updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		ID3D12Resource* uploadBuff;

		// CPUアクセスに特化したヒープを作る（CPUからデータをコピーする時に使用する）
		{
			D3D12_HEAP_PROPERTIES uploadHeapProp{};
			uploadHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
			uploadHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			uploadHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			uploadHeapProp.CreationNodeMask = 0;
			uploadHeapProp.VisibleNodeMask = 0;

			// 中間バッファなのでバッファはただのバイナリデータの塊として解釈させる
			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			resDesc.Format = DXGI_FORMAT_UNKNOWN;
			resDesc.Width = m_vertexBuffer->GetDesc().Width;
			resDesc.Height = 1;
			resDesc.DepthOrArraySize = 1;
			resDesc.MipLevels = 1;
			resDesc.SampleDesc.Count = 1;
			resDesc.SampleDesc.Quality = 0;
			resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
			resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

			device->CreateCommittedResource(
				&uploadHeapProp,
				D3D12_HEAP_FLAG_NONE,
				&resDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&uploadBuff)
			);
		}

		// 頂点バッファをCPUアクセス特化ヒープにコピーする
		{
			void* mappedVertexData{ nullptr };
			uploadBuff->Map(0, nullptr, &mappedVertexData);
			memcpy(mappedVertexData, vertexDataTopPos, vertexTypeSize * vertexDataCount);
			uploadBuff->Unmap(0, nullptr);
		}

		// 頂点バッファーのバリアを「読み取り」状態から「コピー先」状態に変更する
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_vertexBuffer;
		barrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_GENERIC_READ;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
		commandList->ResourceBarrier(1, &barrierDesc);

		if (uploadBuff == nullptr)
		{
#ifdef _DEBUG
			throw std::runtime_error("uploadBuff create error");
			return;
#else
			return;
#endif // _DEBUG

		}

		// GPU間のメモリのコピーを行う
		commandList->CopyBufferRegion(m_vertexBuffer, 0, uploadBuff, 0, static_cast<unsigned long long>(vertexTypeSize) * vertexDataCount);

		// 定数バッファーのバリアを「コピー先」状態から「読み取り」状態に変更する
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
		commandList->ResourceBarrier(1, &barrierDesc);

		// 一時的にアップロードバッファを保存する
		m_uploadBufferList.push_front(uploadBuff);
	}

	void VertexBufferData::deleteUploadBufferAll()
	{
		for (auto node : m_uploadBufferList)
		{
			if (node != nullptr)
			{
				node->Release();
			}
		}
		m_uploadBufferList.clear();
	}

	ID3D12Resource* VertexBufferData::getBufferPtr() const
	{
		return m_vertexBuffer;
	}
}