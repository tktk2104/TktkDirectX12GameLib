#include "TktkDX12Wrapper/Resource/Buffer/Constant/ConstantBufferData.h"

#include <algorithm>
#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	ConstantBufferData::ConstantBufferData(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		// GPUアクセスに特化したヒープを作る（シェーダーが使用する）
		D3D12_HEAP_PROPERTIES constBuffHeapProp{};
		constBuffHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;//D3D12_HEAP_TYPE_UPLOAD;
		constBuffHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		constBuffHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		constBuffHeapProp.CreationNodeMask = 0U;
		constBuffHeapProp.VisibleNodeMask = 0U;

		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Format = DXGI_FORMAT_UNKNOWN;
		resDesc.Width = (constantBufferTypeSize + 0xff) & ~0xff;
		resDesc.Height = 1;
		resDesc.DepthOrArraySize = 1;
		resDesc.MipLevels = 1;
		resDesc.SampleDesc.Count = 1;
		resDesc.SampleDesc.Quality = 0;
		resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		device->CreateCommittedResource(
			&constBuffHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_constantBuffer)
		);
	}

	ConstantBufferData::~ConstantBufferData()
	{
		if (m_constantBuffer != nullptr)
		{
			m_constantBuffer->Release();
		}

		for (auto node : m_uploadBufferList)
		{
			if (node != nullptr)
			{
				node->Release();
			}
		}
	}

	ConstantBufferData::ConstantBufferData(ConstantBufferData&& other) noexcept
		: m_constantBuffer(other.m_constantBuffer)
		, m_uploadBufferList(std::move(other.m_uploadBufferList))
	{
		other.m_constantBuffer = nullptr;
		other.m_uploadBufferList.clear();
	}

	void ConstantBufferData::createCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc{};
		cbvDesc.BufferLocation = m_constantBuffer->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = static_cast<UINT>(m_constantBuffer->GetDesc().Width);

		device->CreateConstantBufferView(&cbvDesc, heapHandle);
	}

	void ConstantBufferData::updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
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
			resDesc.Width = m_constantBuffer->GetDesc().Width;
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

		// 定数バッファをCPUアクセス特化ヒープにコピーする
		void* mappedBuffer{ nullptr };
		uploadBuff->Map(0, nullptr, &mappedBuffer);
		memcpy(mappedBuffer, constantBufferDataTopPos, constantBufferTypeSize);
		uploadBuff->Unmap(0, nullptr);

		// 定数バッファーのバリアを「読み取り」状態から「コピー先」状態に変更する
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_constantBuffer;
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
		commandList->CopyBufferRegion(m_constantBuffer, 0, uploadBuff, 0, constantBufferTypeSize);

		// 定数バッファーのバリアを「コピー先」状態から「読み取り」状態に変更する
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
		commandList->ResourceBarrier(1, &barrierDesc);

		// 一時的にアップロードバッファを保存する
		m_uploadBufferList.push_front(uploadBuff);
	}

	void ConstantBufferData::deleteUploadBufferAll()
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

	ID3D12Resource* ConstantBufferData::getBufferPtr() const
	{
		return m_constantBuffer;
	}
}