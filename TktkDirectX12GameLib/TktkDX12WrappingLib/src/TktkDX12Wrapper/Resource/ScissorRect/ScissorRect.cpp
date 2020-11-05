#include "TktkDX12Wrapper/Resource/ScissorRect/ScissorRect.h"

namespace tktk
{
	ScissorRect::ScissorRect(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_scissorRectDataArray(initParam)
	{
	}

	size_t ScissorRect::create(const std::vector<ScissorRectInitParam>& initParamArray)
	{
		return m_scissorRectDataArray.create(initParamArray);
	}

	void ScissorRect::erase(size_t handle)
	{
		m_scissorRectDataArray.erase(handle);
	}

	void ScissorRect::set(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_scissorRectDataArray.getMatchHandlePtr(handle)->set(commandList);
	}
}