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

		// シーンを作成して追加する
		void createScene(unsigned int id, const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);

		// シーンを有効にする
		void enableScene(unsigned int id);

		// シーンを無効にする
		void disableScene(unsigned int id);

		// 有効になっているシーンを更新する
		void updateScene();

	public: /* サウンド関係の処理 */

		// サウンドを更新する
		void updateSound();

		// 読み込んだサウンドをすべて削除する
		void clearSound();

		// 新しいサウンドを読み込む
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		void loadSound(unsigned int id, const std::string& fileName);

		// 指定したサウンドを再生する
		void playSound(unsigned int id, bool loopPlay);

		// 指定したサウンドを停止する
		void stopSound(unsigned int id);

		// 指定したサウンドを一時停止する
		void pauseSound(unsigned int id);

		// 大元の音量を変更する（0.0f～1.0f）
		void setMasterVolume(float volume);

	public: /* ポストエフェクト関係の処理 */

		// ポストエフェクトのマテリアルを作る
		void createPostEffectMaterial(unsigned int id, const PostEffectMaterialInitParam& initParam);

		// 指定のポストエフェクトを描画する
		void drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	public: /* スプライト関係の処理 */

		// スプライトマテリアルを作る
		void createSpriteMaterial(unsigned int id, const SpriteMaterialInitParam& initParam);

		// 指定したスプライトを描画する
		void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

	public: /* 2Dライン関係の処理 */

		// ２Ｄラインを作る
		void createLine(unsigned int id);

		// 線を描画する
		void drawLine(unsigned int id, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	public: /* メッシュ関係の処理 */

		// 通常メッシュを作る
		void createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam);

		// 通常メッシュのコピーを作る
		void copyBasicMesh(unsigned int id, unsigned int originalId);

		// 通常メッシュマテリアルを作る
		void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		// 通常メッシュマテリアルのコピーを作る
		void copyBasicMeshMaterial(unsigned int id, unsigned int originalId);

		// 通常メッシュが使用しているマテリアルを更新する
		void setMaterialId(unsigned int id, unsigned int materialSlot, unsigned int materialId);

		// 指定の通常メッシュでシャドウマップを書き込む
		void writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData) const;

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMaterialData(unsigned int id) const;

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		void addMaterialAppendParam(unsigned int id, unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos);

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		void updateMaterialAppendParam(unsigned int id, unsigned int cbufferHandle, unsigned int dataSize, const void* dataTopPos);

		// 指定の通常メッシュを描画する
		void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs) const;

		// pmdファイルをロードしてゲームの各種リソースクラスを作る
		BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	public: /* スケルトン関連の処理 */

		// スケルトンを作成する
		void createSkeleton(unsigned int id, const SkeletonInitParam& initParam);

		// 指定のスケルトンを使って骨情報を管理する定数バッファを更新する
		void updateBoneMatrixCbuffer(unsigned int id) const;

		// 骨情報を管理する定数バッファに単位行列を設定する
		void resetBoneMatrixCbuffer() const;

	public: /* モーション関係の処理 */

		// vmdファイルを読み込んで「MotionData」のインスタンスを作る
		void loadMotion(unsigned int id, const std::string& motionFileName);

		// 指定のモーションの終了キーの番号を取得する
		unsigned int getMotionEndFrameNo(unsigned int id) const;

		// 2種類のモーション情報を線形補完してスケルトンを更新する
		// ※補完割合の値は「0.0fでpreFrame100%」、「1.0fでcurFrame100%」となる
		void updateMotion(
			unsigned int skeletonId,
			unsigned int curMotionId,
			unsigned int preMotionId,
			unsigned int curFrame,
			unsigned int preFrame,
			float amount
		);

	public: /* カメラ関係の処理 */

		// カメラを作る
		void createCamera(unsigned int id);

		// 指定のカメラのビュー行列を取得する
		const tktkMath::Matrix4& getViewMatrix(unsigned int cameraId) const;

		// 指定のカメラのビュー行列を設定する
		void setViewMatrix(unsigned int cameraId, const tktkMath::Matrix4& view);

		// 指定のカメラのプロジェクション行列を取得する
		const tktkMath::Matrix4& getProjectionMatrix(unsigned int cameraId) const;

		// 指定のカメラのプロジェクション行列を設定する
		void setProjectionMatrix(unsigned int cameraId, const tktkMath::Matrix4& projection);

	public: /* ライト関係の処理 */

		// ライトを作る
		void createLight(
			unsigned int id,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ライト情報の定数バッファを更新する
		void updateLightCBuffer(unsigned int id) const;

		// 指定のライトの環境光を設定する
		void setLightAmbient(unsigned int id, const tktkMath::Color& ambient);

		// 指定のライトの拡散反射光を設定する
		void setLightDiffuse(unsigned int id, const tktkMath::Color& diffuse);

		// 指定のライトの鏡面反射光を設定する
		void setLightSpeqular(unsigned int id, const tktkMath::Color& speqular);

		// 指定のライトの座標を設定する
		void setLightPosition(unsigned int id, const tktkMath::Vector3& position);

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
