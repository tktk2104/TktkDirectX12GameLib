#ifndef DX_3D_RESOURCE_H_
#define DX_3D_RESOURCE_H_

/* std::unique_ptr */
#include <memory>

/* IDXGISwapChain1 */
#include <dxgi1_6.h>

/* ID3D12Device, ID3D12GraphicsCommandList, D3D12_CPU_DESCRIPTOR_HANDLE */
#include <d3d12.h>
#undef min
#undef max

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "DX3DResourceInitParamIncluder.h"
#include "DX3DResourceFuncArgsIncluder.h"
#include "DX3DResourceNum.h"

namespace tktk
{
	// 前方宣言達
	class Viewport;
	class ScissorRect;
	class GraphicsPipeLine;
	class DescriptorHeap;
	class BufferResource;

	// DirectX12のリソースを管理するクラス
	class DX3DResource
	{
	public:

		explicit DX3DResource(const DX3DResourceNum& resNum);
		~DX3DResource();

	public: /* 作成、ロード処理 */

		// ビューポートを作り、そのリソースのハンドルを返す
		size_t createViewport(const std::vector<ViewportInitParam>& initParamArray);

		// シザー矩形を作り、そのリソースのハンドルを返す
		size_t createScissorRect(const std::vector<ScissorRectInitParam>& initParamArray);

		// ルートシグネチャを作り、そのリソースのハンドルを返す
		size_t createRootSignature(ID3D12Device* device, const RootSignatureInitParam& initParam);

