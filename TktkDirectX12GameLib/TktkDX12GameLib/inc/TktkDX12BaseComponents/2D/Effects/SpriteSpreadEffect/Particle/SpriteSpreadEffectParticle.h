#ifndef SPRITE_SPREAD_EFFECT_PARTICLE_H_
#define SPRITE_SPREAD_EFFECT_PARTICLE_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

/* base class */
#include "../../../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	class Transform2D;
	class SpriteDrawer;

	class SpriteSpreadEffectParticle
		: public ComponentBase
	{
	public:

		SpriteSpreadEffectParticle(const ComponentPtr<SpriteDrawer>& targetDrawer, float moveSpeed, const tktkMath::Vector2& scalingSize, const tktkMath::Color& blendRateChangeWidth, float lifeTimeSec);

	public:

		void update();

	private:

		// 移動速度（毎秒）
		float	m_moveSpeedPerSec;

		// スケーリング増加速度（毎秒）
		tktkMath::Vector2 m_scalingSizePerSec;

		// スプライトのブレンドレート増加幅（毎秒）
		tktkMath::Color m_blendRateChangeWidthPerSec;

		// 生存時間タイマー
		float	m_lifeSecTimer;

		// スプライト描画コンポーネント
		ComponentPtr<SpriteDrawer> m_spriteDrawer;
	};
}
#endif // !SPRITE_SPREAD_EFFECT_PARTICLE_H_