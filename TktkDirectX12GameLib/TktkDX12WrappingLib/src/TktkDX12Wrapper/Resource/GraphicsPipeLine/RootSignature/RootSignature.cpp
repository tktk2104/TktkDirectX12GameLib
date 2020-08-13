#include "TktkDX12Wrapper/Resource/GraphicsPipeLine/RootSignature/RootSignature.h"

namespace tktk
{
	RootSignature::RootSignature(unsigned int rootSignatureNum)
		: m_rootSignatureDataArray(rootSignatureNum)
	{
	}

	void RootSignature::create(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		m_rootSignatureDataArray.emplaceAt(id, device, initParam);
	}

	ID3D12RootSignature* RootSignature::getPtr(unsigned int id) const
	{
		return m_rootSignatureDataArray.at(id)->getPtr();
	}

	void RootSignature::set(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_rootSignatureDataArray.at(id)->set(commandList);
	}
}