#include "TktkDX12Wrapper/Resource/Buffer/Copy/CopyBufferData.h"

namespace tktk
{
	CopyBufferData::CopyBufferData(ID3D12Device* device, const CopyBufferInitParam& initParam)
		: m_targetBufferType(initParam.targetBufferType)
		, m_targetBufferHandle(initParam.targetBufferHandle)
		, m_copyBufferSize(initParam.bufferWidth)
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
		resDesc.Width = static_cast<unsigned long long>(initParam.bufferWidth);
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
			IID_PPV_ARGS(&m_copyBuffer)
		);

		// 定数バッファをCPUアクセス特化ヒープにコピーする
		void* mappedBuffer{ nullptr };
		m_copyBuffer->Map(0, nullptr, &mappedBuffer);
		memcpy(mappedBuffer, initParam.dataTopPos, initParam.bufferWidth);
		m_copyBuffer->Unmap(0, nullptr);
	}

	CopyBufferData::~CopyBufferData()
	{
		if (m_copyBuffer == nullptr)
		{
			m_copyBuffer->Release();
		}
	}

	CopyBufferData::CopyBufferData(ID3D12Device* device, const CopyBufferData& other)
		: m_copyBuffer(other.m_copyBuffer)
		, m_targetBufferType(other.m_targetBufferType)
		, m_targetBufferHandle(other.m_targetBufferHandle)
		, m_copyBufferSize(other.m_copyBufferSize)
	{
		D3D12_HEAP_PROPERTIES uploadHeapProp{};
		uploadHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
		uploadHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		uploadHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		uploadHeapProp.CreationNodeMask = 0;
		uploadHeapProp.VisibleNodeMask = 0;

		device->CreateCommittedResource(
			&uploadHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&other.m_copyBuffer->GetDesc(),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_copyBuffer)
		);

		// 定数バッファをCPUアクセス特化ヒープにコピーする
		void* mappedReadBuffer{ nullptr };
		void* mappedDestBuffer{ nullptr };
		other.m_copyBuffer->Map(0, nullptr, &mappedReadBuffer);
		m_copyBuffer->Map(0, nullptr, &mappedDestBuffer);
		memcpy(mappedDestBuffer, mappedReadBuffer, static_cast<unsigned int>(other.m_copyBuffer->GetDesc().Width));
		m_copyBuffer->Unmap(0, nullptr);
		other.m_copyBuffer->Unmap(0, nullptr);
	}

	CopyBufferData::CopyBufferData(CopyBufferData&& other) noexcept
		: m_copyBuffer(other.m_copyBuffer)
		, m_targetBufferType(other.m_targetBufferType)
		, m_targetBufferHandle(other.m_targetBufferHandle)
		, m_copyBufferSize(other.m_copyBufferSize)
	{
		other.m_copyBuffer = nullptr;
	}

	void CopyBufferData::updateBuffer(unsigned int bufferSize, const void* bufferDataTopPos)
	{
		// 定数バッファをCPUアクセス特化ヒープにコピーする
		void* mappedBuffer{ nullptr };
		m_copyBuffer->Map(0, nullptr, &mappedBuffer);
		memcpy(mappedBuffer, bufferDataTopPos, bufferSize);
		m_copyBuffer->Unmap(0, nullptr);
	}

	BufferType CopyBufferData::getTargetBufferType() const
	{
		return m_targetBufferType;
	}

	unsigned int CopyBufferData::getTargetBufferHandle() const
	{
		return m_targetBufferHandle;
	}

	void CopyBufferData::copyBuffer(ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer) const
	{
		// 対象のバッファーのバリアを「読み取り」状態から「コピー先」状態に変更する
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = targetBuffer;
		barrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_GENERIC_READ;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
		commandList->ResourceBarrier(1, &barrierDesc);

		// GPU間のメモリのコピーを行う
		commandList->CopyBufferRegion(targetBuffer, 0, m_copyBuffer, 0, static_cast<unsigned long long>(m_copyBufferSize));

		// 定数バッファーのバリアを「コピー先」状態から「読み取り」状態に変更する
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
		commandList->ResourceBarrier(1, &barrierDesc);
	}
}