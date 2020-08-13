#include "TktkDX12Wrapper/Resource/Viewport/Viewport.h"

namespace tktk
{
	Viewport::Viewport(unsigned int viewportNum)
		: m_viewportDataArray(viewportNum)
	{
	}

	void Viewport::create(unsigned int id, const std::vector<ViewportInitParam>& initParamArray)
	{
		m_viewportDataArray.emplaceAt(id, initParamArray);
	}

	void Viewport::set(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_viewportDataArray.at(id)->set(commandList);
	}
}