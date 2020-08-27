#ifndef SUBSET_H_
#define SUBSET_H_

namespace tktk
{
	// サブセット（使用するマテリアル情報）
	struct Subset
	{
	public:

		// 使用するマテリアルのID
		unsigned int useMaterialHandle;

		// インデックスバッファの使用開始位置
		unsigned int indexBufferStartPos;

		// インデックスバッファの使用幅
		unsigned int indexBufferUseCount;
	};
}
#endif // !SUBSET_H_