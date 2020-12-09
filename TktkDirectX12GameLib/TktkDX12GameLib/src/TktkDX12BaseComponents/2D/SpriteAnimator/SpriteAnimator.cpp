#include "TktkDX12BaseComponents/2D/SpriteAnimator/SpriteAnimator.h"

#include <stdexcept>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawer.h"


namespace tktk
{
	SpriteAnimator::SpriteAnimator(float initFrame, bool isLoop, float animSpeedRate, float animFramePerSec, unsigned int totalAnimFrameSize)
		: m_isLoop(isLoop)
		, m_curFrame(initFrame)
		, m_animSpeedRate(animSpeedRate)
		, m_animFramePerSec(animFramePerSec)
		, m_totalAnimFrameSize(totalAnimFrameSize)
	{
	}

	void SpriteAnimator::start()
	{
		m_spriteDrawer = getComponent<SpriteDrawer>();

		if (m_spriteDrawer.expired())
		{
			throw std::runtime_error("SpriteAnimator not found SpriteDrawer");
		}
	}

	void SpriteAnimator::update()
	{
		// アニメーションフレームをカウントアップ
		m_curFrame += DX12GameManager::deltaTime() * m_animSpeedRate;

		// アニメーションフレームのリセット（ループフラグによって分岐）
		if (m_curFrame > m_animFramePerSec * m_totalAnimFrameSize)
		{
			if (m_isLoop)	m_curFrame = 0.0f;
			else			m_curFrame = m_animFramePerSec * (m_totalAnimFrameSize - 1);
		}

		m_spriteDrawer->setClippingSizeRate({ 1.0f / m_totalAnimFrameSize, 1.0f });

		m_spriteDrawer->setClippingLeftTopPosRate({ static_cast<float>(static_cast<int>(m_curFrame / m_animFramePerSec)) / m_totalAnimFrameSize, 0.0f });
	}

	void SpriteAnimator::changeAnimSpeedRate(float animSpeedRate)
	{
		m_animSpeedRate = animSpeedRate;
	}
}