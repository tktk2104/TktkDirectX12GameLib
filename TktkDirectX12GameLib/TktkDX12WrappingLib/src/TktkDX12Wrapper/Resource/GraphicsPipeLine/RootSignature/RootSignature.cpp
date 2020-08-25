#include "TktkDX12Wrapper/Resource/GraphicsPipeLine/RootSignature/RootSignature.h"

namespace tktk
{
	RootSignature::RootSignature(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_rootSignatureDataArray(initParam)
	{
	}

	unsigned int RootSignature::create(ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		return m_rootSignatureDataArray.create(device, initParam);
	}

	ID3D12RootSignature* RootSignature::getPtr(unsigned int handle) const
	{
		return m_rootSignatureDataArray.getMatchHandlePtr(handle)->getPtr();
	}

	void RootSignature::set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_rootSignatureDataArray.getMatchHandlePtr(handle)->set(commandList);
	}
}