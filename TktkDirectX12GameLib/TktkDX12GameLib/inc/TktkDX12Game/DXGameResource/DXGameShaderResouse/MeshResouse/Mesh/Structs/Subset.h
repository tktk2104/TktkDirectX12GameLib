#ifndef SUBSET_H_
#define SUBSET_H_

namespace tktk
{
	// サブセット（使用するマテリアル情報）
	struct Subset
	{
	public:

		// 使用するマテリアルのID
		size_t useMaterialHandle;

		// インデックスバッファの使用開始位置
		size_t indexBufferStartPos;

		// インデックスバッファの使用幅
		size_t indexBufferUseCount;
	};
}
#endif // !SUBSET_H_