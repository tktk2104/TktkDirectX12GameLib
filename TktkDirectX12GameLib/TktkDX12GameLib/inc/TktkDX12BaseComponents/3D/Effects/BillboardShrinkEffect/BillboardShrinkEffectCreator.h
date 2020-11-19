#ifndef BILLBOARD_SHRINK_EFFECT_CREATOR_H_

/* base class */
#include "../../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

#include "BillboardShrinkEffectParam.h"

namespace tktk
{
	class Transform3D;

	class BillboardShrinkEffectCreator
		: public ComponentBase
	{
	public:

		BillboardShrinkEffectCreator(const BillboardShrinkEffectParam& param);

	public:

		void start();
		void onEnable();
		void update();

	private:

		// �p�����[�^
		BillboardShrinkEffectParam m_param;

		// �����p�x�^�C�}�[
		float	m_generateIntervalSecTimer{ 0.0f };

		// �������J�E���^
		int		m_totalGenerateCounter{ 0 };

		// ���W�Ǘ��R���|�[�l���g
		ComponentPtr<Transform3D> m_transform;
	};
}
#endif // !BILLBOARD_SHRINK_EFFECT_CREATOR_H_
