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
	// スケルトンの情報を管理するクラス
	class SkeletonData
	{
	public:

		SkeletonData(const SkeletonInitParam& initParam);

		// ムーブコンストラクタ
		SkeletonData(SkeletonData&& other) noexcept;

		~SkeletonData() = default;

	public:

		// 引数のボーン毎の座標変換行列を使ってスケルトンを変形する
		void transform(const std::vector<MotionBoneParam>& transformMatrices);

		// 骨情報を管理する定数バッファを更新する
		void updateBoneMatrixCbuffer() const;

	private:

		// 骨の情報
		struct BoneNode
		{
			int						boneIndex	{};
			tktkMath::Vector3		startPos	{};
			tktkMath::Vector3		endPos		{};
			std::vector<BoneNode*>	children	{};
		};

	private:

		void transform(const SkeletonData::BoneNode* boneNode, const tktkMath::Matrix4& transformMat);

	private:

		std::vector<tktkMath::Matrix4>				m_boneMatrixArray;
		std::unordered_map<std::string, BoneNode>	m_boneNodeMap;
	};
}
#endif // !SKELETON_DATA_H_