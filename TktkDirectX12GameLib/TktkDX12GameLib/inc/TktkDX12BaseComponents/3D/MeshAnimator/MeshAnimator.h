#ifndef MESH_ANIMATOR_H_
#define MESH_ANIMATOR_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	// ���b�V�����A�j���[�V����������R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FBasicMeshDrawer�z
	class MeshAnimator
		: public ComponentBase
	{
	public:

		MeshAnimator(unsigned int initMotionHandle, bool isLoop, float animFramePerSec);

	public:

		void update();

		// �����̃X�P���g�������g�̃��[�V�����ŕό`������
		void transformSkeleton(unsigned int skeletonHandle);

	public:

		// �V�������[�V����ID��ݒ肷��
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		template <class MotionIdType, is_idType<MotionIdType> = nullptr>
		void setNewMotionId(MotionIdType motionId, bool isLoop, float lerpTimeSec) { setNewMotionIdImpl(static_cast<int>(motionId), isLoop, lerpTimeSec); }

		// �V�������[�V�����n���h����ݒ肷��
		void setNewMotionHandle(unsigned int motionHandle, bool isLoop, float lerpTimeSec);

	private:

		// ������
		void setNewMotionIdImpl(int motionId, bool isLoop, float lerpTimeSec);

	private:

		bool m_isLoop;

		unsigned int m_preMotionHandle;
		unsigned int m_curMotionHandle;

		float m_curFrame				{ 0.0f };
		float m_preFrame				{ 0.0f };

		float m_animFramePerSec			{ 60.0f };	// �P�b�Ԃɉ��t���[�����̃A�j���[�V�������Đ����邩�H

		float m_lerpTimer				{ 1.0f };
		float m_increaseLerpTimePerSec	{ 0.0f };
	};
}
#endif // !MESH_ANIMATOR_H_