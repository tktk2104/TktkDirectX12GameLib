#ifndef DEPTH_STENCIL_BUFFER_DATA_H_
#define DEPTH_STENCIL_BUFFER_DATA_H_

#include <TktkMath/Structs/Vector2.h>
#include "../../../Includer/D3d12Includer.h"
#include "DepthStencilBufferInitParam.h"

namespace tktk
{
	// 深度バッファを管理するクラス
	class DepthStencilBufferData
	{
	public:

		DepthStencilBufferData(ID3D12Device* device, const DepthStencilBufferInitParam& initParam);
		~DepthStencilBufferData();

		// ムーブコンストラクタ
		DepthStencilBufferData(DepthStencilBufferData&& other) noexcept;

	public:

		// 自身のリソースバリアを深度書き込み状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void beginWrite(ID3D12GraphicsCommandList* commandList) const;

		// 自身のリソースバリアをシェーダー使用状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void endWrite(ID3D12GraphicsCommandList* commandList) const;

		// 引数のディスクリプタハンドルに深度ステンシルビューを作る
		void createDsv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 引数のディスクリプタハンドルにシェーダーリソースビューを作る
		// ※シェーダーリソースとして使用しない設定の場合、エラーを吐きます
		void createSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 深度ステンシルバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector2& getDepthStencilSizePx() const;

	private:

		bool				m_useAsShaderResource;
		tktkMath::Vector2	m_depthStencilSize;
		ID3D12Resource*		m_depthStencilBuffer{ nullptr };
	};
}
#endif // !DEPTH_STENCIL_BUFFER_DATA_H_