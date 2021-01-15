#ifndef BILLBOARD_SPREAD_EFFECT_CREATOR_H_
#define BILLBOARD_SPREAD_EFFECT_CREATOR_H_

/* base class */
#include "../../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

#include "BillboardSpreadEffectParam.h"

namespace tktk
{
	class Transform3D;

	class BillboardSpreadEffectCreator
		: public ComponentBase
	{
	public:

		explicit BillboardSpreadEffectCreator(const BillboardSpreadEffectParam& param);

	public:

		void start();
		void onEnable();
		void update();

	private:

		// パラメータ
		BillboardSpreadEffectParam m_param;

		// 生成頻度タイマー
		float	m_generateIntervalSecTimer	{ 0.0f };

		// 生成数カウンタ
		int		m_totalGenerateCounter		{ 0 };

		// 座標管理コンポーネント
		ComponentPtr<Transform3D> m_transform;
	};
}
#endif // !BILLBOARD_SPREAD_EFFECT_CREATOR_H_