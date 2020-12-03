#include "TktkDX12Game/UtilityProcessManager/TimeManager/ElapsedTimer.h"

#include <cmath>

namespace tktk
{
	ElapsedTimer::ElapsedTimer()
	{
		reset();
	}

	// デストラクタを非インライン化する
	ElapsedTimer::~ElapsedTimer() = default;

	void ElapsedTimer::reset()
	{
		m_preTime = std::clock();
		m_totalTime = 0.0f;
	}

	void ElapsedTimer::update()
	{
		auto curTime = std::clock();
		long timeDist = (curTime - m_preTime);
		m_deltaTime = (static_cast<float>(timeDist) / 1000.0f);
		m_totalTime += deltaTime();
		m_preTime = curTime;
	}

	float ElapsedTimer::deltaTime() const
	{
		return std::fmin(m_deltaTime, m_maximumDeltaTime) * m_timeScaleRate;
	}

	float ElapsedTimer::noScaleDeltaTime() const
	{
		return std::fmin(m_deltaTime, m_maximumDeltaTime);
	}

	float ElapsedTimer::getCurTimeSec() const
	{
		return m_totalTime;
	}

	void ElapsedTimer::setMaximumDeltaTime(float maximumDeltaTime)
	{
		m_maximumDeltaTime = std::abs(maximumDeltaTime);
	}

	float ElapsedTimer::getTimeScale() const
	{
		return m_timeScaleRate;
	}

	void ElapsedTimer::setTimeScale(float timeScaleRate)
	{
		m_timeScaleRate = std::fmax(0.0f, timeScaleRate);
	}

	float ElapsedTimer::fps() const
	{
		return 1.0f / deltaTime();
	}

	void ElapsedTimer::setBaseFps(unsigned int baseFps)
	{
		m_baseFps = baseFps;
	}

	unsigned int ElapsedTimer::getBaseFps() const
	{
		return m_baseFps;
	}
}