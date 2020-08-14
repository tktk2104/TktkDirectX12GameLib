#ifndef DX12_GAME_MANAGER_H_
#define DX12_GAME_MANAGER_H_

#include <string>
#include <vector>
#include <forward_list>
#include <memory>
#include <utility>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>

#include "../Component/ComponentManager.h"			// テンプレート引数に型情報を渡す必要がある為隠蔽できない
#include "../DXGameResource/Scene/SceneVTable.h"	// シーンマネージャークラスを隠蔽する為にテンプレート関連のみ分離
#include "../DXGameResource/Mesh/BasicMesh/Maker/SphereMeshMaker.h"	// デフォルトの球体メッシュを作るためのクラス

// 関数呼び出しに必要な型のインクルード
#include <TktkDX12Wrapper/Resource/_SystemResourceIdGetter/SystemResourceType.h>
#include "../DXGameResource/_SystemDXGameResourceIdGetter/IdType/SystemBasicMeshType.h"
#include "../DXGameResource/_SystemDXGameResourceIdGetter/IdType/SystemBasicMeshMaterialType.h"
#include "../DXGameResource/_SystemDXGameResourceIdGetter/IdType/SystemPostEffectMaterialType.h"
#include "../GameObject/GameObjectPtr.h"			
#include "../EventMessage/MessageAttachment.h"

#include "DX12GameManagerUseInitParams.h"
#include "DX12GameManagerFuncInOutValueType.h"
#include "DX12GameManagerInitParam.h"

namespace tktk
{
	// 前方宣言
	class Window;
	class DX3DBaseObjects;
	class GameObjectManager;
	class DXGameResource;
	class SystemDXGameResourceIdGetter;
	class DirectInputWrapper;
	class ElapsedTimer;
	class Mouse;

	class DX12GameManager
	{
	public: /* このマネージャー自体の処理 */

		// 初期化
		static void initialize(const DX12GameManagerInitParam& initParam);

		// 実行
		static void run();

	public: /* ウィンドウの処理 */

		// ウィンドウサイズを取得する
		static const tktkMath::Vector2& getWindowSize();

	public: /* シーンの処理 */

		// シーンを作成して追加する
		template<class SceneType, class... Args>
		static void addScene(unsigned int id, Args&&... constructorArgs);

		// シーンを有効にする
		static void enableScene(unsigned int id);

		// シーンを無効にする
		static void disableScene(unsigned int id);

	public: /* ゲームオブジェクトの処理 */

		// 全てのGameObjectにメッセージを送信する
		static void sendMessageAll(unsigned int messageId, const MessageAttachment& value = {});

		// ゲームオブジェクトを作成し、そのポインタを返す
		static GameObjectPtr createGameObject();
		
		// 引数のタグを持ったゲームオブジェクトを取得する
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		static GameObjectPtr findGameObjectWithTag(int tag);
		
		// 引数のタグを持ったゲームオブジェクトを全て取得する
		static std::forward_list<GameObjectPtr> findGameObjectsWithTag(int tag);

	public: /* コンポーネントの処理 */

		// コンポーネントの型ごとの更新優先度を設定する
		// ※デフォルト（0.0f）で値が小さい程、早く実行される
		template <class ComponentType>
		static void addUpdatePriority(float priority);

		// 衝突判定の組み合わせを追加する
		static void addCollisionGroup(int firstGroup, int secondGroup);

		// テンプレート引数の型のコンポーネントを引数の値を使って作る
		template <class ComponentType, class... Args>
		static std::weak_ptr<ComponentType> createComponent(Args&&... args);

	public: /* 直接DX12の処理を呼ぶ */

		// コマンドリストを手動で実行する
		static void executeCommandList();

		// 背景色を設定する
		static void setBackGroundColor(const tktkMath::Color& backGroundColor);

		// 指定のレンダーターゲット用のディスクリプタヒープをコマンドリストに設定する
		static void setRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定の（レンダーターゲットと深度ステンシルビュー）用のディスクリプタヒープ２つをコマンドリストに設定する
		static void setRtvAndDsv(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定の深度ステンシルビュー用のディスクリプタヒープをコマンドリストに設定する（※レンダーターゲットは設定できない）
		static void setOnlyDsv(unsigned int dsvDescriptorHeapId);

		// バックバッファーを設定する
		static void setBackBufferView();

		// バックバッファーと深度ステンシルビューを設定する
		static void setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapId);

