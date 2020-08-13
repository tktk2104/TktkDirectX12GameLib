#include "TktkDX12Wrapper/Resource/DescriptorHeap/DescriptorHeap.h"

namespace tktk
{
	DescriptorHeap::DescriptorHeap(const DescriptorHeapInitParam& initParam)
		: m_basicDescriptorHeap(initParam.basicDescriptorHeapNum)
		, m_rtvDescriptorHeap(initParam.rtvDescriptorHeapNum)
		, m_dsvDescriptorHeap(initParam.dsvDescriptorHeapNum)
	{
	}

	void DescriptorHeap::set(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray) const
	{
		std::vector<ID3D12DescriptorHeap*> descriptorHeapArray{};
		descriptorHeapArray.reserve(heapParamArray.size());
	
		for (const auto& heapParam : heapParamArray)
		{
			switch (heapParam.m_type)
			{
			case DescriptorHeapType::basic:
	
				descriptorHeapArray.push_back(m_basicDescriptorHeap.getPtr(heapParam.m_id));
				break;
	
			case DescriptorHeapType::rtv:
	
				descriptorHeapArray.push_back(m_rtvDescriptorHeap.getPtr(heapParam.m_id));
				break;

			case DescriptorHeapType::dsv:

				descriptorHeapArray.push_back(m_dsvDescriptorHeap.getPtr(heapParam.m_id));
				break;
			}
		}
	
		commandList->SetDescriptorHeaps(descriptorHeapArray.size(), descriptorHeapArray.data());
	
		for (const auto& heapParam : heapParamArray)
		{
			switch (heapParam.m_type)
			{
			case DescriptorHeapType::basic:
	
				m_basicDescriptorHeap.setRootDescriptorTable(heapParam.m_id, device, commandList);
				break;
	
			case DescriptorHeapType::rtv:
	
				m_rtvDescriptorHeap.setRootDescriptorTable(heapParam.m_id, device, commandList);
				break;

			case DescriptorHeapType::dsv:

				m_dsvDescriptorHeap.setRootDescriptorTable(heapParam.m_id, device, commandList);
				break;
			}
		}
	}

	void DescriptorHeap::setRtv(unsigned int rtvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		m_rtvDescriptorHeap.setRtv(rtvDescriptorHeapId, device, commandList, startRtvLocationIndex, rtvCount, nullptr);
	}

	void DescriptorHeap::setRtvAndDsv(unsigned int renderTargetId, unsigned int depthStencilViewId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocation, unsigned int rtvCount) const
	{
		auto cpuHeapHandleArray = m_dsvDescriptorHeap.getCpuHeapHandleArray(depthStencilViewId, device);
		m_rtvDescriptorHeap.setRtv(renderTargetId, device, commandList, startRtvLocation, rtvCount, cpuHeapHandleArray.data());
	}

	void DescriptorHeap::setOnlyDsv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_dsvDescriptorHeap.setOnlyDsv(id, device, commandList);
	}

	void DescriptorHeap::clearRtv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color) const
	{
		m_rtvDescriptorHeap.clearRtv(id, device, commandList, rtvLocationIndex, color);
	}

	void DescriptorHeap::clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_dsvDescriptorHeap.clearDsvAll(device, commandList);
	}

	void DescriptorHeap::createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		m_basicDescriptorHeap.create(id, device, initParam);
	}

	void DescriptorHeap::createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		m_rtvDescriptorHeap.create(id, device, initParam);
	}

	void DescriptorHeap::createDsvDescriptorHeap(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam)
	{
		m_dsvDescriptorHeap.create(id, device, initParam);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> DescriptorHeap::getCpuBasicHeapHandleArray(unsigned int id, ID3D12Device* device) const
	{
		return m_basicDescriptorHeap.getCpuHeapHandleArray(id, device);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> DescriptorHeap::getCpuRtvHeapHandleArray(unsigned int id, ID3D12Device* device) const
	{
		return m_rtvDescriptorHeap.getCpuHeapHandleArray(id, device);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> DescriptorHeap::getCpuDsvHeapHandleArray(unsigned int id, ID3D12Device* device) const
	{
		return m_dsvDescriptorHeap.getCpuHeapHandleArray(id, device);
	}

	const std::vector<unsigned int>& DescriptorHeap::getRtvDescriptorHeapUseBufferIdArray(unsigned int id) const
	{
		return m_rtvDescriptorHeap.getRtBufferIdArray(id);
	}

	const std::vector<unsigned int>& DescriptorHeap::getDsvDescriptorHeapUseBufferIdArray(unsigned int id) const
	{
		return m_dsvDescriptorHeap.getDsBufferIdArray(id);
	}
}