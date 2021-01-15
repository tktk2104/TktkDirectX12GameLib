#ifndef HIT_INFO_2D_H_
#define HIT_INFO_2D_H_

#include <TktkMath/Structs/Vector2.h>

namespace tktkCollision
{
	// �Q�����̏Փ˔��茋��
	struct HitInfo2D
	{
		// �Փ˂������ǂ����H
		bool				isHit			{ false };

		// �Փˎ����g�������o�����̃x�N�g��
		// ������������o�����̃x�N�g���͂��̃x�N�g���𔽓]����
		tktkMath::Vector2	selfExtrudeVec	{ tktkMath::Vector2_v::zero };
	};


}
#endif // !HIT_INFO_2D_H_