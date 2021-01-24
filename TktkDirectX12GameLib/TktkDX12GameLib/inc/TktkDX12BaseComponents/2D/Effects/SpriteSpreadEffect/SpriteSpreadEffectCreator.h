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

		// パラメータ
		SpriteSpreadEffectParam m_param;

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
#endif // !SPRITE_SPREAD_EFFECT_CREATOR_H_