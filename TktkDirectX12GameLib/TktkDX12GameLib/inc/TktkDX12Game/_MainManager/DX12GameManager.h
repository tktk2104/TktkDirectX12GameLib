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
#include "../Component/ComponentManager.h"			// テンプレート引数に型情報を渡す必要がある為隠蔽できない
#include "../EventMessage/MessageAttachment.h"		// メッセージを送信する時に好きな型の変数を添付する
#include "../DXGameResource/Scene/SceneVTable.h"	// シーンマネージャークラスを隠蔽する為にテンプレート関連のみ分離
#include "DX12GameManagerInitParam.h"
#include "DX12GameManagerInitParamIncluder.h"
#include "DX12GameManagerFuncArgsIncluder.h"

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

	//************************************************************
	/* ウィンドウの処理 */
	public:

		// ウィンドウサイズを取得する
		static const tktkMath::Vector2& getWindowSize();

	//************************************************************
	/* シーンの処理 */
	public:

		// シーンを作り、そのリソースのハンドルを返す
		template<class SceneType, class... Args>
		static unsigned int addScene(Args&&... constructorArgs)	{ return createSceneImpl(std::make_shared<SceneType>(std::forward<Args>(constructorArgs)...), &SceneVTableInitializer<SceneType>::m_vtable); }

		// シーンを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		template<class SceneType, class IdType, class... Args>
		static unsigned int addSceneAndAttachId(IdType id, Args&&... constructorArgs);

		// シーンを有効にする
		static void enableScene(unsigned int handle);

		// シーンを無効にする
		static void disableScene(unsigned int handle);

	//************************************************************
	/* ゲームオブジェクトの処理 */
	public:

		// 全てのGameObjectにメッセージを送信する
		static void sendMessageAll(unsigned int messageId, const MessageAttachment& value = {});

		// ゲームオブジェクトを作成し、そのポインタを返す
		static GameObjectPtr createGameObject();
		
		// 引数のタグを持ったゲームオブジェクトを取得する
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		static GameObjectPtr findGameObjectWithTag(int tag);
		
		// 引数のタグを持ったゲームオブジェクトを全て取得する
		static std::forward_list<GameObjectPtr> findGameObjectsWithTag(int tag);

	//************************************************************
	/* コンポーネントの処理 */
	public:

		// コンポーネントの型ごとの更新優先度を設定する
		// ※デフォルト（0.0f）で値が小さい程、早く実行される
		template <class ComponentType>
		static void addUpdatePriority(float priority) { m_componentManager->addUpdatePriority<ComponentType>(priority); }

		// 衝突判定の組み合わせを追加する
		template <class CollisionGroupType>
		static void addCollisionGroup(CollisionGroupType firstGroup, CollisionGroupType secondGroup) { addCollisionGroupImpl(static_cast<int>(firstGroup), static_cast<int>(secondGroup)); }

		// テンプレート引数の型のコンポーネントを引数の値を使って作る
		template <class ComponentType, class... Args>
		static std::weak_ptr<ComponentType> createComponent(Args&&... args) { return m_componentManager->createComponent<ComponentType>(std::forward<Args>(args)...); }

	//************************************************************
	/* 直接DX12の処理を呼ぶ */
	public:

		// コマンドリストを手動で実行する
		static void executeCommandList();

		// 背景色を設定する
		static void setBackGroundColor(const tktkMath::Color& backGroundColor);

		// 指定のレンダーターゲット用のディスクリプタヒープをコマンドリストに設定する
		static void setRtv(unsigned int rtvDescriptorHeapHandle, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定の（レンダーターゲットと深度ステンシルビュー）用のディスクリプタヒープ２つをコマンドリストに設定する
		static void setRtvAndDsv(unsigned int rtvDescriptorHeapHandle, unsigned int dsvDescriptorHeapHandle, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定の深度ステンシルビュー用のディスクリプタヒープをコマンドリストに設定する（※レンダーターゲットは設定できない）
		static void setOnlyDsv(unsigned int dsvDescriptorHeapHandle);

		// バックバッファーを設定する
		static void setBackBufferView();

		// バックバッファーと深度ステンシルビューを設定する
		static void setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapHandle);

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファの書き込み後処理を行う
		static void unSetRtv(unsigned int rtvDescriptorHeapHandle, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファの書き込み後処理を行う
		static void unSetDsv(unsigned int dsvDescriptorHeapHandle);

		// 指定のビューポートをコマンドリストに設定する
		static void setViewport(unsigned int handle);

		// 指定のシザー矩形をコマンドリストに設定する
		static void setScissorRect(unsigned int handle);

		// 指定のパイプラインステートをコマンドリストに設定する
		static void setPipeLineState(unsigned int handle);

		// 指定の頂点バッファをコマンドリストに設定する
		static void setVertexBuffer(unsigned int handle);

		// 指定のインデックスバッファをコマンドリストに設定する
		static void setIndexBuffer(unsigned int handle);

		// 指定のディスクリプタヒープの配列をコマンドリストに設定する
		static void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray);

		// ブレンドファクターを設定する
		static void setBlendFactor(const std::array<float, 4>& blendFactor);

		// プリミティブトポロジを設定する
		static void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);

		// インスタンス描画を行う
		static void drawInstanced(
			unsigned int vertexCountPerInstance,
			unsigned int instanceCount,
			unsigned int baseVertexLocation,
			unsigned int startInstanceLocation
		);

		// インデックスを使用してインスタンス描画を行う
		static void drawIndexedInstanced(
			unsigned int indexCountPerInstance,
			unsigned int instanceCount,
			unsigned int startIndexLocation,
			unsigned int baseVertexLocation,
			unsigned int startInstanceLocation
		);

	//************************************************************
	/* 直接DX12のリソースを作る */
	public:

		// ルートシグネチャを作り、そのリソースのハンドルを返す
		static unsigned int createRootSignature(const RootSignatureInitParam& initParam);

		// パイプラインステートを作り、そのリソースのハンドルを返す
		static unsigned int createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// コピーバッファを作り、そのリソースのハンドルを返す
		template <class CopyBufferDataType>
		static unsigned int createCopyBuffer(BufferType bufferData, unsigned int targetBufferHandle, const CopyBufferDataType& copyBuffer) { return createCopyBufferImpl({ bufferData, targetBufferHandle, sizeof(CopyBufferDataType),  &copyBuffer }); }

		// コピーバッファのコピーを作り、そのリソースのハンドルを返す
		static unsigned int copyCopyBuffer(unsigned int originalHandle);

		// コピーバッファを作り、そのリソースのハンドルを返す
		template <class VertexData>
		static unsigned int createVertexBuffer(const std::vector<VertexData>& vertexDataArray) { return createVertexBufferImpl(sizeof(VertexData), vertexDataArray.size(), vertexDataArray.data()); }

		// インデックスバッファを作り、そのリソースのハンドルを返す
		static unsigned int createIndexBuffer(const std::vector<unsigned short>& indices);

		// 定数バッファを作り、そのリソースのハンドルを返す
		template <class ConstantBufferDataType>
		static unsigned int createCBuffer(const ConstantBufferDataType& rawConstantBufferData) { return createCbufferImpl(sizeof(ConstantBufferDataType), &rawConstantBufferData); }

		// レンダーターゲットバッファを作り、そのリソースのハンドルを返す
		static unsigned int createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// 深度ステンシルバッファを作り、そのリソースのハンドルを返す
		static unsigned int createDsBuffer(const DepthStencilBufferInitParam& initParam);

		// ディスクリプタヒープを作り、そのリソースのハンドルを返す
		static unsigned int createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam);

		// レンダーターゲットのディスクリプタヒープを作り、そのリソースのハンドルを返す
		static unsigned int createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam);

		// 深度ステンシルディスクリプタヒープを作り、そのリソースのハンドルを返す
		static unsigned int createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam);

		// コマンドリストを使わずにテクスチャを作り、そのリソースのハンドルを返す
		static unsigned int cpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使ってテクスチャを作り、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		static unsigned int gpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使わずにテクスチャをロードし、そのリソースのハンドルを返す
		static unsigned int cpuPriorityLoadTextureBuffer(const std::string& texDataPath);

		// コマンドリストを使ってテクスチャをロードし、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		static unsigned int gpuPriorityLoadTextureBuffer(const std::string& texDataPath);
		
	//************************************************************
	/* 直接DX12のリソースを削除する */
	public:

		// 指定のビューポートを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseViewport(unsigned int handle);

		// 指定のシザー矩形を削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseScissorRect(unsigned int handle);

		// 指定のルートシグネチャを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseRootSignature(unsigned int handle);

		// 指定のパイプラインステートを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void erasePipeLineState(unsigned int handle);

		// 指定のコピーバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseCopyBuffer(unsigned int handle);

		// 指定の頂点バッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseVertexBuffer(unsigned int handle);

		// 指定のインデックスバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseIndexBuffer(unsigned int handle);

		// 指定の定数バッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseCBuffer(unsigned int handle);

		// 指定のテクスチャバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseTextureBuffer(unsigned int handle);

		// 指定の深度ステンシルバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseDsBuffer(unsigned int handle);

		// 指定のレンダーターゲットバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseRtBuffer(unsigned int handle);

		// 指定の通常のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseBasicDescriptorHeap(unsigned int handle);

		// 指定のレンダーターゲット用のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseRtvDescriptorHeap(unsigned int handle);

		// 指定の深度ステンシル用のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		static void eraseDsvDescriptorHeap(unsigned int handle);

	//************************************************************
	/* 直接DX12のリソースを設定、取得する */
	public:

		// 引数のポインタのデータを指定のコピーバッファにコピーする
		template <class CopyBufferDataType>
		static void updateCopyBuffer(unsigned int handle, const CopyBufferDataType& bufferData) { updateCopyBufferImpl(handle, sizeof(CopyBufferDataType), &bufferData); }

		// 指定のコピーバッファの内容を設定したバッファにコピーするGPU命令を設定する
		static void copyBuffer(unsigned int handle);

		// 指定のレンダーターゲットビューを指定の色でクリアする
		static void clearRtv(unsigned int handle, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		// 指定のテクスチャのサイズを取得する（ピクセル（テクセル））
		static const tktkMath::Vector3& getTextureBufferSizePx(unsigned int handle);
		static const tktkMath::Vector2& getDsBufferSizePx(unsigned int handle);
		static const tktkMath::Vector2& getRtBufferSizePx(unsigned int handle);

	//************************************************************
	/* スプライト関係の処理 */
	public:

		// スプライトマテリアルを作り、そのリソースのハンドルを返す
		static unsigned int createSpriteMaterial(const SpriteMaterialInitParam& initParam);

		// スプライトマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		template<class IdType>
		static unsigned int createSpriteMaterialAndAttachId(IdType id, const SpriteMaterialInitParam& initParam);

		// 指定したスプライトを描画する
		static void drawSprite(unsigned int handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs);

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する
		static void updateSpriteTransformCbuffer(unsigned int handle, unsigned int copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate);

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する（切り抜き範囲指定版）
		static void updateSpriteTransformCbufferUseClippingParam(unsigned int handle, unsigned int copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate, const SpriteClippingParam& clippingParam);

	//************************************************************
	/* 2Dライン関係の処理 */
	public:

		// ２Ｄラインマテリアルを作り、そのリソースのハンドルを返す
		static unsigned int createLine2DMaterial();

		// ２Ｄラインマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		template<class IdType>
		static unsigned int createLine2DMaterialAndAttachId(IdType id);

		// 線を描画する
		static void drawLine(unsigned int handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	//************************************************************
	/* メッシュ関係の処理 */
	public:

		// 通常メッシュを作り、そのリソースのハンドルを返す
		static unsigned int createBasicMesh(const BasicMeshInitParam& initParam);

		// 通常メッシュを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		template<class IdType>
		static unsigned int createBasicMeshAndAttachId(IdType id, const BasicMeshInitParam& initParam);

		// 通常メッシュのコピーを作り、そのリソースのハンドルを返す
		static unsigned int copyBasicMesh(unsigned int originalHandle);

		// 通常メッシュのコピーを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		template<class IdType>
		static unsigned int copyBasicMeshAndAttachId(IdType id, unsigned int originalHandle);

		// 通常メッシュマテリアルを作り、そのリソースのハンドルを返す
		static unsigned int createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam);

		// 通常メッシュマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		template<class IdType>
		static unsigned int createBasicMeshMaterialAndAttachId(IdType id, const BasicMeshMaterialInitParam& initParam);

		// 通常メッシュマテリアルのコピーを作り、そのリソースのハンドルを返す
		static unsigned int copyBasicMeshMaterial(unsigned int originalHandle);

		// 通常メッシュマテリアルのコピーを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		template<class IdType>
		static unsigned int copyBasicMeshMaterialAndAttachId(IdType id, unsigned int originalHandle);

		// 通常メッシュが使用しているマテリアルを更新する
		static void setMaterialHandle(unsigned int meshHandle, unsigned int materialSlot, unsigned int materialHandle);

		// 指定の通常メッシュでシャドウマップを書き込む
		static void writeBasicMeshShadowMap(unsigned int handle);

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		static void setMaterialData(unsigned int handle);

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		template <class CbufferType>
		static void addMaterialAppendParam(unsigned int handle, unsigned int cbufferHandle, CbufferType&& value) { addMaterialAppendParamImpl(handle, cbufferHandle, sizeof(CbufferType), new CbufferType(std::forward<CbufferType>(value))); }

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		template <class CbufferType>
		static void updateMaterialAppendParam(unsigned int handle, unsigned int cbufferHandle, const CbufferType& value) { updateMaterialAppendParamImpl(handle, cbufferHandle, sizeof(CbufferType), &value); }

		// 指定の通常メッシュを描画する
		static void drawBasicMesh(unsigned int handle, const MeshDrawFuncBaseArgs& baseArgs);

		// pmdファイルをロードしてゲームの各種リソースクラスを作る
		static BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	//************************************************************
	/* スケルトン関連の処理 */
	public:

		// スケルトンを作り、そのリソースのハンドルを返す
		static unsigned int createSkeleton(const SkeletonInitParam& initParam);

		// スケルトンのコピーを作り、そのリソースのハンドルを返す
		static unsigned int copySkeleton(unsigned int originalHandle);

		// 指定のスケルトンの骨情報の定数バッファの値にコピーするためのバッファを作り、そのハンドルを返す
		// ※この関数で取得したハンドルは使用後に「DX12GameManager::eraseCopyBuffer(handle)」を必ず読んでバッファを削除してください
		static unsigned int createSkeletonCopyBufferHandle(unsigned int handle);

		// スケルトンを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		template<class IdType>
		static unsigned int createSkeletonAndAttachId(IdType id, const SkeletonInitParam& initParam);

		// 指定のスケルトンを使って引数が表すコピーバッファを使い骨情報を管理する定数バッファを更新する
		static void updateBoneMatrixCbuffer(unsigned int handle, unsigned int copyBufferHandle);

		// 骨情報を管理する定数バッファに単位行列を設定する
		static void resetBoneMatrixCbuffer();

	//************************************************************
	/* モーション関係の処理 */
	public:

		// vmdファイルを読み込んでモーションを作り、そのリソースのハンドルを返す
		static unsigned int loadMotion(const std::string& motionFileName);

		// vmdファイルを読み込んでモーションを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		template<class IdType>
		static unsigned int loadMotionAndAttachId(IdType id, const std::string& motionFileName);

		// 指定のモーションの終了キーの番号を取得する
		static unsigned int getMotionEndFrameNo(unsigned int handle);

		// 2種類のモーション情報を線形補完してスケルトンを更新する
		// ※補完割合の値は「0.0fでpreFrame100%」、「1.0fでcurFrame100%」となる
		static void updateMotion(
			unsigned int skeletonHandle,
			unsigned int curMotionHandle,
			unsigned int preMotionHnadle,
			unsigned int curFrame,
			unsigned int preFrame,
			float amount
		);

	//************************************************************
	/* ポストエフェクト関係の処理 */
	public:

		// ポストエフェクトのマテリアルを作り、そのリソースのハンドルを返す
		static unsigned int createPostEffectMaterial(const PostEffectMaterialInitParam& initParam);

		// ポストエフェクトのマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		template<class IdType>
		static unsigned int createPostEffectMaterialAndAttachId(IdType id, const PostEffectMaterialInitParam& initParam);

		// 指定のポストエフェクトを描画する
		static void drawPostEffect(unsigned int handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs);

	//************************************************************
	/* カメラ関係の処理 */
	public:

		// カメラを作り、そのリソースのハンドルを返す
		static unsigned int createCamera();

		// カメラを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		template<class IdType>
		static unsigned int createCameraAndAttachId(IdType id);

		// 指定のカメラのビュー行列を取得する
		static const tktkMath::Matrix4& getViewMatrix(unsigned int cameraHandle);

		// 指定のカメラのビュー行列を設定する
		static void setViewMatrix(unsigned int cameraHandle, const tktkMath::Matrix4& view);

		// 指定のカメラのプロジェクション行列を取得する
		static const tktkMath::Matrix4& getProjectionMatrix(unsigned int cameraHandle);

		// 指定のカメラのプロジェクション行列を設定する
		static void setProjectionMatrix(unsigned int cameraHandle, const tktkMath::Matrix4& projection);

	//************************************************************
	/* ライト関係の処理 */
	public:

		// ライトを作り、そのリソースのハンドルを返す
		static unsigned int createLight(
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ライトを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		template<class IdType>
		static unsigned int createLightAndAttachId(
			IdType id,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ライト情報の定数バッファを更新する
		static void updateLightCBuffer(unsigned int handle);

		// 指定のライトの環境光を設定する
		static void setLightAmbient(unsigned int handle, const tktkMath::Color& ambient);

		// 指定のライトの拡散反射光を設定する
		static void setLightDiffuse(unsigned int handle, const tktkMath::Color& diffuse);

		// 指定のライトの鏡面反射光を設定する
		static void setLightSpeqular(unsigned int handle, const tktkMath::Color& speqular);

		// 指定のライトの座標を設定する
		static void setLightPosition(unsigned int handle, const tktkMath::Vector3& position);

	//************************************************************
	/* サウンド関係の処理 */
	public:

		// 新しいサウンドを読み込み、そのリソースのハンドルを返す
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		static unsigned int loadSound(const std::string& fileName);

		// 新しいサウンドを読み込み、そのリソースのハンドルと引数のハンドルを結び付ける
		template<class IdType>
		static unsigned int loadSoundAndAttachId(IdType id, const std::string& fileName);

		// 指定したサウンドを再生する
		static void playSound(unsigned int handle, bool loopPlay);

		// 指定したサウンドを停止する
		static void stopSound(unsigned int handle);

		// 指定したサウンドを一時停止する
		static void pauseSound(unsigned int handle);

		// 大元の音量を変更する（0.0f～1.0f）
		static void setMasterVolume(float volume);

	//************************************************************
	/* マウス入力関係の処理 */
	public:

		// 指定のボタンが押されているか
		static bool isPush(MouseButtonType buttonType);

		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(MouseButtonType buttonType);

		// マウスカーソルの座標を取得する
		static tktkMath::Vector2 mousePos();

	//************************************************************
	/* キーボード入力関係の処理 */
	public:

		// 指定のキーが押されているかを判定
		static bool isPush(KeybordKeyType keyType);

		// 指定のキーが押され始めたかを判定
		static bool isTrigger(KeybordKeyType keyType);

	//************************************************************
	/* ゲームパッド入力関係の処理 */
	public:

		// 左スティックの傾きを取得（-1.0～1.0の間）
		static tktkMath::Vector2 getLstick();

		// 右スティックの傾きを取得（-1.0～1.0の間）
		static tktkMath::Vector2 getRstick();

		// 指定のボタンが押されているかを判定
		static bool isPush(GamePadBtnType btnType);

		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(GamePadBtnType btnType);

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
	/* リソース毎に設定したIDを引数にリソースハンドルを取得する */
	public:

		template <class SceneType>
		static unsigned int getSceneHandle				(SceneType id)				{ return getSceneHandleImpl(static_cast<int>(id)); };
		template <class SoundType>
		static unsigned int getSoundHandle				(SoundType id)				{ return getSoundHandleImpl(static_cast<int>(id)); };
		template <class PostEffectMaterialType>
		static unsigned int getPostEffectMaterialHandle	(PostEffectMaterialType id) { return getPostEffectMaterialHandleImpl(static_cast<int>(id)); };
		template <class SpriteMaterialType>
		static unsigned int getSpriteMaterialHandle		(SpriteMaterialType id)		{ return getSpriteMaterialHandleImpl(static_cast<int>(id)); };
		template <class Line2DMaterialType>
		static unsigned int getLine2DMaterialHandle		(Line2DMaterialType id)		{ return getLine2DMaterialHandleImpl(static_cast<int>(id)); };
		template <class SkeletonType>
		static unsigned int getSkeletonHandle			(SkeletonType id)			{ return getSkeletonHandleImpl(static_cast<int>(id)); };
		template <class MotionType>
		static unsigned int getMotionHandle				(MotionType id)				{ return getMotionHandleImpl(static_cast<int>(id)); };
		template <class BasicMeshType>
		static unsigned int getBasicMeshHandle			(BasicMeshType id)			{ return  getBasicMeshHandleImpl(static_cast<int>(id)); };
		template <class BasicMeshMaterialType>
		static unsigned int getBasicMeshMaterialHandle	(BasicMeshMaterialType id)	{ return getBasicMeshMaterialHandleImpl(static_cast<int>(id)); };
		template <class CameraType>
		static unsigned int getCameraHandle				(CameraType id)				{ return getCameraHandleImpl(static_cast<int>(id)); };
		template <class LightType>
		static unsigned int getLightHandle				(LightType id)				{ return  getLightHandleImpl(static_cast<int>(id)); };

	//************************************************************
	/* リソースを使うためのハンドルとIDを結びつける */
	public:

		static void setSceneHandle				(int id, unsigned int handle);
		static void setSoundHandle				(int id, unsigned int handle);
		static void setPostEffectMaterialHandle	(int id, unsigned int handle);
		static void setSpriteMaterialHandle		(int id, unsigned int handle);
		static void setLine2DMaterialHandle		(int id, unsigned int handle);
		static void setSkeletonHandle			(int id, unsigned int handle);
		static void setMotionHandle				(int id, unsigned int handle);
		static void setBasicMeshHandle			(int id, unsigned int handle);
		static void setBasicMeshMaterialHandle	(int id, unsigned int handle);
		static void setCameraHandle				(int id, unsigned int handle);
		static void setLightHandle				(int id, unsigned int handle);

	//************************************************************
	/* システムのリソースを使うためのハンドルを取得する */
	public:

		static unsigned int getSystemHandle(SystemViewportType type);
		static unsigned int getSystemHandle(SystemScissorRectType type);
		static unsigned int getSystemHandle(SystemVertexBufferType type);
		static unsigned int getSystemHandle(SystemIndexBufferType type);
		static unsigned int getSystemHandle(SystemCBufferType type);
		static unsigned int getSystemHandle(SystemTextureBufferType type);
		static unsigned int getSystemHandle(SystemDsBufferType type);
		static unsigned int getSystemHandle(SystemBasicDescriptorHeapType type);
		static unsigned int getSystemHandle(SystemRtvDescriptorHeapType type);
		static unsigned int getSystemHandle(SystemDsvDescriptorHeapType type);
		static unsigned int getSystemHandle(SystemRootSignatureType type);
		static unsigned int getSystemHandle(SystemPipeLineStateType type);
		static unsigned int getSystemHandle(SystemCameraType type);
		static unsigned int getSystemHandle(SystemLightType type);
		static unsigned int getSystemHandle(SystemBasicMeshType type);
		static unsigned int getSystemHandle(SystemBasicMeshMaterialType type);
		static unsigned int getSystemHandle(SystemPostEffectMaterialType type);

	//************************************************************
	/* システムのリソースを使うためのハンドルとシステムのリソースの種類を結びつける */

		static void setSystemHandle(SystemViewportType type,			unsigned int handle);
		static void setSystemHandle(SystemScissorRectType type,			unsigned int handle);
		static void setSystemHandle(SystemVertexBufferType type,		unsigned int handle);
		static void setSystemHandle(SystemIndexBufferType type,			unsigned int handle);
		static void setSystemHandle(SystemCBufferType type,				unsigned int handle);
		static void setSystemHandle(SystemTextureBufferType type,		unsigned int handle);
		static void setSystemHandle(SystemRtBufferType type,			unsigned int handle);
		static void setSystemHandle(SystemDsBufferType type,			unsigned int handle);
		static void setSystemHandle(SystemBasicDescriptorHeapType type,	unsigned int handle);
		static void setSystemHandle(SystemRtvDescriptorHeapType type,	unsigned int handle);
		static void setSystemHandle(SystemDsvDescriptorHeapType type,	unsigned int handle);
		static void setSystemHandle(SystemRootSignatureType type,		unsigned int handle);
		static void setSystemHandle(SystemPipeLineStateType type,		unsigned int handle);
		static void setSystemHandle(SystemCameraType type,				unsigned int handle);
		static void setSystemHandle(SystemLightType type,				unsigned int handle);
		static void setSystemHandle(SystemBasicMeshType type,			unsigned int handle);
		static void setSystemHandle(SystemBasicMeshMaterialType type,	unsigned int handle);
		static void setSystemHandle(SystemPostEffectMaterialType type,	unsigned int handle);

	//************************************************************
	/* 裏実装 */
	public:

		static void addCollisionGroupImpl(int firstGroup, int secondGroup);

		static unsigned int createCopyBufferImpl(const CopyBufferInitParam& initParam);
		static unsigned int createVertexBufferImpl(unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);
		static unsigned int createCbufferImpl(unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);
		static unsigned int createSceneImpl(const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);
		static void updateCopyBufferImpl(unsigned int handle, unsigned int bufferSize, const void* bufferDataTopPos);
		static void addMaterialAppendParamImpl(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos);
		static void updateMaterialAppendParamImpl(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, const void* dataTopPos);

		static unsigned int getSceneHandleImpl					(int id);
		static unsigned int getSoundHandleImpl					(int id);
		static unsigned int getPostEffectMaterialHandleImpl		(int id);
		static unsigned int getSpriteMaterialHandleImpl			(int id);
		static unsigned int getLine2DMaterialHandleImpl			(int id);
		static unsigned int getSkeletonHandleImpl				(int id);
		static unsigned int getMotionHandleImpl					(int id);
		static unsigned int getBasicMeshHandleImpl				(int id);
		static unsigned int getBasicMeshMaterialHandleImpl		(int id);
		static unsigned int getCameraHandleImpl					(int id);
		static unsigned int getLightHandleImpl					(int id);

	//************************************************************
	private:

		static std::unique_ptr<Window>							m_window;
		static std::unique_ptr<DX3DBaseObjects>					m_dx3dBaseObjects;
		static std::unique_ptr<GameObjectManager>				m_gameObjectManager;
		static std::unique_ptr<ComponentManager>				m_componentManager;
		static std::unique_ptr<DXGameResource>					m_dxGameResource;
		static std::unique_ptr<DXGameResourceHandleGetter>		m_dxGameResourceHandleGetter;
		static std::unique_ptr<SystemDXGameResourceHandleGetter>m_systemDXGameResourceHandleGetter;
		static std::unique_ptr<DirectInputWrapper>				m_directInputWrapper;
		static std::unique_ptr<Mouse>							m_mouse;
		static std::unique_ptr<ElapsedTimer>					m_elapsedTimer;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は実装が多めのテンプレート関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// シーンを作り、そのリソースのハンドルと引数のハンドルを結び付ける
	template<class SceneType, class IdType, class ...Args>
	inline unsigned int DX12GameManager::addSceneAndAttachId(IdType id, Args && ...constructorArgs)
	{
		unsigned int createdHandle = addScene<SceneType>(std::forward<Args>(constructorArgs)...);
		setSceneHandle(static_cast<int>(id), createdHandle);
		return createdHandle;
	}

	// スプライトマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
	template<class IdType>
	inline unsigned int DX12GameManager::createSpriteMaterialAndAttachId(IdType id, const SpriteMaterialInitParam& initParam)
	{
		unsigned int createdHandle = createSpriteMaterial(initParam);
		setSpriteMaterialHandle(static_cast<int>(id), createdHandle);
		return createdHandle;
	}

	// ２Ｄラインマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
	template<class IdType>
	inline unsigned int DX12GameManager::createLine2DMaterialAndAttachId(IdType id)
	{
		unsigned int createdHandle = createLine2DMaterial();
		setLine2DMaterialHandle(static_cast<int>(id), createdHandle);
		return createdHandle;
	}

	// 通常メッシュを作り、そのリソースのハンドルと引数のハンドルを結び付ける
	template<class IdType>
	inline unsigned int DX12GameManager::createBasicMeshAndAttachId(IdType id, const BasicMeshInitParam& initParam)
	{
		unsigned int createdHandle = createBasicMesh(initParam);
		setBasicMeshHandle(static_cast<int>(id), createdHandle);
		return createdHandle;
	}

	// 通常メッシュのコピーを作り、そのリソースのハンドルと引数のハンドルを結び付ける
	template<class IdType>
	inline unsigned int DX12GameManager::copyBasicMeshAndAttachId(IdType id, unsigned int originalHandle)
	{
		unsigned int createdHandle = copyBasicMesh(originalHandle);
		setBasicMeshHandle(static_cast<int>(id), createdHandle);
		return createdHandle;
	}

	// 通常メッシュマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
	template<class IdType>
	inline unsigned int DX12GameManager::createBasicMeshMaterialAndAttachId(IdType id, const BasicMeshMaterialInitParam& initParam)
	{
		unsigned int createdHandle = createBasicMeshMaterial(initParam);
		setBasicMeshMaterialHandle(static_cast<int>(id), createdHandle);
		return createdHandle;
	}

	// 通常メッシュマテリアルのコピーを作り、そのリソースのハンドルと引数のハンドルを結び付ける
	template<class IdType>
	inline unsigned int DX12GameManager::copyBasicMeshMaterialAndAttachId(IdType id, unsigned int originalHandle)
	{
		unsigned int createdHandle = copyBasicMeshMaterial(originalHandle);
		setBasicMeshMaterialHandle(static_cast<int>(id), createdHandle);
		return createdHandle;
	}

	// スケルトンを作り、そのリソースのハンドルと引数のハンドルを結び付ける
	template<class IdType>
	inline unsigned int DX12GameManager::createSkeletonAndAttachId(IdType id, const SkeletonInitParam& initParam)
	{
		unsigned int createdHandle = createSkeleton(initParam);
		setSkeletonHandle(static_cast<int>(id), createdHandle);
		return createdHandle;
	}

	// vmdファイルを読み込んでモーションを作り、そのリソースのハンドルと引数のハンドルを結び付ける
	template<class IdType>
	inline unsigned int DX12GameManager::loadMotionAndAttachId(IdType id, const std::string& motionFileName)
	{
		unsigned int createdHandle = loadMotion(motionFileName);
		setMotionHandle(static_cast<int>(id), createdHandle);
		return createdHandle;
	}

	// ポストエフェクトのマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
	template<class IdType>
	inline unsigned int DX12GameManager::createPostEffectMaterialAndAttachId(IdType id, const PostEffectMaterialInitParam& initParam)
	{
		unsigned int createdHandle = createPostEffectMaterial(initParam);
		setPostEffectMaterialHandle(static_cast<int>(id), createdHandle);
		return createdHandle;
	}

	// ライトを作り、そのリソースのハンドルと引数のハンドルを結び付ける
	template<class IdType>
	inline unsigned int DX12GameManager::createCameraAndAttachId(IdType id)
	{
		unsigned int createdHandle = createCamera();
		setCameraHandle(static_cast<int>(id), createdHandle);
		return createdHandle;
	}

	// ライトを作り、そのリソースのハンドルと引数のハンドルを結び付ける
	template<class IdType>
	inline unsigned int DX12GameManager::createLightAndAttachId(IdType id, const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular, const tktkMath::Vector3& position)
	{
		unsigned int createdHandle = createLight(ambient, diffuse, speqular, position);
		setLightHandle(static_cast<int>(id), createdHandle);
		return createdHandle;
	}

	// 新しいサウンドを読み込み、そのリソースのハンドルと引数のハンドルを結び付ける
	template<class IdType>
	inline unsigned int DX12GameManager::loadSoundAndAttachId(IdType id, const std::string& fileName)
	{
		unsigned int createdHandle = loadSound(fileName);
		setSoundHandle(static_cast<int>(id), createdHandle);
		return createdHandle;
	}
}
#endif // !DX12_GAME_MANAGER_H_