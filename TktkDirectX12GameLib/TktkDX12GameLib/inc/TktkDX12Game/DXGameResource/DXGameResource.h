#ifndef DX_GAME_RESOURCE_H_
#define DX_GAME_RESOURCE_H_

/* std::unique_ptr */
#include <memory>

/* std::string */
#include <string>

/* std::type_index */
#include <typeindex>

/* std::forward_list */
#include <forward_list>

/* funcUseType */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "GameObjectResouse/GameObject/GameObjectPtr.h"
#include "GameObjectResouse/GameObject/GameObjectTagCarrier.h"
#include "GameObjectResouse/Component/ComponentBasePtr.h"
#include "GameObjectResouse/Component/ComponentCollisionFunc/CollisionGroupTypeCarrier.h"
#include "DXGameShaderResouse/MeshResouse/Mesh/Loader/MeshLoadPmdReturnValue.h"
#include "DXGameShaderResouse/MeshResouse/Mesh/Loader/MeshLoadPmxReturnValue.h"
#include "../EventMessage/MessageTypeCarrier.h"

namespace tktk
{
	/* SelfInitParam */
	struct DXGameResourceInitParam;

	/* class member */
	class Draw3DParameters;
	class DXGameShaderResouse;
	class GameObjectResouse;
	class OtherResouse;

	/* funcUseType */
	class MessageAttachment;
	struct ComponentVTableBundle;
	struct ComponentListVTable;
	struct PostEffectMaterialInitParam;
	struct PostEffectMaterialDrawFuncArgs;
	struct SpriteMaterialInitParam;
	struct SpriteMaterialDrawFuncArgs;
	struct SpriteCbufferUpdateFuncArgs;
	struct SpriteClippingParam;
	struct Line2DMaterialDrawFuncArgs;
	struct BillboardMaterialInitParam;
	struct BillboardDrawFuncBaseArgs;
	struct BillboardMaterialInstanceVertData;
	struct MeshResourceInitParam;
	struct SkeletonInitParam;
	struct MeshInitParam;
	struct MeshMaterialInitParam;
	struct MeshMaterialAppendParamInitParam;
	struct MeshMaterialAppendParamUpdateFuncArgs;
	struct MeshDrawFuncBaseArgs;
	struct MeshLoadPmdArgs;
	struct MeshLoadPmxArgs;
	struct MeshDrawFuncRunnerInitParam;
	struct CopySourceDataCarrier;
	struct SceneInitParam;

	// ゲームで使用するリソースを管理するクラス
	class DXGameResource
	{
	public:

		explicit DXGameResource(const DXGameResourceInitParam& initParam);
		~DXGameResource();

	public:

		// 更新処理
		void update();

		// 死んだインスタンスを削除する
		void removeDeadInstance();

		// 描画処理
		void draw();

	public: /* シーン関係の処理 */

		// シーンを作り、そのリソースのハンドルを返す
		size_t createScene(const SceneInitParam& initParam);

		// シーンの終了時に削除するゲームオブジェクトタグを設定する
		void setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag);

		// シーンを有効にする
		void enableScene(size_t handle);

		// シーンを無効にする
		void disableScene(size_t handle);

	public: /* サウンド関係の処理 */

		// 読み込んだサウンドをすべて削除する
		void clearSound();

		// 新しいサウンドを読み込み、そのリソースのハンドルを返す
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		size_t loadSound(const std::string& fileName);

		// 指定したサウンドを再生する
		void playSound(size_t handle, bool loopPlay);

		// 指定したサウンドを停止する
		void stopSound(size_t handle);

		// 指定したサウンドを一時停止する
		void pauseSound(size_t handle);

		// 大元の音量を変更する（0.0f～1.0f）
		void setMasterVolume(float volume);

	public: /* ゲームオブジェクト関係の処理 */

