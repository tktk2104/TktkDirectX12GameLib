#ifndef SPRITE_SPREAD_EFFECT_PARTICLE_H_
#define SPRITE_SPREAD_EFFECT_PARTICLE_H_

/* base class */
#include "../../../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	class Transform2D;

	class SpriteSpreadEffectParticle
		: public ComponentBase
	{
	public:

		SpriteSpreadEffectParticle(float moveSpeed, float lifeTimeSec);

	public:

		void start();
		void update();

	private:

		// �ړ����x�i���b�j
		float	m_moveSpeedPerSec;

		// �������ԃ^�C�}�[
		float	m_lifeSecTimer;

		// ���W�Ǘ��R���|�[�l���g
		ComponentPtr<Transform2D> m_transform;
	};
}
#endif // !SPRITE_SPREAD_EFFECT_PARTICLE_H_