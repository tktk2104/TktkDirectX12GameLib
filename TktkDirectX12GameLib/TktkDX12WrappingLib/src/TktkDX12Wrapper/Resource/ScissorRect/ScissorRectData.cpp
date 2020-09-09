#include "TktkDX12Wrapper/Resource/ScissorRect/ScissorRectData.h"

namespace tktk
{
	ScissorRectData::ScissorRectData(const std::vector<ScissorRectInitParam>& initParamArray)
	{
		m_scissorRectArray.resize(initParamArray.size());

		for (unsigned int i = 0; i < initParamArray.size(); i++)
		{
			m_scissorRectArray.at(i).top = static_cast<long>(initParamArray.at(i).m_topLeft.y);
			m_scissorRectArray.at(i).left = static_cast<long>(initParamArray.at(i).m_topLeft.x);
			m_scissorRectArray.at(i).right = static_cast<long>(initParamArray.at(i).m_botRight.x);
			m_scissorRectArray.at(i).bottom = static_cast<long>(initParamArray.at(i).m_botRight.y);
		}
	}

	ScissorRectData::ScissorRectData(ScissorRectData&& other) noexcept
		: m_scissorRectArray(std::move(other.m_scissorRectArray))
	{
		other.m_scissorRectArray.clear();
	}

	void ScissorRectData::set(ID3D12GraphicsCommandList* commandList) const
	{
#ifdef _M_AMD64 /* x64ƒrƒ‹ƒh‚È‚ç */
		commandList->RSSetScissorRects(static_cast<unsigned int>(m_scissorRectArray.size()), m_scissorRectArray.data());
#else
		commandList->RSSetScissorRects(m_scissorRectArray.size(), m_scissorRectArray.data());
#endif // _M_AMD64
	}
}