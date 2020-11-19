#ifndef MESH_ANIMATOR_H_
#define MESH_ANIMATOR_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

namespace tktk
{
	// メッシュをアニメーションさせるコンポーネント
	// 【必須コンポーネント：BasicMeshDrawer】
	class MeshAnimator
		: public ComponentBase
	{
	public:

		MeshAnimator(size_t initMotionHandle, float initFrame, bool isLoop, float motionSpeedRate, float animFramePerSec);

	public:

		void update();

		// 引数のスケルトンを自身のモーションで変形させる
		void transformSkeleton(size_t skeletonHandle);

	public:

		// 新しいモーションIDを設定する
		// ※内部で対応するリソースハンドルに変換される
		void setNewMotionId(ResourceIdCarrier motionId, float initFrame, bool isLoop, float motionSpeedRate, float lerpTimeSec);

		// 新しいモーションハンドルを設定する
		void setNewMotionHandle(size_t motionHandle, float initFrame, bool isLoop, float motionSpeedRate, float lerpTimeSec);

	private:

		bool m_isLoop;

		float m_motionSpeedRate			{ 1.0f };

		size_t m_preMotionHandle;
		size_t m_curMotionHandle;

		float m_curFrame;
		float m_preFrame;

		float m_animFramePerSec			{ 60.0f };	// １秒間に何フレーム分のアニメーションを再生するか？

		float m_lerpTimer				{ 1.0f };
		float m_increaseLerpTimePerSec	{ 0.0f };
	};
}
#endif // !MESH_ANIMATOR_H_