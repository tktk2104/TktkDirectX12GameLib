#ifndef MESH_ANIMATOR_MAKER_H_
#define MESH_ANIMATOR_MAKER_H_

#include "MeshAnimator.h"

namespace tktk
{
	// 「MeshAnimator」を作るヘルパークラス
	class MeshAnimatorMaker
	{
	private: /* プライベートコンストラクタ達 */

		MeshAnimatorMaker() = default;
		MeshAnimatorMaker(const MeshAnimatorMaker& other) = default;
		MeshAnimatorMaker& operator = (const MeshAnimatorMaker& other) = default;

	public:

		// 作成開始
		static MeshAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<MeshAnimator> create();

	public:  /* パラメータ設定関数 */

		// モーションをループさせるかを設定する
		MeshAnimatorMaker& isLoop(bool value);

		// モーションの再生速度倍率を設定する
		MeshAnimatorMaker& motionSpeedRate(float value);

		// 使用する初期モーションハンドルを設定する
		MeshAnimatorMaker& initMotionHandle(size_t value);

		// 使用する初期モーションIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		MeshAnimatorMaker& initMotionId(ResourceIdCarrier value);

		// １秒間に何フレーム分のアニメーションを再生するかを設定する
		MeshAnimatorMaker& animFramePerSec(float value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static MeshAnimatorMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user				{  };
		bool				m_isLoop			{ true };
		float				m_motionSpeedRate	{ 1.0f };
		size_t				m_initMotionHandle	{ 0U };
		float				m_animFramePerSec	{ 60.0f };
	};
}
#endif // !MESH_ANIMATOR_MAKER_H_
