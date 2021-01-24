#ifndef SPRITE_SPREAD_EFFECT_CREATOR_H_
#define SPRITE_SPREAD_EFFECT_CREATOR_H_

/* base class */
#include "../../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

#include "SpriteSpreadEffectParam.h"

namespace tktk
{
	class Transform2D;

	class SpriteSpreadEffectCreator
		: public ComponentBase
	{
	public:

		explicit SpriteSpreadEffectCreator(const SpriteSpreadEffectParam& param);

	public:

		void start();
		void onEnable();
		void update();

	private:

		// �p�����[�^
		SpriteSpreadEffectParam m_param;

		// �����p�x�^�C�}�[
		float	m_generateIntervalSecTimer{ 0.0f };

		// �������J�E���^
		int		m_totalGenerateCounter{ 0 };

		// ���W�Ǘ��R���|�[�l���g
		ComponentPtr<Transform2D> m_transform;

		// �p�[�e�B�N����`�悷��I�u�W�F�N�g
		tktk::GameObjectPtr m_particleObject;
	};
}
#endif // !SPRITE_SPREAD_EFFECT_CREATOR_H_