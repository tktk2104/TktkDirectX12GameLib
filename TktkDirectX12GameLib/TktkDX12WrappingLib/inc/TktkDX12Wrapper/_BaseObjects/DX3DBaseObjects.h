#ifndef DX3D_BASE_OBJECTS_H_
#define DX3D_BASE_OBJECTS_H_

#include <memory>
#include <array>
#include <dxgi1_6.h> //IDXGIFactory6
#include <TktkMath/Structs/Vector3.h>
#include "../Includer/D3d12Includer.h"
#include "DX3DBaseObjectsInitParamIncluder.h"
#include "DX3DBaseObjectsFuncArgsIncluder.h"
#include "DX3DBaseObjectsInitParam.h"

namespace tktk
{
	// 前方宣言達
	class SwapChain;
	class Fence;
	class DX3DResource;

	// DirectX12の描画を行うためのメインマネージャー
	class DX3DBaseObjects
	{
	public:

		explicit DX3DBaseObjects(const DX3DBaseObjectsInitParam& initParam);
		~DX3DBaseObjects();

	public: /* 描画開始、終了処理 */

		// 描画開始
		void beginDraw();

		// 描画終了
		void endDraw();

	public: /* リソース作成、ロード処理 */

		// ルートシグネチャを作り、そのリソースのハンドルを返す
		size_t createRootSignature(const RootSignatureInitParam& initParam);

		// パイプラインステートを作り、そのリソースのハンドルを返す
		size_t createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// アップロードバッファを作り、そのリソースのハンドルを返す
		size_t createUploadBuffer(const UploadBufferInitParam& initParam);

		// アップロードバッファのコピーを作り、そのリソースのハンドルを返す
		size_t duplicateUploadBuffer(size_t originalHandle);

		// 頂点バッファを作り、そのリソースのハンドルを返す
		size_t createVertexBuffer(const VertexDataCarrier& vertexData);

		// インデックスバッファを作り、そのリソースのハンドルを返す
		size_t createIndexBuffer(const std::vector<unsigned short>& indices);

		// 定数バッファを作り、そのリソースのハンドルを返す
		size_t createCBuffer(const CopySourceDataCarrier& constantBufferData);

		// レンダーターゲットバッファを作り、そのリソースのハンドルを返す
		size_t createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// 深度ステンシルバッファを作り、そのリソースのハンドルを返す
		size_t createDsBuffer(const DepthStencilBufferInitParam& initParam);

		// 定数、テクスチャのディスクリプタヒープを作り、そのリソースのハンドルを返す
		size_t createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam);

