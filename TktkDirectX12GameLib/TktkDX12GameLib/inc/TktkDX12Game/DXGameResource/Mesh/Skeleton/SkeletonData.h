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

		// コピーコンストラクタ
		SkeletonData(const SkeletonData& other);

		// ムーブコンストラクタ
		SkeletonData(SkeletonData&& other) noexcept;

		~SkeletonData() = default;

	public:

		// 骨情報の定数バッファの値にアップロードするためのバッファを作り、そのハンドルを返す
		// ※この関数で取得したハンドルは使用後に「DX12GameManager::eraseUploadBuffer(handle)」を必ず呼んでバッファを削除してください
		size_t createUploadBufferHandle() const;

		// 引数のボーン毎の座標変換行列を使ってスケルトンを変形する
		void transform(const std::vector<MotionBoneParam>& transformMatrices);

		// 引数が表すコピーバッファを使って骨情報を管理する定数バッファを更新する
		void updateBoneMatrixCbuffer(size_t copyBufferHandle) const;

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

		// 指定のコピーバッファを更新する
		void updateCopyBuffer(size_t copyBufferHandle) const;

	private:

		//size_t									m_createCopyBufferHandle{ 0U };
		std::vector<tktkMath::Matrix4>				m_boneMatrixArray;
		std::unordered_map<std::string, BoneNode>	m_boneNodeMap;
	};
}
#endif // !SKELETON_DATA_H_