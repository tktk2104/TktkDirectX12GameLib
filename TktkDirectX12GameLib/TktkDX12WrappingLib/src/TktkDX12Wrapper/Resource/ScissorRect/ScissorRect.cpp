#include "TktkDX12Wrapper/Resource/ScissorRect/ScissorRect.h"

namespace tktk
{
	ScissorRect::ScissorRect(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_scissorRectDataArray(initParam)
	{
	}

	unsigned int ScissorRect::create(const std::vector<ScissorRectInitParam>& initParamArray)
	{
		return m_scissorRectDataArray.create(initParamArray);
	}

	void ScissorRect::set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_scissorRectDataArray.getMatchHandlePtr(handle)->set(commandList);
	}
}