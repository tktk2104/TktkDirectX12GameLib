#ifndef DX12_GAME_MANAGER_H_
#define DX12_GAME_MANAGER_H_

#include <string>
#include <vector>
#include <forward_list>
#include <memory>
#include <utility>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "../GameObject/GameObjectPtr.h"			// ゲームオブジェクトを扱う時に使用する
#include "../GameObject/GameObjectTagCarrier.h"
#include "../Component/ComponentManager.h"			// テンプレート引数に型情報を渡す必要がある為隠蔽できない
#include "../EventMessage/MessageTypeCarrier.h"
#include "../EventMessage/MessageAttachment.h"		// メッセージを送信する時に好きな型の変数を添付する
#include "../DXGameResource/Scene/SceneVTable.h"	// シーンマネージャークラスを隠蔽する為にテンプレート関連のみ分離
#include "DX12GameManagerInitParam.h"
#include "DX12GameManagerInitParamIncluder.h"
#include "DX12GameManagerFuncArgsIncluder.h"

#include "TktkDX12Game/DXGameResource/_HandleGetter/ResourceIdCarrier.h"

namespace tktk
{
	// 前方宣言
	class Window;
	class DX3DBaseObjects;
	class GameObjectManager;
	class DXGameResource;
	class DXGameResourceHandleGetter;
	class SystemDXGameResourceHandleGetter;
	class DirectInputWrapper;
	class ElapsedTimer;
	class Mouse;
	class InputManager;

	// ゲームフレームワークのメインマネージャー
	// ※簡略版マネージャーは「tktk::DX12Game」です
	class DX12GameManager
	{
	//************************************************************
	/* このマネージャー自体の処理 */
	public:

		// 初期化
		static void initialize(const DX12GameManagerInitParam& initParam);

		// 実行
		static void run();

		// 終了
		static void exit();

	//************************************************************
	/* ウィンドウの処理 */
	public:

		// ウィンドウサイズを取得する
		static const tktkMath::Vector2& getWindowSize();

	//************************************************************
	/* シーンの処理 */
	public:

		// シーンを作り、そのリソースのハンドルを返す
		static size_t addScene(const SceneDataInitParam& initParam);

		// シーンを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t addSceneAndAttachId(ResourceIdCarrier id, const SceneDataInitParam& initParam);

		// シーンの終了時に削除するゲームオブジェクトタグを設定する
		static void setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag);

		// シーンを有効にする
		static void enableScene(size_t handle);

		// シーンを無効にする
		static void disableScene(size_t handle);

	//************************************************************
	/* ゲームオブジェクトの処理 */
	public:

