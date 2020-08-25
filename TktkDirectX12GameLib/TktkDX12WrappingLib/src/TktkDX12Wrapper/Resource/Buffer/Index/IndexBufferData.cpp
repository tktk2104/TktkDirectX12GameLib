#include "TktkDX12Wrapper/Resource/Buffer/Index/IndexBufferData.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	IndexBufferData::IndexBufferData(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray)
	{
		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Format = DXGI_FORMAT_UNKNOWN;
		resDesc.Width = (UINT64)sizeof(unsigned short) * (UINT64)indexDataArray.size();
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
			IID_PPV_ARGS(&m_indexBuffer)
		);

		unsigned short* mappedIndex{ nullptr };
		m_indexBuffer->Map(0, nullptr, (void**)&mappedIndex);
		std::copy(std::begin(indexDataArray), std::end(indexDataArray), mappedIndex);
		m_indexBuffer->Unmap(0, nullptr);

		m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
		m_indexBufferView.Format = DXGI_FORMAT_R16_UINT;
		m_indexBufferView.SizeInBytes = sizeof(unsigned short) * indexDataArray.size();
	}

	IndexBufferData::~IndexBufferData()
	{
		if (m_indexBuffer != nullptr)
		{
			m_indexBuffer->Release();
		}

		for (auto node : m_uploadBufferList)
		{
			if (node != nullptr)
			{
				node->Release();
			}
		}
	}

	IndexBufferData::IndexBufferData(IndexBufferData&& other) noexcept
		: m_indexBuffer(other.m_indexBuffer)
		, m_indexBufferView(other.m_indexBufferView)
		, m_uploadBufferList(std::move(other.m_uploadBufferList))
	{
		other.m_indexBuffer = nullptr;
		other.m_uploadBufferList.clear();
	}

	void IndexBufferData::set(ID3D12GraphicsCommandList* commandList) const
	{
		commandList->IASetIndexBuffer(&m_indexBufferView);
	}

	void IndexBufferData::updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray)
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
			resDesc.Width = m_indexBuffer->GetDesc().Width;
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

		// インデックスバッファをCPUアクセス特化ヒープにコピーする
		{
			unsigned short* mappedIndex{ nullptr };
			uploadBuff->Map(0, nullptr, (void**)&mappedIndex);
			std::copy(std::begin(indexDataArray), std::end(indexDataArray), mappedIndex);
			uploadBuff->Unmap(0, nullptr);
		}

		// インデックスバッファーのバリアを「読み取り」状態から「コピー先」状態に変更する
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_indexBuffer;
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
		commandList->CopyBufferRegion(m_indexBuffer, 0, uploadBuff, 0, static_cast<unsigned long long>(sizeof(unsigned short)) * indexDataArray.size());

		// インデックスバッファーのバリアを「コピー先」状態から「読み取り」状態に変更する
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
		commandList->ResourceBarrier(1, &barrierDesc);

		// 一時的にアップロードバッファを保存する
		m_uploadBufferList.push_front(uploadBuff);
	}

	void IndexBufferData::deleteUploadBufferAll()
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
}