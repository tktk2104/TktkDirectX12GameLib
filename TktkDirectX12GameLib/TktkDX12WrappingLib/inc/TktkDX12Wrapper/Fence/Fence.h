#ifndef FENCE_H_
#define FENCE_H_

#include "../Includer/D3d12Includer.h"

namespace tktk
{
	// GPUの処理を待つフェンスを管理するクラス
	class Fence
	{
	public:

		Fence() = default;
		~Fence();

	public:

		// 初期化
		void initialize(ID3D12Device* device);

		// GPUの処理が終わるまで待機する
		void waitGpuProcess(ID3D12CommandQueue* commandQueue);

	private:

		ID3D12Fence* m_fence{ nullptr };
		unsigned int m_fenceVal{ 0U };
	};
}
#endif // !FENCE_H_