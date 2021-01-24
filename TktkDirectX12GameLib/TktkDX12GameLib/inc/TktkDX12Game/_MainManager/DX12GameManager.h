#ifndef DX12_GAME_MANAGER_H_
#define DX12_GAME_MANAGER_H_

/* SelfInitParam */
#include "DX12GameManagerInitParam.h"

/* funcUseType */
#include <string>
#include <typeindex>
#include <array>
#include <vector>
#include <forward_list>

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix3.h>
#include <TktkMath/Structs/Matrix4.h>

#include <TktkDX12Wrapper/Resource/Viewport/ViewportInitParam.h>
#include <TktkDX12Wrapper/Resource/ScissorRect/ScissorRectInitParam.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/RootSignature/RootSignatureInitParam.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include <TktkDX12Wrapper/Resource/Buffer/CopySourceDataCarrier.h>
#include <TktkDX12Wrapper/Resource/Buffer/Upload/UploadBufferInitParam.h>
#include <TktkDX12Wrapper/Resource/Buffer/Vertex/VertexDataCarrier.h>
#include <TktkDX12Wrapper/Resource/Buffer/DepthStencil/DepthStencilBufferInitParam.h>
#include <TktkDX12Wrapper/Resource/Buffer/Texture/TextureBufferInitParam.h>
#include <TktkDX12Wrapper/Resource/DescriptorHeap/Basic/BasicDescriptorHeapInitParam.h>
#include <TktkDX12Wrapper/Resource/DescriptorHeap/Rtv/RtvDescriptorHeapInitParam.h>
#include <TktkDX12Wrapper/Resource/DescriptorHeap/Dsv/DsvDescriptorHeapInitParam.h>
#include <TktkDX12Wrapper/_BaseObjects/PrimitiveTopology.h>
#include <TktkDX12Wrapper/Resource/DescriptorHeap/DescriptorHeapParam.h>

#include "../EventMessage/MessageTypeCarrier.h"
#include "../EventMessage/MessageAttachment.h"

#include "../DXGameResource/DXGameShaderResouse/Sprite/Structs/SpriteMaterialInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/Sprite/Structs/SpriteMaterialDrawFuncArgs.h"
#include "../DXGameResource/DXGameShaderResouse/Sprite/Structs/TempSpriteMaterialInstanceData.h"
#include "../DXGameResource/DXGameShaderResouse/Line2D/Structs/Line2DMaterialDrawFuncArgs.h"
#include "../DXGameResource/DXGameShaderResouse/Billboard/Structs/BillboardMaterialInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/Billboard/Structs/BillboardDrawFuncBaseArgs.h"
#include "../DXGameResource/DXGameShaderResouse/Billboard/Structs/BillboardMaterialInstanceData.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshDrawFuncBaseArgs.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/Structs/MeshLoadPmdArgs.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/Structs/MeshLoadPmxArgs.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/Structs/MeshLoadPmdReturnValue.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/Structs/MeshLoadPmxReturnValue.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialAppendParamInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialAppendParamUpdateFuncArgs.h"
#include "../DXGameResource/DXGameShaderResouse/MeshResouse/Skeleton/Structs/SkeletonInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/PostEffect/Structs/PostEffectMaterialInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/PostEffect/Structs/PostEffectMaterialDrawFuncArgs.h"
#include "../DXGameResource/DXGameShaderResouse/PostEffect/Structs/PostEffectMaterialAppendParamInitParam.h"
#include "../DXGameResource/DXGameShaderResouse/PostEffect/Structs/PostEffectMaterialAppendParamUpdateFuncArgs.h"
#include "../DXGameResource/GameObjectResouse/GameObject/GameObjectPtr.h"
#include "../DXGameResource/GameObjectResouse/GameObject/GameObjectTagCarrier.h"
#include "../DXGameResource/GameObjectResouse/Component/ComponentVTable.h"
#include "../DXGameResource/GameObjectResouse/Component/ComponentMainList/ComponentListVTable.h" // TODO : フォルダ階層
#include "../DXGameResource/GameObjectResouse/Component/ComponentCollisionFunc/CollisionGroupTypeCarrier.h"
#include "../DXGameResource/OtherResouse/Scene/Structs/SceneInitParam.h"

