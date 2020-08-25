#ifndef DEPTH_STENCIL_BUFFER_H_
#define DEPTH_STENCIL_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "DepthStencilBufferData.h"

namespace tktk
{
	// 「DepthStencilBufferData」を管理するクラス
	class DepthStencilBuffer
	{
	public:

		explicit DepthStencilBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~DepthStencilBuffer() = default;

	public:

		// 「DepthStencilBufferData」のインスタンスを作り、そのリソースのハンドルを返す
		unsigned int create(ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// 指定の深度ステンシルバッファのリソースバリアを深度書き込み状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void beginWrite(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定の深度ステンシルバッファのリソースバリアをシェーダー使用状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void endWrite(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 全ての深度ステンシルバッファのリソースバリアを深度書き込み状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void allBeginWrite(ID3D12GraphicsCommandList* commandList) const;

		// 全ての深度ステンシルバッファのリソースバリアをシェーダー使用状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void allEndWrite(ID3D12GraphicsCommandList* commandList) const;

		// 指定の深度ステンシルバッファを使用して、引数のディスクリプタハンドルに深度ステンシルビューを作る
		void createDsv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定の深度ステンシルバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		// ※シェーダーリソースとして使用しない設定の場合、エラーを吐きます
		void createSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定の深度ステンシルバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector2& getDepthStencilSizePx(unsigned int handle) const;

	private:

		tktkContainer::ResourceContainer<DepthStencilBufferData> m_depthStencilBufferDataArray;
	};
}
#endif // !DEPTH_STENCIL_BUFFER_H_
