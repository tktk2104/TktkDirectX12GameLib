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
		unsigned int createRootSignature(const RootSignatureInitParam& initParam);

		// パイプラインステートを作り、そのリソースのハンドルを返す
		unsigned int createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// 頂点バッファを作り、そのリソースのハンドルを返す
		unsigned int createVertexBuffer(unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// インデックスバッファを作り、そのリソースのハンドルを返す
		unsigned int createIndexBuffer(const std::vector<unsigned short>& indices);

		// 定数バッファを作り、そのリソースのハンドルを返す
		unsigned int createCBuffer(unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// レンダーターゲットバッファを作り、そのリソースのハンドルを返す
		unsigned int createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// 深度ステンシルバッファを作り、そのリソースのハンドルを返す
		unsigned int createDsBuffer(const DepthStencilBufferInitParam& initParam);

		// 定数、テクスチャのディスクリプタヒープを作り、そのリソースのハンドルを返す
		unsigned int createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam);

		// レンダーターゲットのディスクリプタヒープを作り、そのリソースのハンドルを返す
		unsigned int createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam);

		// 深度ステンシルビューのディスクリプタヒープを作り、そのリソースのハンドルを返す
		unsigned int createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam);

		// コマンドリストを使わずにテクスチャを作り、そのリソースのハンドルを返す
		unsigned int cpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使ってテクスチャを作り、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		unsigned int gpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使わずにテクスチャをロードし、そのリソースのハンドルを返す
		unsigned int cpuPriorityLoadTextureBuffer(const std::string& texDataPath);

		// コマンドリストを使ってテクスチャをロードし、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		unsigned int gpuPriorityLoadTextureBuffer(const std::string& texDataPath);

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