		// レンダーターゲットのディスクリプタヒープを作り、そのリソースのハンドルを返す
		size_t createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam);

		// 深度ステンシルビューのディスクリプタヒープを作り、そのリソースのハンドルを返す
		size_t createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam);

		// コマンドリストを使わずにテクスチャを作り、そのリソースのハンドルを返す
		size_t cpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使ってテクスチャを作り、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		size_t gpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使わずにテクスチャをロードし、そのリソースのハンドルを返す
		size_t cpuPriorityLoadTextureBuffer(const std::string& texDataPath);

		// コマンドリストを使ってテクスチャをロードし、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		size_t gpuPriorityLoadTextureBuffer(const std::string& texDataPath);

	public: /* リソース削除処理 */

		// 指定のビューポートを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseViewport(size_t handle);

		// 指定のシザー矩形を削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseScissorRect(size_t handle);

		// 指定のルートシグネチャを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseRootSignature(size_t handle);

		// 指定のパイプラインステートを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erasePipeLineState(size_t handle);

		// 指定のアップロードバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseUploadBuffer(size_t handle);

		// 指定の頂点バッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseVertexBuffer(size_t handle);

		// 指定のインデックスバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseIndexBuffer(size_t handle);

		// 指定の定数バッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseCBuffer(size_t handle);

		// 指定のテクスチャバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseTextureBuffer(size_t handle);

		// 指定の深度ステンシルバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseDsBuffer(size_t handle);

		// 指定のレンダーターゲットバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseRtBuffer(size_t handle);

		// 指定の通常のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseBasicDescriptorHeap(size_t handle);

		// 指定のレンダーターゲット用のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseRtvDescriptorHeap(size_t handle);

		// 指定の深度ステンシル用のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseDsvDescriptorHeap(size_t handle);

	public: /* リソース更新処理 */

		// 背景色を設定する
		void setBackGroundColor(const tktkMath::Color& backGroundColor);

		// 引数のポインタのデータを指定のアップロードバッファにコピーする
		void updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData);

		// 指定のアップロードバッファの内容を設定したバッファにアップロードするGPU命令を行う
		void copyBuffer(size_t handle) const;

		// 指定のレンダーターゲットビューを指定の色でクリアする
		void clearRtv(size_t handle, size_t rtvLocationIndex, const tktkMath::Color& color) const;

	public: /* リソース情報取得処理 */

		// 指定のテクスチャのサイズを取得する（ピクセル）
		const tktkMath::Vector3& getTextureBufferSizePx(size_t handle) const;
		const tktkMath::Vector2& getDsBufferSizePx(size_t handle) const;
		const tktkMath::Vector2& getRtBufferSizePx(size_t handle) const;

	public: /* リソースをコマンドリストに登録する処理 */

		// 指定のレンダーターゲット用のディスクリプタヒープをコマンドリストに設定する
		void setRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const;

		// 指定の（レンダーターゲットと深度ステンシルビュー）用のディスクリプタヒープ２つをコマンドリストに設定する
		void setRtvAndDsv(size_t rtvDescriptorHeapHandle, size_t dsvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const;

		// 指定の深度ステンシルビュー用のディスクリプタヒープをコマンドリストに設定する（※レンダーターゲットは設定できない）
		void setOnlyDsv(size_t handle) const;

		// バックバッファーを設定する
		void setBackBufferView() const;

		// バックバッファーと深度ステンシルビューを設定する
		void setBackBufferViewAndDsv(size_t dsvDescriptorHeapHandle) const;

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファの書き込み後処理を行う
		void unSetRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const;

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファの書き込み後処理を行う
		void unSetDsv(size_t dsvDescriptorHeapHandle) const;

		// 指定のビューポートをコマンドリストに設定する
		void setViewport(size_t handle) const;

		// 指定のシザー矩形をコマンドリストに設定する
		void setScissorRect(size_t handle) const;

		// 指定のパイプラインステートをコマンドリストに設定する
		void setPipeLineState(size_t handle) const;

		// 指定の頂点バッファをコマンドリストに設定する
		void setVertexBuffer(size_t handle) const;

		// 指定のインデックスバッファをコマンドリストに設定する
		void setIndexBuffer(size_t handle) const;

		// 指定のディスクリプタヒープの配列をコマンドリストに設定する
		void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray) const;

		// ブレンドファクターを設定する
		void setBlendFactor(const std::array<float, 4>& blendFactor) const;

		// プリミティブトポロジを設定する
		void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology) const;

	public: /* ドローコール、その他処理 */

		// インスタンス描画を行う
		void drawInstanced(
			size_t vertexCountPerInstance,
			size_t instanceCount,
			size_t baseVertexLocation,
			size_t startInstanceLocation
		) const;

		// インデックスを使用してインスタンス描画を行う
		void drawIndexedInstanced(
			size_t indexCountPerInstance,
			size_t instanceCount,
			size_t startIndexLocation,
			size_t baseVertexLocation,
			size_t startInstanceLocation
		) const;

		// コマンドリストを実行する
		void executeCommandList();

	public: /* システムのリソースを使うためのハンドルを取得する */

		// システムのビューポートハンドルを取得する
		size_t getSystemHandle(SystemViewportType type) const;

		// システムのシザー矩形ハンドルを取得する
		size_t getSystemHandle(SystemScissorRectType type) const;

		// システムの頂点バッファハンドルを取得する
		size_t getSystemHandle(SystemVertexBufferType type) const;

		// システムのインデックスバッファハンドルを取得する
		size_t getSystemHandle(SystemIndexBufferType type) const;

		// システムの定数バッファハンドルを取得する
		size_t getSystemHandle(SystemCBufferType type) const;

		// システムのテクスチャバッファハンドルを取得する
		size_t getSystemHandle(SystemTextureBufferType type) const;

		// システムのレンダーターゲットバッファハンドルを取得する
		size_t getSystemHandle(SystemRtBufferType type) const;

		// システムの深度ステンシルバッファハンドルを取得する
		size_t getSystemHandle(SystemDsBufferType type) const;

		// システムの通常のディスクリプタヒープハンドルを取得する
		size_t getSystemHandle(SystemBasicDescriptorHeapType type) const;

		// システムのレンダーターゲット用のディスクリプタヒープハンドルを取得する
		size_t getSystemHandle(SystemRtvDescriptorHeapType type) const;

		// システムの深度ステンシル用のディスクリプタヒープハンドルを取得する
		size_t getSystemHandle(SystemDsvDescriptorHeapType type) const;

		// システムのルートシグネチャハンドルを取得する
		size_t getSystemHandle(SystemRootSignatureType type) const;

		// システムのパイプラインステートハンドルを取得する
		size_t getSystemHandle(SystemPipeLineStateType type) const;

	public: /* システムのリソースを使うためのハンドルとシステムのリソースの種類を結びつける */

		void setSystemHandle(SystemViewportType type,				size_t handle);
		void setSystemHandle(SystemScissorRectType type,			size_t handle);
		void setSystemHandle(SystemVertexBufferType type,			size_t handle);
		void setSystemHandle(SystemIndexBufferType type,			size_t handle);
		void setSystemHandle(SystemCBufferType type,				size_t handle);
		void setSystemHandle(SystemTextureBufferType type,			size_t handle);
		void setSystemHandle(SystemRtBufferType type,				size_t handle);
		void setSystemHandle(SystemDsBufferType type,				size_t handle);
		void setSystemHandle(SystemBasicDescriptorHeapType type,	size_t handle);
		void setSystemHandle(SystemRtvDescriptorHeapType type,		size_t handle);
		void setSystemHandle(SystemDsvDescriptorHeapType type,		size_t handle);
		void setSystemHandle(SystemRootSignatureType type,			size_t handle);
		void setSystemHandle(SystemPipeLineStateType type,			size_t handle);

	private:

		ID3D12Device*					m_device				{ nullptr };
		IDXGIFactory6*					m_factory				{ nullptr };
		ID3D12CommandAllocator*			m_commandAllocator		{ nullptr };
		ID3D12GraphicsCommandList*		m_commandList			{ nullptr };
		ID3D12CommandQueue*				m_commandQueue			{ nullptr };
		std::unique_ptr<SwapChain>		m_swapChain;
		std::unique_ptr<Fence>			m_fence;
		std::unique_ptr<DX3DResource>	m_dX3DResource;
		tktkMath::Color					m_backGroundColor		{ tktkMath::Color_v::blue };
	};
}
#endif // !DX3D_BASE_OBJECTS_H_