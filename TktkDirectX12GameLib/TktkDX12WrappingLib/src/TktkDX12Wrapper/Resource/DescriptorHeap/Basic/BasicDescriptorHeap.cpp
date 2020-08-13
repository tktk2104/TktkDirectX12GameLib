#include "TktkDX12Wrapper/Resource/DescriptorHeap/Basic/BasicDescriptorHeap.h"

namespace tktk
{
	BasicDescriptorHeap::BasicDescriptorHeap(unsigned int basicDescriptorHeapNum)
		: m_basicDescriptorHeapDataArray(basicDescriptorHeapNum)
	{
	}

	void BasicDescriptorHeap::create(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		m_basicDescriptorHeapDataArray.emplaceAt(id, device, initParam);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> BasicDescriptorHeap::getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const
	{
		return m_basicDescriptorHeapDataArray.at(id)->getCpuHeapHandleArray(device);
	}

	ID3D12DescriptorHeap* BasicDescriptorHeap::getPtr(unsigned int id) const
	{
		return m_basicDescriptorHeapDataArray.at(id)->getPtr();
	}

	void BasicDescriptorHeap::setRootDescriptorTable(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_basicDescriptorHeapDataArray.at(id)->setRootDescriptorTable(device, commandList);
	}
}