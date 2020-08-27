#ifndef MESH_ANIMATOR_H_
#define MESH_ANIMATOR_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	// メッシュをアニメーションさせるコンポーネント
	// 【必須コンポーネント：BasicMeshDrawer】
	class MeshAnimator
		: public ComponentBase
	{
	public:

		MeshAnimator(unsigned int initMotionHandle, bool isLoop);

	public:

		void update();

		// 引数のスケルトンを自身のモーションで変形させる
		void transformSkeleton(unsigned int skeletonHandle);

	public:

		// 新しいモーションIDを設定する
		// ※内部で対応するリソースハンドルに変換される
		void setNewMotionId(int motionId, float lerpTimeSec);

		// 新しいモーションハンドルを設定する
		void setNewMotionHandle(unsigned int motionHandle, float lerpTimeSec);

	private:

		bool m_isLoop;

		unsigned int m_preMotionHandle;
		unsigned int m_curMotionHandle;

		float m_curFrame				{ 0.0f };
		float m_preFrame				{ 0.0f };

		float m_animFrameIntervalPerSec	{ 60.0f };

		float m_lerpTimer				{ 1.0f };
		float m_increaseLerpTimePerSec	{ 0.0f };
	};
}
#endif // !MESH_ANIMATOR_H_