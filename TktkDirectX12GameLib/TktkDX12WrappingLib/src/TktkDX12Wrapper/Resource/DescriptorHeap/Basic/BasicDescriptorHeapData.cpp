#include "TktkDX12Wrapper/Resource/DescriptorHeap/Basic/BasicDescriptorHeapData.h"

namespace tktk
{
	BasicDescriptorHeapData::BasicDescriptorHeapData(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		// ディスクリプタテーブルの数分のメモリを確保する
		m_descriptorTableSizeArray.reserve(initParam.descriptorTableParamArray.size());

		// ディスクリプタヒープを作る
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
		descHeapDesc.Flags = (initParam.shaderVisible) ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		descHeapDesc.NodeMask = 0U;
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		descHeapDesc.NumDescriptors = 0U; /* 値の初期化のみ */

		// ディスクリプタテーブルの数だけループする
		for (const auto& node : initParam.descriptorTableParamArray)
		{
			// ディスクリプタの数をディスクリプタテーブルが管理している数分加算する
			descHeapDesc.NumDescriptors += node.descriptorParamArray.size();

			// ディスクリプタテーブル毎のディスクリプタの数を記録する
			m_descriptorTableSizeArray.push_back(node.descriptorParamArray.size());
		}
		device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&m_descriptorHeap));
	}

	BasicDescriptorHeapData::~BasicDescriptorHeapData()
	{
		if (m_descriptorHeap != nullptr)
		{
			m_descriptorHeap->Release();
		}
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> BasicDescriptorHeapData::getCpuHeapHandleArray(ID3D12Device* device) const
	{
		// ディスクリプタヒープ上に存在するディスクリプタの数分のメモリを確保する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> handleArray;
		unsigned int descriptorNum = m_descriptorHeap->GetDesc().NumDescriptors;
		handleArray.reserve(descriptorNum);

		// 自身の先頭のアドレスを取得
		auto cpuHandle = m_descriptorHeap->GetCPUDescriptorHandleForHeapStart();

		for (unsigned int i = 0; i < descriptorNum; i++)
		{
			handleArray.push_back(cpuHandle);
			cpuHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		}
		return handleArray;
	}

	ID3D12DescriptorHeap* BasicDescriptorHeapData::getPtr() const
	{
		return m_descriptorHeap;
	}

	void BasicDescriptorHeapData::setRootDescriptorTable(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		auto gpuHandle = m_descriptorHeap->GetGPUDescriptorHandleForHeapStart();
		
		for (unsigned int i = 0; i < m_descriptorTableSizeArray.size(); i++)
		{
			commandList->SetGraphicsRootDescriptorTable(i, gpuHandle);
			gpuHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * static_cast<unsigned long long>(m_descriptorTableSizeArray.at(i));
		}
	}
}