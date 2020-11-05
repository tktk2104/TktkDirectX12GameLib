#include "TktkDX12Wrapper/Resource/Buffer/Upload/UploadBufferData.h"

namespace tktk
{
	UploadBufferData::UploadBufferData(ID3D12Device* device, const UploadBufferInitParam& initParam)
		: m_targetBufferType(initParam.targetBufferType)
		, m_targetBufferHandle(initParam.targetBufferHandle)
		, m_copyBufferSize(initParam.bufferWidth)
	{
		D3D12_HEAP_PROPERTIES uploadHeapProp{};
		uploadHeapProp.Type					= D3D12_HEAP_TYPE_UPLOAD;
		uploadHeapProp.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		uploadHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		uploadHeapProp.CreationNodeMask		= 0;
		uploadHeapProp.VisibleNodeMask		= 0;

		// 中間バッファなのでバッファはただのバイナリデータの塊として解釈させる
		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension			= D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Format				= DXGI_FORMAT_UNKNOWN;
		resDesc.Width				= static_cast<unsigned long long>(initParam.bufferWidth);
		resDesc.Height				= 1;
		resDesc.DepthOrArraySize	= 1;
		resDesc.MipLevels			= 1;
		resDesc.SampleDesc.Count	= 1;
		resDesc.SampleDesc.Quality	= 0;
		resDesc.Flags				= D3D12_RESOURCE_FLAG_NONE;
		resDesc.Layout				= D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		device->CreateCommittedResource(
			&uploadHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_uploadBuffer)
		);

		// 定数バッファをCPUアクセス特化ヒープにコピーする
		void* mappedBuffer{ nullptr };
		m_uploadBuffer->Map(0, nullptr, &mappedBuffer);
		memcpy(mappedBuffer, initParam.dataTopPos, initParam.bufferWidth);
		m_uploadBuffer->Unmap(0, nullptr);
	}

	UploadBufferData::~UploadBufferData()
	{
		if (m_uploadBuffer == nullptr)
		{
			m_uploadBuffer->Release();
		}
	}

	UploadBufferData::UploadBufferData(ID3D12Device* device, const UploadBufferData& other)
		: m_uploadBuffer(other.m_uploadBuffer)
		, m_targetBufferType(other.m_targetBufferType)
		, m_targetBufferHandle(other.m_targetBufferHandle)
		, m_copyBufferSize(other.m_copyBufferSize)
	{
		D3D12_HEAP_PROPERTIES uploadHeapProp{};
		uploadHeapProp.Type					= D3D12_HEAP_TYPE_UPLOAD;
		uploadHeapProp.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		uploadHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		uploadHeapProp.CreationNodeMask		= 0;
		uploadHeapProp.VisibleNodeMask		= 0;

		device->CreateCommittedResource(
			&uploadHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&other.m_uploadBuffer->GetDesc(),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_uploadBuffer)
		);

		// 定数バッファをCPUアクセス特化ヒープにコピーする
		void* mappedReadBuffer{ nullptr };
		void* mappedDestBuffer{ nullptr };
		other.m_uploadBuffer->Map(0, nullptr, &mappedReadBuffer);
		m_uploadBuffer->Map(0, nullptr, &mappedDestBuffer);
		memcpy(mappedDestBuffer, mappedReadBuffer, static_cast<unsigned int>(other.m_uploadBuffer->GetDesc().Width));
		m_uploadBuffer->Unmap(0, nullptr);
		other.m_uploadBuffer->Unmap(0, nullptr);
	}

	UploadBufferData::UploadBufferData(UploadBufferData&& other) noexcept
		: m_uploadBuffer(other.m_uploadBuffer)
		, m_targetBufferType(other.m_targetBufferType)
		, m_targetBufferHandle(other.m_targetBufferHandle)
		, m_copyBufferSize(other.m_copyBufferSize)
	{
		other.m_uploadBuffer = nullptr;
	}

	void UploadBufferData::updateBuffer(const CopySourceDataCarrier& bufferData)
	{
		// 定数バッファをCPUアクセス特化ヒープにコピーする
		void* mappedBuffer{ nullptr };
		m_uploadBuffer->Map(0, nullptr, &mappedBuffer);
		memcpy(mappedBuffer, bufferData.dataTopPos, bufferData.dataSize);
		m_uploadBuffer->Unmap(0, nullptr);
	}

	BufferType UploadBufferData::getTargetBufferType() const
	{
		return m_targetBufferType;
	}

	size_t UploadBufferData::getTargetBufferHandle() const
	{
		return m_targetBufferHandle;
	}

	void UploadBufferData::copyBuffer(ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer) const
	{
		// 対象のバッファーのバリアを「読み取り」状態から「コピー先」状態に変更する
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type					= D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags					= D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource	= targetBuffer;
		barrierDesc.Transition.Subresource	= D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrierDesc.Transition.StateBefore	= D3D12_RESOURCE_STATE_GENERIC_READ;
		barrierDesc.Transition.StateAfter	= D3D12_RESOURCE_STATE_COPY_DEST;
		commandList->ResourceBarrier(1, &barrierDesc);

		// GPU間のメモリのコピーを行う
		commandList->CopyBufferRegion(targetBuffer, 0, m_uploadBuffer, 0, static_cast<unsigned long long>(m_copyBufferSize));

		// 定数バッファーのバリアを「コピー先」状態から「読み取り」状態に変更する
		barrierDesc.Transition.StateBefore	= D3D12_RESOURCE_STATE_COPY_DEST;
		barrierDesc.Transition.StateAfter	= D3D12_RESOURCE_STATE_GENERIC_READ;
		commandList->ResourceBarrier(1, &barrierDesc);
	}
}