		// 全てのGameObjectにメッセージを送信する
		static void sendMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment = {});

		// ゲームオブジェクトを作成し、そのポインタを返す
		static GameObjectPtr createGameObject();
		
		// 引数のタグを持ったゲームオブジェクトを取得する
		// ※該当オブジェクトが無かった場合、空のGameObjectPtrを取得する
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		static GameObjectPtr findGameObjectWithTag(GameObjectTagCarrier tag);
		
		// 引数のタグを持ったゲームオブジェクトを全て取得する
		static std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagCarrier tag);

		// 引数のタグを持ったゲームオブジェクトを全て削除する
		static void destroyGameObjectsWithTag(GameObjectTagCarrier tag);

	//************************************************************
	/* コンポーネントの処理 */
	public:

		// コンポーネントの型ごとの更新優先度を設定する
		// ※デフォルト（0.0f）で値が小さい程、早く実行される
		template <class ComponentType>
		static void addUpdatePriority(float priority) { m_componentManager->addUpdatePriority<ComponentType>(priority); }

		// 衝突判定の組み合わせを追加する
		static void addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup);

		// テンプレート引数の型のコンポーネントを引数の値を使って作る
		template <class ComponentType, class... Args>
		static std::weak_ptr<ComponentType> createComponent(const GameObjectPtr& user, Args&&... args) { return m_componentManager->createComponent<ComponentType>(user, std::forward<Args>(args)...); }

	//************************************************************
	/* 直接DX12の処理を呼ぶ */
	public:

		// コマンドリストを手動で実行する
		static void executeCommandList();

		// 背景色を設定する
		static void setBackGroundColor(const tktkMath::Color& backGroundColor);

		// 指定のレンダーターゲット用のディスクリプタヒープをコマンドリストに設定する
		static void setRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount);

		// 指定の（レンダーターゲットと深度ステンシルビュー）用のディスクリプタヒープ２つをコマンドリストに設定する
		static void setRtvAndDsv(size_t rtvDescriptorHeapHandle, size_t dsvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount);

		// 指定の深度ステンシルビュー用のディスクリプタヒープをコマンドリストに設定する（※レンダーターゲットは設定できない）
		static void setOnlyDsv(size_t dsvDescriptorHeapHandle);

		// バックバッファーを設定する
		static void setBackBufferView();

		// バックバッファーと深度ステンシルビューを設定する
		static void setBackBufferViewAndDsv(size_t dsvDescriptorHeapHandle);

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファの書き込み後処理を行う
		static void unSetRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount);

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファの書き込み後処理を行う
		static void unSetDsv(size_t dsvDescriptorHeapHandle);

		// 指定のビューポートをコマンドリストに設定する
		static void setViewport(size_t handle);

		// 指定のシザー矩形をコマンドリストに設定する
		static void setScissorRect(size_t handle);

		// 指定のパイプラインステートをコマンドリストに設定する
		static void setPipeLineState(size_t handle);

		// 指定の頂点バッファをコマンドリストに設定する
		static void setVertexBuffer(size_t handle);

		// 指定のインデックスバッファをコマンドリストに設定する
		static void setIndexBuffer(size_t handle);

		// 指定のディスクリプタヒープの配列をコマンドリストに設定する
		static void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray);

		// ブレンドファクターを設定する
		static void setBlendFactor(const std::array<float, 4>& blendFactor);

		// プリミティブトポロジを設定する
		static void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);

		// インスタンス描画を行う
		static void drawInstanced(
			size_t vertexCountPerInstance,
			size_t instanceCount,
			size_t baseVertexLocation,
			size_t startInstanceLocation
		);

		// インデックスを使用してインスタンス描画を行う
		static void drawIndexedInstanced(
			size_t indexCountPerInstance,
			size_t instanceCount,
			size_t startIndexLocation,
			size_t baseVertexLocation,
			size_t startInstanceLocation
		);

	//************************************************************
	/* 直接DX12のリソースを作る */
	public:

		// ルートシグネチャを作り、そのリソースのハンドルを返す
		static size_t createRootSignature(const RootSignatureInitParam& initParam);

		// パイプラインステートを作り、そのリソースのハンドルを返す
		static size_t createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// アップロードバッファを作り、そのリソースのハンドルを返す
		static size_t createUploadBuffer(const UploadBufferInitParam& initParam);
		
		// アップロードバッファのコピーを作り、そのリソースのハンドルを返す
		static size_t duplicateUploadBuffer(size_t originalHandle);

		// コピーバッファを作り、そのリソースのハンドルを返す
		static size_t createVertexBuffer(const VertexDataCarrier& vertexData);
		
		// インデックスバッファを作り、そのリソースのハンドルを返す
		static size_t createIndexBuffer(const std::vector<unsigned short>& indices);

		// 定数バッファを作り、そのリソースのハンドルを返す
		static size_t createCBuffer(const CopySourceDataCarrier& constantBufferData);
		
		// レンダーターゲットバッファを作り、そのリソースのハンドルを返す
		static size_t createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// 深度ステンシルバッファを作り、そのリソースのハンドルを返す
		static size_t createDsBuffer(const DepthStencilBufferInitParam& initParam);

		// ディスクリプタヒープを作り、そのリソースのハンドルを返す
		static size_t createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam);

		// レンダーターゲットのディスクリプタヒープを作り、そのリソースのハンドルを返す
		static size_t createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam);

		// 深度ステンシルディスクリプタヒープを作り、そのリソースのハンドルを返す
		static size_t createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam);

		// コマンドリストを使わずにテクスチャを作り、そのリソースのハンドルを返す
		static size_t cpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使ってテクスチャを作り、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		static size_t gpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使わずにテクスチャをロードし、そのリソースのハンドルを返す
		static size_t cpuPriorityLoadTextureBuffer(const std::string& texDataPath);

		// コマンドリストを使ってテクスチャをロードし、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		static size_t gpuPriorityLoadTextureBuffer(const std::string& texDataPath);
		
	//************************************************************
	/* 直接DX12のリソースを削除する */
	public:

		// 指定のビューポートを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseViewport(size_t handle);

		// 指定のシザー矩形を削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseScissorRect(size_t handle);

		// 指定のルートシグネチャを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseRootSignature(size_t handle);

		// 指定のパイプラインステートを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void erasePipeLineState(size_t handle);

		// 指定のアップロードバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseUploadBuffer(size_t handle);

		// 指定の頂点バッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseVertexBuffer(size_t handle);

		// 指定のインデックスバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseIndexBuffer(size_t handle);

		// 指定の定数バッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseCBuffer(size_t handle);

		// 指定のテクスチャバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseTextureBuffer(size_t handle);

		// 指定の深度ステンシルバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseDsBuffer(size_t handle);

		// 指定のレンダーターゲットバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseRtBuffer(size_t handle);

		// 指定の通常のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseBasicDescriptorHeap(size_t handle);

		// 指定のレンダーターゲット用のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseRtvDescriptorHeap(size_t handle);

		// 指定の深度ステンシル用のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseDsvDescriptorHeap(size_t handle);

	//************************************************************
	/* 直接DX12のリソースを設定、取得する */
	public:

		// 引数のポインタのデータを指定のアップロードバッファにコピーする
		static void updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData);
		
		// 指定のアップロードバッファの内容を設定したバッファにコピーするGPU命令を設定する
		static void copyBuffer(size_t handle);

		// 指定のレンダーターゲットビューを指定の色でクリアする
		static void clearRtv(size_t handle, size_t rtvLocationIndex, const tktkMath::Color& color);

		// 指定のテクスチャのサイズを取得する（ピクセル（テクセル））
		static const tktkMath::Vector3& getTextureBufferSizePx(size_t handle);
		static const tktkMath::Vector2& getDsBufferSizePx(size_t handle);
		static const tktkMath::Vector2& getRtBufferSizePx(size_t handle);

	//************************************************************
	/* スプライト関係の処理 */
	public:

		// スプライトマテリアルを作り、そのリソースのハンドルを返す
		static size_t createSpriteMaterial(const SpriteMaterialInitParam& initParam);

		// スプライトマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createSpriteMaterialAndAttachId(ResourceIdCarrier id, const SpriteMaterialInitParam& initParam);

		// 指定したスプライトを描画する
		static void drawSprite(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs);

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する
		static void updateSpriteTransformCbuffer(size_t handle, size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate);

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する（切り抜き範囲指定版）
		static void updateSpriteTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate, const SpriteClippingParam& clippingParam);

	//************************************************************
	/* 2Dライン関係の処理 */
	public:

		// ２Ｄラインマテリアルを作り、そのリソースのハンドルを返す
		static size_t createLine2DMaterial();

		// ２Ｄラインマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createLine2DMaterialAndAttachId(ResourceIdCarrier id);

		// ２Ｄラインを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseLine(size_t handle);

		// 線を描画する
		static void drawLine(size_t handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	//************************************************************
	/* ビルボード関係の処理 */

		// ビルボードマテリアルを作り、そのリソースのハンドルを返す
		static size_t createBillboardMaterial(const BillboardMaterialInitParam& initParam);

		// ビルボードマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createBillboardMaterialAndAttachId(ResourceIdCarrier id, const BillboardMaterialInitParam& initParam);

		// 指定したビルボードを描画する
		static void drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs);

		// 引数が表すコピーバッファを使って定数バッファを更新する
		static void updateBillboardCbuffer(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs);

		// 引数が表すコピーバッファを使って定数バッファを更新する（切り抜き範囲指定版）
		static void updateBillboardCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam);

	//************************************************************
	/* メッシュ関係の処理 */
	public:

		// 通常メッシュを作り、そのリソースのハンドルを返す
		static size_t createBasicMesh(const BasicMeshInitParam& initParam);

		// 通常メッシュを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createBasicMeshAndAttachId(ResourceIdCarrier id, const BasicMeshInitParam& initParam);

		// 通常メッシュのコピーを作り、そのリソースのハンドルを返す
		static size_t copyBasicMesh(size_t originalHandle);

		// 通常メッシュのコピーを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t copyBasicMeshAndAttachId(ResourceIdCarrier id, size_t originalHandle);

		// 通常メッシュマテリアルを作り、そのリソースのハンドルを返す
		static size_t createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam);

		// 通常メッシュマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createBasicMeshMaterialAndAttachId(ResourceIdCarrier id, const BasicMeshMaterialInitParam& initParam);

		// 通常メッシュマテリアルのコピーを作り、そのリソースのハンドルを返す
		static size_t copyBasicMeshMaterial(size_t originalHandle);

		// 通常メッシュマテリアルのコピーを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t copyBasicMeshMaterialAndAttachId(ResourceIdCarrier id, size_t originalHandle);

		// 通常メッシュが使用しているマテリアルを更新する
		static void setMaterialHandle(size_t handle, size_t materialSlot, size_t materialHandle);

		// 指定の通常メッシュでシャドウマップを書き込む
		static void writeBasicMeshShadowMap(size_t handle);

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		static void setMaterialData(size_t handle);

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		template <class CbufferType>
		static void addMaterialAppendParam(size_t handle, size_t cbufferHandle, CbufferType&& value)			{ addMaterialAppendParamImpl(handle, cbufferHandle, sizeof(CbufferType), new CbufferType(std::forward<CbufferType>(value))); }

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		template <class CbufferType>
		static void updateMaterialAppendParam(size_t handle, size_t cbufferHandle, const CbufferType& value)	{ updateMaterialAppendParamImpl(handle, cbufferHandle, sizeof(CbufferType), &value); }

		// 指定の通常メッシュを描画する
		static void drawBasicMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs);

		// pmdファイルをロードしてゲームの各種リソースクラスを作る
		static BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

		// pmxファイルをロードしてゲームの各種リソースクラスを作る
		static BasicMeshLoadPmxReturnValue loadPmx(const BasicMeshLoadPmxArgs& args);

	//************************************************************
	/* スケルトン関連の処理 */
	public:

		// スケルトンを作り、そのリソースのハンドルを返す
		static size_t createSkeleton(const SkeletonInitParam& initParam);

		// スケルトンのコピーを作り、そのリソースのハンドルを返す
		static size_t copySkeleton(size_t originalHandle);

		// 指定のスケルトンの骨情報の定数バッファの値にアップロードするためのバッファを作り、そのハンドルを返す
		// ※この関数で取得したハンドルは使用後に「DX12GameManager::eraseUploadBuffer(handle)」を必ず読んでバッファを削除してください
		static size_t createSkeletonUploadBufferHandle(size_t handle);

		// スケルトンを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createSkeletonAndAttachId(ResourceIdCarrier id, const SkeletonInitParam& initParam);

		// 指定のスケルトンを使って引数が表すコピーバッファを使い骨情報を管理する定数バッファを更新する
		static void updateBoneMatrixCbuffer(size_t handle, size_t copyBufferHandle);

		// 骨情報を管理する定数バッファに単位行列を設定する
		static void resetBoneMatrixCbuffer();

	//************************************************************
	/* モーション関係の処理 */
	public:

		// vmdファイルを読み込んでモーションを作り、そのリソースのハンドルを返す
		static size_t loadMotion(const std::string& motionFileName);

		// vmdファイルを読み込んでモーションを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t loadMotionAndAttachId(ResourceIdCarrier id, const std::string& motionFileName);

		// 指定のモーションの終了キーの番号を取得する
		static size_t getMotionEndFrameNo(size_t handle);

		// 2種類のモーション情報を線形補完してスケルトンを更新する
		// ※補完割合の値は「0.0fでpreFrame100%」、「1.0fでcurFrame100%」となる
		static void updateMotion(
			size_t skeletonHandle,
			size_t curMotionHandle,
			size_t preMotionHnadle,
			size_t curFrame,
			size_t preFrame,
			float amount
		);

	//************************************************************
	/* ポストエフェクト関係の処理 */
	public:

		// ポストエフェクトのマテリアルを作り、そのリソースのハンドルを返す
		static size_t createPostEffectMaterial(const PostEffectMaterialInitParam& initParam);

		// ポストエフェクトのマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createPostEffectMaterialAndAttachId(ResourceIdCarrier id, const PostEffectMaterialInitParam& initParam);

		// 指定のポストエフェクトを描画する
		static void drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs);

	//************************************************************
	/* カメラ関係の処理 */
	public:

		// カメラを作り、そのリソースのハンドルを返す
		static size_t createCamera();

		// カメラを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createCameraAndAttachId(ResourceIdCarrier id);

		// 指定のカメラのビュー行列を取得する
		static const tktkMath::Matrix4& getViewMatrix(size_t cameraHandle);

		// 指定のカメラのビュー行列を設定する
		static void setViewMatrix(size_t cameraHandle, const tktkMath::Matrix4& view);

		// 指定のカメラのプロジェクション行列を取得する
		static const tktkMath::Matrix4& getProjectionMatrix(size_t cameraHandle);

		// 指定のカメラのプロジェクション行列を設定する
		static void setProjectionMatrix(size_t cameraHandle, const tktkMath::Matrix4& projection);

	//************************************************************
	/* ライト関係の処理 */
	public:

		// ライトを作り、そのリソースのハンドルを返す
		static size_t createLight(
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ライトを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createLightAndAttachId(
			ResourceIdCarrier id,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ライト情報の定数バッファを更新する
		static void updateLightCBuffer(size_t handle);

		// 指定のライトの環境光を設定する
		static void setLightAmbient(size_t handle, const tktkMath::Color& ambient);

		// 指定のライトの拡散反射光を設定する
		static void setLightDiffuse(size_t handle, const tktkMath::Color& diffuse);

		// 指定のライトの鏡面反射光を設定する
		static void setLightSpeqular(size_t handle, const tktkMath::Color& speqular);

		// 指定のライトの座標を設定する
		static void setLightPosition(size_t handle, const tktkMath::Vector3& position);

	//************************************************************
	/* サウンド関係の処理 */
	public:

		// 新しいサウンドを読み込み、そのリソースのハンドルを返す
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		static size_t loadSound(const std::string& fileName);

		// 新しいサウンドを読み込み、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t loadSoundAndAttachId(ResourceIdCarrier id, const std::string& fileName);

		// 指定したサウンドを再生する
		static void playSound(size_t handle, bool loopPlay);

		// 指定したサウンドを停止する
		static void stopSound(size_t handle);

		// 指定したサウンドを一時停止する
		static void pauseSound(size_t handle);

		// 大元の音量を変更する（0.0f～1.0f）
		static void setMasterVolume(float volume);

	//************************************************************
	/* 入力関係共通の処理 */
	public:

		// 特定の入力が押されているかを始める
		// 「対応する入力：MouseButtonType, KeybordKeyType, GamePadBtnType」
		// 上記以外の引数の型の場合、InputManagerを使った入力検知になる
		template <class T>
		static bool isPush(T type);

		// 特定の入力が押され始めたかを始める
		// 「対応する入力：MouseButtonType, KeybordKeyType, GamePadBtnType」
		// 上記以外の引数の型の場合、InputManagerを使った入力検知になる
		template <class T>
		static bool isTrigger(T type);

	//************************************************************
	/* インプットマネージャーの処理 */
	public:

		// IDに対応した入力が押されているかを判定
		static bool isPushCommand(int commandId);

		// IDに対応した入力が押され始めたかを判定
		static bool isTriggerCommand(int commandId);

		// 移動方向を取得
		static const tktkMath::Vector2& moveVec();

		// 視点移動方向を取得
		static const tktkMath::Vector2& lookVec();

		// 各種入力とIDを結びつける
		static void addCommand(int commandId, KeybordKeyType keyType);
		static void addCommand(int commandId, GamePadBtnType btnType);
		static void addCommand(int commandId, MouseButtonType btnType);

		// 各種入力と移動コマンドを結びつける
		static void addDirectionCommand(DirectionCommandType directionCommand, KeybordKeyType keyType);
		static void addDirectionCommand(DirectionCommandType directionCommand, GamePadBtnType btnType);
		static void addDirectionCommand(DirectionCommandType directionCommand, MouseButtonType btnType);

	//************************************************************
	/* マウス入力関係の処理 */
	public:

		// 指定のボタンが押されているか
		static bool isMousePush(MouseButtonType buttonType);

		// 指定のボタンが押され始めたかを判定
		static bool isMouseTrigger(MouseButtonType buttonType);

		// マウスカーソルの座標を取得する
		static tktkMath::Vector2 mousePos();

	//************************************************************
	/* キーボード入力関係の処理 */
	public:

		// 指定のキーが押されているかを判定
		static bool isKeybordPush(KeybordKeyType keyType);

		// 指定のキーが押され始めたかを判定
		static bool isKeybordTrigger(KeybordKeyType keyType);

	//************************************************************
	/* ゲームパッド入力関係の処理 */
	public:

		// 左スティックの傾きを取得（-1.0～1.0の間）
		static tktkMath::Vector2 getLstick();

		// 右スティックの傾きを取得（-1.0～1.0の間）
		static tktkMath::Vector2 getRstick();

		// 指定のボタンが押されているかを判定
		static bool isPadPush(GamePadBtnType btnType);

		// 指定のボタンが押され始めたかを判定
		static bool isPadTrigger(GamePadBtnType btnType);

	//************************************************************
	/* タイム関係の処理 */
	public:

		// 経過時間を初期化する
		static void resetElapsedTime();

		// 前フレームとの時間の差を求める
		static float deltaTime();

		// 前フレームとの時間の差を求める（TimeScaleを無視）
		static float noScaleDeltaTime();

		// プログラムが起動してからの時間（秒）を返す
		static float getCurTimeSec();

		// 最大のdeltaTimeの値を設定（正の数）
		static void setMaximumDeltaTime(float maximumDeltaTime);

		// 時間の経過速度割合を取得する
		static float getTimeScale();

		// 時間の経過速度割合を設定する（0.0～float_max）
		static void setTimeScale(float timeScaleRate);

		// 基準となるFPSを設定する
		static void setBaseFps(unsigned int baseFps = 60U);

		// 基準となるFPSを取得する
		static unsigned int getBaseFps();

		// 瞬間的なFPSを取得する
		static float fps();

	//************************************************************
	/* システムのリソースを使うためのハンドルを取得する */
	public:

		static size_t getSystemHandle(SystemViewportType type);
		static size_t getSystemHandle(SystemScissorRectType type);
		static size_t getSystemHandle(SystemVertexBufferType type);
		static size_t getSystemHandle(SystemIndexBufferType type);
		static size_t getSystemHandle(SystemCBufferType type);
		static size_t getSystemHandle(SystemTextureBufferType type);
		static size_t getSystemHandle(SystemDsBufferType type);
		static size_t getSystemHandle(SystemBasicDescriptorHeapType type);
		static size_t getSystemHandle(SystemRtvDescriptorHeapType type);
		static size_t getSystemHandle(SystemDsvDescriptorHeapType type);
		static size_t getSystemHandle(SystemRootSignatureType type);
		static size_t getSystemHandle(SystemPipeLineStateType type);
		static size_t getSystemHandle(SystemCameraType type);
		static size_t getSystemHandle(SystemLightType type);
		static size_t getSystemHandle(SystemBasicMeshType type);
		static size_t getSystemHandle(SystemBasicMeshMaterialType type);
		static size_t getSystemHandle(SystemPostEffectMaterialType type);

	//************************************************************
	/* システムのリソースを使うためのハンドルとシステムのリソースの種類を結びつける */

		static void setSystemHandle(SystemViewportType type,			size_t handle);
		static void setSystemHandle(SystemScissorRectType type,			size_t handle);
		static void setSystemHandle(SystemVertexBufferType type,		size_t handle);
		static void setSystemHandle(SystemIndexBufferType type,			size_t handle);
		static void setSystemHandle(SystemCBufferType type,				size_t handle);
		static void setSystemHandle(SystemTextureBufferType type,		size_t handle);
		static void setSystemHandle(SystemRtBufferType type,			size_t handle);
		static void setSystemHandle(SystemDsBufferType type,			size_t handle);
		static void setSystemHandle(SystemBasicDescriptorHeapType type,	size_t handle);
		static void setSystemHandle(SystemRtvDescriptorHeapType type,	size_t handle);
		static void setSystemHandle(SystemDsvDescriptorHeapType type,	size_t handle);
		static void setSystemHandle(SystemRootSignatureType type,		size_t handle);
		static void setSystemHandle(SystemPipeLineStateType type,		size_t handle);
		static void setSystemHandle(SystemCameraType type,				size_t handle);
		static void setSystemHandle(SystemLightType type,				size_t handle);
		static void setSystemHandle(SystemBasicMeshType type,			size_t handle);
		static void setSystemHandle(SystemBasicMeshMaterialType type,	size_t handle);
		static void setSystemHandle(SystemPostEffectMaterialType type,	size_t handle);

	//************************************************************
	/* 裏実装 */
	public:

		static void addMaterialAppendParamImpl		(size_t handle, size_t cbufferHandle, size_t dataSize, void* dataTopPos);
		static void updateMaterialAppendParamImpl	(size_t handle, size_t cbufferHandle, size_t dataSize, const void* dataTopPos);

		static size_t getSceneHandle				(ResourceIdCarrier id);
		static size_t getSoundHandle				(ResourceIdCarrier id);
		static size_t getPostEffectMaterialHandle	(ResourceIdCarrier id);
		static size_t getSpriteMaterialHandle		(ResourceIdCarrier id);
		static size_t getLine2DMaterialHandle		(ResourceIdCarrier id);
		static size_t getBillboardMaterialHandle	(ResourceIdCarrier id);
		static size_t getSkeletonHandle				(ResourceIdCarrier id);
		static size_t getMotionHandle				(ResourceIdCarrier id);
		static size_t getBasicMeshHandle			(ResourceIdCarrier id);
		static size_t getBasicMeshMaterialHandle	(ResourceIdCarrier id);
		static size_t getCameraHandle				(ResourceIdCarrier id);
		static size_t getLightHandle				(ResourceIdCarrier id);

	//************************************************************
	private:

		static bool												m_isGameExit;
		static std::unique_ptr<Window>							m_window;
		static std::unique_ptr<DX3DBaseObjects>					m_dx3dBaseObjects;
		static std::unique_ptr<GameObjectManager>				m_gameObjectManager;
		static std::unique_ptr<ComponentManager>				m_componentManager;
		static std::unique_ptr<DXGameResource>					m_dxGameResource;
		static std::unique_ptr<DXGameResourceHandleGetter>		m_resHandleGetter;
		static std::unique_ptr<SystemDXGameResourceHandleGetter>m_systemDXGameResourceHandleGetter;
		static std::unique_ptr<DirectInputWrapper>				m_directInputWrapper;
		static std::unique_ptr<Mouse>							m_mouse;
		static std::unique_ptr<InputManager>					m_inputManager;
		static std::unique_ptr<ElapsedTimer>					m_elapsedTimer;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は実装が多めのテンプレート関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// IDに対応した入力が押されているかを判定
	template<class T>
	inline bool DX12GameManager::isPush(T type)
	{
		return isPushCommand(static_cast<int>(type));
	}

	// 指定のマウスボタンが押されているか
	template<>
	inline bool DX12GameManager::isPush(MouseButtonType type)
	{
		return isMousePush(type);
	}

	// 指定のキーが押されているかを判定
	template<>
	inline bool DX12GameManager::isPush(KeybordKeyType type)
	{
		return isKeybordPush(type);
	}

	// 指定のパッドボタンが押されているかを判定
	template<>
	inline bool DX12GameManager::isPush(GamePadBtnType type)
	{
		return isPadPush(type);
	}

	template<class T>
	inline bool DX12GameManager::isTrigger(T type)
	{
		return isTriggerCommand(static_cast<int>(type));
	}

	// 指定のマウスボタンが押され始めたかを判定
	template<>
	inline bool DX12GameManager::isTrigger(MouseButtonType type)
	{
		return isMouseTrigger(type);
	}

	// 指定のキーが押され始めたかを判定
	template<>
	inline bool DX12GameManager::isTrigger(KeybordKeyType type)
	{
		return isKeybordTrigger(type);
	}

	// 指定のパッドボタンが押され始めたかを判定
	template<>
	inline bool DX12GameManager::isTrigger(GamePadBtnType type)
	{
		return isPadTrigger(type);
	}
}
#endif // !DX12_GAME_MANAGER_H_