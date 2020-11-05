#ifndef MOTION_H_
#define MOTION_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "MotionData.h"

namespace tktk
{
	// �uMotionData�v���Ǘ�����N���X
	class Motion
	{
	public:

		explicit Motion(const tktkContainer::ResourceContainerInitParam& initParam);

	public:

		// vmd�t�@�C����ǂݍ���ŁuMotionData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t load(const std::string& motionFileName);

		// �w��̃��[�V�����̏I���L�[�̔ԍ����擾����
		size_t getEndFrameNo(size_t handle) const;

		// �Q�̃t���[���̃{�[�����̍s��ƕ⊮�������g�p���A���`�⊮�����{�[�����̍s����v�Z����i�L�[���������͑O��̃L�[����v�Z����j
		// ���⊮�����̒l�́u0.0��preFrame100%�v�A�u1.0��curFrame100%�v�ƂȂ�
		std::vector<MotionBoneParam> calculateBoneTransformMatrices(size_t curHandle, size_t preHandle, size_t curFrame, size_t preFrame, float amount) const;

	private:

		tktkContainer::ResourceContainer<MotionData> m_motionArray;
	};
}
#endif // !MOTION_H_