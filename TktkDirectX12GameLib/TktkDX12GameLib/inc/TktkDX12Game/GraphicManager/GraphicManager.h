#ifndef GRAPHIC_MANAGER_H_
#define GRAPHIC_MANAGER_H_

/* std::unique_ptr */
#include <memory>

/* std::array */
#include <array>

/* HWND */
#include <d3d12.h>
#undef min
#undef max

/* funcUseType */
#include <TktkDX12Wrapper/_BaseObjects/DX3DBaseObjectsInitParam.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkDX12Wrapper/_BaseObjects/DX3DBaseObjectsInitParamIncluder.h>
#include <TktkDX12Wrapper/_BaseObjects/DX3DBaseObjectsFuncArgsIncluder.h>
#include <TktkDX12Wrapper/_BaseObjects/DX3DBaseObjectsInitParam.h>
#include <TktkDX12Wrapper/_BaseObjects/PrimitiveTopology.h>

namespace tktk
{
	/* class member */
	class Window;
	class DX3DBaseObjects;

	/* funcUseType */
	struct WindowInitParam;

	// グラフィックマネージャー
	class GraphicManager
	{
	public:

		GraphicManager(const WindowInitParam& windowInitParam, const DX3DBaseObjectsInitParam& baseObjectsInitParam);
		~GraphicManager();

	public:

		// ウィンドウハンドルを取得する
		HWND getHWND() const;

		// ゲーム描画エリアサイズを取得する
		const tktkMath::Vector2& getDrawGameAreaSize() const;

		// スクリーンサイズを取得する
		const tktkMath::Vector2& getScreenSize() const;

	public: /* 描画開始、終了処理 */

		// 描画開始
		void beginDraw();

		// 描画終了
		void endDraw();

	public: /* リソース作成、ロード処理 */

		// ビューポートを作り、そのリソースのハンドルを返す
		size_t createViewport(const std::vector<ViewportInitParam>& initParamArray);

		// シザー矩形を作り、そのリソースのハンドルを返す
		size_t createScissorRect(const std::vector<ScissorRectInitParam>& initParamArray);

		// ルートシグネチャを作り、そのリソースのハンドルを返す
		size_t createRootSignature(const RootSignatureInitParam& initParam);

		// パイプラインステートを作り、そのリソースのハンドルを返す
		size_t createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// アップロードバッファを作り、そのリソースのハンドルを返す
		size_t createUploadBuffer(const UploadBufferInitParam& initParam);

		// 一時的なアップロードバッファを作る（次のフレームでは消滅する想定の為、ハンドルは返さない）
		void createTempUploadBuffer(const UploadBufferInitParam& initParam);

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

		// バックバッファーを使ってレンダーターゲットバッファを作り、そのリソースのハンドルを返す
		std::array<size_t, 2U> createBackBufferRtBuffer();

		// 深度ステンシルバッファを作り、そのリソースのハンドルを返す
		size_t createDsBuffer(const DepthStencilBufferInitParam& initParam);

		// 定数、テクスチャのディスクリプタヒープを作り、そのリソースのハンドルを返す
		size_t createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam);

		// レンダーターゲットのディスクリプタヒープを作り、そのリソースのハンドルを返す
		size_t createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam);

		// バックバッファーのレンダーターゲットディスクリプタヒープを作り、そのリソースのハンドルを返す
		size_t createBackBufferRtvDescriptorHeap(const std::array<size_t, 2U>& backBufferRtBufferHandles);

		// 深度ステンシルビューのディスクリプタヒープを作り、そのリソースのハンドルを返す
		size_t createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam);

		// テクスチャを作り、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		size_t createTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// テクスチャをロードし、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		size_t loadTextureBuffer(const std::string& texDataPath);

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

		// 引数のポインタのデータを指定のアップロードバッファにコピーする
		void updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData);

		// 指定の頂点バッファをコマンドリストを使わずに更新する
		void updateVertexBuffer(size_t handle, const VertexDataCarrier& vertexData);

		// 指定のアップロードバッファの内容を設定したバッファにアップロードするGPU命令を行う
		void copyBuffer(size_t handle) const;

		// 指定のレンダーターゲットビューを事前に設定したクリアカラーでクリアする
		void clearRtv(size_t handle, size_t rtvLocationIndex) const;

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

		// バックバッファービューを設定する
		void setBackBufferView() const;

		// バックバッファービューと深度ステンシルビューを設定する
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

		// コマンドリストに指定の頂点バッファを登録する（インスタンス描画用）
		void setVertexBuffer(size_t meshVertHandle, size_t instancingVertHandle) const;

		// 指定のインデックスバッファをコマンドリストに設定する
		void setIndexBuffer(size_t handle) const;

		// 指定のディスクリプタヒープの配列をコマンドリストに設定する
		void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray) const;

		// ブレンドファクターを設定する
		void setBlendFactor(const std::array<float, 4>& blendFactor) const;

		// プリミティブトポロジを設定する
		void setPrimitiveTopology(PrimitiveTopology topology) const;

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

	private:

		std::unique_ptr<Window>				m_window;
		std::unique_ptr<DX3DBaseObjects>	m_dx3dBaseObjects;
	};
}
#endif // !GRAPHIC_MANAGER_H_