		// 指定のレンダーターゲット用のディスクリプタヒープが使用しているレンダーターゲットバッファの書き込み後処理を行う
		static void unSetRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// 指定の深度書き込み用のディスクリプタヒープが使用している深度バッファの書き込み後処理を行う
		static void unSetDsv(unsigned int dsvDescriptorHeapId);

		// 指定のビューポートをコマンドリストに設定する
		static void setViewport(unsigned int id);

		// 指定のシザー矩形をコマンドリストに設定する
		static void setScissorRect(unsigned int id);

		// 指定のパイプラインステートをコマンドリストに設定する
		static void setPipeLineState(unsigned int id);

		// 指定の頂点バッファをコマンドリストに設定する
		static void setVertexBuffer(unsigned int id);

		// 指定のインデックスバッファをコマンドリストに設定する
		static void setIndexBuffer(unsigned int id);

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

	public: /* 直接DX12のリソースを作る */

		// ルートシグネチャを作る
		static void createRootSignature(unsigned int id, const RootSignatureInitParam& initParam);

		// パイプラインステートを作る
		static void createPipeLineState(unsigned int graphicsPipeLineId, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// 頂点バッファを作る
		template <class VertexData>
		static void createVertexBuffer(unsigned int id, const std::vector<VertexData>& vertexDataArray);

		// インデックスバッファを作る
		static void createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices);

		// 定数バッファを作る
		template <class ConstantBufferDataType>
		static void createCBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData);

		// レンダーターゲットバッファを作る
		static void createRtBuffer(unsigned int id, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// 深度ステンシルバッファを作る
		static void createDsBuffer(unsigned int id, const DepthStencilBufferInitParam& initParam);

		// ディスクリプタヒープを作る
		static void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		// レンダーターゲットのディスクリプタヒープを作る
		static void createRtvDescriptorHeap(unsigned int id, const RtvDescriptorHeapInitParam& initParam);

		// 深度ステンシルディスクリプタヒープを作る
		static void createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam);

