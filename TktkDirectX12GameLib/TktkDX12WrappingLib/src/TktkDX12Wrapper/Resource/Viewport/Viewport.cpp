#include "TktkDX12Wrapper/Resource/Viewport/Viewport.h"

namespace tktk
{
	Viewport::Viewport(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_viewportDataArray(initParam)
	{
	}

	unsigned int Viewport::create(const std::vector<ViewportInitParam>& initParamArray)
	{
		return m_viewportDataArray.create(initParamArray);
	}

	void Viewport::set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_viewportDataArray.getMatchHandlePtr(handle)->set(commandList);
	}
}