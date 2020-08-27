#include "TktkDX12BaseComponents/3D/MeshAnimator/MeshAnimator.h"

namespace tktk
{
	MeshAnimator::MeshAnimator(unsigned int initMotionHandle, bool isLoop)
		: m_isLoop(isLoop)
		, m_curMotionHandle(initMotionHandle)
		, m_preMotionHandle(initMotionHandle)
	{
	}

	void MeshAnimator::update()
	{
		m_curFrame += m_animFrameIntervalPerSec * DX12GameManager::deltaTime();

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

	void MeshAnimator::transformSkeleton(unsigned int skeletonHandle)
	{
		if (isActive())
		{
			DX12GameManager::updateMotion(
				skeletonHandle,
				m_curMotionHandle,
				m_preMotionHandle,
				static_cast<unsigned int>(m_curFrame),
				static_cast<unsigned int>(m_preFrame),
				m_lerpTimer
				);
		}
	}

	void MeshAnimator::setNewMotionHandle(unsigned int motionHandle, float lerpTimeSec)
	{
		m_preMotionHandle = m_curMotionHandle;
		m_curMotionHandle = motionHandle;

		m_preFrame = m_curFrame;
		m_curFrame = 0.0f;

		m_lerpTimer = 0.0f;
		m_increaseLerpTimePerSec = 1.0f / lerpTimeSec;
	}

	void MeshAnimator::setNewMotionId(int motionId, float lerpTimeSec)
	{
		setNewMotionHandle(DX12GameManager::getMotionHandle(motionId), lerpTimeSec);
	}
}