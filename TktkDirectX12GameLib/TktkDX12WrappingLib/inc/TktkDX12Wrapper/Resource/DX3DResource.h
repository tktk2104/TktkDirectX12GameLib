#ifndef DX_3D_RESOURCE_H_
#define DX_3D_RESOURCE_H_

#include <memory>		// std::unique_ptr
#include <dxgi1_6.h>	// swapChain
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "../Includer/D3d12Includer.h"
#include "DX3DResourceInitParamIncluder.h"
#include "DX3DResourceFuncArgsIncluder.h"
#include "DX3DResourceNum.h"

namespace tktk
{
	// 前方宣言達
	class SystemResourceHandleGetter;
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
		unsigned int createViewport(const std::vector<ViewportInitParam>& initParamArray);

		// シザー矩形を作り、そのリソースのハンドルを返す
		unsigned int createScissorRect(const std::vector<ScissorRectInitParam>& initParamArray);

		// ルートシグネチャを作り、そのリソースのハンドルを返す
		unsigned int createRootSignature(ID3D12Device* device, const RootSignatureInitParam& initParam);

		// パイプラインステートを作り、そのリソースのハンドルを返す
		unsigned int createPipeLineState(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// コピーバッファを作り、そのリソースのハンドルを返す
		unsigned int createCopyBuffer(ID3D12Device* device, const CopyBufferInitParam& initParam);

		// コピーバッファのコピーを作り、そのリソースのハンドルを返す
		unsigned int copyCopyBuffer(ID3D12Device* device, unsigned int originalHandle);

		// 頂点バッファを作り、そのリソースのハンドルを返す
		unsigned int createVertexBuffer(ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// インデックスバッファを作り、そのリソースのハンドルを返す
		unsigned int createIndexBuffer(ID3D12Device* device, const std::vector<unsigned short>& indices);

		// 定数バッファを作り、そのリソースのハンドルを返す
		unsigned int createCBuffer(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// レンダーターゲットバッファを作り、そのリソースのハンドルを返す
		unsigned int createRtBuffer(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// スワップチェーンからレンダーターゲットバッファを取得し、そのリソースのハンドルを返す
		unsigned int createRtBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// 深度ステンシルバッファを作り、そのリソースのハンドルを返す
		unsigned int createDsBuffer(ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// コマンドリストを使わずにテクスチャバッファを作り、そのリソースのハンドルを返す
		unsigned int cpuPriorityCreateTextureBuffer(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使ってテクスチャバッファを作り、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		unsigned int gpuPriorityCreateTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使わずにテクスチャをロードしてバッファを作り、そのリソースのハンドルを返す
		unsigned int cpuPriorityLoadTextureBuffer(ID3D12Device* device, const std::string& texDataPath);

		// コマンドリストを使ってテクスチャをロードしてバッファを作り、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		unsigned int gpuPriorityLoadTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

		// 定数、テクスチャのディスクリプタヒープを作り、そのリソースのハンドルを返す
		unsigned int createBasicDescriptorHeap(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		// レンダーターゲットのディスクリプタヒープを作り、そのリソースのハンドルを返す
		unsigned int createRtvDescriptorHeap(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);

		// 深度ステンシルのディスクリプタヒープを作り、そのリソースのハンドルを返す
		unsigned int createDsvDescriptorHeap(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

	public: /* リソース削除処理 */

		// 指定のビューポートを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseViewport(unsigned int handle);

		// 指定のシザー矩形を削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseScissorRect(unsigned int handle);

		// 指定のルートシグネチャを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseRootSignature(unsigned int handle);

		// 指定のパイプラインステートを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erasePipeLineState(unsigned int handle);

		// 指定のコピーバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseCopyBuffer(unsigned int handle);

		// 指定の頂点バッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseVertexBuffer(unsigned int handle);

		// 指定のインデックスバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseIndexBuffer(unsigned int handle);

		// 指定の定数バッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseCBuffer(unsigned int handle);

		// 指定のテクスチャバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseTextureBuffer(unsigned int handle);

		// 指定の深度ステンシルバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseDsBuffer(unsigned int handle);

		// 指定のレンダーターゲットバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseRtBuffer(unsigned int handle);

		// 指定の通常のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseBasicDescriptorHeap(unsigned int handle);

		// 指定のレンダーターゲット用のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseRtvDescriptorHeap(unsigned int handle);

		// 指定の深度ステンシル用のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseDsvDescriptorHeap(unsigned int handle);

	public: /* リソース更新系処理 */

		// 引数のポインタのデータを指定のコピーバッファにコピーする
		void updateCopyBuffer(unsigned int handle, unsigned int bufferSize, const void* bufferDataTopPos);

		// 指定のコピーバッファの内容を設定したバッファにコピーするGPU命令を設定する
		void copyBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットビューを指定の色でクリアする
		void clearRtv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color) const;

		// 全てのデプスステンシルビューをクリアする
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	public: /* リソース情報取得系処理 */

		// 指定のバッファのテクスチャとしてのサイズを取得する（ピクセル）
		const tktkMath::Vector3& getTextureBufferSizePx(unsigned int handle) const;
		const tktkMath::Vector2& getDsBufferSizePx(unsigned int handle) const;
		const tktkMath::Vector2& getRtBufferSizePx(unsigned int handle) const;

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファーのIDを取得する
		const std::vector<unsigned int>& getRtvDescriptorHeapUseBufferIdArray(unsigned int handle) const;

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファーのIDを取得する
		const std::vector<unsigned int>& getDsvDescriptorHeapUseBufferIdArray(unsigned int handle) const;

	public: /* 描画準備 */

		// レンダーターゲットビューをコマンドリストに設定する
		void setRtv(unsigned int rtvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// レンダーターゲットビューと深度ステンシルビューをコマンドリストに設定する
		void setRtvAndDsv(unsigned int rtvDescriptorHeapHandle, unsigned int dsvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// 深度ステンシルビューをコマンドリストに設定する
		// ※レンダーターゲットビューは設定できない
		void setOnlyDsv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// バックバッファービューを設定する
		void setBackBufferView(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const;

		// バックバッファービューと深度ステンシルビューを設定する
		void setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const;

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファの書き込み後処理を行う
		void unSetRtv(unsigned int rtvDescriptorHeapHandle, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファの書き込み後処理を行う
		void unSetDsv(unsigned int dsvDescriptorHeapHandle, ID3D12GraphicsCommandList* commandList) const;

		// バックバッファをレンダーターゲット状態にする
		// TODO : 「unsigned int id」を「unsigned int backBufferIndex」に変更する
		void beginWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// バックバッファをプリセット状態にする
		// TODO : 「unsigned int id」を「unsigned int backBufferIndex」に変更する
		void endWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のビューポートをコマンドリストに設定する
		void setViewport(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のシザー矩形をコマンドリストに設定する
		void setScissorRect(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のパイプラインステートをコマンドリストに設定する
		void setPipeLineState(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定の頂点バッファをコマンドリストに設定する
		void setVertexBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のインデックスバッファをコマンドリストに設定する
		void setIndexBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のディスクリプタヒープの配列をコマンドリストに設定する
		void setDescriptorHeap(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray) const;

	public: /* システムのリソースを使うためのハンドルを取得する */

		// システムのビューポートハンドルを取得する
		unsigned int getSystemHandle(SystemViewportType type) const;

		// システムのシザー矩形ハンドルを取得する
		unsigned int getSystemHandle(SystemScissorRectType type) const;

		// システムの頂点バッファハンドルを取得する
		unsigned int getSystemHandle(SystemVertexBufferType type) const;

		// システムのインデックスバッファハンドルを取得する
		unsigned int getSystemHandle(SystemIndexBufferType type) const;

		// システムの定数バッファハンドルを取得する
		unsigned int getSystemHandle(SystemCBufferType type) const;

		// システムのテクスチャバッファハンドルを取得する
		unsigned int getSystemHandle(SystemTextureBufferType type) const;

		// システムのレンダーターゲットバッファハンドルを取得する
		unsigned int getSystemHandle(SystemRtBufferType type) const;

		// システムの深度ステンシルバッファハンドルを取得する
		unsigned int getSystemHandle(SystemDsBufferType type) const;

		// システムの通常のディスクリプタヒープハンドルを取得する
		unsigned int getSystemHandle(SystemBasicDescriptorHeapType type) const;

		// システムのレンダーターゲット用のディスクリプタヒープハンドルを取得する
		unsigned int getSystemHandle(SystemRtvDescriptorHeapType type) const;

		// システムの深度ステンシル用のディスクリプタヒープハンドルを取得する
		unsigned int getSystemHandle(SystemDsvDescriptorHeapType type) const;

		// システムのルートシグネチャハンドルを取得する
		unsigned int getSystemHandle(SystemRootSignatureType type) const;

		// システムのパイプラインステートハンドルを取得する
		unsigned int getSystemHandle(SystemPipeLineStateType type) const;

	public: /* システムのリソースを使うためのハンドルとシステムのリソースの種類を結びつける */

		void setSystemHandle(SystemViewportType type,				unsigned int handle);
		void setSystemHandle(SystemScissorRectType type,			unsigned int handle);
		void setSystemHandle(SystemVertexBufferType type,			unsigned int handle);
		void setSystemHandle(SystemIndexBufferType type,			unsigned int handle);
		void setSystemHandle(SystemCBufferType type,				unsigned int handle);
		void setSystemHandle(SystemTextureBufferType type,			unsigned int handle);
		void setSystemHandle(SystemRtBufferType type,				unsigned int handle);
		void setSystemHandle(SystemDsBufferType type,				unsigned int handle);
		void setSystemHandle(SystemBasicDescriptorHeapType type,	unsigned int handle);
		void setSystemHandle(SystemRtvDescriptorHeapType type,		unsigned int handle);
		void setSystemHandle(SystemDsvDescriptorHeapType type,		unsigned int handle);
		void setSystemHandle(SystemRootSignatureType type,			unsigned int handle);
		void setSystemHandle(SystemPipeLineStateType type,			unsigned int handle);

	private:

		// 引数のバッファ情報が定数バッファであれば定数バッファビューを作り、そうでなければエラーを吐く
		void createBasicDescriptorCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const;

		// 引数のバッファ情報がシェーダーリソースになれるバッファであればシェーダーリソースビューを作り、そうでなければエラーを吐く
		void createBasicDescriptorSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const;

	private:

		std::unique_ptr<SystemResourceHandleGetter>	m_sysResHandleGetter;
		std::unique_ptr<Viewport>					m_viewport;
		std::unique_ptr<ScissorRect>				m_scissorRect;
		std::unique_ptr<GraphicsPipeLine>			m_graphicsPipeLine;
		std::unique_ptr<DescriptorHeap>				m_descriptorHeap;
		std::unique_ptr<BufferResource>				m_bufferResource;
	};
}
#endif // !DX_3D_RESOURCE_H_