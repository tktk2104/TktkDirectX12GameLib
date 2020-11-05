#ifndef MOTION_DATA_H_
#define MOTION_DATA_H_

#include <string>
#include <vector>
#include <map>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Quaternion.h>
#include <TktkMath/Structs/Matrix4.h>
#include "MotionBoneParam.h"

namespace tktk
{
	// ���[�V�����f�[�^���Ǘ�����N���X
	class MotionData
	{
	public:

		MotionData(const std::string& motionFileName);

		// ���[�u�R���X�g���N�^
		MotionData(MotionData&& other) noexcept;

		~MotionData() = default;

	public:

		// ���[�V�����̏I���L�[�̔ԍ����擾����
		size_t getEndFrameNo() const;

		// �w��̃t���[���̃{�[�����̍s����擾����i�L�[���������͑O��̃L�[����v�Z����j
		std::vector<MotionBoneParam> calculateBoneTransformMatrices(size_t frame) const;

	private:

		// �L�[�t���[�����
		struct KeyFrame
		{
			size_t					frameNo;
			tktkMath::Vector3		position;
			tktkMath::Vector3		scale;
			tktkMath::Quaternion	rotation;
		};

	private:

		// ���݂̃t���[���ɑΉ������L�[�t���[�������߂�
		KeyFrame calculateKeyFrame(const std::vector<KeyFrame>& keyFrames, size_t frame) const;

	private:

		size_t  m_endFrameNo;

		// �{�[�����Ƃ̃L�[�t���[���̔z����Ǘ�����A�z�z��
		std::map<std::string, std::vector<KeyFrame>> m_boneKeyFrames;
	};
}
#endif // !MOTION_DATA_H_