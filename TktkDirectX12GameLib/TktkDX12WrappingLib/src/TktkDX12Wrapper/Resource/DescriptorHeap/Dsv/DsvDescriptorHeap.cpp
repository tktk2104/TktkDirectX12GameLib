#include "TktkDX12Wrapper/Resource/DescriptorHeap/Dsv/DsvDescriptorHeap.h"

namespace tktk
{
	DsvDescriptorHeap::DsvDescriptorHeap(unsigned int dsvDescriptorHeapNum)
		: m_dsvDescriptorHeapDataArray(dsvDescriptorHeapNum)
	{
	}

	void DsvDescriptorHeap::create(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam)
	{
		m_dsvDescriptorHeapDataArray.emplaceAt(id, device,initParam);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> DsvDescriptorHeap::getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const
	{
		return m_dsvDescriptorHeapDataArray.at(id)->getCpuHeapHandleArray(device);
	}

	const std::vector<unsigned int>& DsvDescriptorHeap::getDsBufferIdArray(unsigned int id) const
	{
		return m_dsvDescriptorHeapDataArray.at(id)->getDsBufferIdArray();
	}

	ID3D12DescriptorHeap* DsvDescriptorHeap::getPtr(unsigned int id) const
	{
		return m_dsvDescriptorHeapDataArray.at(id)->getPtr();
	}

	void DsvDescriptorHeap::setRootDescriptorTable(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_dsvDescriptorHeapDataArray.at(id)->setRootDescriptorTable(device, commandList);
	}

	void DsvDescriptorHeap::setOnlyDsv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_dsvDescriptorHeapDataArray.at(id)->setOnlyDsv(device, commandList);
	}

	void DsvDescriptorHeap::clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		for (const auto& node : m_dsvDescriptorHeapDataArray)
		{
			node.clearDsv(device, commandList);
		}
	}
}