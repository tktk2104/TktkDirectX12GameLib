#ifndef BILLBOARD_SPREAD_EFFECT_PARTICLE_H_
#define BILLBOARD_SPREAD_EFFECT_PARTICLE_H_

/* base class */
#include "../../../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	class Transform3D;

	class BillboardSpreadEffectParticle
		: public ComponentBase
	{
	public:

		BillboardSpreadEffectParticle(float	moveSpeed, float lifeTimeSec);

	public:

		void start();
		void update();

	private:

		// �ړ����x�i���b�j
		float	m_moveSpeedPerSec;

		// �������ԃ^�C�}�[
		float	m_lifeSecTimer;

		// ���W�Ǘ��R���|�[�l���g
		ComponentPtr<Transform3D> m_transform;
	};
}
#endif // !BILLBOARD_SPREAD_EFFECT_PARTICLE_H_