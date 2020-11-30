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

	// スケルトンの情報を管理するクラス
	class SkeletonData
	{
	public:

		SkeletonData(const SkeletonInitParam& initParam);

		// コピーコンストラクタ
		SkeletonData(const SkeletonData& other);

		// ムーブコンストラクタ
		SkeletonData(SkeletonData&& other) noexcept;

		~SkeletonData() = default;

	public:

		// 引数のボーン毎の座標変換行列を使ってスケルトンを変形する
		void transform(const std::vector<MotionBoneParam>& transformMatrices);

		// 骨行列の配列を取得する
		std::array<tktkMath::Matrix4, 128U> getBoneMatrixArray() const;

	private:

		// 骨の情報
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