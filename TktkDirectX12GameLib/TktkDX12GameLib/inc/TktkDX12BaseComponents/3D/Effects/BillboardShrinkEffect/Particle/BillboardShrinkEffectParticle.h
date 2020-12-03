#ifndef BILLBOARD_SHRINK_EFFECT_PARTICLE_H_
#define BILLBOARD_SHRINK_EFFECT_PARTICLE_H_

/* base class */
#include "../../../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	class Transform3D;

	class BillboardShrinkEffectParticle
		: public ComponentBase
	{
	public:

		BillboardShrinkEffectParticle(float	moveSpeed, float lifeTimeSec);

	public:

		void start();
		void update();

	private:

		// 移動速度（毎秒）
		float	m_moveSpeedPerSec;

		// 生存時間タイマー
		float	m_lifeSecTimer;

		// 座標管理コンポーネント
		ComponentPtr<Transform3D> m_transform;
	};
}
#endif // !BILLBOARD_SHRINK_EFFECT_PARTICLE_H_