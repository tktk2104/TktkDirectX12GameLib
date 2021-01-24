#ifndef SPRITE_ANIMATOR_H_
#define SPRITE_ANIMATOR_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	/* class member */
	class SpriteDrawer;

	// スプライトをアニメーションさせるコンポーネント
	class SpriteAnimator
		: public ComponentBase
	{
	public:

		SpriteAnimator(const ComponentPtr<SpriteDrawer>& targetDrawer, float initFrame, bool isLoop, float animSpeedRate, float animFramePerSec, unsigned int totalAnimFrameSize);

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
		ComponentPtr<SpriteDrawer>	m_spriteDrawer;
	};
}
#endif // !SPRITE_ANIMATOR_H_