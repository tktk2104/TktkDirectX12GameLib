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

		MeshAnimator(unsigned int initMotionId, bool isLoop);

	public:

		void update();

		// 引数のスケルトンを自身のモーションで変形させる
		void transformSkeleton(unsigned int skeletonId);

	public:

		// モーションを変更する
		void changeMotion(unsigned int motionId, float lerpTimeSec);

	private:

		bool m_isLoop;

		unsigned int m_preMotionId;
		unsigned int m_curMotionId;

		float m_curFrame				{ 0.0f };
		float m_preFrame				{ 0.0f };

		float m_animFrameIntervalPerSec	{ 60.0f };

		float m_lerpTimer				{ 1.0f };
		float m_increaseLerpTimePerSec	{ 0.0f };
	};
}
#endif // !MESH_ANIMATOR_H_