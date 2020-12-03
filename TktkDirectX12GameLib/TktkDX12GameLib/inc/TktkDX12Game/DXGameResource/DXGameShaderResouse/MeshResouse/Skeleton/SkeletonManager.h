#ifndef SKELETON_H_
#define SKELETON_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "SkeletonData.h"

namespace tktk
{
	// �uSkeletonData�v���Ǘ�����N���X
	class SkeletonManager
	{
	public:

		explicit SkeletonManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~SkeletonManager();

	public:

		// �uSkeletonData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(const SkeletonInitParam& initParam);

		// �w��́uSkeletonData�v�̃C���X�^���X�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t copy(size_t originalHandle);

		// �����̃{�[�����̍��W�ϊ��s����g���Ďw��̃X�P���g����ό`����
		void transform(size_t handle, const std::vector<MotionBoneParam>& transformMatrices);

		// ���s��̔z����擾����
		std::array<tktkMath::Matrix4, 128U> getBoneMatrixArray(size_t handle) const;

	private:

		tktkContainer::ResourceContainer<SkeletonData> m_skeletonArray;
	};
}
#endif // !SKELETON_H_