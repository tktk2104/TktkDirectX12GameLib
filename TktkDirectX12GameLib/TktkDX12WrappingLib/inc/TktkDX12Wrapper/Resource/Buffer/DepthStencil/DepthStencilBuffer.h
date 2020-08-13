#ifndef DEPTH_STENCIL_BUFFER_H_
#define DEPTH_STENCIL_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "DepthStencilBufferData.h"

namespace tktk
{
	// 「DepthStencilBufferData」を管理するクラス
	class DepthStencilBuffer
	{
	public:

		DepthStencilBuffer(unsigned int depthStencilBufferNum);
		~DepthStencilBuffer() = default;

	public:

		// 「DepthStencilBufferData」のインスタンスを作る
		void create(unsigned int id, ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// 指定の深度ステンシルバッファのリソースバリアを深度書き込み状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void beginWrite(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// 指定の深度ステンシルバッファのリソースバリアをシェーダー使用状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void endWrite(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// 全ての深度ステンシルバッファのリソースバリアを深度書き込み状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void allBeginWrite(ID3D12GraphicsCommandList* commandList) const;

		// 全ての深度ステンシルバッファのリソースバリアをシェーダー使用状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void allEndWrite(ID3D12GraphicsCommandList* commandList) const;

		// 指定の深度ステンシルバッファを使用して、引数のディスクリプタハンドルに深度ステンシルビューを作る
		void createDsv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定の深度ステンシルバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		// ※シェーダーリソースとして使用しない設定の場合、エラーを吐きます
		void createSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定の深度ステンシルバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector2& getDepthStencilSizePx(unsigned int id) const;

	private:

		HeapArray<DepthStencilBufferData> m_depthStencilBufferDataArray;
	};
}
#endif // !DEPTH_STENCIL_BUFFER_H_
