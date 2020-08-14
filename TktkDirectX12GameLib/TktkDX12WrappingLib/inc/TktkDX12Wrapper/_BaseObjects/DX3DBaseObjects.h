#ifndef DX3D_BASE_OBJECTS_H_
#define DX3D_BASE_OBJECTS_H_

#include <array>
#include <vector>
#include <dxgi1_6.h> //IDXGIFactory6
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../Includer/D3d12Includer.h"
#include "../SwapChain/SwapChain.h"
#include "../Fence/Fence.h"
#include "../Resource/DX3DResource.h"

namespace tktk
{
	// DirectX12の描画を行うためのメインマネージャー
	class DX3DBaseObjects
	{
	public:

		DX3DBaseObjects(const DX3DResourceNum& initParam, HWND hwnd, const tktkMath::Vector2& windowSize, const tktkMath::Color& backGroundColor, bool craeteDebugLayer);
		~DX3DBaseObjects();

	public: /* 描画開始、終了処理 */

		// 描画開始
		void beginDraw();

		// 描画終了
		void endDraw();

	public: /* リソース作成、ロード処理 */

		// ルートシグネチャを作る
		void createRootSignature(unsigned int id, const RootSignatureInitParam& initParam);

		// パイプラインステートを作る
		void createPipeLineState(unsigned int id, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// 頂点バッファを作る
		void createVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// インデックスバッファを作る
		void createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices);

		// 定数バッファを作る
		void createCBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// レンダーターゲットバッファを作る
		void createRtBuffer(unsigned int id, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// 深度ステンシルバッファを作る
		void createDsBuffer(unsigned int id, const DepthStencilBufferInitParam& initParam);

		// 定数、テクスチャのディスクリプタヒープを作る
		void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		// レンダーターゲットのディスクリプタヒープを作る
		void createRtvDescriptorHeap(unsigned int id, const RtvDescriptorHeapInitParam& initParam);

		// 深度ステンシルビューのディスクリプタヒープを作る
		void createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam);

		// コマンドリストを使わずにテクスチャを作る
		void cpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使ってテクスチャを作る（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		void gpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使わずにテクスチャをロードする
		void cpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);

		// コマンドリストを使ってテクスチャをロードする（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		void gpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);

	public: /* リソース更新処理 */

		// 背景色を設定する
		void setBackGroundColor(const tktkMath::Color& backGroundColor);

		// 指定の頂点バッファを更新する
		void updateVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// 指定のインデックスバッファを更新する
		void updateIndexBuffer(unsigned int id, const std::vector<unsigned short>& indexDataArray);

		// 指定の定数バッファを更新する
		void updateCBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// 指定のレンダーターゲットビューを指定の色でクリアする
		void clearRtv(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color) const;

	public: /* リソース情報取得処理 */

		// 指定のテクスチャのサイズを取得する（ピクセル）
		const tktkMath::Vector3& getTextureBufferSizePx(unsigned int id) const;
		const tktkMath::Vector2& getDsBufferSizePx(unsigned int id) const;
		const tktkMath::Vector2& getRtBufferSizePx(unsigned int id) const;

	public: /* リソースをコマンドリストに登録する処理 */

		// 指定のレンダーターゲット用のディスクリプタヒープをコマンドリストに設定する
		void setRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// 指定の（レンダーターゲットと深度ステンシルビュー）用のディスクリプタヒープ２つをコマンドリストに設定する
		void setRtvAndDsv(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// 指定の深度ステンシルビュー用のディスクリプタヒープをコマンドリストに設定する（※レンダーターゲットは設定できない）
		void setOnlyDsv(unsigned int id) const;

		// バックバッファーを設定する
		void setBackBufferView() const;

		// バックバッファーと深度ステンシルビューを設定する
		void setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapId) const;

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファの書き込み後処理を行う
		void unSetRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファの書き込み後処理を行う
		void unSetDsv(unsigned int dsvDescriptorHeapId) const;