		// 全てのGameObjectにメッセージを送信する
		void runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment);

		// ゲームオブジェクトを作成し、そのポインタを返す
		GameObjectPtr createGameObject();

		// 引数のタグを持ったゲームオブジェクトを取得する
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		GameObjectPtr findGameObjectWithTag(GameObjectTagCarrier tag) const;

		// 引数のタグを持ったゲームオブジェクトを全て取得する
		std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagCarrier tag) const;

		// 引数のタグを持ったゲームオブジェクトを全て削除する
		void destroyGameObjectsWithTag(GameObjectTagCarrier tag);

	public: /* コンポーネント関係の処理 */

		// コンポーネントの型ごとの更新優先度を設定する
		// ※デフォルト（0.0f）で値が小さい程、早く実行される
		void addRunFuncPriority(std::type_index type, float priority);

		// 衝突判定の組み合わせを追加する
		void addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup);

		// 引数のコンポーネントを追加する
		ComponentBasePtr addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const GameObjectPtr& user, const std::shared_ptr<ComponentBase>& componentPtr);

	public: /* ポストエフェクト関係の処理 */

		// ポストエフェクトのマテリアルを作り、そのリソースのハンドルを返す
		size_t createPostEffectMaterial(const PostEffectMaterialInitParam& initParam);

		// 指定のポストエフェクトを描画する
		void drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	public: /* スプライト関係の処理 */

		// スプライトマテリアルを作り、そのリソースのハンドルを返す
		size_t createSpriteMaterial(const SpriteMaterialInitParam& initParam);

		// 指定したスプライトを描画する
		void drawSprite(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する
		void updateSpriteTransformCbuffer(size_t handle, size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs) const;

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する（切り抜き範囲指定版）
		void updateSpriteTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs, const SpriteClippingParam& clippingParam) const;

	public: /* 2Dライン関係の処理 */

		// ２Ｄラインを作り、そのリソースのハンドルを返す
		size_t createLine();

		// ２Ｄラインを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseLine(size_t handle);

		// 線を描画する
		void drawLine(size_t handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	public: /* ビルボード関係の処理 */

		// ビルボードマテリアルを作り、そのリソースのハンドルを返す
		size_t createBillboardMaterial(const BillboardMaterialInitParam& initParam);

		// 指定したビルボードが使用するテクスチャのサイズを取得する
		const tktkMath::Vector2& getBillboardTextureSize(size_t handle) const;

		// 指定したビルボードをインスタンス描画する時に使用する値を削除する
		void clearBillboardInstanceParam(size_t handle);

		// 指定したビルボードをインスタンス描画する時に使用する値を追加する
		void addBillboardInstanceVertParam(size_t handle, const BillboardMaterialInstanceVertData& instanceParam);

		// 指定したビルボードを描画する
		void drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const;

	public: /* メッシュ関係の処理 */

		// 初期から存在するメッシュを作る
		void createSystemMesh();


		// メッシュを作り、そのリソースのハンドルを返す
		size_t createMesh(const MeshInitParam& initParam);

		// メッシュのコピーを作り、そのリソースのハンドルを返す
		size_t copyMesh(size_t originalHandle);

		// メッシュマテリアルを作り、そのリソースのハンドルを返す
		size_t createMeshMaterial(const MeshMaterialInitParam& initParam);

		// メッシュマテリアルのコピーを作り、そのリソースのハンドルを返す
		size_t copyMeshMaterial(size_t originalHandle);

		// テクスチャを貼った立方体メッシュを作り、そのハンドルを返す
		size_t makeBoxMesh(size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// スカイボックスメッシュを作り、そのハンドルを返す
		size_t makeSkyBoxMesh(size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// pmdファイルをロードしてゲームの各種リソースクラスを作る
		MeshLoadPmdReturnValue loadPmd(const MeshLoadPmdArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// pmxファイルをロードしてゲームの各種リソースクラスを作る
		MeshLoadPmxReturnValue loadPmx(const MeshLoadPmxArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// メッシュが使用しているマテリアルを更新する
		void setMeshMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle);

		// 指定のメッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMeshMaterialData(size_t handle) const;

		// 指定のメッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		void addMeshMaterialAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam);

		// 指定のメッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		void updateMeshMaterialAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

		// 指定のメッシュをインスタンス描画する時に使用する値を削除する
		void clearMeshInstanceParam(size_t handle);

		// 指定のメッシュをインスタンス描画する時に使用する値を追加する
		void addMeshInstanceVertParam(size_t handle, const CopySourceDataCarrier& instanceParam);

		// スキニングメッシュをインスタンス描画する時に使用する骨行列を追加する
		void addMeshInstanceBoneMatrix(size_t meshHandle, size_t skeletonHandle);
		
		// 指定のメッシュでシャドウマップを書き込む
		void writeMeshShadowMap(size_t handle) const;

		// 指定のスキニングメッシュでシャドウマップを書き込む
		void writeMeshShadowMapUseBone(size_t handle) const;

		// 指定のメッシュをインスタンス描画する
		void drawMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

		// スキニングメッシュをインスタンス描画する
		void drawMeshUseBone(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

	public: /* スケルトン関連の処理 */

		// スケルトンを作り、そのリソースのハンドルを返す
		size_t createSkeleton(const SkeletonInitParam& initParam);

		// スケルトンのコピーを作り、そのリソースのハンドルを返す
		size_t copySkeleton(size_t originalHandle);

		// 指定のスケルトンの骨情報の定数バッファの値にアップロードするためのバッファを作り、そのハンドルを返す
		// ※この関数で取得したハンドルは使用後に「DX12GameManager::eraseUploadBuffer(handle)」を必ず読んでバッファを削除してください
		size_t createSkeletonUploadBufferHandle(size_t handle) const;

		// 指定のスケルトンを使って引数が表すコピーバッファを使い骨情報を管理する定数バッファを更新する
		void updateBoneMatrixCbuffer(size_t handle, size_t copyBufferHandle) const;

		// 骨情報を管理する定数バッファに単位行列を設定する
		void resetBoneMatrixCbuffer() const;

	public: /* モーション関係の処理 */

		// vmdファイルを読み込んで「MotionData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t loadMotion(const std::string& motionFileName);

		// 指定のモーションの終了キーの番号を取得する
		size_t getMotionEndFrameNo(size_t handle) const;

		// 2種類のモーション情報を線形補完してスケルトンを更新する
		// ※補完割合の値は「0.0fでpreFrame100%」、「1.0fでcurFrame100%」となる
		void updateMotion(
			size_t skeletonHandle,
			size_t curMotionHandle,
			size_t preMotionHandle,
			size_t curFrame,
			size_t preFrame,
			float amount
		);

	public: /* カメラ関係の処理 */

		// カメラを作り、そのリソースのハンドルを返す
		size_t createCamera();

		// 指定のカメラのビュー行列を取得する
		const tktkMath::Matrix4& getViewMatrix(size_t cameraHandle) const;

		// 指定のカメラのビュー行列を設定する
		void setViewMatrix(size_t cameraHandle, const tktkMath::Matrix4& view);

		// 指定のカメラのプロジェクション行列を取得する
		const tktkMath::Matrix4& getProjectionMatrix(size_t cameraHandle) const;

		// 指定のカメラのプロジェクション行列を設定する
		void setProjectionMatrix(size_t cameraHandle, const tktkMath::Matrix4& projection);

	public: /* ライト関係の処理 */

		// ライトを作り、そのリソースのハンドルを返す
		size_t createLight(
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ライト情報の定数バッファを更新する
		void updateLightCBuffer(size_t handle) const;

		// 指定のライトの環境光を設定する
		void setLightAmbient(size_t handle, const tktkMath::Color& ambient);

		// 指定のライトの拡散反射光を設定する
		void setLightDiffuse(size_t handle, const tktkMath::Color& diffuse);

		// 指定のライトの鏡面反射光を設定する
		void setLightSpeqular(size_t handle, const tktkMath::Color& speqular);

		// 指定のライトの座標を設定する
		void setLightPosition(size_t handle, const tktkMath::Vector3& position);

	private:

		std::unique_ptr<Draw3DParameters>		m_draw3DParameters;
		std::unique_ptr<DXGameShaderResouse>	m_dxGameShaderResouse;
		std::unique_ptr<GameObjectResouse>		m_gameObjectResouse;
		std::unique_ptr<OtherResouse>			m_otherResouse;
	};
}
#endif // !DX_GAME_RESOURCE_H_