#include "TktkDX12Wrapper/Resource/ScissorRect/ScissorRect.h"

namespace tktk
{
	ScissorRect::ScissorRect(unsigned int scissorRectNum)
		: m_scissorRectDataArray(scissorRectNum)
	{
	}

	void ScissorRect::create(unsigned int id, const std::vector<ScissorRectInitParam>& initParamArray)
	{
		m_scissorRectDataArray.emplaceAt(id, initParamArray);
	}

	void ScissorRect::set(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_scissorRectDataArray.at(id)->set(commandList);
	}
}