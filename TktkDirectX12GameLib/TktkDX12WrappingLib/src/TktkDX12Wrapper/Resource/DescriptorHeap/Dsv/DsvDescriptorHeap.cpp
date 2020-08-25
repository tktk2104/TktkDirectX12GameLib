#include "TktkDX12Wrapper/Resource/DescriptorHeap/Dsv/DsvDescriptorHeap.h"

namespace tktk
{
	DsvDescriptorHeap::DsvDescriptorHeap(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_dsvDescriptorHeapDataArray(initParam)
	{
	}

	unsigned int DsvDescriptorHeap::create(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam)
	{
		return m_dsvDescriptorHeapDataArray.create(device, initParam);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> DsvDescriptorHeap::getCpuHeapHandleArray(unsigned int handle, ID3D12Device* device) const
	{
		return m_dsvDescriptorHeapDataArray.getMatchHandlePtr(handle)->getCpuHeapHandleArray(device);
	}

	const std::vector<unsigned int>& DsvDescriptorHeap::getDsBufferIdArray(unsigned int handle) const
	{
		return m_dsvDescriptorHeapDataArray.getMatchHandlePtr(handle)->getDsBufferIdArray();
	}

	ID3D12DescriptorHeap* DsvDescriptorHeap::getPtr(unsigned int handle) const
	{
		return m_dsvDescriptorHeapDataArray.getMatchHandlePtr(handle)->getPtr();
	}

	void DsvDescriptorHeap::setRootDescriptorTable(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_dsvDescriptorHeapDataArray.getMatchHandlePtr(handle)->setRootDescriptorTable(device, commandList);
	}

	void DsvDescriptorHeap::setOnlyDsv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
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