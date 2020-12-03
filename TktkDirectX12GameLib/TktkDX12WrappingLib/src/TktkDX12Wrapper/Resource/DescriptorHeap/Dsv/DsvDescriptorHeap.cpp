#include "TktkDX12Wrapper/Resource/DescriptorHeap/Dsv/DsvDescriptorHeap.h"

namespace tktk
{
	DsvDescriptorHeap::DsvDescriptorHeap(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_dsvDescriptorHeapDataArray(initParam)
	{
	}

	size_t DsvDescriptorHeap::create(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam)
	{
		return m_dsvDescriptorHeapDataArray.create(device, initParam);
	}

	void DsvDescriptorHeap::erase(size_t handle)
	{
		m_dsvDescriptorHeapDataArray.erase(handle);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> DsvDescriptorHeap::getCpuHeapHandleArray(size_t handle, ID3D12Device* device) const
	{
		return m_dsvDescriptorHeapDataArray.getMatchHandlePtr(handle)->getCpuHeapHandleArray(device);
	}

	const std::vector<size_t>& DsvDescriptorHeap::getDsBufferHandleArray(size_t handle) const
	{
		return m_dsvDescriptorHeapDataArray.getMatchHandlePtr(handle)->getDsBufferHandleArray();
	}

	ID3D12DescriptorHeap* DsvDescriptorHeap::getPtr(size_t handle) const
	{
		return m_dsvDescriptorHeapDataArray.getMatchHandlePtr(handle)->getPtr();
	}

	void DsvDescriptorHeap::setRootDescriptorTable(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_dsvDescriptorHeapDataArray.getMatchHandlePtr(handle)->setRootDescriptorTable(device, commandList);
	}

	void DsvDescriptorHeap::setOnlyDsv(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_dsvDescriptorHeapDataArray.getMatchHandlePtr(handle)->setOnlyDsv(device, commandList);
	}

	void DsvDescriptorHeap::clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		for (const auto& node : m_dsvDescriptorHeapDataArray)
		{
			node.clearDsv(device, commandList);
		}
	}
}