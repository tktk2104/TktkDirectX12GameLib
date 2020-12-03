#ifndef SKELETON_DATA_H_
#define SKELETON_DATA_H_

/* std::string */
#include <string>

/* std::array<> */
#include <array>

/* std::vector<> */
#include <vector>

/* std::unordered_map */
#include <unordered_map>

/* class member */
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	struct SkeletonInitParam;
	struct MotionBoneParam;

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

		// �����̃{�[�����̍��W�ϊ��s����g���ăX�P���g����ό`����
		void transform(const std::vector<MotionBoneParam>& transformMatrices);

		// ���s��̔z����擾����
		std::array<tktkMath::Matrix4, 128U> getBoneMatrixArray() const;

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

	private:

		//size_t									m_createCopyBufferHandle{ 0U };
		std::vector<tktkMath::Matrix4>				m_boneMatrixArray;
		std::unordered_map<std::string, BoneNode>	m_boneNodeMap;
	};
}
#endif // !SKELETON_DATA_H_