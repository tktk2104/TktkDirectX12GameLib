#ifndef MOTION_H_
#define MOTION_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "MotionData.h"

namespace tktk
{
	// �uMotionData�v���Ǘ�����N���X
	class Motion
	{
	public:

		Motion(unsigned int motionNum);

	public:

		// vmd�t�@�C����ǂݍ���ŁuMotionData�v�̃C���X�^���X�����
		void load(unsigned int id, const std::string& motionFileName);

		// �w��̃��[�V�����̏I���L�[�̔ԍ����擾����
		unsigned int getEndFrameNo(unsigned int id) const;

		// �Q�̃t���[���̃{�[�����̍s��ƕ⊮�������g�p���A���`�⊮�����{�[�����̍s����v�Z����i�L�[���������͑O��̃L�[����v�Z����j
		// ���⊮�����̒l�́u0.0��preFrame100%�v�A�u1.0��curFrame100%�v�ƂȂ�
		std::vector<MotionBoneParam> calculateBoneTransformMatrices(unsigned int curId, unsigned int preId, unsigned int curFrame, unsigned int preFrame, float amount) const;

	private:

		tktkContainer::HeapArray<MotionData> m_motionArray;
	};
}
#endif // !MOTION_H_