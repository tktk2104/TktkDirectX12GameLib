#include "TktkDX12BaseComponents/3D/MeshAnimator/MeshAnimator.h"

namespace tktk
{
	MeshAnimator::MeshAnimator(unsigned int initMotionId, bool isLoop)
		: m_isLoop(isLoop)
		, m_curMotionId(initMotionId)
		, m_preMotionId(initMotionId)
	{
	}

	void MeshAnimator::update()
	{
		m_curFrame += m_animFrameIntervalPerSec * DX12GameManager::deltaTime();

		if (m_curFrame > static_cast<float>(DX12GameManager::getMotionEndFrameNo(m_curMotionId)))
		{
			if (m_isLoop) m_curFrame = 0.0f;
			else m_curFrame = static_cast<float>(DX12GameManager::getMotionEndFrameNo(m_curMotionId));
		}
		else if (m_curFrame < 0.0f)
		{
			if (m_isLoop) m_curFrame = static_cast<float>(DX12GameManager::getMotionEndFrameNo(m_curMotionId));
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

	void MeshAnimator::transformSkeleton(unsigned int skeletonId)
	{
		if (isActive())
		{
			DX12GameManager::updateMotion(
				skeletonId,
				m_curMotionId,
				m_preMotionId,
				static_cast<unsigned int>(m_curFrame),
				static_cast<unsigned int>(m_preFrame),
				m_lerpTimer
				);
		}
	}

	void MeshAnimator::changeMotion(unsigned int motionId, float lerpTimeSec)
	{
		m_preMotionId = m_curMotionId;
		m_curMotionId = motionId;

		m_preFrame = m_curFrame;
		m_curFrame = 0.0f;

		m_lerpTimer = 0.0f;
		m_increaseLerpTimePerSec = 1.0f / lerpTimeSec;
	}
}