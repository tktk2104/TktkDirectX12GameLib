#ifndef SPRITE_SHRINK_EFFECT_CREATOR_H_

/* base class */
#include "../../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

#include "SpriteShrinkEffectParam.h"

namespace tktk
{
	class Transform2D;

	class SpriteShrinkEffectCreator
		: public ComponentBase
	{
	public:

		explicit SpriteShrinkEffectCreator(const SpriteShrinkEffectParam& param);

	public:

		void start();
		void onEnable();
		void update();

	private:

		// �p�����[�^
		SpriteShrinkEffectParam m_param;

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
#endif // !SPRITE_SHRINK_EFFECT_CREATOR_H_