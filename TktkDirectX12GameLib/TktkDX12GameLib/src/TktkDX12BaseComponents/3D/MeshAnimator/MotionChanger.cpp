#include "TktkDX12BaseComponents/3D/MeshAnimator/MotionChanger.h"

#include <stdexcept>
#include "TktkDX12BaseComponents/3D/MeshAnimator/MeshAnimator.h"

namespace tktk
{
	MotionChanger::MotionChanger(size_t changeMotionHandle, float initFrame, bool isLoop, float motionSpeedRate, float lerpTimeSec)
		: m_changeMotionHandle(changeMotionHandle)
		, m_initFrame(initFrame)
		, m_isLoop(isLoop)
		, m_motionSpeedRate(motionSpeedRate)
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

		m_meshAnimator->setNewMotionHandle(m_changeMotionHandle, m_initFrame, m_isLoop, m_motionSpeedRate, m_lerpTimeSec);
	}
}