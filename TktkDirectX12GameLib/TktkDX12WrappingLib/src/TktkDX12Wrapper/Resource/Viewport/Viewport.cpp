#include "TktkDX12Wrapper/Resource/Viewport/Viewport.h"

namespace tktk
{
	Viewport::Viewport(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_viewportDataArray(initParam)
	{
	}

	size_t Viewport::create(const std::vector<ViewportInitParam>& initParamArray)
	{
		return m_viewportDataArray.create(initParamArray);
	}

	void Viewport::erase(size_t handle)
	{
		m_viewportDataArray.erase(handle);
	}

	void Viewport::set(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_viewportDataArray.getMatchHandlePtr(handle)->set(commandList);
	}
}