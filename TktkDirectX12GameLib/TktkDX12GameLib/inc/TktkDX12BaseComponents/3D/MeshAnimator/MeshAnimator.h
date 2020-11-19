#ifndef MESH_ANIMATOR_H_
#define MESH_ANIMATOR_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

namespace tktk
{
	// ���b�V�����A�j���[�V����������R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FBasicMeshDrawer�z
	class MeshAnimator
		: public ComponentBase
	{
	public:

		MeshAnimator(size_t initMotionHandle, float initFrame, bool isLoop, float motionSpeedRate, float animFramePerSec);

	public:

		void update();

		// �����̃X�P���g�������g�̃��[�V�����ŕό`������
		void transformSkeleton(size_t skeletonHandle);

	public:

		// �V�������[�V����ID��ݒ肷��
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		void setNewMotionId(ResourceIdCarrier motionId, float initFrame, bool isLoop, float motionSpeedRate, float lerpTimeSec);

		// �V�������[�V�����n���h����ݒ肷��
		void setNewMotionHandle(size_t motionHandle, float initFrame, bool isLoop, float motionSpeedRate, float lerpTimeSec);

	private:

		bool m_isLoop;

		float m_motionSpeedRate			{ 1.0f };

		size_t m_preMotionHandle;
		size_t m_curMotionHandle;

		float m_curFrame;
		float m_preFrame;

		float m_animFramePerSec			{ 60.0f };	// �P�b�Ԃɉ��t���[�����̃A�j���[�V�������Đ����邩�H

		float m_lerpTimer				{ 1.0f };
		float m_increaseLerpTimePerSec	{ 0.0f };
	};
}
#endif // !MESH_ANIMATOR_H_