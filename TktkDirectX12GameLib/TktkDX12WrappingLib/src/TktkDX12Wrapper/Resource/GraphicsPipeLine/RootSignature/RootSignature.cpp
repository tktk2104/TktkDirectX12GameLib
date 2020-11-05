#include "TktkDX12Wrapper/Resource/GraphicsPipeLine/RootSignature/RootSignature.h"

namespace tktk
{
	RootSignature::RootSignature(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_rootSignatureDataArray(initParam)
	{
	}

	size_t RootSignature::create(ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		return m_rootSignatureDataArray.create(device, initParam);
	}

	void RootSignature::erase(size_t handle)
	{
		m_rootSignatureDataArray.erase(handle);
	}

	ID3D12RootSignature* RootSignature::getPtr(size_t handle) const
	{
		return m_rootSignatureDataArray.getMatchHandlePtr(handle)->getPtr();
	}

	void RootSignature::set(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_rootSignatureDataArray.getMatchHandlePtr(handle)->set(commandList);
	}
}