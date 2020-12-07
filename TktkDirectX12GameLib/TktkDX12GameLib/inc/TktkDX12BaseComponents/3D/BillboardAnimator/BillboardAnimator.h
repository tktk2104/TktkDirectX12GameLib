#ifndef BILLBOARD_ANIMATOR_H_
#define BILLBOARD_ANIMATOR_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	/* class member */
	class BillboardDrawer;

	// ビルボードをアニメーションさせるコンポーネント
	class BillboardAnimator
		: public ComponentBase
	{
	public:

		BillboardAnimator(float initFrame, bool isLoop, float animSpeedRate, float animFramePerSec, unsigned int totalAnimFrameSize);

	public:

		void start();
		void update();

	public:

		void changeAnimSpeedRate(float animSpeedRate);

	private:

		bool	m_isLoop;
		float	m_curFrame;
		float	m_animSpeedRate;
		float	m_animFramePerSec;
		unsigned int m_totalAnimFrameSize;
		ComponentPtr<BillboardDrawer>	m_billboardDrawer;
	};
}
#endif // !BILLBOARD_ANIMATOR_H_