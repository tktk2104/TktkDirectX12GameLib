#ifndef DX_GAME_RESOURCE_H_
#define DX_GAME_RESOURCE_H_

#include <memory>
#include "DXGameResourceNum.h"
#include "DXGameBaseShaderFilePaths.h"
#include "DXGameResourceInitParamIncluder.h"
#include "DXGameResourceFuncArgsIncluder.h"
#include "../GameObject/GameObjectTagCarrier.h"

namespace tktk
{
	// 前方宣言達
	class SceneManager;
	class Sound;
	class PostEffectMaterial;
	class SpriteMaterial;
	class Line2DMaterial;
	class BillboardMaterial;
	class MeshResource;
	class Camera;
	class Light;

	// ゲームで使用するリソースを管理するクラス
	class DXGameResource
	{
	public:

		DXGameResource(const DXGameResourceNum& resourceNum, const DXGameBaseShaderFilePaths& filePaths);
		~DXGameResource();

	public: /* シーン関係の処理 */

		// シーンを作り、そのリソースのハンドルを返す
		size_t createScene(const SceneDataInitParam& initParam);

		// シーンの終了時に削除するゲームオブジェクトタグを設定する
		void setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag);

		// シーンを有効にする
		void enableScene(size_t handle);

		// シーンを無効にする
		void disableScene(size_t handle);

		// 有効になっているシーンを更新する
		void updateScene();

	public: /* サウンド関係の処理 */

		// サウンドを更新する
		void updateSound();

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
		void updateSpriteTransformCbuffer(size_t handle, size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate) const;

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する（切り抜き範囲指定版）
		void updateSpriteTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate, const SpriteClippingParam& clippingParam) const;
	
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

		// 指定したビルボードを描画する
		void drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const;

		// 引数が表すコピーバッファを使って定数バッファを更新する
		void updateBillboardCbuffer(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs) const;

		// 引数が表すコピーバッファを使って定数バッファを更新する（切り抜き範囲指定版）
		void updateBillboardCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const;

	public: /* メッシュ関係の処理 */

		// 通常メッシュを作り、そのリソースのハンドルを返す
		size_t createBasicMesh(const BasicMeshInitParam& initParam);

		// 通常メッシュのコピーを作り、そのリソースのハンドルを返す
		size_t copyBasicMesh(size_t originalHandle);

		// 通常メッシュマテリアルを作り、そのリソースのハンドルを返す
		size_t createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam);

		// 通常メッシュマテリアルのコピーを作り、そのリソースのハンドルを返す
		size_t copyBasicMeshMaterial(size_t originalHandle);

		// 通常メッシュが使用しているマテリアルを更新する
		void setMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle);

		// 指定の通常メッシュでシャドウマップを書き込む
		void writeBasicMeshShadowMap(size_t handle) const;

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMaterialData(size_t handle) const;

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		void addMaterialAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, void* dataTopPos);

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		void updateMaterialAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, const void* dataTopPos);

		// 指定の通常メッシュを描画する
		void drawBasicMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

		// pmdファイルをロードしてゲームの各種リソースクラスを作る
		BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

		// pmxファイルをロードしてゲームの各種リソースクラスを作る
		BasicMeshLoadPmxReturnValue loadPmx(const BasicMeshLoadPmxArgs& args);

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

		std::unique_ptr<SceneManager>		m_sceneManager;
		std::unique_ptr<Sound>				m_sound;
		std::unique_ptr<PostEffectMaterial>	m_postEffectMaterial;
		std::unique_ptr<SpriteMaterial>		m_spriteMaterial;
		std::unique_ptr<Line2DMaterial>		m_line2DMaterial;
		std::unique_ptr<BillboardMaterial>	m_billboardMaterial;
		std::unique_ptr<MeshResource>		m_meshResource;
		std::unique_ptr<Camera>				m_camera;
		std::unique_ptr<Light>				m_light;
	};
}
#endif // !DX_GAME_RESOURCE_H_
