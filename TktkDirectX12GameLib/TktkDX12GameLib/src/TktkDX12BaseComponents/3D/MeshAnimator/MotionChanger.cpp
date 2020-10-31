#include "TktkDX12BaseComponents/3D/MeshAnimator/MotionChanger.h"

namespace tktk
{
	MotionChanger::MotionChanger(unsigned int changeMotionHandle, bool isLoop, float lerpTimeSec)
		: m_changeMotionHandle(changeMotionHandle)
		, m_isLoop(isLoop)
		, m_lerpTimeSec(lerpTimeSec)
	{
	}

	void MotionChanger::onEnable()
	{
		if (m_meshAnimator.expired())
		{
			m_meshAnimator = getComponent<MeshAnimator>();

			if (m_meshAnimator.expired())
			{
				throw std::runtime_error("MotionChanger not found MeshAnimator");
			}
		}

		m_meshAnimator->setNewMotionHandle(m_changeMotionHandle, m_isLoop, m_lerpTimeSec);
	}
}