#ifndef SKELETON_H_
#define SKELETON_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "SkeletonData.h"

namespace tktk
{
	// 「SkeletonData」を管理するクラス
	class Skeleton
	{
	public:

		Skeleton(unsigned int skeletonNum);

	public:

		// 「SkeletonData」のインスタンスを作る
		void create(unsigned int id, const SkeletonInitParam& initParam);

		// 引数のボーン毎の座標変換行列を使って指定のスケルトンを変形する
		void transform(unsigned int id, const std::vector<MotionBoneParam>& transformMatrices);

		// 指定のスケルトンを使って骨情報を管理する定数バッファを更新する
		void updateBoneMatrixCbuffer(unsigned int id) const;

		// 骨情報を管理する定数バッファに単位行列を設定する
		void resetBoneMatrixCbuffer() const;

	private:

		HeapArray<SkeletonData> m_skeletonArray;
	};
}
#endif // !SKELETON_H_