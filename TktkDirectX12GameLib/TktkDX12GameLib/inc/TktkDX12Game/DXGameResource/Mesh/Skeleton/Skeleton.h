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
		~Skeleton();

	public:

		// 「SkeletonData」のインスタンスを作り、そのリソースのハンドルを返す
		unsigned int create(const SkeletonInitParam& initParam);

		// 指定の「SkeletonData」のインスタンスのコピーを作り、そのリソースのハンドルを返す
		unsigned int copy(unsigned int originalHandle);

		// 指定のスケルトンの骨情報の定数バッファの値にコピーするためのバッファを作り、そのハンドルを返す
		// ※この関数で取得したハンドルは使用後に「DX12GameManager::eraseCopyBuffer(handle)」を必ず読んでバッファを削除してください
		unsigned int createCopyBufferHandle(unsigned int handle) const;

		// 引数のボーン毎の座標変換行列を使って指定のスケルトンを変形する
		void transform(unsigned int handle, const std::vector<MotionBoneParam>& transformMatrices);

		// 指定のスケルトンを使って引数が表すコピーバッファを使い骨情報を管理する定数バッファを更新する
		void updateBoneMatrixCbuffer(unsigned int handle, unsigned int copyBufferHandle) const;

		// 骨情報を管理する定数バッファに単位行列を設定する
		void resetBoneMatrixCbuffer() const;

	private:

		unsigned int m_resetBoneMatrixCopyBufferHandle;
		tktkContainer::ResourceContainer<SkeletonData> m_skeletonArray;
	};
}
#endif // !SKELETON_H_