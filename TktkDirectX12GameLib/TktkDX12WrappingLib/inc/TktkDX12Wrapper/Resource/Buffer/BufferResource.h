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

	public: /* バッファ共通の処理 */

		// 全てのアップロード用のバッファを削除する
		void deleteUploadBufferAll();

	public: /* 頂点バッファの処理 */

		// 頂点バッファを作り、そのリソースのハンドルを返す
		unsigned int createVertexBuffer(ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// 指定の頂点バッファを更新する
		// ※アップロードバッファを新規に作成し、そのバッファから自身にコピーする命令をコマンドリストに登録する
		void updateVertexBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// コマンドリストに指定の頂点バッファを登録する
		void setVertexBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

	public: /* インデックスバッファの処理 */

		// インデックスバッファを作り、そのリソースのハンドルを返す
		unsigned int createIndexBuffer(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		// 指定のインデックスバッファを更新する
		// ※アップロードバッファを新規に作成し、そのバッファから自身にコピーする命令をコマンドリストに登録する
		void updateIndexBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray);

		// コマンドリストに指定のインデックスバッファを登録する
		void setIndexBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

	public: /* 定数バッファの処理 */

		// 定数バッファを作り、そのリソースのハンドルを返す
		unsigned int createCBuffer(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// 指定の定数バッファを使用して、引数のディスクリプタハンドルに定数バッファビューを作る
		void createCbv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定の定数バッファを更新する
		// ※アップロードバッファを新規に作成し、そのバッファから自身にコピーする命令をコマンドリストに登録する
		void updateCBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

	public: /* テクスチャバッファの処理 */

		// コマンドリストを使わずにテクスチャバッファを作り、そのリソースのハンドルを返す
		unsigned int cpuPriorityCreateTextureBuffer(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		
		// コマンドリストを使ってテクスチャバッファを作り、そのリソースのハンドルを返す
		unsigned int gpuPriorityCreateTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// 引数のファイルから画像情報をロードし、コマンドリストを使わずにテクスチャバッファを作り、そのリソースのハンドルを返す
		unsigned int cpuPriorityLoadTextureBuffer(ID3D12Device* device, const std::string& texDataPath);
		
		// 引数のファイルから画像情報をロードし、コマンドリストを使ってテクスチャバッファを作り、そのリソースのハンドルを返す
		unsigned int gpuPriorityLoadTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

		// 指定のテクスチャバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定のテクスチャバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector3& getTextureSizePx(unsigned int handle) const;

	public: /* 深度ステンシルバッファの処理 */

		// 深度ステンシルバッファを作り、そのリソースのハンドルを返す
		unsigned int createDsBuffer(ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// 指定の深度ステンシルバッファを使用して、引数のディスクリプタハンドルに深度ステンシルビューを作る
		void createDsv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定の深度ステンシルバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createDsSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定の深度ステンシルバッファのリソースバリアを深度書き込み状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void beginWriteDsBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定の深度ステンシルバッファのリソースバリアをシェーダー使用状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void endWriteDsBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 全ての深度ステンシルバッファのリソースバリアを深度書き込み状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void allBeginWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const;

		// 全ての深度ステンシルバッファのリソースバリアをシェーダー使用状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void allEndWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const;

		// 指定の深度ステンシルバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector2& getDepthStencilSizePx(unsigned int handle) const;

	public: /* レンダーターゲットバッファの処理 */

		// ゼロからレンダーターゲットバッファを作り、そのリソースのハンドルを返す
		unsigned int createRtBuffer(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);
		
		// スワップチェインからレンダーターゲットバッファを作り、そのリソースのハンドルを返す
		unsigned int createRtBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// 指定のレンダーターゲットバッファを使用して、引数のディスクリプタハンドルにレンダーターゲットビューを作る
		void createRtv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定のレンダーターゲットバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createRtSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定のレンダーターゲットバッファのリソースバリアをレンダーターゲット状態に変更する
		void beginWriteBasicRtBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをシェーダー使用状態に変更する
		void endWriteBasicRtBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをレンダーターゲット状態に変更する
		void beginWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをプリセット状態に変更する
		void endWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファ画像の大きさを取得す（ピクセル）
		const tktkMath::Vector2& getRenderTargetSizePx(unsigned int handle) const;

	private:

		std::unique_ptr<VertexBuffer>		m_vertexBuffer;
		std::unique_ptr<IndexBuffer>		m_indexBuffer;
		std::unique_ptr<ConstantBuffer>		m_constantBuffer;
		std::unique_ptr<TextureBuffer>		m_textureBuffer;
		std::unique_ptr<DepthStencilBuffer>	m_depthStencilBuffer;
		std::unique_ptr<RenderTargetBuffer>	m_renderTargetBuffer;
	};
}
#endif // !BUFFER_RESOURCE_H_