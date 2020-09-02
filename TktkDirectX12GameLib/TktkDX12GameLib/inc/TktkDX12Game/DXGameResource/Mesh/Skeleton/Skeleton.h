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
		~Skeleton();

	public:

		// �uSkeletonData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(const SkeletonInitParam& initParam);

		// �w��́uSkeletonData�v�̃C���X�^���X�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int copy(unsigned int originalHandle);

		// �w��̃X�P���g���̍����̒萔�o�b�t�@�̒l�ɃR�s�[���邽�߂̃o�b�t�@�����A���̃n���h����Ԃ�
		// �����̊֐��Ŏ擾�����n���h���͎g�p��ɁuDX12GameManager::eraseCopyBuffer(handle)�v��K���ǂ�Ńo�b�t�@���폜���Ă�������
		unsigned int createCopyBufferHandle(unsigned int handle) const;

		// �����̃{�[�����̍��W�ϊ��s����g���Ďw��̃X�P���g����ό`����
		void transform(unsigned int handle, const std::vector<MotionBoneParam>& transformMatrices);

		// �w��̃X�P���g�����g���Ĉ������\���R�s�[�o�b�t�@���g���������Ǘ�����萔�o�b�t�@���X�V����
		void updateBoneMatrixCbuffer(unsigned int handle, unsigned int copyBufferHandle) const;

		// �������Ǘ�����萔�o�b�t�@�ɒP�ʍs���ݒ肷��
		void resetBoneMatrixCbuffer() const;

	private:

		unsigned int m_resetBoneMatrixCopyBufferHandle;
		tktkContainer::ResourceContainer<SkeletonData> m_skeletonArray;
	};
}
#endif // !SKELETON_H_