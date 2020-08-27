#ifndef SKELETON_H_
#define SKELETON_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "SkeletonData.h"

namespace tktk
{
	// 「SkeletonData」を管理するクラス
	class Skeleton
	{
	public:

		explicit Skeleton(const tktkContainer::ResourceContainerInitParam& initParam);

	public:

		// 「SkeletonData」のインスタンスを作り、そのリソースのハンドルを返す
		unsigned int create(const SkeletonInitParam& initParam);

		// 引数のボーン毎の座標変換行列を使って指定のスケルトンを変形する
		void transform(unsigned int handle, const std::vector<MotionBoneParam>& transformMatrices);

		// 指定のスケルトンを使って骨情報を管理する定数バッファを更新する
		void updateBoneMatrixCbuffer(unsigned int handle) const;

		// 骨情報を管理する定数バッファに単位行列を設定する
		void resetBoneMatrixCbuffer() const;

	private:

		tktkContainer::ResourceContainer<SkeletonData> m_skeletonArray;
	};
}
#endif // !SKELETON_H_