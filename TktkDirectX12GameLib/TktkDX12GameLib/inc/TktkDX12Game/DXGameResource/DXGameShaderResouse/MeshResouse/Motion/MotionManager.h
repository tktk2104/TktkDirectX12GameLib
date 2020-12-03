#ifndef MOTION_H_
#define MOTION_H_

/* std::vector */
#include <vector>

/* std::string */
#include <string>

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	class MotionData;
	struct MotionBoneParam;

	// �uMotionData�v���Ǘ�����N���X
	class MotionManager
	{
	public:

		explicit MotionManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~MotionManager();

	public:

		// vmd�t�@�C����ǂݍ���ŁuMotionData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t load(const std::string& motionFileName);

		// �w��̃��[�V�����̏I���L�[�̔ԍ����擾����
		size_t getEndFrameNo(size_t handle) const;

		// �Q�̃t���[���̃{�[�����̍s��ƕ⊮�������g�p���A���`�⊮�����{�[�����̍s����v�Z����i�L�[���������͑O��̃L�[����v�Z����j
		// ���⊮�����̒l�́u0.0��preFrame100%�v�A�u1.0��curFrame100%�v�ƂȂ�
		std::vector<MotionBoneParam> calculateBoneTransformMatrices(size_t curHandle, size_t preHandle, float curFrame, float preFrame, float amount) const;

	private:

		tktkContainer::ResourceContainer<MotionData> m_motionArray;
	};
}
#endif // !MOTION_H_