		// パイプラインステートを作り、そのリソースのハンドルを返す
		size_t createPipeLineState(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// アップロードバッファを作り、そのリソースのハンドルを返す
		size_t createUploadBuffer(ID3D12Device* device, const UploadBufferInitParam& initParam);

		// アップロードバッファのコピーを作り、そのリソースのハンドルを返す
		size_t duplicateUploadBuffer(ID3D12Device* device, size_t originalHandle);

		// 頂点バッファを作り、そのリソースのハンドルを返す
		size_t createVertexBuffer(ID3D12Device* device, const VertexDataCarrier& vertexData);

		// インデックスバッファを作り、そのリソースのハンドルを返す
		size_t createIndexBuffer(ID3D12Device* device, const std::vector<unsigned short>& indices);

		// 定数バッファを作り、そのリソースのハンドルを返す
		size_t createCBuffer(ID3D12Device* device, const CopySourceDataCarrier& constantBufferData);

		// レンダーターゲットバッファを作り、そのリソースのハンドルを返す
		size_t createRtBuffer(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// スワップチェーンからレンダーターゲットバッファを取得し、そのリソースのハンドルを返す
		size_t createRtBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// 深度ステンシルバッファを作り、そのリソースのハンドルを返す
		size_t createDsBuffer(ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// コマンドリストを使わずにテクスチャバッファを作り、そのリソースのハンドルを返す
		size_t cpuPriorityCreateTextureBuffer(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使ってテクスチャバッファを作り、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		size_t gpuPriorityCreateTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使わずにテクスチャをロードしてバッファを作り、そのリソースのハンドルを返す
		size_t cpuPriorityLoadTextureBuffer(ID3D12Device* device, const std::string& texDataPath);

		// コマンドリストを使ってテクスチャをロードしてバッファを作り、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		size_t gpuPriorityLoadTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

		// 定数、テクスチャのディスクリプタヒープを作り、そのリソースのハンドルを返す
		size_t createBasicDescriptorHeap(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		// レンダーターゲットのディスクリプタヒープを作り、そのリソースのハンドルを返す
		size_t createRtvDescriptorHeap(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);

		// 深度ステンシルのディスクリプタヒープを作り、そのリソースのハンドルを返す
		size_t createDsvDescriptorHeap(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

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

	public: /* リソース更新系処理 */

		// 引数のポインタのデータを指定のアップロードバッファにコピーする
		void updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData);

		// 指定の頂点バッファをコマンドリストを使わずに更新する
		void updateVertexBuffer(size_t handle, const VertexDataCarrier& vertexData);

		// 指定のアップロードバッファの内容を設定したバッファにアップロードするGPU命令を行う
		void copyBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットビューを事前に設定したクリアカラーでクリアする
		void clearRtv(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t rtvLocationIndex) const;

		// 全てのデプスステンシルビューをクリアする
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	public: /* リソース情報取得系処理 */

		// 指定のバッファのテクスチャとしてのサイズを取得する（ピクセル）
		const tktkMath::Vector3& getTextureBufferSizePx(size_t handle) const;
		const tktkMath::Vector2& getDsBufferSizePx(size_t handle) const;
		const tktkMath::Vector2& getRtBufferSizePx(size_t handle) const;

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファーのIDを取得する
		const std::vector<size_t>& getRtvDescriptorHeapUseBufferHandleArray(size_t handle) const;

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファーのIDを取得する
		const std::vector<size_t>& getDsvDescriptorHeapUseBufferHandleArray(size_t handle) const;

	public: /* 描画準備 */

		// レンダーターゲットビューをコマンドリストに設定する
		void setRtv(size_t rtvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, size_t rtvCount) const;

		// レンダーターゲットビューと深度ステンシルビューをコマンドリストに設定する
		void setRtvAndDsv(size_t rtvDescriptorHeapHandle, size_t dsvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, size_t rtvCount) const;

		// 深度ステンシルビューをコマンドリストに設定する
		// ※レンダーターゲットビューは設定できない
		void setOnlyDsv(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// バックバッファービューを設定する
		void setBackBufferView(size_t backBufferRtvDescriptorHeap, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const;

		// バックバッファービューと深度ステンシルビューを設定する
		void setBackBufferViewAndDsv(size_t backBufferRtvDescriptorHeap, size_t dsvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const;

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファの書き込み後処理を行う
		void unSetRtv(size_t rtvDescriptorHeapHandle, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, size_t rtvCount) const;

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファの書き込み後処理を行う
		void unSetDsv(size_t dsvDescriptorHeapHandle, ID3D12GraphicsCommandList* commandList) const;

		// バックバッファをレンダーターゲット状態にする
		// TODO : 「unsigned int id」を「unsigned int backBufferIndex」に変更する
		void beginWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// バックバッファをプリセット状態にする
		// TODO : 「unsigned int id」を「unsigned int backBufferIndex」に変更する
		void endWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のビューポートをコマンドリストに設定する
		void setViewport(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のシザー矩形をコマンドリストに設定する
		void setScissorRect(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のパイプラインステートをコマンドリストに設定する
		void setPipeLineState(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定の頂点バッファをコマンドリストに設定する
		void setVertexBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// コマンドリストに指定の頂点バッファを登録する（インスタンス描画用）
		void setVertexBuffer(size_t meshVertHandle, size_t instancingVertHandle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のインデックスバッファをコマンドリストに設定する
		void setIndexBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のディスクリプタヒープの配列をコマンドリストに設定する
		void setDescriptorHeap(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray) const;

	private:

		// 引数のバッファ情報が定数バッファであれば定数バッファビューを作り、そうでなければエラーを吐く
		void createBasicDescriptorCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const;

		// 引数のバッファ情報がシェーダーリソースになれるバッファであればシェーダーリソースビューを作り、そうでなければエラーを吐く
		void createBasicDescriptorSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const;

	private:

		std::unique_ptr<Viewport>					m_viewport;
		std::unique_ptr<ScissorRect>				m_scissorRect;
		std::unique_ptr<GraphicsPipeLine>			m_graphicsPipeLine;
		std::unique_ptr<DescriptorHeap>				m_descriptorHeap;
		std::unique_ptr<BufferResource>				m_bufferResource;
	};
}
#endif // !DX_3D_RESOURCE_H_