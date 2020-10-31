#ifndef STATE_CHANGE_TIMER_H_
#define STATE_CHANGE_TIMER_H_

#include <vector>
#include "../../ComponentBase.h"

namespace tktk
{
	// �A�N�e�B�u��ԂɂȂ��Ă���w��b��Ɏ��g�̃X�e�[�g��ύX����R���|�[�l���g
	class StateChangeTimer
		: public ComponentBase
	{
	public:

		StateChangeTimer(float stateChangeTimeSec, const std::vector<int>& enableStateArray, const std::vector<int>& disableStateArray);

	public:

		void onEnable();

		void update();

	private:

		float				m_stateChangeTimer	{ 0.0f };
		bool				m_afterChange		{ false };
		float				m_stateChangeTimeSec;
		std::vector<int>	m_enableStateArray;
		std::vector<int>	m_disableStateArray;
	};
}
#endif // !STATE_CHANGE_TIMER_H_