#include "TktkDX12BaseComponents/3D/BillboardAnimator/BillboardAnimator.h"

#include <stdexcept>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawer.h"

namespace tktk
{
	BillboardAnimator::BillboardAnimator(float initFrame, bool isLoop, float animSpeedRate, float animFramePerSec, unsigned int totalAnimFrameSize)
		: m_isLoop(isLoop)
		, m_curFrame(initFrame)
		, m_animSpeedRate(animSpeedRate)
		, m_animFramePerSec(animFramePerSec)
		, m_totalAnimFrameSize(totalAnimFrameSize)
	{
	}

	void BillboardAnimator::start()
	{
		m_billboardDrawer = getComponent<BillboardDrawer>();

		if (m_billboardDrawer.expired())
		{
			throw std::runtime_error("BillboardAnimator not found BillboardDrawer");
		}
	}

	void BillboardAnimator::update()
	{
		// アニメーションフレームをカウントアップ
		m_curFrame += DX12GameManager::deltaTime() * m_animSpeedRate;

		// アニメーションフレームのリセット（ループフラグによって分岐）
		if (m_curFrame > m_animFramePerSec * m_totalAnimFrameSize)
		{
			if (m_isLoop)	m_curFrame = 0.0f;
			else			m_curFrame = m_animFramePerSec * (m_totalAnimFrameSize - 1);
		}

		m_billboardDrawer->setClippingSizeRate({ 1.0f / m_totalAnimFrameSize, 1.0f });

		m_billboardDrawer->setClippingLeftTopPosRate({ static_cast<float>(static_cast<int>(m_curFrame / m_animFramePerSec)) / m_totalAnimFrameSize, 0.0f });
	}

	void BillboardAnimator::changeAnimSpeedRate(float animSpeedRate)
	{
		m_animSpeedRate = animSpeedRate;
	}
}