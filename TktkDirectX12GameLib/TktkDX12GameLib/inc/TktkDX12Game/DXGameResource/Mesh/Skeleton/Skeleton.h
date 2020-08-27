#ifndef SKELETON_H_
#define SKELETON_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "SkeletonData.h"

namespace tktk
{
	// �uSkeletonData�v���Ǘ�����N���X
	class Skeleton
	{
	public:

		explicit Skeleton(const tktkContainer::ResourceContainerInitParam& initParam);

	public:

		// �uSkeletonData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(const SkeletonInitParam& initParam);

		// �����̃{�[�����̍��W�ϊ��s����g���Ďw��̃X�P���g����ό`����
		void transform(unsigned int handle, const std::vector<MotionBoneParam>& transformMatrices);

		// �w��̃X�P���g�����g���č������Ǘ�����萔�o�b�t�@���X�V����
		void updateBoneMatrixCbuffer(unsigned int handle) const;

		// �������Ǘ�����萔�o�b�t�@�ɒP�ʍs���ݒ肷��
		void resetBoneMatrixCbuffer() const;

	private:

		tktkContainer::ResourceContainer<SkeletonData> m_skeletonArray;
	};
}
#endif // !SKELETON_H_