#include "../UtilityProcessManager/InputManager/InputGetter/MouseInputGetter/MouseBtnType.h"
#include "../UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/KeyboardInputGetter/KeybordKeyType.h"
#include "../UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/GamePadInputGetter/GamePadBtnType.h"
#include "../UtilityProcessManager/InputManager/CommandTypeManager/CommandIdCarrier.h"
#include "../UtilityProcessManager/InputManager/CommandTypeManager/DirectionCommandId.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemViewportType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemScissorRectType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemUploadBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemVertexBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemIndexBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemConstantBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemTextureBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRenderTargetBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemDepthStencilBufferType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemBasicDescriptorHeapType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRtvDescriptorHeapType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemDsvDescriptorHeapType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRootSignatureType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemPipeLineStateType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemSpriteType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemCameraType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemLightType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemMeshType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemMeshMaterialType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemPostEffectMaterialType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemPostEffectDrawFuncRunnerType.h"
#include "../UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

#include "../../TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawFuncRunnerInitParam.h"
#include "../../TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawFuncRunnerInitParam.h"
#include "../../TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawFuncRunnerInitParam.h"
#include "../../TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawFuncRunnerInitParam.h"


namespace tktk
{
	// 前方宣言
	class GraphicManager;
	class DXGameResource;
	class UtilityProcessManager;
	
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
	
		// ゲーム描画エリアサイズを取得する
		static const tktkMath::Vector2& getDrawGameAreaSize();

		// スクリーンサイズを取得する
		static const tktkMath::Vector2& getScreenSize();
	
	//************************************************************
	/* シーンの処理 */
	public:
	
		// シーンを作り、そのリソースのハンドルを返す
		static size_t addScene(const SceneInitParam& initParam);
	
		// シーンを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t addSceneAndAttachId(ResourceIdCarrier id, const SceneInitParam& initParam);
	
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
		static void addRunFuncPriority(float priority)
		{
			addRunFuncPriority(typeid(ComponentType), priority);
		}

		// コンポーネントの型ごとの更新優先度を設定する
		// ※デフォルト（0.0f）で値が小さい程、早く実行される
		static void addRunFuncPriority(std::type_index type, float priority);
	
