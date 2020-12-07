#ifndef BILLBOARD_ANIMATOR_MAKER_H_
#define BILLBOARD_ANIMATOR_MAKER_H_

#include "BillboardAnimator.h"

namespace tktk
{
	// 「BillboardAnimator」を作るヘルパークラス
	class BillboardAnimatorMaker
	{
	private: /* プライベートコンストラクタ達 */

		BillboardAnimatorMaker() = default;
		BillboardAnimatorMaker(const BillboardAnimatorMaker& other) = default;
		BillboardAnimatorMaker& operator = (const BillboardAnimatorMaker& other) = default;

	public:

		// 作成開始
		static BillboardAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<BillboardAnimator> create();

	public:  /* パラメータ設定関数 */

		// アニメーションがループするかを設定する
		BillboardAnimatorMaker& isLoop(bool value);

		// アニメーションの初期フレームを設定する
		BillboardAnimatorMaker& initFrame(float value);

		// アニメーションの再生速度割合を設定する
		BillboardAnimatorMaker& animSpeedRate(float value);

		// アニメーション１フレームあたりにかける時間を設定する
		BillboardAnimatorMaker& animFramePerSec(float value);

		// アニメーションの総フレーム数を設定する
		BillboardAnimatorMaker& totalAnimFrameSize(unsigned int value);


	private: /* 自身のインスタンスは静的な存在として扱う */

		static BillboardAnimatorMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user				{  };
		bool				m_isLoop			{ true };
		float				m_initFrame			{ 0.0f };
		float				m_animSpeedRate		{ 1.0f };
		float				m_animFramePerSec	{ 0.1f };
		unsigned int		m_totalAnimFrameSize{ 1U };
	};
}
#endif // !BILLBOARD_ANIMATOR_MAKER_H_