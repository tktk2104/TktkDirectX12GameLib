#ifndef STATE_CHANGE_TIMER_H_
#define STATE_CHANGE_TIMER_H_

#include <vector>
#include "../../ComponentBase.h"
#include "StateTypeList.h"

namespace tktk
{
	// アクティブ状態になってから指定秒後に自身のステートを変更するコンポーネント
	class StateChangeTimer
		: public ComponentBase
	{
	public:

		StateChangeTimer(float stateChangeTimeSec, const StateTypeList& enableStateArray, const StateTypeList& disableStateArray);

	public:

		void onEnable();

		void update();

	private:

		float		m_stateChangeTimer	{ 0.0f };
		bool		m_afterChange		{ false };
		float		m_stateChangeTimeSec;
		StateTypeList	m_enableStateArray;
		StateTypeList	m_disableStateArray;
	};
}
#endif // !STATE_CHANGE_TIMER_H_