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

		// �ړ����x�i���b�j
		float	m_moveSpeedPerSec;

		// �X�P�[�����O�������x�i���b�j
		tktkMath::Vector2 m_scalingSizePerSec;

		// �X�v���C�g�̃u�����h���[�g�������i���b�j
		tktkMath::Color m_blendRateChangeWidthPerSec;

		// �������ԃ^�C�}�[
		float	m_lifeSecTimer;

		// �X�v���C�g�`��R���|�[�l���g
		ComponentPtr<SpriteDrawer> m_spriteDrawer;
	};
}
#endif // !SPRITE_SPREAD_EFFECT_PARTICLE_H_