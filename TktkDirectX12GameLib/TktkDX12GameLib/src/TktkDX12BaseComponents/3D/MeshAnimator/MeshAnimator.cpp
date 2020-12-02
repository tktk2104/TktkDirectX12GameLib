#include "TktkDX12BaseComponents/3D/MeshAnimator/MeshAnimator.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	MeshAnimator::MeshAnimator(size_t initMotionHandle, float initFrame, bool isLoop, float motionSpeedRate, float animFramePerSec)
		: m_isLoop(isLoop)
		, m_motionSpeedRate(motionSpeedRate)
		, m_curMotionHandle(initMotionHandle)
		, m_preMotionHandle(initMotionHandle)
		, m_curFrame(initFrame)
		, m_preFrame(initFrame)
		, m_animFramePerSec(animFramePerSec)
	{
	}

	void MeshAnimator::update()
	{
		m_curFrame += m_animFramePerSec * DX12GameManager::deltaTime() * m_motionSpeedRate;

		if (m_curFrame > static_cast<float>(DX12GameManager::getMotionEndFrameNo(m_curMotionHandle)))
		{
			if (m_isLoop) m_curFrame = 0.0f;
			else m_curFrame = static_cast<float>(DX12GameManager::getMotionEndFrameNo(m_curMotionHandle));
		}
		else if (m_curFrame < 0.0f)
		{
			if (m_isLoop) m_curFrame = static_cast<float>(DX12GameManager::getMotionEndFrameNo(m_curMotionHandle));
			else m_curFrame = 0.0f;
		}

		if (m_lerpTimer < 1.0f)
		{
			m_lerpTimer += m_increaseLerpTimePerSec * DX12GameManager::deltaTime();
		}
		else
		{
			m_lerpTimer = 1.0f;
		}
	}

	void MeshAnimator::setNewMotionId(ResourceIdCarrier motionId, float initFrame, bool isLoop, float motionSpeedRate, float lerpTimeSec)
	{
		setNewMotionHandle(DX12GameManager::getMotionHandle(motionId), initFrame, isLoop, motionSpeedRate, lerpTimeSec);
	}

	void MeshAnimator::transformSkeleton(size_t skeletonHandle)
	{
		if (isActive())
		{
			DX12GameManager::updateMotion(
				skeletonHandle,
				m_curMotionHandle,
				m_preMotionHandle,
				m_curFrame,
				m_preFrame,
				m_lerpTimer
				);
		}
	}

	void MeshAnimator::setNewMotionHandle(size_t motionHandle, float initFrame, bool isLoop, float motionSpeedRate, float lerpTimeSec)
	{
		m_isLoop = isLoop;

		m_motionSpeedRate = motionSpeedRate;

		m_preMotionHandle = m_curMotionHandle;
		m_curMotionHandle = motionHandle;

		m_preFrame = m_curFrame;
		m_curFrame = initFrame;

		m_lerpTimer = 0.0f;
		m_increaseLerpTimePerSec = 1.0f / lerpTimeSec;
	}
}