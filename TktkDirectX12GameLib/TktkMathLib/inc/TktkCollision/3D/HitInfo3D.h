#ifndef HIT_INFO_3D_H_
#define HIT_INFO_3D_H_

#include <TktkMath/Structs/Vector3.h>

namespace tktkCollision
{
	// �R�����̏Փ˔��茋��
	struct HitInfo3D
	{
		// �Փ˂������H
		bool				isHit			{ false };

		// �Փˎ����g�������o�����̃x�N�g��
		// ������������o�����̃x�N�g���͂��̃x�N�g���𔽓]����
		tktkMath::Vector3	selfExtrudeVec	{ tktkMath::Vector3_v::zero };
	};
}
#endif // !HIT_INFO_3D_H_