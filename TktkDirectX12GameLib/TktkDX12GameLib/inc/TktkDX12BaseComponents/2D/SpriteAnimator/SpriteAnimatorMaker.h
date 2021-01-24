#ifndef SPRITE_ANIMATOR_MAKER_H_
#define SPRITE_ANIMATOR_MAKER_H_

#include "SpriteAnimator.h"

namespace tktk
{
	// 「SpriteAnimator」を作るヘルパークラス
	class SpriteAnimatorMaker
	{
	private: /* プライベートコンストラクタ達 */

		SpriteAnimatorMaker() = default;
		SpriteAnimatorMaker(const SpriteAnimatorMaker& other) = default;
		SpriteAnimatorMaker& operator = (const SpriteAnimatorMaker& other) = default;

	public:

		// 作成開始
		static SpriteAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<SpriteAnimator> create();

	public:  /* パラメータ設定関数 */

		// アニメーション対象のスプライト描画コンポーネントを事前に設定する（※設定しなかった場合、自動で共通のGameObjectが所持しているスプライト描画コンポーネントが対象になる）
		SpriteAnimatorMaker& targetDrawer(const ComponentPtr<SpriteDrawer>& value);

		// アニメーションがループするかを設定する
		SpriteAnimatorMaker& isLoop(bool value);

		// アニメーションの初期フレームを設定する
		SpriteAnimatorMaker& initFrame(float value);

		// アニメーションの再生速度割合を設定する
		SpriteAnimatorMaker& animSpeedRate(float value);

		// アニメーション１フレームあたりにかける時間を設定する
		SpriteAnimatorMaker& animFramePerSec(float value);

		// アニメーションの総フレーム数を設定する
		SpriteAnimatorMaker& totalAnimFrameSize(unsigned int value);


	private: /* 自身のインスタンスは静的な存在として扱う */

		static SpriteAnimatorMaker m_self;

	private: /* 変数達 */

		GameObjectPtr				m_user					{  };
		ComponentPtr<SpriteDrawer>	m_targetDrawer			{ ComponentPtr<SpriteDrawer>() };
		bool						m_isLoop				{ true };
		float						m_initFrame				{ 0.0f };
		float						m_animSpeedRate			{ 1.0f };
		float						m_animFramePerSec		{ 0.1f };
		unsigned int				m_totalAnimFrameSize	{ 1U };
	};
}
#endif // !SPRITE_ANIMATOR_MAKER_H_