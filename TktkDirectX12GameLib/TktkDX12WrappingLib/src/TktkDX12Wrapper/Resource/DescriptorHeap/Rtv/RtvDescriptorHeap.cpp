#include "TktkDX12Wrapper/Resource/DescriptorHeap/Rtv/RtvDescriptorHeap.h"

namespace tktk
{
	RtvDescriptorHeap::RtvDescriptorHeap(unsigned int rtvDescriptorHeapNum)
		: m_rtvDescriptorHeapDataArray(rtvDescriptorHeapNum)
	{
	}

	void RtvDescriptorHeap::create(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		m_rtvDescriptorHeapDataArray.emplaceAt(id, device, initParam);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> RtvDescriptorHeap::getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const
	{
		return m_rtvDescriptorHeapDataArray.at(id)->getCpuHeapHandleArray(device);
	}

	const std::vector<unsigned int>& RtvDescriptorHeap::getRtBufferIdArray(unsigned int id) const
	{
		return m_rtvDescriptorHeapDataArray.at(id)->getRtBufferIdArray();
	}

	ID3D12DescriptorHeap* RtvDescriptorHeap::getPtr(unsigned int id) const
	{
		return m_rtvDescriptorHeapDataArray.at(id)->getPtr();
	}

	void RtvDescriptorHeap::setRootDescriptorTable(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_rtvDescriptorHeapDataArray.at(id)->setRootDescriptorTable(device, commandList);
	}

	void RtvDescriptorHeap::setRtv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount, const D3D12_CPU_DESCRIPTOR_HANDLE* useDsvHandle) const
	{
		m_rtvDescriptorHeapDataArray.at(id)->setRtv(device, commandList, startRtvLocationIndex, rtvCount, useDsvHandle);
	}

	void RtvDescriptorHeap::clearRtv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color) const
	{
		m_rtvDescriptorHeapDataArray.at(id)->clearRtv(device, commandList, rtvLocationIndex, color);
	}
}