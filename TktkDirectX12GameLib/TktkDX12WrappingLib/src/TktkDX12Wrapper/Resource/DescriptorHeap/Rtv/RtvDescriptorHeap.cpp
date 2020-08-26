#include "TktkDX12Wrapper/Resource/DescriptorHeap/Rtv/RtvDescriptorHeap.h"

namespace tktk
{
	RtvDescriptorHeap::RtvDescriptorHeap(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_rtvDescriptorHeapDataArray(initParam)
	{
	}

	unsigned int RtvDescriptorHeap::create(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		return m_rtvDescriptorHeapDataArray.create(device, initParam);
	}

	void RtvDescriptorHeap::erase(unsigned int handle)
	{
		m_rtvDescriptorHeapDataArray.erase(handle);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> RtvDescriptorHeap::getCpuHeapHandleArray(unsigned int handle, ID3D12Device* device) const
	{
		return m_rtvDescriptorHeapDataArray.getMatchHandlePtr(handle)->getCpuHeapHandleArray(device);
	}

	const std::vector<unsigned int>& RtvDescriptorHeap::getRtBufferIdArray(unsigned int handle) const
	{
		return m_rtvDescriptorHeapDataArray.getMatchHandlePtr(handle)->getRtBufferIdArray();
	}

	ID3D12DescriptorHeap* RtvDescriptorHeap::getPtr(unsigned int handle) const
	{
		return m_rtvDescriptorHeapDataArray.getMatchHandlePtr(handle)->getPtr();
	}

	void RtvDescriptorHeap::setRootDescriptorTable(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_rtvDescriptorHeapDataArray.getMatchHandlePtr(handle)->setRootDescriptorTable(device, commandList);
	}

	void RtvDescriptorHeap::setRtv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount, const D3D12_CPU_DESCRIPTOR_HANDLE* useDsvHandle) const
	{
		m_rtvDescriptorHeapDataArray.getMatchHandlePtr(handle)->setRtv(device, commandList, startRtvLocationIndex, rtvCount, useDsvHandle);
	}

	void RtvDescriptorHeap::clearRtv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color) const
	{
		m_rtvDescriptorHeapDataArray.getMatchHandlePtr(handle)->clearRtv(device, commandList, rtvLocationIndex, color);
	}
}