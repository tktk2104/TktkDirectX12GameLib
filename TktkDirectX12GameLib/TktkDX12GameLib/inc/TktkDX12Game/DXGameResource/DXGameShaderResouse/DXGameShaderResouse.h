#ifndef DX_GAME_SHADER_RESOUSE_H_
#define DX_GAME_SHADER_RESOUSE_H_

/* std::unique_ptr */
#include <memory>

/* funcUseType */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Matrix3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "MeshResouse/Mesh/Loader/MeshLoadPmdReturnValue.h"
#include "MeshResouse/Mesh/Loader/MeshLoadPmxReturnValue.h"


namespace tktk
{
	class PostEffectMaterialManager;
	class Line2DMaterialManager;
	class SpriteMaterialManager;
	class BillboardMaterialManager;
	class MeshResource;

	struct DXGameShaderResouseInitParam;
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

	// シェーダーのレジスタにぶち込む値を管理するクラス
	class DXGameShaderResouse
	{
	public:

		DXGameShaderResouse(const DXGameShaderResouseInitParam& initParam);
		~DXGameShaderResouse();

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
			float curFrame,
			float preFrame,
			float amount
		);

	private:

		std::unique_ptr<PostEffectMaterialManager> m_postEffectMaterial;
		std::unique_ptr<Line2DMaterialManager>		m_line2DMaterial;
		std::unique_ptr<SpriteMaterialManager>		m_spriteMaterial;
		std::unique_ptr<BillboardMaterialManager>	m_billboardMaterial;
		std::unique_ptr<MeshResource>		m_meshResource;
	};
}
#endif // !DX_GAME_SHADER_RESOUSE_H_