		// コマンドリストを使わずにテクスチャを作る
		static void cpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使ってテクスチャを作る（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		static void gpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使わずにテクスチャをロードする
		static void cpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);

		// コマンドリストを使ってテクスチャをロードする（※GPU命令なので「executeCommandList()」を呼ばないとロードが完了しません）
		static void gpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);
		
	public: /* 直接DX12のリソースを設定、取得する */

		// 指定の頂点バッファを更新する
		template <class VertexData>
		static void updateVertexBuffer(unsigned int id, const std::vector<VertexData>& vertexDataArray);

		// 指定のインデックスバッファを更新する
		static void updateIndexBuffer(unsigned int id, const std::vector<unsigned short>& indexDataArray);

		// 指定の定数バッファを更新する
		template <class ConstantBufferDataType>
		static void updateCBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData);

		// 指定のレンダーターゲットビューを指定の色でクリアする
		static void clearRtv(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		// 指定のテクスチャのサイズを取得する（ピクセル（テクセル））
		static const tktkMath::Vector3& getTextureBufferSizePx(unsigned int id);
		static const tktkMath::Vector2& getDsBufferSizePx(unsigned int id);
		static const tktkMath::Vector2& getRtBufferSizePx(unsigned int id);

	public: /* スプライト関係の処理 */

		// スプライトマテリアルを作る
		static void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		// 指定したスプライトを描画する
		static void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs);

	public: /* 2Dライン関係の処理 */

		// ２Ｄラインを作る
		static void createLine(unsigned int id, const Line2DMaterialDataInitParam& initParam);

		// 線を描画する
		static void drawLine(unsigned int id, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	public: /* メッシュ関係の処理 */

		// 通常メッシュを作る
		static void createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam);

		// 通常メッシュのコピーを作る
		static void copyBasicMesh(unsigned int id, unsigned int originalId);

		// 通常メッシュマテリアルを作る
		static void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		// 通常メッシュマテリアルのコピーを作る
		static void copyBasicMeshMaterial(unsigned int id, unsigned int originalId);

		// 通常メッシュが使用しているマテリアルを更新する
		static void setMaterialId(unsigned int id, unsigned int materialSlot, unsigned int materialId);

		// 指定の通常メッシュでシャドウマップを書き込む
		static void writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData);

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		static void setMaterialData(unsigned int id);

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		template <class CbufferType>
		static void addMaterialAppendParam(unsigned int id, unsigned int cbufferId, CbufferType&& value);

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		template <class CbufferType>
		static void updateMaterialAppendParam(unsigned int id, unsigned int cbufferId, const CbufferType& value);

		// 指定の通常メッシュを描画する
		static void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs);

		// pmdファイルをロードしてゲームの各種リソースクラスを作る
		static BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	public: /* スケルトン関連の処理 */

		// スケルトンを作成する
		static void createSkeleton(unsigned int id, const SkeletonInitParam& initParam);

		// 指定のスケルトンを使って骨情報を管理する定数バッファを更新する
		static void updateBoneMatrixCbuffer(unsigned int id);

		// 骨情報を管理する定数バッファに単位行列を設定する
		static void resetBoneMatrixCbuffer();

	public: /* モーション関係の処理 */

		// vmdファイルを読み込んで「MotionData」のインスタンスを作る
		static void loadMotion(unsigned int id, const std::string& motionFileName);

		// 指定のフレームのモーション情報を使用してスケルトンを更新する
		static void updateMotion(unsigned int skeletonId, unsigned int motionId, unsigned int curFrame);

	public: /* ポストエフェクト関係の処理 */

		// ポストエフェクトのマテリアルを作る
		static void createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam);

		// 指定のポストエフェクトを描画する
		static void drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs);

	public: /* カメラ関係の処理 */

		// カメラを作る
		static void createCamera(unsigned int id);

		// 指定のカメラのビュー行列を取得する
		static const tktkMath::Matrix4& getViewMatrix(unsigned int cameraId);

		// 指定のカメラのビュー行列を設定する
		static void setViewMatrix(unsigned int cameraId, const tktkMath::Matrix4& view);

		// 指定のカメラのプロジェクション行列を取得する
		static const tktkMath::Matrix4& getProjectionMatrix(unsigned int cameraId);

		// 指定のカメラのプロジェクション行列を設定する
		static void setProjectionMatrix(unsigned int cameraId, const tktkMath::Matrix4& projection);

	public: /* ライト関係の処理 */

		// ライトを作る
		static void createLight(
			unsigned int id,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ライト情報の定数バッファを更新する
		static void updateLightCBuffer(unsigned int id);

		// 指定のライトの環境光を設定する
		static void setLightAmbient(unsigned int id, const tktkMath::Color& ambient);

		// 指定のライトの拡散反射光を設定する
		static void setLightDiffuse(unsigned int id, const tktkMath::Color& diffuse);

		// 指定のライトの鏡面反射光を設定する
		static void setLightSpeqular(unsigned int id, const tktkMath::Color& speqular);

		// 指定のライトの座標を設定する
		static void setLightPosition(unsigned int id, const tktkMath::Vector3& position);

	public: /* サウンド関係の処理 */

		// 新しいサウンドを読み込む
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		static void loadSound(unsigned int id, const std::string& fileName);

		// 指定したサウンドを再生する
		static void playSound(unsigned int id, bool loopPlay);

		// 指定したサウンドを停止する
		static void stopSound(unsigned int id);

		// 指定したサウンドを一時停止する
		static void pauseSound(unsigned int id);

		// 大元の音量を変更する（0.0f～1.0f）
		static void setMasterVolume(float volume);

	public: /* マウス入力関係の処理 */

		// 指定のボタンが押されているか
		static bool isPush(MouseButtonType buttonType);

		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(MouseButtonType buttonType);

		// マウスカーソルの座標を取得する
		static tktkMath::Vector2 mousePos();

	public: /* キーボード入力関係の処理 */

		// 指定のキーが押されているかを判定
		static bool isPush(KeybordKeyType keyType);

		// 指定のキーが押され始めたかを判定
		static bool isTrigger(KeybordKeyType keyType);

	public: /* ゲームパッド入力関係の処理 */

		// 左スティックの傾きを取得（-1.0～1.0の間）
		static tktkMath::Vector2 getLstick();

		// 右スティックの傾きを取得（-1.0～1.0の間）
		static tktkMath::Vector2 getRstick();

		// 指定のボタンが押されているかを判定
		static bool isPush(GamePadBtnType btnType);

		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(GamePadBtnType btnType);

	public: /* タイム関係の処理 */

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

	public: /* デフォルトのリソースを使うためのIDを取得する */

		static unsigned int getSystemId(SystemViewportType type);
		static unsigned int getSystemId(SystemScissorRectType type);
		static unsigned int getSystemId(SystemVertexBufferType type);
		static unsigned int getSystemId(SystemIndexBufferType type);
		static unsigned int getSystemId(SystemCBufferType type);
		static unsigned int getSystemId(SystemTextureBufferType type);
		static unsigned int getSystemId(SystemDsBufferType type);
		static unsigned int getSystemId(SystemBasicDescriptorHeapType type);
		static unsigned int getSystemId(SystemRtvDescriptorHeapType type);
		static unsigned int getSystemId(SystemDsvDescriptorHeapType type);
		static unsigned int getSystemId(SystemRootSignatureType type);
		static unsigned int getSystemId(SystemPipeLineStateType type);
		static unsigned int getSystemId(SystemBasicMeshType type);
		static unsigned int getSystemId(SystemBasicMeshMaterialType type);
		static unsigned int getSystemId(SystemPostEffectMaterialType type);

	public: /* 裏実装 */

		static void createSceneImpl(unsigned int id, const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);
		static void createVertexBufferImpl(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);
		static void createCbufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);
		static void updateVertexBufferImpl(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);
		static void updateCbufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);
		static void addMaterialAppendParamImpl(unsigned int id, unsigned int cbufferId, unsigned int dataSize, void* dataTopPos);
		static void updateMaterialAppendParamImpl(unsigned int id, unsigned int cbufferId, unsigned int dataSize, const void* dataTopPos);

	private:
		static std::unique_ptr<Window>							m_window;
		static std::unique_ptr<DX3DBaseObjects>					m_dx3dBaseObjects;
		static std::unique_ptr<GameObjectManager>				m_gameObjectManager;
		static std::unique_ptr<ComponentManager>				m_componentManager;
		static std::unique_ptr<DXGameResource>					m_dxGameResource;
		static std::unique_ptr<SystemDXGameResourceIdGetter>	m_systemDXGameResourceIdGetter;
		static std::unique_ptr<DirectInputWrapper>				m_directInputWrapper;
		static std::unique_ptr<ElapsedTimer>					m_elapsedTimer;

		static std::unique_ptr<Mouse>							m_mouse;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// シーンを作成して追加する
	template<class SceneType, class ...Args>
	inline void DX12GameManager::addScene(unsigned int id, Args&&...constructorArgs)
	{
		createSceneImpl(id, std::make_shared<SceneType>(std::forward<Args>(constructorArgs)...), &SceneVTableInitializer<SceneType>::m_vtable);
	}

	// コンポーネントの型ごとの更新優先度を設定する
		// ※デフォルト（0.0f）で値が小さい程、早く実行される
	template<class ComponentType>
	inline void DX12GameManager::addUpdatePriority(float priority)
	{
		m_componentManager->addUpdatePriority<ComponentType>(priority);
	}

	// テンプレート引数の型のコンポーネントを引数の値を使って作る
	template<class ComponentType, class ...Args>
	inline std::weak_ptr<ComponentType> DX12GameManager::createComponent(Args&&...args)
	{
		return m_componentManager->createComponent<ComponentType>(std::forward<Args>(args)...);
	}

	// 頂点バッファを作る
	template<class VertexData>
	inline void DX12GameManager::createVertexBuffer(unsigned int id, const std::vector<VertexData>& vertexDataArray)
	{
		createVertexBufferImpl(id, sizeof(VertexData), vertexDataArray.size(), vertexDataArray.data());
	}

	// 定数バッファを作る
	template<class ConstantBufferDataType>
	inline void DX12GameManager::createCBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData)
	{
		createCbufferImpl(id, sizeof(ConstantBufferDataType), &rawConstantBufferData);
	}

	// 指定の頂点バッファを更新する
	template<class VertexData>
	inline void DX12GameManager::updateVertexBuffer(unsigned int id, const std::vector<VertexData>& vertexDataArray)
	{
		updateVertexBufferImpl(id, sizeof(VertexData), vertexDataArray.size(), vertexDataArray.data());
	}

	// 指定の定数バッファを更新する
	template<class ConstantBufferDataType>
	inline void DX12GameManager::updateCBuffer(unsigned int id, const ConstantBufferDataType& rawConstantBufferData)
	{
		updateCbufferImpl(id, sizeof(ConstantBufferDataType), &rawConstantBufferData);
	}

	// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
	template<class CbufferType>
	inline void DX12GameManager::addMaterialAppendParam(unsigned int id, unsigned int cbufferId, CbufferType&& value)
	{
		addMaterialAppendParamImpl(id, cbufferId, sizeof(CbufferType), new CbufferType(std::forward<CbufferType>(value)));
	}

	// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
	template<class CbufferType>
	inline void DX12GameManager::updateMaterialAppendParam(unsigned int id, unsigned int cbufferId, const CbufferType& value)
	{
		updateMaterialAppendParamImpl(id, cbufferId, sizeof(CbufferType), &value);
	}
}
#endif // !DX12_GAME_MANAGER_H_