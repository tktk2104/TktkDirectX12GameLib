#include "TktkDX12Wrapper/Resource/DescriptorHeap/DescriptorHeap.h"

#include "TktkDX12Wrapper/Resource/DescriptorHeap/Basic/BasicDescriptorHeap.h"
#include "TktkDX12Wrapper/Resource/DescriptorHeap/Rtv/RtvDescriptorHeap.h"
#include "TktkDX12Wrapper/Resource/DescriptorHeap/Dsv/DsvDescriptorHeap.h"

namespace tktk
{
	DescriptorHeap::DescriptorHeap(const DescriptorHeapNum& initParam)
	{
		m_basicDescriptorHeap	= std::make_unique<BasicDescriptorHeap>(initParam.basicDescriptorHeapContainerInitParam);
		m_rtvDescriptorHeap		= std::make_unique<RtvDescriptorHeap>(initParam.rtvDescriptorHeapContainerInitParam);
		m_dsvDescriptorHeap		= std::make_unique<DsvDescriptorHeap>(initParam.dsvDescriptorHeapContainerInitParam);
	}

	// デストラクタを非インライン化する
	DescriptorHeap::~DescriptorHeap() = default;

	void DescriptorHeap::set(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray) const
	{
		std::vector<ID3D12DescriptorHeap*> descriptorHeapArray{};
		descriptorHeapArray.reserve(heapParamArray.size());
	
		for (const auto& heapParam : heapParamArray)
		{
			switch (heapParam.m_type)
			{
			case DescriptorHeapType::basic:
	
				descriptorHeapArray.push_back(m_basicDescriptorHeap->getPtr(heapParam.m_id));
				break;
	
			case DescriptorHeapType::rtv:
	
				descriptorHeapArray.push_back(m_rtvDescriptorHeap->getPtr(heapParam.m_id));
				break;

			case DescriptorHeapType::dsv:

				descriptorHeapArray.push_back(m_dsvDescriptorHeap->getPtr(heapParam.m_id));
				break;
			}
		}
	
		commandList->SetDescriptorHeaps(descriptorHeapArray.size(), descriptorHeapArray.data());
	
		for (const auto& heapParam : heapParamArray)
		{
			switch (heapParam.m_type)
			{
			case DescriptorHeapType::basic:
	
				m_basicDescriptorHeap->setRootDescriptorTable(heapParam.m_id, device, commandList);
				break;
	
			case DescriptorHeapType::rtv:
	
				m_rtvDescriptorHeap->setRootDescriptorTable(heapParam.m_id, device, commandList);
				break;

			case DescriptorHeapType::dsv:

				m_dsvDescriptorHeap->setRootDescriptorTable(heapParam.m_id, device, commandList);
				break;
			}
		}
	}

	void DescriptorHeap::setRtv(unsigned int rtvHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		m_rtvDescriptorHeap->setRtv(rtvHandle, device, commandList, startRtvLocationIndex, rtvCount, nullptr);
	}

	void DescriptorHeap::setRtvAndDsv(unsigned int rtvHandle, unsigned int dsvHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocation, unsigned int rtvCount) const
	{
		auto cpuHeapHandleArray = m_dsvDescriptorHeap->getCpuHeapHandleArray(dsvHandle, device);
		m_rtvDescriptorHeap->setRtv(rtvHandle, device, commandList, startRtvLocation, rtvCount, cpuHeapHandleArray.data());
	}

	void DescriptorHeap::setOnlyDsv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_dsvDescriptorHeap->setOnlyDsv(handle, device, commandList);
	}

	void DescriptorHeap::clearRtv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color) const
	{
		m_rtvDescriptorHeap->clearRtv(handle, device, commandList, rtvLocationIndex, color);
	}

	void DescriptorHeap::clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_dsvDescriptorHeap->clearDsvAll(device, commandList);
	}

	unsigned int DescriptorHeap::createBasicDescriptorHeap(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		return m_basicDescriptorHeap->create(device, initParam);
	}

	unsigned int DescriptorHeap::createRtvDescriptorHeap(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		return m_rtvDescriptorHeap->create(device, initParam);
	}

	unsigned int DescriptorHeap::createDsvDescriptorHeap(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam)
	{
		return m_dsvDescriptorHeap->create(device, initParam);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> DescriptorHeap::getCpuBasicHeapHandleArray(unsigned int handle, ID3D12Device* device) const
	{
		return m_basicDescriptorHeap->getCpuHeapHandleArray(handle, device);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> DescriptorHeap::getCpuRtvHeapHandleArray(unsigned int handle, ID3D12Device* device) const
	{
		return m_rtvDescriptorHeap->getCpuHeapHandleArray(handle, device);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> DescriptorHeap::getCpuDsvHeapHandleArray(unsigned int handle, ID3D12Device* device) const
	{
		return m_dsvDescriptorHeap->getCpuHeapHandleArray(handle, device);
	}

	const std::vector<unsigned int>& DescriptorHeap::getRtvDescriptorHeapUseBufferIdArray(unsigned int handle) const
	{
		return m_rtvDescriptorHeap->getRtBufferIdArray(handle);
	}

	const std::vector<unsigned int>& DescriptorHeap::getDsvDescriptorHeapUseBufferIdArray(unsigned int handle) const
	{
		return m_dsvDescriptorHeap->getDsBufferIdArray(handle);
	}
}