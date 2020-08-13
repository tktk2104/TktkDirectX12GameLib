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

		MeshAnimator(unsigned int initMotionId);

	public:

		void update();

		// 引数のスケルトンを自身のモーションで変形させる
		void transformSkeleton(unsigned int skeletonId);

	public:

		// モーションを新たに設定する
		void setMotionId(unsigned int motionId);

	private:

		unsigned int m_motionId;
		unsigned int m_curFrame{ 0U };
	};
}
#endif // !MESH_ANIMATOR_H_