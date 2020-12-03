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

		// パラメータ
		BillboardShrinkEffectParam m_param;

		// 生成頻度タイマー
		float	m_generateIntervalSecTimer{ 0.0f };

		// 生成数カウンタ
		int		m_totalGenerateCounter{ 0 };

		// 座標管理コンポーネント
		ComponentPtr<Transform3D> m_transform;
	};
}
#endif // !BILLBOARD_SHRINK_EFFECT_CREATOR_H_
