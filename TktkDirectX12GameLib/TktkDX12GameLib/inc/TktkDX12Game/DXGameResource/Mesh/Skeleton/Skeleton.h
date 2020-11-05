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
		size_t create(const SkeletonInitParam& initParam);

		// 指定の「SkeletonData」のインスタンスのコピーを作り、そのリソースのハンドルを返す
		size_t copy(size_t originalHandle);

		// 指定のスケルトンの骨情報の定数バッファの値にコピーするためのバッファを作り、そのハンドルを返す
		// ※この関数で取得したハンドルは使用後に「DX12GameManager::eraseCopyBuffer(handle)」を必ず読んでバッファを削除してください
		size_t createUploadBufferHandle(size_t handle) const;

		// 引数のボーン毎の座標変換行列を使って指定のスケルトンを変形する
		void transform(size_t handle, const std::vector<MotionBoneParam>& transformMatrices);

		// 指定のスケルトンを使って引数が表すコピーバッファを使い骨情報を管理する定数バッファを更新する
		void updateBoneMatrixCbuffer(size_t handle, size_t copyBufferHandle) const;

		// 骨情報を管理する定数バッファに単位行列を設定する
		void resetBoneMatrixCbuffer() const;

	private:

		size_t m_resetBoneMatrixUploadBufferHandle;
		tktkContainer::ResourceContainer<SkeletonData> m_skeletonArray;
	};
}
#endif // !SKELETON_H_