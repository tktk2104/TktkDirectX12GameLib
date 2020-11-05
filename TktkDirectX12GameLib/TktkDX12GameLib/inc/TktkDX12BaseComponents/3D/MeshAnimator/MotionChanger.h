#ifndef MOTION_CHANGER_H_
#define MOTION_CHANGER_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "MeshAnimator.h"

namespace tktk
{
	// 自身がアクティブ状態になった時にメッシュのアニメーションを変更するコンポーネント
	// 【必須コンポーネント：MeshAnimator】
	class MotionChanger
		: public ComponentBase
	{
	public:

		MotionChanger(size_t changeMotionHandle, bool isLoop, float lerpTimeSec);

	public:

		void onEnable();

	private:

		size_t						m_changeMotionHandle;
		bool						m_isLoop;
		float						m_lerpTimeSec;
		ComponentPtr<MeshAnimator>	m_meshAnimator;
	};
}
#endif // !MOTION_CHANGER_H_
