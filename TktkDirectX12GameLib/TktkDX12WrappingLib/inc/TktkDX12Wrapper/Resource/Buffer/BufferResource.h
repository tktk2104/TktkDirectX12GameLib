#ifndef BUFFER_RESOURCE_H_
#define BUFFER_RESOURCE_H_

#include "BufferResourceInitParam.h"
#include "Vertex/VertexBuffer.h"
#include "Index/IndexBuffer.h"
#include "Constant/ConstantBuffer.h"
#include "Texture/TextureBuffer.h"
#include "DepthStencil/DepthStencilBuffer.h"
#include "RenderTarget/RenderTargetBuffer.h"

namespace tktk
{
	// ６種類のバッファリソースを管理するクラス
	class BufferResource
	{
	public:

		BufferResource(const BufferResourceInitParam& initParam);
		~BufferResource() = default;

	public: /* バッファ共通の処理 */

		// 全てのアップロード用のバッファを削除する
		void deleteUploadBufferAll();

	public: /* 頂点バッファの処理 */

		// 頂点バッファを作る
		void createVertexBuffer(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// 指定の頂点バッファを更新する
		// ※アップロードバッファを新規に作成し、そのバッファから自身にコピーする命令をコマンドリストに登録する
		void updateVertexBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// コマンドリストに指定の頂点バッファを登録する
		void setVertexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	public: /* インデックスバッファの処理 */

		// インデックスバッファを作る
		void createIndexBuffer(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		// 指定のインデックスバッファを更新する
		// ※アップロードバッファを新規に作成し、そのバッファから自身にコピーする命令をコマンドリストに登録する
		void updateIndexBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray);

		// コマンドリストに指定のインデックスバッファを登録する
		void setIndexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	public: /* 定数バッファの処理 */

		// 定数バッファを作る
		void createCBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// 指定の定数バッファを使用して、引数のディスクリプタハンドルに定数バッファビューを作る
		void createCbv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定の定数バッファを更新する
		// ※アップロードバッファを新規に作成し、そのバッファから自身にコピーする命令をコマンドリストに登録する
		void updateCBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

	public: /* テクスチャバッファの処理 */

		// コマンドリストを使わずにテクスチャバッファを作る
		void cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		
		// コマンドリストを使ってテクスチャバッファを作る
		void gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// 引数のファイルから画像情報をロードし、コマンドリストを使わずにテクスチャバッファを作る
		void cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const std::string& texDataPath);
		
		// 引数のファイルから画像情報をロードし、コマンドリストを使ってテクスチャバッファを作る
		void gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

		// 指定のテクスチャバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定のテクスチャバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector3& getTextureSizePx(unsigned int id) const;

	public: /* 深度ステンシルバッファの処理 */

		// 深度ステンシルバッファを作る
		void createDsBuffer(unsigned int id, ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// 指定の深度ステンシルバッファを使用して、引数のディスクリプタハンドルに深度ステンシルビューを作る
		void createDsv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定の深度ステンシルバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createDsSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定の深度ステンシルバッファのリソースバリアを深度書き込み状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void beginWriteDsBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// 指定の深度ステンシルバッファのリソースバリアをシェーダー使用状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void endWriteDsBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// 全ての深度ステンシルバッファのリソースバリアを深度書き込み状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void allBeginWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const;

		// 全ての深度ステンシルバッファのリソースバリアをシェーダー使用状態に変更する
		// ※シェーダーリソースとして使用しない設定の場合読んでも何も起きない
		void allEndWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const;

		// 指定の深度ステンシルバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector2& getDepthStencilSizePx(unsigned int id) const;

	public: /* レンダーターゲットバッファの処理 */

		// ゼロからレンダーターゲットバッファを作る
		void createRtBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);
		
		// スワップチェインからレンダーターゲットバッファを作る
		void createRtBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// 指定のレンダーターゲットバッファを使用して、引数のディスクリプタハンドルにレンダーターゲットビューを作る
		void createRtv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定のレンダーターゲットバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createRtSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定のレンダーターゲットバッファのリソースバリアをレンダーターゲット状態に変更する
		void beginWriteBasicRtBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをシェーダー使用状態に変更する
		void endWriteBasicRtBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをレンダーターゲット状態に変更する
		void beginWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをプリセット状態に変更する
		void endWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファ画像の大きさを取得す（ピクセル）
		const tktkMath::Vector2& getRenderTargetSizePx(unsigned int id) const;

	private:

		VertexBuffer		m_vertexBuffer;
		IndexBuffer			m_indexBuffer;
		ConstantBuffer		m_constantBuffer;
		TextureBuffer		m_textureBuffer;
		DepthStencilBuffer	m_depthStencilBuffer;
		RenderTargetBuffer	m_renderTargetBuffer;
	};
}
#endif // !BUFFER_RESOURCE_H_