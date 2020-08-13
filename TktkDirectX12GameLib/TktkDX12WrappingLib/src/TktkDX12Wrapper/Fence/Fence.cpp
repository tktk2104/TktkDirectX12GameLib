#include "TktkDX12Wrapper/Fence/Fence.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	Fence::~Fence()
	{
		if (m_fence != nullptr)
		{
			m_fence->Release();
		}
	}

	void Fence::initialize(ID3D12Device* device)
	{
		device->CreateFence(m_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
	}

	void Fence::waitGpuProcess(ID3D12CommandQueue* commandQueue)
	{
		// GPU処理が終わった事を検知するための準備
		commandQueue->Signal(m_fence, ++m_fenceVal);

		// もしGPU処理が終わっていなければ
		if (m_fence->GetCompletedValue() != m_fenceVal)
		{
			// イベントを作ってそのハンドルを取得
			auto eventHandle = CreateEvent(nullptr, false, false, nullptr);

			// フェンスにGPU処理が終わったらイベントを発生させる事を設定する
			m_fence->SetEventOnCompletion(m_fenceVal, eventHandle);

#ifdef _DEBUG
			if (eventHandle == nullptr) throw std::runtime_error("EventHandle Fraud Ptr");
#else
			if (eventHandle == nullptr) return;
#endif // _DEBUG

			// フェンスに指定したイベントが発生するまで無限に待ち続ける
			WaitForSingleObject(eventHandle, INFINITE);

			// イベントハンドルを閉じる
			CloseHandle(eventHandle);
		}
	}
}