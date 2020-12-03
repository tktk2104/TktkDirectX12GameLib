#include "TktkDX12Wrapper/Resource/DescriptorHeap/Rtv/RtvDescriptorHeap.h"

namespace tktk
{
	RtvDescriptorHeap::RtvDescriptorHeap(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_rtvDescriptorHeapDataArray(initParam)
	{
	}

	size_t RtvDescriptorHeap::create(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		return m_rtvDescriptorHeapDataArray.create(device, initParam);
	}

	void RtvDescriptorHeap::erase(size_t handle)
	{
		m_rtvDescriptorHeapDataArray.erase(handle);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> RtvDescriptorHeap::getCpuHeapHandleArray(size_t handle, ID3D12Device* device) const
	{
		return m_rtvDescriptorHeapDataArray.getMatchHandlePtr(handle)->getCpuHeapHandleArray(device);
	}

	const std::vector<size_t>& RtvDescriptorHeap::getRtBufferHandleArray(size_t handle) const
	{
		return m_rtvDescriptorHeapDataArray.getMatchHandlePtr(handle)->getRtBufferHandleArray();
	}

	ID3D12DescriptorHeap* RtvDescriptorHeap::getPtr(size_t handle) const
	{
		return m_rtvDescriptorHeapDataArray.getMatchHandlePtr(handle)->getPtr();
	}

	void RtvDescriptorHeap::setRootDescriptorTable(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_rtvDescriptorHeapDataArray.getMatchHandlePtr(handle)->setRootDescriptorTable(device, commandList);
	}

	void RtvDescriptorHeap::setRtv(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, unsigned int rtvCount, const D3D12_CPU_DESCRIPTOR_HANDLE* useDsvHandle) const
	{
		m_rtvDescriptorHeapDataArray.getMatchHandlePtr(handle)->setRtv(device, commandList, startRtvLocationIndex, rtvCount, useDsvHandle);
	}
}