#ifndef MOTION_CHANGER_H_
#define MOTION_CHANGER_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "MeshAnimator.h"

namespace tktk
{
	// ���g���A�N�e�B�u��ԂɂȂ������Ƀ��b�V���̃A�j���[�V������ύX����R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FMeshAnimator�z
	class MotionChanger
		: public ComponentBase
	{
	public:

		MotionChanger(size_t changeMotionHandle, bool isLoop, float lerpTimeSec);

	public:

		void onEnable();

	private:

		size_t						m_changeMotionHandle;
		bool						m_isLoop;
		float						m_lerpTimeSec;
		ComponentPtr<MeshAnimator>	m_meshAnimator;
	};
}
#endif // !MOTION_CHANGER_H_
