#ifndef DX_GAME_RESOURCE_H_
#define DX_GAME_RESOURCE_H_

#include <memory>
#include "DXGameResourceNum.h"
#include "DXGameBaseShaderFilePaths.h"
#include "DXGameResourceInitParamIncluder.h"
#include "DXGameResourceFuncArgsIncluder.h"

namespace tktk
{
	// 前方宣言達
	class SceneManager;
	class Sound;
	class PostEffectMaterial;
	class SpriteMaterial;
	class Line2DMaterial;
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
		unsigned int createScene(const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);

		// シーンを有効にする
		void enableScene(unsigned int handle);

		// シーンを無効にする
		void disableScene(unsigned int handle);

		// 有効になっているシーンを更新する
		void updateScene();

	public: /* サウンド関係の処理 */

		// サウンドを更新する
		void updateSound();

		// 読み込んだサウンドをすべて削除する
		void clearSound();

		// 新しいサウンドを読み込み、そのリソースのハンドルを返す
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		unsigned int loadSound(const std::string& fileName);

		// 指定したサウンドを再生する
		void playSound(unsigned int handle, bool loopPlay);

		// 指定したサウンドを停止する
		void stopSound(unsigned int handle);

		// 指定したサウンドを一時停止する
		void pauseSound(unsigned int handle);

		// 大元の音量を変更する（0.0f～1.0f）
		void setMasterVolume(float volume);

	public: /* ポストエフェクト関係の処理 */

		// ポストエフェクトのマテリアルを作り、そのリソースのハンドルを返す
		unsigned int createPostEffectMaterial(const PostEffectMaterialInitParam& initParam);

		// 指定のポストエフェクトを描画する
		void drawPostEffect(unsigned int handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	public: /* スプライト関係の処理 */

		// スプライトマテリアルを作り、そのリソースのハンドルを返す
		unsigned int createSpriteMaterial(const SpriteMaterialInitParam& initParam);

		// 指定したスプライトを描画する
		void drawSprite(unsigned int handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する
		void updateSpriteTransformCbuffer(unsigned int handle, unsigned int copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate) const;

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する（切り抜き範囲指定版）
		void updateSpriteTransformCbufferUseClippingParam(unsigned int handle, unsigned int copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate, const SpriteClippingParam& clippingParam) const;
	
	public: /* 2Dライン関係の処理 */

		// ２Ｄラインを作り、そのリソースのハンドルを返す
		unsigned int createLine();

		// 線を描画する
		void drawLine(unsigned int handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	public: /* メッシュ関係の処理 */

		// 通常メッシュを作り、そのリソースのハンドルを返す
		unsigned int createBasicMesh(const BasicMeshInitParam& initParam);

		// 通常メッシュのコピーを作り、そのリソースのハンドルを返す
		unsigned int copyBasicMesh(unsigned int originalHandle);

		// 通常メッシュマテリアルを作り、そのリソースのハンドルを返す
		unsigned int createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam);

		// 通常メッシュマテリアルのコピーを作り、そのリソースのハンドルを返す
		unsigned int copyBasicMeshMaterial(unsigned int originalHandle);

		// 通常メッシュが使用しているマテリアルを更新する
		void setMaterialHandle(unsigned int meshHandle, unsigned int materialSlot, unsigned int materialHandle);

		// 指定の通常メッシュでシャドウマップを書き込む
		void writeBasicMeshShadowMap(unsigned int handle) const;

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMaterialData(unsigned int handle) const;

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		void addMaterialAppendParam(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos);

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		void updateMaterialAppendParam(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, const void* dataTopPos);

		// 指定の通常メッシュを描画する
		void drawBasicMesh(unsigned int handle, const MeshDrawFuncBaseArgs& baseArgs) const;

		// pmdファイルをロードしてゲームの各種リソースクラスを作る
		BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	public: /* スケルトン関連の処理 */

		// スケルトンを作り、そのリソースのハンドルを返す
		unsigned int createSkeleton(const SkeletonInitParam& initParam);

		// スケルトンのコピーを作り、そのリソースのハンドルを返す
		unsigned int copySkeleton(unsigned int originalHandle);

		// 指定のスケルトンの骨情報の定数バッファの値にコピーするためのバッファを作り、そのハンドルを返す
		// ※この関数で取得したハンドルは使用後に「DX12GameManager::eraseCopyBuffer(handle)」を必ず読んでバッファを削除してください
		unsigned int createSkeletonCopyBufferHandle(unsigned int handle) const;

		// 指定のスケルトンを使って引数が表すコピーバッファを使い骨情報を管理する定数バッファを更新する
		void updateBoneMatrixCbuffer(unsigned int handle, unsigned int copyBufferHandle) const;

		// 骨情報を管理する定数バッファに単位行列を設定する
		void resetBoneMatrixCbuffer() const;

	public: /* モーション関係の処理 */

		// vmdファイルを読み込んで「MotionData」のインスタンスを作り、そのリソースのハンドルを返す
		unsigned int loadMotion(const std::string& motionFileName);

		// 指定のモーションの終了キーの番号を取得する
		unsigned int getMotionEndFrameNo(unsigned int handle) const;

		// 2種類のモーション情報を線形補完してスケルトンを更新する
		// ※補完割合の値は「0.0fでpreFrame100%」、「1.0fでcurFrame100%」となる
		void updateMotion(
			unsigned int skeletonHandle,
			unsigned int curMotionHandle,
			unsigned int preMotionHandle,
			unsigned int curFrame,
			unsigned int preFrame,
			float amount
		);

	public: /* カメラ関係の処理 */

		// カメラを作り、そのリソースのハンドルを返す
		unsigned int createCamera();

		// 指定のカメラのビュー行列を取得する
		const tktkMath::Matrix4& getViewMatrix(unsigned int cameraHandle) const;

		// 指定のカメラのビュー行列を設定する
		void setViewMatrix(unsigned int cameraHandle, const tktkMath::Matrix4& view);

		// 指定のカメラのプロジェクション行列を取得する
		const tktkMath::Matrix4& getProjectionMatrix(unsigned int cameraHandle) const;

		// 指定のカメラのプロジェクション行列を設定する
		void setProjectionMatrix(unsigned int cameraHandle, const tktkMath::Matrix4& projection);

	public: /* ライト関係の処理 */

		// ライトを作り、そのリソースのハンドルを返す
		unsigned int createLight(
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ライト情報の定数バッファを更新する
		void updateLightCBuffer(unsigned int handle) const;

		// 指定のライトの環境光を設定する
		void setLightAmbient(unsigned int handle, const tktkMath::Color& ambient);

		// 指定のライトの拡散反射光を設定する
		void setLightDiffuse(unsigned int handle, const tktkMath::Color& diffuse);

		// 指定のライトの鏡面反射光を設定する
		void setLightSpeqular(unsigned int handle, const tktkMath::Color& speqular);

		// 指定のライトの座標を設定する
		void setLightPosition(unsigned int handle, const tktkMath::Vector3& position);

	private:

		std::unique_ptr<SceneManager>		m_sceneManager;
		std::unique_ptr<Sound>				m_sound;
		std::unique_ptr<PostEffectMaterial>	m_postEffectMaterial;
		std::unique_ptr<SpriteMaterial>		m_spriteMaterial;
		std::unique_ptr<Line2DMaterial>		m_line2DMaterial;
		std::unique_ptr<MeshResource>		m_meshResource;
		std::unique_ptr<Camera>				m_camera;
		std::unique_ptr<Light>				m_light;
	};
}
#endif // !DX_GAME_RESOURCE_H_
