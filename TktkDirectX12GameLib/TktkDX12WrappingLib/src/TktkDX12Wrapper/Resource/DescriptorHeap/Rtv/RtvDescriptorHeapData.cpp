#include "TktkDX12Wrapper/Resource/DescriptorHeap/Rtv/RtvDescriptorHeapData.h"

namespace tktk
{
	RtvDescriptorHeapData::RtvDescriptorHeapData(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
		descHeapDesc.Flags		= (initParam.shaderVisible) ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		descHeapDesc.NodeMask	= 0;
		descHeapDesc.Type		= D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

#ifdef _M_AMD64 /* x64ƒrƒ‹ƒh‚È‚ç */
		descHeapDesc.NumDescriptors = static_cast<unsigned int>(initParam.descriptorParamArray.size());
#else
		descHeapDesc.NumDescriptors = initParam.descriptorParamArray.size();
#endif // WIN64

		device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&m_descriptorHeap));

		m_rtBufferHandleArray.reserve(descHeapDesc.NumDescriptors);

		for (const auto& node : initParam.descriptorParamArray)
		{
			m_rtBufferHandleArray.push_back(node.handle);
		}
	}

	RtvDescriptorHeapData::~RtvDescriptorHeapData()
	{
		if (m_descriptorHeap != nullptr)
		{
			m_descriptorHeap->Release();
		}
	}

	RtvDescriptorHeapData::RtvDescriptorHeapData(RtvDescriptorHeapData&& other) noexcept
		: m_rtBufferHandleArray(std::move(other.m_rtBufferHandleArray))
		, m_descriptorHeap(other.m_descriptorHeap)
	{
		other.m_descriptorHeap = nullptr;
		other.m_rtBufferHandleArray.clear();
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> RtvDescriptorHeapData::getCpuHeapHandleArray(ID3D12Device* device) const
	{
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> handleArray;
		handleArray.reserve(m_descriptorHeap->GetDesc().NumDescriptors);

		auto cpuHandle = m_descriptorHeap->GetCPUDescriptorHandleForHeapStart();
		for (unsigned int i = 0; i < m_descriptorHeap->GetDesc().NumDescriptors; i++)
		{
			handleArray.push_back(cpuHandle);
			cpuHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}
		return handleArray;
	}

	const std::vector<size_t>& RtvDescriptorHeapData::getRtBufferHandleArray() const
	{
		return m_rtBufferHandleArray;
	}

	ID3D12DescriptorHeap* RtvDescriptorHeapData::getPtr() const
	{
		return m_descriptorHeap;
	}

	void RtvDescriptorHeapData::setRootDescriptorTable(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		auto gpuHandle = m_descriptorHeap->GetGPUDescriptorHandleForHeapStart();
		for (unsigned int i = 0; i < m_descriptorHeap->GetDesc().NumDescriptors; i++)
		{
			commandList->SetGraphicsRootDescriptorTable(i, gpuHandle);
			gpuHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}
	}

	void RtvDescriptorHeapData::setRtv(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, unsigned int rtvCount, const D3D12_CPU_DESCRIPTOR_HANDLE* useDsvHandle) const
	{
		auto cpuHeapHandleArray = getCpuHeapHandleArray(device);
		commandList->OMSetRenderTargets(rtvCount, &cpuHeapHandleArray.at(startRtvLocationIndex), true, useDsvHandle);
	}
}