		// 衝突判定の組み合わせを追加する
		static void addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup);
	
		// テンプレート引数の型のコンポーネントを引数の値を使って作る
		template <class ComponentType, class... Args>
		static ComponentPtr<ComponentType> createComponent(const GameObjectPtr& user, Args&&... args)
		{
			auto basePtr = addComponent(typeid(ComponentType), &ComponentVTableInitializer<ComponentType>::m_componentVTableBundle, &ComponentListVTableInitializer<ComponentType>::m_componentListVTable, user, std::make_shared<ComponentType>(std::forward<Args>(args)...));
			return basePtr.castPtr<ComponentType>();
		}

		// 引数のコンポーネントを追加する
		static ComponentBasePtr addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const GameObjectPtr& user, const std::shared_ptr<ComponentBase>& componentPtr);

	//************************************************************
	/* 直接DX12の処理を呼ぶ */
	public:
	
		// コマンドリストを手動で実行する
		static void executeCommandList();
	
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
	
		// コマンドリストに指定の頂点バッファを登録する（インスタンス描画用）
		static void setVertexBuffer(size_t meshVertHandle, size_t instancingVertHandle);

		// 指定のインデックスバッファをコマンドリストに設定する
		static void setIndexBuffer(size_t handle);
	
		// 指定のディスクリプタヒープの配列をコマンドリストに設定する
		static void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray);
	
		// ブレンドファクターを設定する
		static void setBlendFactor(const std::array<float, 4>& blendFactor);
	
		// プリミティブトポロジを設定する
		static void setPrimitiveTopology(PrimitiveTopology topology);
	
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
	
		// ビューポートを作り、そのリソースのハンドルを返す
		static size_t createViewport(const std::vector<ViewportInitParam>& initParamArray);

		// シザー矩形を作り、そのリソースのハンドルを返す
		static size_t createScissorRect(const std::vector<ScissorRectInitParam>& initParamArray);

		// ルートシグネチャを作り、そのリソースのハンドルを返す
		static size_t createRootSignature(const RootSignatureInitParam& initParam);
	
		// パイプラインステートを作り、そのリソースのハンドルを返す
		static size_t createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);
	
		// アップロードバッファを作り、そのリソースのハンドルを返す
		static size_t createUploadBuffer(const UploadBufferInitParam& initParam);
		
		// 一時的なアップロードバッファを作る（次のフレームでは消滅する想定の為、ハンドルは返さない）
		static void createTempUploadBuffer(const UploadBufferInitParam& initParam);

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
	
		// テクスチャを作り、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		static size_t createTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
	
		// テクスチャをロードし、そのリソースのハンドルを返す（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		static size_t loadTextureBuffer(const std::string& texDataPath);
		
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
	
		// 指定のレンダーターゲットビューを事前に設定したクリアカラーでクリアする
		static void clearRtv(size_t handle, size_t rtvLocationIndex);
	
		// 指定のテクスチャのサイズを取得する（ピクセル（テクセル））
		static const tktkMath::Vector3& getTextureBufferSizePx(size_t handle);
		static const tktkMath::Vector2& getDsBufferSizePx(size_t handle);
		static const tktkMath::Vector2& getRtBufferSizePx(size_t handle);
	
	//************************************************************
	/* スプライト関係の処理 */
	public:
	
		// スプライトマテリアルを作り、そのリソースのハンドルを返す
		static size_t createSpriteMaterial(const SpriteMaterialInitParam& initParam, const SpriteDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// スプライトマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createSpriteMaterialAndAttachId(ResourceIdCarrier id, const SpriteMaterialInitParam& initParam, const SpriteDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// 指定したスプライトが使用するテクスチャのサイズを取得する
		static const tktkMath::Vector2& getSpriteTextureSize(size_t handle);

		// 指定したスプライトの最大のインスタンス数を取得する
		static size_t getMaxSpriteInstanceCount(size_t handle);

		// 指定したスプライトの現在のインスタンス数を取得する
		static size_t getCurSpriteInstanceCount(size_t handle);

		// 指定したスプライトをインスタンス描画する時に使用する値を削除する
		static void clearSpriteInstanceParam(size_t handle);

		// 指定したスプライトをインスタンス描画する時に使用する値を追加する
		static void addSpriteInstanceParam(size_t handle, float drawPriority, const TempSpriteMaterialInstanceData& instanceParam);

		// 指定しスプライトをインスタンス描画する時に使用する値を頂点バッファに書き込む
		static void updateSpriteInstanceParam(size_t handle);

		// 指定したスプライトを描画する
		static void drawSprite(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs);
	
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
		static size_t createBillboardMaterial(const BillboardMaterialInitParam& initParam, const BillboardDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// ビルボードマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createBillboardMaterialAndAttachId(ResourceIdCarrier id, const BillboardMaterialInitParam& initParam, const BillboardDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// 指定したビルボードが使用するテクスチャのサイズを取得する
		static const tktkMath::Vector2& getBillboardTextureSize(size_t handle);

		// 指定したビルボードをインスタンス描画する時に使用する値を削除する
		static void clearBillboardInstanceParam(size_t handle);

		// 指定したビルボードをインスタンス描画する時に使用する値を追加する
		static void addBillboardInstanceParam(size_t handle, const BillboardMaterialInstanceData& instanceParam);

		// 指定したビルボードをインスタンス描画する時に使用する値をｚソートして頂点バッファに書き込む
		static void updateBillboardInstanceParam(size_t handle, const tktkMath::Matrix4& viewProjMatrix);

		// 指定したビルボードを描画する
		static void drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs);
	
	//************************************************************
	/* メッシュ関係の処理 */
	public:
	
		// メッシュを作り、そのリソースのハンドルを返す
		static size_t createMesh(const MeshInitParam& meshInitParam, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// メッシュを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createMeshAndAttachId(ResourceIdCarrier id, const MeshInitParam& meshInitParam, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// メッシュのコピーを作り、そのリソースのハンドルを返す
		static size_t copyMesh(size_t originalHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// メッシュのコピーを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t copyMeshAndAttachId(ResourceIdCarrier id, size_t originalHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);
	
		// メッシュマテリアルを作り、そのリソースのハンドルを返す
		static size_t createMeshMaterial(const MeshMaterialInitParam& initParam);
	
		// メッシュマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createMeshMaterialAndAttachId(ResourceIdCarrier id, const MeshMaterialInitParam& initParam);
	
		// メッシュマテリアルのコピーを作り、そのリソースのハンドルを返す
		static size_t copyMeshMaterial(size_t originalHandle);
	
		// メッシュマテリアルのコピーを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t copyMeshMaterialAndAttachId(ResourceIdCarrier id, size_t originalHandle);
	
		// テクスチャを貼った立方体メッシュを作り、そのハンドルを返す
		static size_t makeBoxMesh(size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// テクスチャを貼った立方体メッシュを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t makeBoxMeshAndAttachId(ResourceIdCarrier id, size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// スカイボックスメッシュを作り、そのハンドルを返す
		static size_t makeSkyBoxMesh(size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// スカイボックスメッシュを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t makeSkyBoxMeshAndAttachId(ResourceIdCarrier id, size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// pmdファイルをロードしてゲームの各種リソースクラスを作る
		static MeshLoadPmdReturnValue loadPmd(const MeshLoadPmdArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// pmxファイルをロードしてゲームの各種リソースクラスを作る
		static MeshLoadPmxReturnValue loadPmx(const MeshLoadPmxArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// メッシュが使用しているマテリアルを更新する
		static void setMeshMaterialHandle(size_t handle, size_t materialSlot, size_t materialHandle);
	
		// 指定のメッシュのマテリアル情報をグラフィックパイプラインに設定する
		static void setMeshMaterialData(size_t handle);
	
		// 指定のメッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		static void addMeshMaterialAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam);

		// 指定のメッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		static void updateMeshMaterialAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

		// 指定のメッシュをインスタンス描画する時に使用する値を削除する
		static void clearMeshInstanceParam(size_t handle);

		// 指定のメッシュをインスタンス描画する時に使用する値を追加する
		static void addMeshInstanceVertParam(size_t handle, const CopySourceDataCarrier& instanceParam);

		// 指定のスキニングメッシュをインスタンス描画する時に使用する骨行列を追加する
		static void addMeshInstanceBoneMatrix(size_t meshHandle, size_t skeletonHandle);
		
		// 指定のメッシュでシャドウマップを書き込む
		static void writeMeshShadowMap(size_t handle);

		// 指定のスキニングメッシュでシャドウマップを書き込む
		static void writeMeshShadowMapUseBone(size_t handle);

		// 指定のメッシュをインスタンス描画する
		static void drawMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs);

		// スキニングメッシュをインスタンス描画する
		static void drawMeshUseBone(size_t handle, const MeshDrawFuncBaseArgs& baseArgs);
	
	//************************************************************
	/* スケルトン関連の処理 */
	public:
	
		// スケルトンを作り、そのリソースのハンドルを返す
		static size_t createSkeleton(const SkeletonInitParam& initParam);
	
		// スケルトンのコピーを作り、そのリソースのハンドルを返す
		static size_t copySkeleton(size_t originalHandle);
	
		// スケルトンを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createSkeletonAndAttachId(ResourceIdCarrier id, const SkeletonInitParam& initParam);
	
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
			float curFrame,
			float preFrame,
			float amount
		);
	
	//************************************************************
	/* ポストエフェクトマテリアル関係の処理 */
	public:
	
		// ポストエフェクトのマテリアルを作り、そのリソースのハンドルを返す
		static size_t createPostEffectMaterial(const PostEffectMaterialInitParam& initParam);
	
		// ポストエフェクトのマテリアルを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createPostEffectMaterialAndAttachId(ResourceIdCarrier id, const PostEffectMaterialInitParam& initParam);
	
		// 指定のポストエフェクトを描画する
		static void drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs);
	
		// 指定したポストエフェクトマテリアルで追加で管理する定数バッファのハンドルと値を設定する
		static void addPostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamInitParam& initParam);

		// 指定したポストエフェクトマテリアルで追加で管理する定数バッファの値を更新する
		static void updatePostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

	//************************************************************
	/* ポストエフェクトの描画関数を呼ぶコンポーネントの処理 */
	public:

		// 新たなポストエフェクトの描画関数を呼ぶコンポーネントを作り、そのハンドルを返す
		static size_t createPostEffectDrawFuncRunner(size_t postEffectMaterialHandle, const PostEffectDrawFuncRunnerInitParam& initParam);

		// 新たなポストエフェクトの描画関数を呼ぶコンポーネントを作り、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createPostEffectDrawFuncRunnerAndAttachId(ResourceIdCarrier id, size_t postEffectMaterialHandle, const PostEffectDrawFuncRunnerInitParam& initParam);

		// 指定したポストエフェクトを実行開始する（他のポストエフェクトは停止する）
		static void startPostEffect(size_t handle);

		// 全てのポストエフェクトを停止する
		static void stopPostEffect();

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
	/* フォント関係の処理 */
	public:

		// システムフォントを使う準備をして、そのリソースのハンドルを返す
		static size_t createFont(const std::string& systemFontName, float fontThicknessRate);

		// フォントファイルを読み込み、そのフォントを使う準備をして、そのリソースのハンドルを返す
		static size_t createFont(const std::string& fontFilePath, const std::string& fontName, float fontThicknessRate);

		// システムフォントを使う準備をして、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createFontAndAttachId(ResourceIdCarrier id, const std::string& systemFontName, float fontThicknessRate);

		// フォントファイルを読み込み、そのフォントを使う準備をして、そのリソースのハンドルと引数のハンドルを結び付ける
		static size_t createFontAndAttachId(ResourceIdCarrier id, const std::string& fontFilePath, const std::string& fontName, float fontThicknessRate);

		// テキストテクスチャデータに引数の文字列のテクスチャデータを書き込み、書き込んだバッファの最大ｘ座標を返す
		static size_t updateTextTextureData(size_t handle, const std::string& text, std::vector<unsigned char>* data);

		// テキスト用テクスチャ１行分のデータサイズを計算
		static unsigned int getTextTextureLineDataSize();

		//// 指定のアップロードバッファに引数の文字列のテクスチャデータを書き込み、書き込んだバッファの最大ｘ座標を返す
		//static size_t updateTextTextureUploadBuffData(size_t handle, const std::string& text);
	
		// テキストテクスチャのアップロードバッファを実際のテクスチャバッファにコピーする
		static void copyTextTextureUploadBuffer();

	//************************************************************
	/* インプットマネージャーの処理 */
	public:
	
		// IDに対応した入力が押されているかを判定
		static bool isPush(CommandIdCarrier commandId);
	
		// IDに対応した入力が押され始めたかを判定
		static bool isTrigger(CommandIdCarrier commandId);
	
		// 移動方向を取得
		static const tktkMath::Vector2& getMoveInput();
	
		// 視点移動方向を取得
		static const tktkMath::Vector2& getLookInput();
	
		// 各種入力とIDを結びつける
		static void addCommand(CommandIdCarrier commandId, KeybordKeyType keyType);
		static void addCommand(CommandIdCarrier commandId, GamePadBtnType btnType);
		static void addCommand(CommandIdCarrier commandId, MouseBtnType btnType);
	
		// 各種入力と移動コマンドを結びつける
		static void addDirectionCommand(DirectionCommandId directionCommand, KeybordKeyType keyType);
		static void addDirectionCommand(DirectionCommandId directionCommand, GamePadBtnType btnType);
		static void addDirectionCommand(DirectionCommandId directionCommand, MouseBtnType btnType);
	
	//************************************************************
	/* マウス入力関係の処理 */
	public:
	
		// 指定のボタンが押されているか
		static bool isPush(MouseBtnType buttonType);
	
		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(MouseBtnType buttonType);
	
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
	/* システムのリソースを使うためのハンドルを取得する */
	public:
	
		static size_t getSystemHandle(SystemViewportType type);
		static size_t getSystemHandle(SystemScissorRectType type);
		static size_t getSystemHandle(SystemUploadBufferType type);
		static size_t getSystemHandle(SystemVertexBufferType type);
		static size_t getSystemHandle(SystemIndexBufferType type);
		static size_t getSystemHandle(SystemCBufferType type);
		static size_t getSystemHandle(SystemTextureBufferType type);
		static size_t getSystemHandle(SystemRtBufferType type);
		static size_t getSystemHandle(SystemDsBufferType type);
		static size_t getSystemHandle(SystemBasicDescriptorHeapType type);
		static size_t getSystemHandle(SystemRtvDescriptorHeapType type);
		static size_t getSystemHandle(SystemDsvDescriptorHeapType type);
		static size_t getSystemHandle(SystemRootSignatureType type);
		static size_t getSystemHandle(SystemPipeLineStateType type);
		static size_t getSystemHandle(SystemSpriteType type);
		static size_t getSystemHandle(SystemCameraType type);
		static size_t getSystemHandle(SystemLightType type);
		static size_t getSystemHandle(SystemMeshType type);
		static size_t getSystemHandle(SystemMeshMaterialType type);
		static size_t getSystemHandle(SystemPostEffectMaterialType type);
		static size_t getSystemHandle(SystemPostEffectDrawFuncRunnerType type);
	
	//************************************************************
	/* システムのリソースを使うためのハンドルとシステムのリソースの種類を結びつける */
	
		static void setSystemHandle(SystemViewportType type,					size_t handle);
		static void setSystemHandle(SystemScissorRectType type,					size_t handle);
		static void setSystemHandle(SystemUploadBufferType type,				size_t handle);
		static void setSystemHandle(SystemVertexBufferType type,				size_t handle);
		static void setSystemHandle(SystemIndexBufferType type,					size_t handle);
		static void setSystemHandle(SystemCBufferType type,						size_t handle);
		static void setSystemHandle(SystemTextureBufferType type,				size_t handle);
		static void setSystemHandle(SystemRtBufferType type,					size_t handle);
		static void setSystemHandle(SystemDsBufferType type,					size_t handle);
		static void setSystemHandle(SystemBasicDescriptorHeapType type,			size_t handle);
		static void setSystemHandle(SystemRtvDescriptorHeapType type,			size_t handle);
		static void setSystemHandle(SystemDsvDescriptorHeapType type,			size_t handle);
		static void setSystemHandle(SystemRootSignatureType type,				size_t handle);
		static void setSystemHandle(SystemPipeLineStateType type,				size_t handle);
		static void setSystemHandle(SystemSpriteType type,						size_t handle);
		static void setSystemHandle(SystemCameraType type,						size_t handle);
		static void setSystemHandle(SystemLightType type,						size_t handle);
		static void setSystemHandle(SystemMeshType type,						size_t handle);
		static void setSystemHandle(SystemMeshMaterialType type,				size_t handle);
		static void setSystemHandle(SystemPostEffectMaterialType type,			size_t handle);
		static void setSystemHandle(SystemPostEffectDrawFuncRunnerType type,	size_t handle);
	
	//************************************************************
	/* リソースIDからリソースハンドルを取得する */
	public:
	
		static size_t getSceneHandle					(ResourceIdCarrier id);
		static size_t getSoundHandle					(ResourceIdCarrier id);
		static size_t getFontHandle						(ResourceIdCarrier id);
		static size_t getPostEffectMaterialHandle		(ResourceIdCarrier id);
		static size_t getSpriteMaterialHandle			(ResourceIdCarrier id);
		static size_t getLine2DMaterialHandle			(ResourceIdCarrier id);
		static size_t getBillboardMaterialHandle		(ResourceIdCarrier id);
		static size_t getSkeletonHandle					(ResourceIdCarrier id);
		static size_t getMotionHandle					(ResourceIdCarrier id);
		static size_t getBasicMeshHandle				(ResourceIdCarrier id);
		static size_t getBasicMeshMaterialHandle		(ResourceIdCarrier id);
		static size_t getPostEffectDrawFuncRunnerHandle	(ResourceIdCarrier id);
		static size_t getCameraHandle					(ResourceIdCarrier id);
		static size_t getLightHandle					(ResourceIdCarrier id);
	
	//************************************************************
	private:

		static bool												m_isGameExit;
		static std::unique_ptr<GraphicManager>					m_graphicManager;
		static std::unique_ptr<DXGameResource>					m_dxGameResource;
		static std::unique_ptr<UtilityProcessManager>			m_utilityProcessManager;
	};
}
#endif // !DX12_GAME_MANAGER_H_