		// 指定のビューポートをコマンドリストに設定する
		void setViewport(unsigned int id) const;

		// 指定のシザー矩形をコマンドリストに設定する
		void setScissorRect(unsigned int id) const;

		// 指定のパイプラインステートをコマンドリストに設定する
		void setPipeLineState(unsigned int id) const;

		// 指定の頂点バッファをコマンドリストに設定する
		void setVertexBuffer(unsigned int id) const;

		// 指定のインデックスバッファをコマンドリストに設定する
		void setIndexBuffer(unsigned int id) const;

		// 指定のディスクリプタヒープの配列をコマンドリストに設定する
		void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray) const;

		// ブレンドファクターを設定する
		void setBlendFactor(const std::array<float, 4>& blendFactor) const;

		// プリミティブトポロジを設定する
		void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology) const;

	public: /* ドローコール、その他処理 */

		// インスタンス描画を行う
		void drawInstanced(
			unsigned int vertexCountPerInstance,
			unsigned int instanceCount,
			unsigned int baseVertexLocation,
			unsigned int startInstanceLocation
		) const;

		// インデックスを使用してインスタンス描画を行う
		void drawIndexedInstanced(
			unsigned int indexCountPerInstance,
			unsigned int instanceCount,
			unsigned int startIndexLocation,
			unsigned int baseVertexLocation,
			unsigned int startInstanceLocation
		) const;

		// コマンドリストを実行する
		void executeCommandList();

	public: /* デフォルトのリソースを使うためのIDを取得する */

		// デフォルトのビューポートIDを取得する
		unsigned int getSystemId(SystemViewportType type) const;

		// デフォルトのシザー矩形IDを取得する
		unsigned int getSystemId(SystemScissorRectType type) const;

		// デフォルトの頂点バッファIDを取得する
		unsigned int getSystemId(SystemVertexBufferType type) const;

		// デフォルトのインデックスバッファIDを取得する
		unsigned int getSystemId(SystemIndexBufferType type) const;

		// デフォルトの定数バッファIDを取得する
		unsigned int getSystemId(SystemCBufferType type) const;

		// デフォルトのテクスチャバッファIDを取得する
		unsigned int getSystemId(SystemTextureBufferType type) const;

		// デフォルトのレンダーターゲットバッファIDを取得する
		unsigned int getSystemId(SystemRtBufferType type) const;

		// デフォルトの深度ステンシルバッファIDを取得する
		unsigned int getSystemId(SystemDsBufferType type) const;

		// デフォルトの通常のディスクリプタヒープIDを取得する
		unsigned int getSystemId(SystemBasicDescriptorHeapType type) const;

		// デフォルトのレンダーターゲット用のディスクリプタヒープIDを取得する
		unsigned int getSystemId(SystemRtvDescriptorHeapType type) const;

		// デフォルトの深度ステンシル用のディスクリプタヒープIDを取得する
		unsigned int getSystemId(SystemDsvDescriptorHeapType type) const;

		// デフォルトのルートシグネチャIDを取得する
		unsigned int getSystemId(SystemRootSignatureType type) const;

		// デフォルトのパイプラインステートIDを取得する
		unsigned int getSystemId(SystemPipeLineStateType type) const;

	private:

		ID3D12Device*				m_device				{ nullptr };
		IDXGIFactory6*				m_factory				{ nullptr };
		ID3D12CommandAllocator*		m_commandAllocator		{ nullptr };
		ID3D12GraphicsCommandList*	m_commandList			{ nullptr };
		ID3D12CommandQueue*			m_commandQueue			{ nullptr };
		SwapChain					m_swapChain				{};
		Fence						m_fence					{};
		DX3DResource				m_dX3DResource;
		tktkMath::Color				m_backGroundColor{ tktkMath::colorBlue };
	};
}
#endif // !DX3D_BASE_OBJECTS_H_