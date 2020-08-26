#include "TktkDX12Wrapper/Resource/DescriptorHeap/Basic/BasicDescriptorHeap.h"

namespace tktk
{
	BasicDescriptorHeap::BasicDescriptorHeap(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_basicDescriptorHeapDataArray(initParam)
	{
	}

	unsigned int BasicDescriptorHeap::create(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		return m_basicDescriptorHeapDataArray.create(device, initParam);
	}

	void BasicDescriptorHeap::erase(unsigned int handle)
	{
		m_basicDescriptorHeapDataArray.erase(handle);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> BasicDescriptorHeap::getCpuHeapHandleArray(unsigned int handle, ID3D12Device* device) const
	{
		return m_basicDescriptorHeapDataArray.getMatchHandlePtr(handle)->getCpuHeapHandleArray(device);
	}

	ID3D12DescriptorHeap* BasicDescriptorHeap::getPtr(unsigned int handle) const
	{
		return m_basicDescriptorHeapDataArray.getMatchHandlePtr(handle)->getPtr();
	}

	void BasicDescriptorHeap::setRootDescriptorTable(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_basicDescriptorHeapDataArray.getMatchHandlePtr(handle)->setRootDescriptorTable(device, commandList);
	}
}