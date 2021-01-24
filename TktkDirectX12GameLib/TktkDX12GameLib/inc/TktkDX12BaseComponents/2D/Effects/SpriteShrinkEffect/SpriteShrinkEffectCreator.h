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

		// パラメータ
		SpriteShrinkEffectParam m_param;

		// 生成頻度タイマー
		float	m_generateIntervalSecTimer{ 0.0f };

		// 生成数カウンタ
		int		m_totalGenerateCounter{ 0 };

		// 座標管理コンポーネント
		ComponentPtr<Transform2D> m_transform;

		// パーティクルを描画するオブジェクト
		tktk::GameObjectPtr m_particleObject;
	};
}
#endif // !SPRITE_SHRINK_EFFECT_CREATOR_H_