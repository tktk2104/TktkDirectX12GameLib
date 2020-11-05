#ifndef SKELETON_DATA_H_
#define SKELETON_DATA_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "SkeletonInitParam.h"
#include "../Motion/MotionBoneParam.h"

namespace tktk
{
	// �X�P���g���̏����Ǘ�����N���X
	class SkeletonData
	{
	public:

		SkeletonData(const SkeletonInitParam& initParam);

		// �R�s�[�R���X�g���N�^
		SkeletonData(const SkeletonData& other);

		// ���[�u�R���X�g���N�^
		SkeletonData(SkeletonData&& other) noexcept;

		~SkeletonData() = default;

	public:

		// �����̒萔�o�b�t�@�̒l�ɃA�b�v���[�h���邽�߂̃o�b�t�@�����A���̃n���h����Ԃ�
		// �����̊֐��Ŏ擾�����n���h���͎g�p��ɁuDX12GameManager::eraseUploadBuffer(handle)�v��K���Ă�Ńo�b�t�@���폜���Ă�������
		size_t createUploadBufferHandle() const;

		// �����̃{�[�����̍��W�ϊ��s����g���ăX�P���g����ό`����
		void transform(const std::vector<MotionBoneParam>& transformMatrices);

		// �������\���R�s�[�o�b�t�@���g���č������Ǘ�����萔�o�b�t�@���X�V����
		void updateBoneMatrixCbuffer(size_t copyBufferHandle) const;

	private:

		// ���̏��
		struct BoneNode
		{
			size_t					boneIndex	{};
			tktkMath::Vector3		startPos	{};
			tktkMath::Vector3		endPos		{};
			std::vector<BoneNode*>	children	{};
		};

	private:

		void transform(const SkeletonData::BoneNode* boneNode, const tktkMath::Matrix4& transformMat);

		// �w��̃R�s�[�o�b�t�@���X�V����
		void updateCopyBuffer(size_t copyBufferHandle) const;

	private:

		//size_t									m_createCopyBufferHandle{ 0U };
		std::vector<tktkMath::Matrix4>				m_boneMatrixArray;
		std::unordered_map<std::string, BoneNode>	m_boneNodeMap;
	};
}
#endif // !SKELETON_DATA_H_