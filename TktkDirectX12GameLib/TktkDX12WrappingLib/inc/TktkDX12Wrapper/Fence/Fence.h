#ifndef FENCE_H_
#define FENCE_H_

/* ID3D12Fence, ID3D12CommandQueue */
#include <d3d12.h>
#undef min
#undef max

namespace tktk
{
	// GPUの処理を待つフェンスを管理するクラス
	class Fence
	{
	public:

		explicit Fence(ID3D12Device* device);
		~Fence();

	public:

		// GPUの処理が終わるまで待機する
		void waitGpuProcess(ID3D12CommandQueue* commandQueue);

	private:

		ID3D12Fence* m_fence{ nullptr };
		unsigned int m_fenceVal{ 0U };
	};
}
#endif // !FENCE_H_