#ifndef MESH_ANIMATOR_H_
#define MESH_ANIMATOR_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	// メッシュをアニメーションさせるコンポーネント
	// 【必須コンポーネント：BasicMeshDrawer】
	class MeshAnimator
		: public ComponentBase
	{
	public:

		MeshAnimator(unsigned int initMotionHandle, bool isLoop, float animFramePerSec);

	public:

		void update();

		// 引数のスケルトンを自身のモーションで変形させる
		void transformSkeleton(unsigned int skeletonHandle);

	public:

		// 新しいモーションIDを設定する
		// ※内部で対応するリソースハンドルに変換される
		template <class MotionIdType, is_idType<MotionIdType> = nullptr>
		void setNewMotionId(MotionIdType motionId, bool isLoop, float lerpTimeSec) { setNewMotionIdImpl(static_cast<int>(motionId), isLoop, lerpTimeSec); }

		// 新しいモーションハンドルを設定する
		void setNewMotionHandle(unsigned int motionHandle, bool isLoop, float lerpTimeSec);

	private:

		// 裏実装
		void setNewMotionIdImpl(int motionId, bool isLoop, float lerpTimeSec);

	private:

		bool m_isLoop;

		unsigned int m_preMotionHandle;
		unsigned int m_curMotionHandle;

		float m_curFrame				{ 0.0f };
		float m_preFrame				{ 0.0f };

		float m_animFramePerSec			{ 60.0f };	// １秒間に何フレーム分のアニメーションを再生するか？

		float m_lerpTimer				{ 1.0f };
		float m_increaseLerpTimePerSec	{ 0.0f };
	};
}
#endif // !MESH_ANIMATOR_H_