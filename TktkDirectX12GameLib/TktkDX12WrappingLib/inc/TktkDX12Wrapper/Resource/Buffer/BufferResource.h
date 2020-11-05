#ifndef BUFFER_RESOURCE_H_
#define BUFFER_RESOURCE_H_

#include <memory>		// std::unique_ptr
#include <dxgi1_6.h>	// swapChain
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "../../Includer/D3d12Includer.h"
#include "BufferResourceInitParamIncluder.h"
#include "BufferResourceNum.h"

namespace tktk
{
	// 前方宣言達
	class UploadBuffer;
	class VertexBuffer;
	class IndexBuffer;
	class ConstantBuffer;
	class TextureBuffer;
	class DepthStencilBuffer;
	class RenderTargetBuffer;

	// ６種類のバッファリソースを管理するクラス
	class BufferResource
	{
	public:

		explicit BufferResource(const BufferResourceNum& initParam);
		~BufferResource();

	public: /* アップロードバッファの処理 */

		// アップロードバッファを作り、そのリソースのハンドルを返す
		size_t createUploadBuffer(ID3D12Device* device, const UploadBufferInitParam& initParam);

		// アップロードバッファのコピーを作り、そのリソースのハンドルを返す
		size_t duplicateUploadBuffer(ID3D12Device* device, size_t originalHandle);

		// 指定のアップロードバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseUploadBuffer(size_t handle);

		// 引数のポインタのデータを指定のアップロードバッファにコピーする
		void updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData);

		// 指定のアップロードバッファの内容を設定したバッファにアップロードするGPU命令を設定する
		void copyBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

	public: /* 頂点バッファの処理 */

		// 頂点バッファを作り、そのリソースのハンドルを返す
		size_t createVertexBuffer(ID3D12Device* device, const VertexDataCarrier& vertexData);

		// 指定の頂点バッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseVertexBuffer(size_t handle);

		// コマンドリストに指定の頂点バッファを登録する
		void setVertexBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

	public: /* インデックスバッファの処理 */

		// インデックスバッファを作り、そのリソースのハンドルを返す
		size_t createIndexBuffer(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		// 指定のインデックスバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseIndexBuffer(size_t handle);

		// コマンドリストに指定のインデックスバッファを登録する
		void setIndexBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

	public: /* 定数バッファの処理 */

		// 定数バッファを作り、そのリソースのハンドルを返す
		size_t createCBuffer(ID3D12Device* device, const CopySourceDataCarrier& constantBufferData);

		// 指定の定数バッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseCBuffer(size_t handle);

		// 指定の定数バッファを使用して、引数のディスクリプタハンドルに定数バッファビューを作る
		void createCbv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

	public: /* テクスチャバッファの処理 */

		// コマンドリストを使わずにテクスチャバッファを作り、そのリソースのハンドルを返す
		size_t cpuPriorityCreateTextureBuffer(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		
		// コマンドリストを使ってテクスチャバッファを作り、そのリソースのハンドルを返す
		size_t gpuPriorityCreateTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// 引数のファイルから画像情報をロードし、コマンドリストを使わずにテクスチャバッファを作り、そのリソースのハンドルを返す
		size_t cpuPriorityLoadTextureBuffer(ID3D12Device* device, const std::string& texDataPath);
		
		// 引数のファイルから画像情報をロードし、コマンドリストを使ってテクスチャバッファを作り、そのリソースのハンドルを返す
		size_t gpuPriorityLoadTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

		// 指定のテクスチャバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseTextureBuffer(size_t handle);

		// 指定のテクスチャバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定のテクスチャバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector3& getTextureSizePx(size_t handle) const;

	public: /* 深度ステンシルバッファの処理 */

		// 深度ステンシルバッファを作り、そのリソースのハンドルを返す
		size_t createDsBuffer(ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// 指定の深度ステンシルバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseDsBuffer(size_t handle);

		// 指定の深度ステンシルバッファを使用して、引数のディスクリプタハンドルに深度ステンシルビューを作る
		void createDsv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定の深度ステンシルバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createDsSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定の深度ステンシルバッファのリソースバリアを深度書き込み状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void beginWriteDsBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定の深度ステンシルバッファのリソースバリアをシェーダー使用状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void endWriteDsBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 全ての深度ステンシルバッファのリソースバリアを深度書き込み状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void allBeginWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const;

		// 全ての深度ステンシルバッファのリソースバリアをシェーダー使用状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void allEndWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const;

		// 指定の深度ステンシルバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector2& getDepthStencilSizePx(size_t handle) const;

	public: /* レンダーターゲットバッファの処理 */

		// ゼロからレンダーターゲットバッファを作り、そのリソースのハンドルを返す
		size_t createRtBuffer(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);
		
		// スワップチェインからレンダーターゲットバッファを作り、そのリソースのハンドルを返す
		size_t createRtBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// 指定のレンダーターゲットバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseRtBuffer(size_t handle);

		// 指定のレンダーターゲットバッファを使用して、引数のディスクリプタハンドルにレンダーターゲットビューを作る
		void createRtv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定のレンダーターゲットバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createRtSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定のレンダーターゲットバッファのリソースバリアをレンダーターゲット状態に変更する
		void beginWriteBasicRtBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをシェーダー使用状態に変更する
		void endWriteBasicRtBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをレンダーターゲット状態に変更する
		void beginWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをプリセット状態に変更する
		void endWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファ画像の大きさを取得す（ピクセル）
		const tktkMath::Vector2& getRenderTargetSizePx(size_t handle) const;

	private:

		std::unique_ptr<UploadBuffer>		m_uploadBuffer;
		std::unique_ptr<VertexBuffer>		m_vertexBuffer;
		std::unique_ptr<IndexBuffer>		m_indexBuffer;
		std::unique_ptr<ConstantBuffer>		m_constantBuffer;
		std::unique_ptr<TextureBuffer>		m_textureBuffer;
		std::unique_ptr<DepthStencilBuffer>	m_depthStencilBuffer;
		std::unique_ptr<RenderTargetBuffer>	m_renderTargetBuffer;
	};
}
#endif // !BUFFER_RESOURCE_H_