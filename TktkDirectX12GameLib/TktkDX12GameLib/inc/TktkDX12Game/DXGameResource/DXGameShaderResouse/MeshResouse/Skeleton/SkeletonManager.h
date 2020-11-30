#ifndef SKELETON_H_
#define SKELETON_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "SkeletonData.h"

namespace tktk
{
	// 「SkeletonData」を管理するクラス
	class SkeletonManager
	{
	public:

		explicit SkeletonManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~SkeletonManager();

	public:

		// 「SkeletonData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(const SkeletonInitParam& initParam);

		// 指定の「SkeletonData」のインスタンスのコピーを作り、そのリソースのハンドルを返す
		size_t copy(size_t originalHandle);

		// 引数のボーン毎の座標変換行列を使って指定のスケルトンを変形する
		void transform(size_t handle, const std::vector<MotionBoneParam>& transformMatrices);

		// 骨行列の配列を取得する
		std::array<tktkMath::Matrix4, 128U> getBoneMatrixArray(size_t handle) const;

	private:

		tktkContainer::ResourceContainer<SkeletonData> m_skeletonArray;
	};
}
#endif // !SKELETON_H_